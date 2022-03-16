// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCameraController.generated.h"

UCLASS()
class UNREAL_ROBOT_MAZE_5A_API AGameCameraController : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGameCameraController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere)
	AActor* Cam;
};
