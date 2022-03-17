// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Maze_Game_Instance.h"

void URobot_Maze_Game_Instance::Init()
{
	// TD : Charger le fichier de sauvegarde pour récupérer le temps

	this->_recordTimeSpan = FTimespan();
}

FTimespan URobot_Maze_Game_Instance::GetRecordTimeSpan() const
{
	return this->_recordTimeSpan;
}

bool URobot_Maze_Game_Instance::SetRecordSecondsIfBetter(FTimespan timeSpan)
{
	if (this->_recordTimeSpan <= timeSpan)
		return false;

	// TD : Sauvegarder le temps dans le fichier de sauvegarde

	this->_recordTimeSpan = timeSpan;
	return true;
}

