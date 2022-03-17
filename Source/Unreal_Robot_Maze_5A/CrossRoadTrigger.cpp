// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossRoadTrigger.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

ACrossRoadTrigger::ACrossRoadTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACrossRoadTrigger::OnOverlapBegin);
}


void ACrossRoadTrigger::GetValue()
{
    URobot_Maze_Game_Instance* GI = Cast<URobot_Maze_Game_Instance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (GI)
    {
        print("get value from game instance");
        //printFString("GI value : %d", GI->someValue);
    }
    else print("no instance");

}

void ACrossRoadTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        AUnreal_Robot_Maze_5APawn* actor = Cast<AUnreal_Robot_Maze_5APawn>(OtherActor);
        GetValue();

        if (actor != NULL)
        {
            switch (direction)
            {
            case DirectionEnum::None:
                if (actor->GetIsBiasedDirection())
                    actor->SetIsBiasedDirection(!actor->GetIsBiasedDirection());
                break;
            case DirectionEnum::Up:
                actor->SetBiasedDirection(FVector::ForwardVector);
                direction = DirectionEnum::None;
                break;
            case DirectionEnum::Down:
                actor->SetBiasedDirection(-FVector::ForwardVector);
                direction = DirectionEnum::None;

                break;
            case DirectionEnum::Right:
                actor->SetBiasedDirection(FVector::RightVector);
                direction = DirectionEnum::None;
                break;
            case DirectionEnum::Left:
                actor->SetBiasedDirection(-FVector::RightVector);
                direction = DirectionEnum::None;
                break;
            default:
                break;
            }

        }
    }
}