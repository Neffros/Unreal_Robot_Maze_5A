// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossRoadController.h"
#include "Engine/World.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

// Sets default values
ACrossRoadController::ACrossRoadController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrossRoadController::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	for (TObjectIterator<ACrossRoadTrigger> It; It; ++It)
	{
		ACrossRoadTrigger* crossRoad = *It;
		if (crossRoad->GetWorld() == world) {
			crossRoads.Add(crossRoad);
		}
	}
	
	//
	printFString("amount of crossRoads: %d", crossRoads.Num());

}

// Called every frame
void ACrossRoadController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ACrossRoadTrigger*> ACrossRoadController::GetCrossRoads()
{
	return crossRoads;
}


