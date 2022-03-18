// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInputListenerPawn.h"
#include "Components/InputComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,0.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#define AddDynamic( UserObject, FuncName ) __Internal_AddDynamic( UserObject, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) ) )

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
            GameManager->OnCurrentPhaseUpdateDelegate.AddDynamic(this, &AGameInputListenerPawn::OnCurrentPhaseUpdate);
            this->OnCurrentPhaseUpdate();
            break;
        }
    }
}

// Called every frame
void AGameInputListenerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGameInputListenerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    this->_playerInputComponent = PlayerInputComponent;
}

void AGameInputListenerPawn::OnCurrentPhaseUpdate()
{
    GamePhaseEnum currentPhase = this->GameManager->GetCurrentPhase();

    switch (this->_oldGamePhase)
    {
    case GamePhaseEnum::CrossroadPhase:
        this->UnbindCrossroadPhase();
        break;
    case GamePhaseEnum::EndPhase:
        this->UnbindEndPhase();
        break;
    case GamePhaseEnum::ExplorationPhase:
        this->UnbindExplorationPhase();
        break;
    }

    switch (currentPhase)
    {
    case GamePhaseEnum::CrossroadPhase:
        this->BindCrossroadPhase();
        break;
    case GamePhaseEnum::EndPhase:
        this->BindEndPhase();
        break;
    case GamePhaseEnum::ExplorationPhase:
        this->BindExplorationPhase();
        break;
    }

    this->_oldGamePhase = currentPhase;
}

void AGameInputListenerPawn::BindCrossroadPhase()
{
    if (this->GameManager != NULL)
    {
        this->_playerInputComponent->BindAction("MoveDown", IE_Pressed, this->GameManager, &AGameManager::ToggleToPreviousDirection);
        this->_playerInputComponent->BindAction("StartExplore", IE_Pressed, this->GameManager, &AGameManager::BeginExplorationPhase);
        this->_playerInputComponent->BindAction("MoveLeft", IE_Pressed, this->GameManager, &AGameManager::MoveToPreviousCrossRoad);
        this->_playerInputComponent->BindAction("MoveUp", IE_Pressed, this->GameManager, &AGameManager::ToggleToNextDirection);
        this->_playerInputComponent->BindAction("MoveRight", IE_Pressed, this->GameManager, &AGameManager::MoveToNextCrossRoad);
    }
}

void AGameInputListenerPawn::UnbindCrossroadPhase()
{
    if (this->GameManager != NULL)
    {
        this->_playerInputComponent->RemoveActionBinding("MoveDown", IE_Pressed);
        this->_playerInputComponent->RemoveActionBinding("StartExplore", IE_Pressed);
        this->_playerInputComponent->RemoveActionBinding("MoveLeft", IE_Pressed);
        this->_playerInputComponent->RemoveActionBinding("MoveUp", IE_Pressed);
        this->_playerInputComponent->RemoveActionBinding("MoveRight", IE_Pressed);
    }
}

void AGameInputListenerPawn::BindExplorationPhase()
{
}

void AGameInputListenerPawn::UnbindExplorationPhase()
{
}

void AGameInputListenerPawn::BindEndPhase()
{
    if (this->GameManager != NULL)
    {
        // TD : binder bouton recommencer et bouton écran titre
    }
}

void AGameInputListenerPawn::UnbindEndPhase()
{
    if (this->GameManager != NULL)
    {
        // TD : unbinder bouton recommencer et bouton écran titre
    }
}
