// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameManager.h"
#include "GoalTriggerBox.generated.h"
/**
 *
 */
UCLASS()
class UNREAL_ROBOT_MAZE_5A_API AGoalTriggerBox : public ATriggerBox
{
    GENERATED_BODY()
protected:
    virtual void BeginPlay() override;

    UPROPERTY(Category = Mesh, VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent* GoalMesh;
public:
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
    AGameManager* GameManager;
    
    UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

    AGoalTriggerBox();

};
