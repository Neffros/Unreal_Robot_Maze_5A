// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot_Maze_Game_Instance.h"

void URobot_Maze_Game_Instance::Init()
{
	// TD : Charger le fichier de sauvegarde pour récupérer le temps

	this->_recordSeconds = .0f;
}

float URobot_Maze_Game_Instance::GetRecordSeconds() const
{
	return this->_recordSeconds;
}

bool URobot_Maze_Game_Instance::SetRecordSecondsIfBetter(float seconds)
{
	if (this->_recordSeconds <= seconds)
		return false;

	// TD : Sauvegarder le temps dans le fichier de sauvegarde

	this->_recordSeconds = seconds;
	return true;
}

