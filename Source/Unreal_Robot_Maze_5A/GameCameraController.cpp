// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCameraController.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,0.f, FColor::Green, FString::Printf(TEXT(text), fstring))

// Sets default values
AGameCameraController::AGameCameraController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameCameraController::BeginPlay()
{
	Super::BeginPlay();

	this->_initPos = Cam->GetActorLocation();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);

	if (playerController)
	{
		//playerController->SetViewTargetWithBlend(Cam, 5.0f);
		playerController->SetViewTarget(Cam);
		//Cam->SetActorLocation(FVector(110.0f, 1500.0f, 800.0f));
	}
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

