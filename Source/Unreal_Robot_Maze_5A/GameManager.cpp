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

	this->_currentPhase = GamePhaseEnum::CrossroadPhase;
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
		if (direction == CrossRoadController->GetCrossRoads()[index]->direction)
			isNextValue;
	}

	
}

void AGameManager::ToggleToPreviousDirection()
{
}



// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->_currentPhase == GamePhaseEnum::ExplorationPhase)
	{
		this->SetGameTimer(this->_gameTimer + DeltaTime);
		this->SetCurrentRobotBatteryDuration(this->_currentRobotBatteryDuration - DeltaTime);

		if (this->_currentRobotBatteryDuration < 0.0f)
		{
			this->BeginEndPhase(false);
			return;
		}

		this->Robot->Tick(DeltaTime);
	}
}

GamePhaseEnum AGameManager::GetCurrentPhase() const
{
	return this->_currentPhase;
}

float AGameManager::GetGameTimer() const
{
	return this->_gameTimer;
}

void AGameManager::SetGameTimer(float seconds)
{
	this->_gameTimer = seconds;
}

float AGameManager::GetCurrentRobotBatteryDuration() const
{
	return this->_currentRobotBatteryDuration;
}

void AGameManager::SetCurrentRobotBatteryDuration(float duration)
{
	this->_currentRobotBatteryDuration = duration;
}

float AGameManager::GetBatteryDuration() const
{
	return this->RobotBatteryDuration;
}

void AGameManager::BeginExplorationPhase()
{
	this->_currentPhase = GamePhaseEnum::ExplorationPhase;
	this->SetCurrentRobotBatteryDuration(this->RobotBatteryDuration);
	this->SetGameTimer(0.0f);

	// TD : activer l'UI d'exploration
}

void AGameManager::BeginEndPhase(bool isWin)
{
	this->_currentPhase = GamePhaseEnum::EndPhase;

	// TD : UI - update texte de temps, afficher victoire ou défaite, activer l'UI
}

