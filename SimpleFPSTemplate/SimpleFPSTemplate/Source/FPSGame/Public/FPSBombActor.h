// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBombActor.generated.h"

UCLASS()
class FPSGAME_API AFPSBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBombActor();

	UPROPERTY(EditDefaultsOnly, Category = "explode delay")
		float ExplodeDelay;
		 
	UPROPERTY(EditDefaultsOnly, Category = "explosion template")
		class UParticleSystem* ExplosionTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "bomb mesh")
		class UStaticMeshComponent* BombMesh;
		
	UPROPERTY(VisibleAnywhere, Category = "bomb box")
		class UBoxComponent* BombBox;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class URadialForceComponent* RadialForceComp;

	 void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Hold(USkeletalMeshComponent* HoldingComponent);

	void Throw(FVector direction);

	void Explode();

	void DestroyBomb();

protected:
	FTimerHandle FireTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
