// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "GameInputListenerPawn.generated.h"

UCLASS()
class UNREAL_ROBOT_MAZE_5A_API AGameInputListenerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameInputListenerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void StartExploration();

public:	

	UPROPERTY(EditAnywhere)
	AGameManager* GameManager;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
