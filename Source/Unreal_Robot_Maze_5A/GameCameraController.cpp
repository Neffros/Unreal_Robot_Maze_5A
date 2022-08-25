// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCameraController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AGameCameraController::AGameCameraController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameCameraController::BeginPlay()
{
	Super::BeginPlay();

	this->_initPos = Cam->GetActorLocation();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

	if (playerController)
		playerController->SetViewTarget(Cam);
}

void AGameCameraController::SetCameraPosition(FVector newPosition)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

	if (playerController)
	{
		playerController->SetViewTargetWithBlend(Cam, 1.0f);
		Cam->SetActorLocation(FVector(newPosition.X, newPosition.Y, newPosition.Z + ZOffset));
	}
}

void AGameCameraController::ReinitializePosition()
{
	Cam->SetActorLocation(this->_initPos);
}

