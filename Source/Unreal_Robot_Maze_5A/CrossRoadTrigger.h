// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Unreal_Robot_Maze_5A/Unreal_Robot_Maze_5APawn.h>
#include "Engine/TriggerBox.h"
#include "Robot_Maze_Game_Instance.h"

#include "CrossRoadTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_ROBOT_MAZE_5A_API ACrossRoadTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	ACrossRoadTrigger();
	
	void GetValue();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	DirectionEnum direction;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
