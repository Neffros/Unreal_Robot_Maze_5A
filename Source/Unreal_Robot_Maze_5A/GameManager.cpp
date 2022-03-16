// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

//const FName AUnreal_Robot_Maze_5APawn::MoveForwardBinding("MoveForward");
//const FName AUnreal_Robot_Maze_5APawn::MoveRightBinding("MoveRight");

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

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

