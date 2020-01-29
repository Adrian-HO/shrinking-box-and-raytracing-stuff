// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CollisionSphereComponent.h"
#include "FPSCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class AFPSProjectile;
class USoundBase;
class UAnimSequence;


UENUM(BlueprintType)
enum class ETestTraceType : uint8
{
	TTT_CollisionChannel 	UMETA(DisplayName = "Collision Channel"),
	TTT_ObjectType 	UMETA(DisplayName = "Object Type"),
	TTT_TraceType	UMETA(DisplayName = "Trace Type"),
	TTT_ProfileName UMETA(DisplayName = "Profile Name")
};

UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/** Pawn mesh: 1st person view  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* Mesh1PComponent;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	//new
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CollisionTests)
		ETestTraceType ETraceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CollisionTests)
		FTraceParams TraceCollisionParams;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CollisionSphere)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CollisionTests)
		FCollisonParams SphereCollisionParams;

public:
	AFPSCharacter();

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	UAnimSequence* FireAnimation;

	class AFPSBombActor* HeldBomb;

	bool HoldingBomb = false;

protected:
	
	/** Fires a projectile. */
	void Fire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	void PickupBomb();
	void ThrowBomb();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	//new
	bool GetPickableActor_LineTraceTestByChannel(ECollisionChannel CollisionChannel);
	bool GetPickableActor_LineTraceTestByObjectType(EObjectTypeQuery ObjectType);
	bool GetPickableActor_LineTraceTestByProfile(FName ProfileName);

	AActor* GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel);
	AActor* GetPickableActor_LineTraceSingleByObjectType(EObjectTypeQuery ObjectType);
	AActor* GetPickableActor_LineTraceSingleByTraceType(ETraceTypeQuery TraceType);
	AActor* GetPickableActor_LineTraceSingleByProfile(FName ProfileName);

	TArray<FHitResult> GetPickableActor_LineTraceMultiByChannel(ECollisionChannel CollisionChannel);
	TArray<FHitResult> GetPickableActor_LineTraceMultiByObjectType(EObjectTypeQuery ObjectType);
	TArray<FHitResult> GetPickableActor_LineTraceMultiByProfile(FName ProfileName);


	class UCollisionSphereComponent* CollisionSphere;

	void SetupRay(FVector &StartTrace, FVector &Direction, FVector &EndTrace);

	UFUNCTION()
		void EnableCollisionSphere(bool enable);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	virtual void Tick(float DeltaTime) override;

};

