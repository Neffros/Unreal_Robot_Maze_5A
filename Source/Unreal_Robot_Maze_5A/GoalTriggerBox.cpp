// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTriggerBox.h"
#include "DrawDebugHelpers.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

AGoalTriggerBox::AGoalTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AGoalTriggerBox::OnOverlapBegin);
}

void AGoalTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this)) {
        print("Player win");
    }
}
