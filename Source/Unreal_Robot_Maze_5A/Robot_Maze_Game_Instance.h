// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Robot_Maze_Game_Instance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_ROBOT_MAZE_5A_API URobot_Maze_Game_Instance : public UGameInstance
{
	GENERATED_BODY()
public:
	// Lifecycle - Begin

	void Init() override;

	// Lifecycle - End

	float GetRecordSeconds() const;
	bool SetRecordSecondsIfBetter(float seconds);
private:
	float _recordSeconds;
};
