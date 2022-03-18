// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostTriggerBox.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT(text), fstring))


ABoostTriggerBox::ABoostTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &ABoostTriggerBox::OnOverlapBegin);
}


void ABoostTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && OtherActor != this && Cast<AUnreal_Robot_Maze_5APawn>(OtherActor) != NULL)
    {
        print("overlap boost");
        Cast<AUnreal_Robot_Maze_5APawn>(OtherActor)->MoveSpeed *= 4;
    }
}