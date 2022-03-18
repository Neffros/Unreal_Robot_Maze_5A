// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameManager.h"
#include "GoalTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_ROBOT_MAZE_5A_API AGoalTrigger : public ATriggerBox
{
	GENERATED_BODY()

private:
	AGameManager* GameManager;

protected:
	virtual void BeginPlay() override;


public:
	AGoalTrigger();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* goalMesh;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
