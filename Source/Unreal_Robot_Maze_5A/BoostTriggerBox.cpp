// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostTriggerBox.h"

ABoostTriggerBox::ABoostTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &ABoostTriggerBox::OnOverlapBegin);
}


void ABoostTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && OtherActor != this && Cast<AUnreal_Robot_Maze_5APawn>(OtherActor) != NULL)
        Cast<AUnreal_Robot_Maze_5APawn>(OtherActor)->MoveSpeed *= 3;
}