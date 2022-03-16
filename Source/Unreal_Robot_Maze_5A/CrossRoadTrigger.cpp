// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossRoadTrigger.h"
#include "DrawDebugHelpers.h"
#include <Unreal_Robot_Maze_5A/Unreal_Robot_Maze_5APawn.h>

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

ACrossRoadTrigger::ACrossRoadTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACrossRoadTrigger::OnOverlapBegin);
}

void ACrossRoadTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // TD : checker que le joker est activé
    
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        AUnreal_Robot_Maze_5APawn* actor = Cast<AUnreal_Robot_Maze_5APawn>(OtherActor);

        if (actor != NULL)
        {
            // TD : faire l'enum pour obtenir une direction

            actor->SetBiasedDirection(FVector::ForwardVector);

            // TD : désactiver le joker
        }
    }
}