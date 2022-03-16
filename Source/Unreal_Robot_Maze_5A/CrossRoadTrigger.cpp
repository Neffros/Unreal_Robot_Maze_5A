// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossRoadTrigger.h"
#include "DrawDebugHelpers.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

ACrossRoadTrigger::ACrossRoadTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACrossRoadTrigger::OnOverlapBegin);
}

void ACrossRoadTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // TD : checker que le joker est activ�
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        AUnreal_Robot_Maze_5APawn* actor = Cast<AUnreal_Robot_Maze_5APawn>(OtherActor);

        if (actor != NULL)
        {
            // TD : faire l'enum pour obtenir une direction
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

            // TD : d�sactiver le joker
        }
    }
}