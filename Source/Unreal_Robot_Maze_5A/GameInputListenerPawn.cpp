// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInputListenerPawn.h"
#include "Components/InputComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,0.f, FColor::Green, FString::Printf(TEXT(text), fstring))


// Sets default values
AGameInputListenerPawn::AGameInputListenerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameInputListenerPawn::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	for (TObjectIterator<AGameManager> It; It; ++It)
	{
		AGameManager* gameManager = *It;
		if (gameManager->GetWorld() == world) {
			GameManager = gameManager;
			break;
		}
	}
}

// Called every frame
void AGameInputListenerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Find movement direction

}

// Called to bind functionality to input
void AGameInputListenerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AGameInputListenerPawn::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &AGameInputListenerPawn::MoveLeft);
}

void AGameInputListenerPawn::MoveRight()
{
	if (GameManager != NULL)
		GameManager->MoveToNextCrossRoad();
}

void AGameInputListenerPawn::MoveLeft()
{
	if (GameManager != NULL)
		GameManager->MoveToNextCrossRoad();
}