// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCameraController.h"
#include "CrossRoadController.h"
#include <Unreal_Robot_Maze_5A/Unreal_Robot_Maze_5APawn.h>
#include "GameManager.generated.h"

UENUM(BlueprintType)
enum class GamePhaseEnum : uint8
{
	CrossroadPhase UMETA(DisplayName = "Crossroad Phase"),
	ExplorationPhase UMETA(DisplayName = "Exploration Phase"),
	EndPhase UMETA(DisplayName = "End Phase")
};

UCLASS()
class UNREAL_ROBOT_MAZE_5A_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int index = 0;

	GamePhaseEnum _currentPhase;
	float _currentRobotBatteryDuration;
	float _gameTimer;
public:
	void MoveToNextCrossRoad();
	void MoveToPreviousCrossRoad();
	void ToggleToNextDirection();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AGameCameraController* CameraController;

	UPROPERTY(EditAnywhere)
	ACrossRoadController* CrossRoadController;

	UPROPERTY(EditAnywhere)
	AUnreal_Robot_Maze_5APawn* Robot;

	UPROPERTY(EditAnywhere)
	float RobotBatteryDuration;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Current Phase", CompactNodeTitle = "Get Phase", Keywords = "get current phase"), Category = Game)
	virtual GamePhaseEnum GetCurrentPhase() const;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Game Timer", CompactNodeTitle = "Get Timer", Keywords = "get timer"), Category = Game)
	virtual float GetGameTimer() const;
	virtual void SetGameTimer(float seconds);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Current Robot Battery Duration", CompactNodeTitle = "Get Battery", Keywords = "get battery robot duration"), Category = Game)
	virtual float GetCurrentRobotBatteryDuration() const;
	virtual void SetCurrentRobotBatteryDuration(float duration);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Max Battery Duration", CompactNodeTitle = "Get Max Battery", Keywords = "get max battery robot duration"), Category = Game)
	virtual float GetBatteryDuration() const;
protected:
	virtual void BeginExplorationPhase();
	virtual void BeginEndPhase(bool isWin);
};
