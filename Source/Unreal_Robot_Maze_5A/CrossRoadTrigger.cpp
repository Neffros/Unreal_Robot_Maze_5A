// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossRoadTrigger.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

ACrossRoadTrigger::ACrossRoadTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACrossRoadTrigger::OnOverlapBegin);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> loadedMesh(TEXT("/Game/Geometry/Meshes/Arrow.Arrow"));
    arrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("loadedMesh"));
    arrowMesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
    arrowMesh->SetStaticMesh(loadedMesh.Object);
    //arrowMesh->SetRelativeLocation(FVector(0, 0, 200));
    SetActorHiddenInGame(false);
   
}

void ACrossRoadTrigger::BeginPlay()
{
    Super::BeginPlay();
    arrowMesh->SetRelativeLocation(FVector(0, 0, 0));
    arrowMesh->SetVisibility(false);
}

void ACrossRoadTrigger::UpdateJokerDirection(DirectionEnum dir)
{
    FVector newRotation;
    arrowMesh->SetVisibility(true);

    switch (dir)
    {
        case DirectionEnum::None:
            arrowMesh->SetVisibility(false);
            break;
        case DirectionEnum::Up:
            newRotation = FVector(0, 0, 90);
            break;
        case DirectionEnum::Down:
            newRotation = FVector(0, 0, -90);
            break;
        case DirectionEnum::Right:
            newRotation = FVector(0, 0, 180);
            break;
        case DirectionEnum::Left:
            newRotation = FVector(0, 0, 0);
            break;
        default:
            break;
    }
    print("switching actor rotation");
    print(newRotation.ToString());

    FQuat quaternion(FRotator::MakeFromEuler(newRotation));
    arrowMesh->SetRelativeRotation(quaternion);
}

void ACrossRoadTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this))
    {
        AUnreal_Robot_Maze_5APawn* actor = Cast<AUnreal_Robot_Maze_5APawn>(OtherActor);

        if (actor != NULL)
        {
            switch (direction)
            {
            case DirectionEnum::None:
                actor->UnbiasDirection();
                break;
            case DirectionEnum::Up:
                actor->SetBiasedDirection(FVector::ForwardVector);
                direction = DirectionEnum::None;
                break;
            case DirectionEnum::Down:
                actor->SetBiasedDirection(-FVector::ForwardVector);
                direction = DirectionEnum::None;
                break;
            case DirectionEnum::Right:
                actor->SetBiasedDirection(FVector::RightVector);
                direction = DirectionEnum::None;
                break;
            case DirectionEnum::Left:
                actor->SetBiasedDirection(-FVector::RightVector);
                direction = DirectionEnum::None;
                break;
            default:
                break;
            }

            arrowMesh->SetVisibility(false);
        }
    }
}