// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unreal_Robot_Maze_5APawn.generated.h"


UENUM(BlueprintType)
enum class DirectionEnum : uint8
{
	None UMETA(DisplayName = "None"),
	Left UMETA(DisplayName = "Left"),
	Up UMETA(DisplayName = "Up"),
	Right UMETA(DisplayName = "Right"),
	Down UMETA(DisplayName = "Down")
};

UCLASS(Blueprintable)
class AUnreal_Robot_Maze_5APawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;


public:
	AUnreal_Robot_Maze_5APawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;
	
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float BatteryLife = 100;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	// End Actor Interface

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);
	
	/*Shoots a raycast to see collisions*/
	bool Ray(FVector Direction, float distance, FColor color);
	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	void SetBiasedDirection(FVector direction);
	void SetIsBiasedDirection(bool isBiased);
	bool GetIsBiasedDirection();


private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	bool hasWallForwardOld;
	bool hasWallLeftOld;
	bool isBiasedDirection;
	FVector currentDirection;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
};

