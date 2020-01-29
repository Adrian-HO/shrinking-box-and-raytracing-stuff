// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/UnrealMathUtility.h"

AFPSProjectile::AFPSProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);	// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}


void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Get the Hit Actors Scale
		UStaticMeshComponent* cube = Cast<UStaticMeshComponent>(OtherComp);
		FVector size;
		if (cube)
		{
			 size = cube->GetRelativeScale3D();
		}
		//Scale it by 0.8 or any factor you want ??
		size.X -= 0.8;
		size.Y -= 0.8;
		size.Z -= 0.8;
		if (size.X < 0.5f)
		{
			OtherActor->Destroy();
		}
		else
		{
			float a = FMath::RandRange(0.0f, 200.0f);
			cube->SetRelativeScale3D(size);
			UMaterialInstanceDynamic* MAtinst;
			UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(MAtinst);
			if (MAtinst)
			{
				MatInst->SetVectorParameterValue(FColor::Green, FMath::RandRange(0, 200));
				
			}
				//Set the MatInst to a RANDOM color using the function:
				//void SetVectorParameterValue(FName ParameterName, FLinearColor Value)
				//The parameter name is Color
				//Look up documentation on FLinearColor
			//ENDIF
			FLinearColor
		}

		//Now we will create a dynamic material instance that is the mesh surface. we will name it as MAtinst
		//CREATE a Dynamic Material Instance for the specified element index. +++++++++++++++++++++++++++++
		//The function to use is:
		//UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(int32 ElementIndex)
		//Look it up in the documentation and how and where to use it	
		//IF the MatInst is successful
			//Set the MatInst to a RANDOM color using the function:
			//void SetVectorParameterValue(FName ParameterName, FLinearColor Value)
			//The parameter name is Color
			//Look up documentation on FLinearColor
		//ENDIF

		Destroy();
	}
}