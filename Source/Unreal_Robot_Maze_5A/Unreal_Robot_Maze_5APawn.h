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
ENUM_RANGE_BY_VALUES(DirectionEnum, DirectionEnum::None, DirectionEnum::Left, DirectionEnum::Up, DirectionEnum::Right, DirectionEnum::Down)

UCLASS(Blueprintable)
class AUnreal_Robot_Maze_5APawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;


public:
	AUnreal_Robot_Maze_5APawn();

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	// Begin Actor Interface
	//virtual void Tick(float DeltaSeconds) override;
	// End Actor Interface

	void RobotTick(float DeltaSeconds);
	/*Shoots a raycast to see collisions*/
	bool Ray(FVector Direction, float distance, FColor color);

	void SetBiasedDirection(FVector direction);
	void UnbiasDirection();

private:
	bool hasWallForwardOld;
	bool hasWallLeftOld;
	bool isBiasedDirection;
	FVector currentDirection;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
};

