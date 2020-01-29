// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBombActor.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombBox = CreateDefaultSubobject<UBoxComponent>("overlap");
	BombBox->SetCollisionProfileName("BlockAll");
	BombBox->OnComponentHit.AddDynamic(this, &AFPSBombActor::OnHit);
	BombBox->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	BombBox->CanCharacterStepUpOn = ECB_No;
	RootComponent = BombBox;

	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>("stat Mesh");
	BombMesh->SetupAttachment(RootComponent);
	BombMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("radial force");
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 250;
	RadialForceComp->bImpulseVelChange = true;
	// This will prevent the RadialForceComp from ticking and we will only use FireImpulse() instead
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->bIgnoreOwningActor = true;

	BombBox->SetSimulatePhysics(true);
	BombBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BombBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	ExplodeDelay = 2.0f;

}

// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSBombActor::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AFPSBombActor::Explode, ExplodeDelay, true);
}

void AFPSBombActor::Hold(USkeletalMeshComponent * HoldingComponent)
{
	if (HoldingComponent) {

		BombBox->SetSimulatePhysics(false);
		BombBox->AttachTo(HoldingComponent, "Muzzle", EAttachLocation::SnapToTarget);
		//ATTACH the BombBox to the HoldingComponent at the HoldingComponents Muzzle Socket
	}

	//ENDIF
}

void AFPSBombActor::Throw(FVector direction)
{
	BombBox->SetSimulatePhysics(true);
	BombBox->SetNotifyRigidBodyCollision(true);
	BombBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BombBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	BombBox->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	//CALL AddForce(...) to BombBox to throw it, using the direction passed in
	BombBox->AddForce(direction);
}

// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSBombActor::Explode()
{
	//SPAWN the ExplosionTemplate Particle System using UGameplayStatics::SpawnEmitterAtLocation(....)
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());
	//BLAST away nearby physics actors by Calling FireImpulse() on the Radial Force Component
	RadialForceComp->FireImpulse();
	//CREATE a Timer to Destroy this Actor After 1 second
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &AFPSBombActor::DestroyBomb, 1.f, true);
}

void AFPSBombActor::DestroyBomb()
{
	//Destroy this Actor
	Destroy();
}