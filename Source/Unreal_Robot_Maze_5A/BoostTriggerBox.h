#pragma once


#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameManager.h"
#include "BoostTriggerBox.generated.h"
/**
 *
 */
UCLASS()
class UNREAL_ROBOT_MAZE_5A_API ABoostTriggerBox : public ATriggerBox
{
    GENERATED_BODY()

public:
    UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
        AGameManager* GameManager;

    UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

    ABoostTriggerBox();

};
