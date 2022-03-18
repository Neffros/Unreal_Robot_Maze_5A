// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTrigger.h"
#include "Engine/CollisionProfile.h"

void AGoalTrigger::BeginPlay()
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

	goalMesh->SetRelativeLocation(FVector(0, 0, 0));
	goalMesh->SetVisibility(true);

}

AGoalTrigger::AGoalTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AGoalTrigger::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> loadedMesh(TEXT("/Game/Meshes/GoalMesh.GoalMesh"));
	goalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("loadedMesh"));
	goalMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	goalMesh->SetStaticMesh(loadedMesh.Object);

	SetActorHiddenInGame(false);

}

void AGoalTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GameManager->BeginEndPhase(true);
}
