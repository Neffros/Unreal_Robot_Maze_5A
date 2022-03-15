// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
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

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
