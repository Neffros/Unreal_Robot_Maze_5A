// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalTriggerBox.h"
#include "Engine/CollisionProfile.h"

AGoalTriggerBox::AGoalTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AGoalTriggerBox::OnOverlapBegin);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> loadedMesh(TEXT("/Game/Geometry/Meshes/GoalMesh.GoalMesh"));
    this->GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("loadedMesh"));
    this->GoalMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    this->GoalMesh->SetStaticMesh(loadedMesh.Object);
}

void AGoalTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    this->GoalMesh->SetRelativeLocation(FVector(0, 0, 0));
    this->GoalMesh->SetVisibility(true);
}

void AGoalTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if (OtherActor && OtherActor != this && Cast<AUnreal_Robot_Maze_5APawn>(OtherActor) != NULL)
        this->GameManager->BeginEndPhase(true);
}