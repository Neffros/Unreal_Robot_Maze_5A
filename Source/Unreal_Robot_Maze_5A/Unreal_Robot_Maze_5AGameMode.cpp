// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Robot_Maze_5AGameMode.h"
#include "Unreal_Robot_Maze_5APawn.h"
#include "GameInputListenerPawn.h"

AUnreal_Robot_Maze_5AGameMode::AUnreal_Robot_Maze_5AGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AGameInputListenerPawn::StaticClass();
	// 
	//DefaultPawnClass = AUnreal_Robot_Maze_5APawn::StaticClass();
}

