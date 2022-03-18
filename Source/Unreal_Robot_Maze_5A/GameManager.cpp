// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT(text), fstring))


// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGameManager::MoveToNextCrossRoad()
{
	++index;
	index = index % CrossRoadController->GetCrossRoads().Num();
	CameraController->SetCameraPosition(CrossRoadController->GetCrossRoads()[index]->GetActorLocation());
}


void AGameManager::MoveToPreviousCrossRoad()
{
	if(index == 0)
		index = CrossRoadController->GetCrossRoads().Num() - 1;
	else
		--index;

	CameraController->SetCameraPosition(CrossRoadController->GetCrossRoads()[index]->GetActorLocation());
}

void AGameManager::ToggleToNextDirection()
{
	bool isNextValue = false;
	for (DirectionEnum direction : TEnumRange<DirectionEnum>()) {
		if (isNextValue)
		{
			CrossRoadController->GetCrossRoads()[index]->direction = direction;
			CrossRoadController->GetCrossRoads()[index]->UpdateJokerDirection(direction);
			return;
		}
		if (CrossRoadController->GetCrossRoads()[index]->direction == DirectionEnum::Down)
		{
			CrossRoadController->GetCrossRoads()[index]->direction = DirectionEnum::None;
			CrossRoadController->GetCrossRoads()[index]->UpdateJokerDirection(DirectionEnum::None);
			return;
		}
		if (direction == CrossRoadController->GetCrossRoads()[index]->direction)
		{
			isNextValue = true;
		}
	}

	
}

void AGameManager::ToggleToPreviousDirection()
{
}



// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

