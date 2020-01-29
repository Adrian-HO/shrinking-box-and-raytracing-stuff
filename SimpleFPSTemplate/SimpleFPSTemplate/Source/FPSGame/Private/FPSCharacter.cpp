// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CollisionSphereComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSBombActor.h"


AFPSCharacter::AFPSCharacter()
{
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1PComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh1PComponent->SetupAttachment(CameraComponent);
	Mesh1PComponent->CastShadow = false;
	Mesh1PComponent->SetRelativeRotation (FRotator(2.0f, -15.0f, 5.0f));
	Mesh1PComponent->SetRelativeLocation(FVector(0, 0, -160.0f));

	// Create a gun mesh component
	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(Mesh1PComponent, "GripPoint");
}


void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	PlayerInputComponent->BindAction("Hold", IE_Pressed, this, &AFPSCharacter::PickupBomb);
	PlayerInputComponent->BindAction("Hold", IE_Released, this, &AFPSCharacter::ThrowBomb);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}


void AFPSCharacter::Fire()
{
	// try and fire a projectile
	if (ProjectileClass)
	{
		FVector MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		FRotator MuzzleRotation = GunMeshComponent->GetSocketRotation("Muzzle");

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1PComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}


void AFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::PickupBomb()
{
	//RAY CAST to check if a Actor is hit by a raycast
	AActor* HitActor = GetPickableActor_LineTraceSingleByObjectType(TraceCollisionParams.ObjectType);

	if (HitActor)
	{
		AFPSBombActor* tempt = Cast<AFPSBombActor>(HitActor);
		if (tempt)
		{
			HoldingBomb = true;
			HeldBomb = tempt;
			HeldBomb->Hold(GunMeshComponent);
		}
	}
}

void AFPSCharacter::ThrowBomb()
{
	if (HeldBomb)
	{
		HeldBomb->Throw(GetActorForwardVector() );
		HeldBomb = nullptr;
	}
	//IF we have a HeldBomb
		//Throw the Held Bomb passing in the Direction
	//ENDIF
}

void AFPSCharacter::SetupRay(FVector & StartTrace, FVector & Direction, FVector & EndTrace)
{
	FVector CamLoc;
	FRotator CamRot;

	Controller->GetPlayerViewPoint(CamLoc, CamRot); // Get the camera position and rotation
	CamLoc = GetActorLocation();

	StartTrace = CamLoc; // trace start is the camera location
	Direction = CamRot.Vector();
	EndTrace = StartTrace + (Direction * 300); // and trace end is the camera location + an offset in the direction you are looking, the 300 is the distance at which it checks
}

void AFPSCharacter::EnableCollisionSphere(bool enable)
{
	if (!enable)
	{
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CollisionSphere->SetHiddenInGame(true);
	}
	else
	{
		CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CollisionSphere->SetHiddenInGame(false);
	}
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AFPSCharacter::GetPickableActor_LineTraceTestByChannel(ECollisionChannel CollisionChannel)
{
	bool hit = false;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;
		//Call SetupRay() to set the Start end End Trace
		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		//Ignore this Actor
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		//FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		hit = World->LineTraceTestByChannel(StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return hit;
	}

	return hit;
}

bool AFPSCharacter::GetPickableActor_LineTraceTestByObjectType(EObjectTypeQuery ObjectType)
{
	bool hit = false;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		//Convert the EObjectTypeQuery to a byte
		TEnumAsByte<EObjectTypeQuery> ObjectToTrace = ObjectType;
		//Create a TArray of type TEnumAsByte<EObjectTypeQuery>
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectsToTraceAsByte;
		//Add the ObjectToTrace into the TArray, we can trace (look) for more than 1 ObjectType
		ObjectsToTraceAsByte.Add(ObjectToTrace);

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		hit = World->LineTraceTestByObjectType(StartTrace, EndTrace, FCollisionObjectQueryParams(ObjectsToTraceAsByte), TraceParams); // simple trace function
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return hit;
	}

	return hit;
}

bool AFPSCharacter::GetPickableActor_LineTraceTestByProfile(FName ProfileName)
{
	bool hit = false;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		hit = World->LineTraceTestByProfile(StartTrace, EndTrace, ProfileName, TraceParams); // simple trace function "Pawn"
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return hit;
	}

	return hit;
}

AActor* AFPSCharacter::GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel)
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller because we don't want bots to grab the use object and we need a controller for the GetPlayerViewpoint function
	{

		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function  ECC_PhysicsBody
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 1.f);
		return Hit.GetActor();
	}

	return nullptr;
}
AActor* AFPSCharacter::GetPickableActor_LineTraceSingleByObjectType(EObjectTypeQuery ObjectType)
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;


		SetupRay(StartTrace, Direction, EndTrace);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld(); //FCollisionObjectQueryParams(EObjectTypeQuery::ObjectTypeQuery1)

		//need to convert the enum to a Byte
		//World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, ObjectType, TraceParams); // simple trace function  ObjectTypeQuery1
		TEnumAsByte<EObjectTypeQuery> ObjectToTrace = ObjectType;
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectsToTraceAsByte;
		ObjectsToTraceAsByte.Add(ObjectToTrace);

		World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, FCollisionObjectQueryParams(ObjectsToTraceAsByte), TraceParams); // simple trace function  ObjectTypeQuery1
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, -1.0f, 0, 1.f);
		return Hit.GetActor();
	}

	return nullptr;
}

AActor* AFPSCharacter::GetPickableActor_LineTraceSingleByTraceType(ETraceTypeQuery TraceType)
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;


		SetupRay(StartTrace, Direction, EndTrace);

		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld(); //FCollisionObjectQueryParams(EObjectTypeQuery::ObjectTypeQuery1)


		//need to convert the enum to a Byte
		//World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, ObjectType, TraceParams); // simple trace function  ObjectTypeQuery1
		TEnumAsByte<ETraceTypeQuery> ObjectToTrace = TraceType;
		TArray<TEnumAsByte<ETraceTypeQuery> > ObjectsToTraceAsByte;
		ObjectsToTraceAsByte.Add(ObjectToTrace);


		World->LineTraceSingleByObjectType(Hit, StartTrace, EndTrace, FCollisionObjectQueryParams(TraceType), TraceParams); // simple trace function  ObjectTypeQuery1
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, -1.0f, 0, 1.f);
		return Hit.GetActor();
	}

	return nullptr;
}

AActor* AFPSCharacter::GetPickableActor_LineTraceSingleByProfile(FName ProfileName)
{
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		World->LineTraceSingleByProfile(Hit, StartTrace, EndTrace, ProfileName, TraceParams); // simple trace function "Pawn"
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, 1, 0, 1.f);
		return Hit.GetActor();
	}

	return nullptr;
}

TArray<FHitResult> AFPSCharacter::GetPickableActor_LineTraceMultiByChannel(ECollisionChannel CollisionChannel)
{
	TArray<FHitResult> OutHits;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		UWorld* World = GetWorld();
		World->LineTraceMultiByChannel(OutHits, StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function ECC_PhysicsBody
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, 1, 0, 1.f);

	}

	return OutHits;
}

TArray<FHitResult> AFPSCharacter::GetPickableActor_LineTraceMultiByObjectType(EObjectTypeQuery ObjectType)
{
	TArray<FHitResult> OutHits;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		TEnumAsByte<EObjectTypeQuery> ObjectToTrace = ObjectType;
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectsToTraceAsByte;
		ObjectsToTraceAsByte.Add(ObjectToTrace);

		UWorld* World = GetWorld();
		World->LineTraceMultiByObjectType(OutHits, StartTrace, EndTrace, FCollisionObjectQueryParams(ObjectsToTraceAsByte), TraceParams); // simple trace function ObjectTypeQuery1
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, 1, 0, 1.f);

	}

	return OutHits;
}

TArray<FHitResult> AFPSCharacter::GetPickableActor_LineTraceMultiByProfile(FName ProfileName)
{
	TArray<FHitResult> OutHits;
	if (Controller && Controller->IsLocalPlayerController()) // we check the controller because we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;

		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		UWorld* World = GetWorld();
		World->LineTraceMultiByProfile(OutHits, StartTrace, EndTrace, ProfileName, TraceParams); // simple trace function "Pawn"
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, 1, 0, 1.f);
		// return OutHits;
	}

	return OutHits;
}

