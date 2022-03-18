// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
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

	this->BeginCrossroadPhase();
}

void AGameManager::MoveToNextCrossRoad()
{
	// TD : à revoir
	++index;
	index = index % CrossRoadController->GetCrossRoads().Num();
	CameraController->SetCameraPosition(CrossRoadController->GetCrossRoads()[index]->GetActorLocation());
}


void AGameManager::MoveToPreviousCrossRoad()
{
	// TD : à revoir
	if(index == 0)
		index = CrossRoadController->GetCrossRoads().Num() - 1;
	else
		--index;

	CameraController->SetCameraPosition(CrossRoadController->GetCrossRoads()[index]->GetActorLocation());
}

void AGameManager::ToggleToNextDirection()
{
	bool isNextValue = false;
	auto crossRoad = CrossRoadController->GetCrossRoads()[index];

	for (DirectionEnum direction : TEnumRange<DirectionEnum>()) {
		if (isNextValue)
		{
			crossRoad->direction = direction;
			crossRoad->UpdateJokerDirection(direction);
			return;
		}
		if (crossRoad->direction == DirectionEnum::Down)
		{
			crossRoad->direction = DirectionEnum::None;
			crossRoad->UpdateJokerDirection(DirectionEnum::None);
			return;
		}
		if (direction == crossRoad->direction)
		{
			isNextValue = true;
		}
	}
}

void AGameManager::ToggleToPreviousDirection()
{
	// TD : itération inverse à faire
	bool isNextValue = false;
	auto crossRoad = CrossRoadController->GetCrossRoads()[index];

	for (DirectionEnum direction : TEnumRange<DirectionEnum>()) {
		if (isNextValue)
		{
			crossRoad->direction = direction;
			crossRoad->UpdateJokerDirection(direction);
			return;
		}
		if (crossRoad->direction == DirectionEnum::Down)
		{
			crossRoad->direction = DirectionEnum::None;
			crossRoad->UpdateJokerDirection(DirectionEnum::None);
			return;
		}
		if (direction == crossRoad->direction)
		{
			isNextValue = true;
		}
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->GetCurrentPhase() == GamePhaseEnum::ExplorationPhase)
	{
		this->SetGameTimer(this->_gameTimer + DeltaTime);
		this->SetCurrentRobotBatteryDuration(this->_currentRobotBatteryDuration - DeltaTime);

		if (this->GetCurrentRobotBatteryDuration() < 0.0f)
		{
			this->BeginEndPhase(false);
			return;
		}

		this->Robot->Update(DeltaTime);
	}
}

GamePhaseEnum AGameManager::GetCurrentPhase() const
{
	return this->_currentPhase;
}

void AGameManager::SetCurrentPhase(GamePhaseEnum phase)
{
	this->_currentPhase = phase;
	this->OnCurrentPhaseUpdateDelegate.Broadcast();
}

float AGameManager::GetGameTimer() const
{
	return this->_gameTimer;
}

void AGameManager::SetGameTimer(float seconds)
{
	this->_gameTimer = seconds;
	this->OnTimerUpdateDelegate.Broadcast();
}

float AGameManager::GetCurrentRobotBatteryDuration() const
{
	return this->_currentRobotBatteryDuration;
}

void AGameManager::SetCurrentRobotBatteryDuration(float duration)
{
	this->_currentRobotBatteryDuration = duration;
	this->OnCurrentRobotBatteryDurationUpdateDelegate.Broadcast();
}

float AGameManager::GetBatteryDuration() const
{
	return this->RobotBatteryDuration;
}

void AGameManager::BeginCrossroadPhase()
{
	if (this->GetCurrentPhase() == GamePhaseEnum::CrossroadPhase) return;

	this->SetCurrentPhase(GamePhaseEnum::CrossroadPhase);
}

void AGameManager::BeginExplorationPhase()
{
	if (this->GetCurrentPhase() == GamePhaseEnum::ExplorationPhase) return;
	
	this->SetCurrentPhase(GamePhaseEnum::ExplorationPhase);
	this->SetCurrentRobotBatteryDuration(this->RobotBatteryDuration);
	this->SetGameTimer(0.0f);
	this->CameraController->ReinitializePosition();
}

void AGameManager::BeginEndPhase(bool isWin)
{
	if (this->GetCurrentPhase() == GamePhaseEnum::EndPhase) return;

	this->SetCurrentPhase(GamePhaseEnum::EndPhase);

	if (isWin)
	{
		this->OnWinDelegate.Broadcast();
	
		URobot_Maze_Game_Instance* GI = Cast<URobot_Maze_Game_Instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GI->SetRecordSecondsIfBetter(FTimespan::FromSeconds(this->GetGameTimer()));

		// TD : ajouter un texte "Nouveau record !" sur l'UI si SetRecordSecondsIfBetter retourne true
	}
	else
	{
		this->OnLoseDelegate.Broadcast();
	}
}

