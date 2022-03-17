// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCameraController.h"
#include "CrossRoadController.h"
#include "GameManager.generated.h"

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

public:	
	void MoveToNextCrossRoad();
	void MoveToPreviousCrossRoad();
	void ToggleToNextDirection();
	void ToggleToPreviousDirection();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AGameCameraController* CameraController;

	UPROPERTY(EditAnywhere)
	ACrossRoadController* CrossRoadController;

};
