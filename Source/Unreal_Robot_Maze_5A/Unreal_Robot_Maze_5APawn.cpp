// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Robot_Maze_5APawn.h"
#include "Unreal_Robot_Maze_5AProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AUnreal_Robot_Maze_5APawn::AUnreal_Robot_Maze_5APawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	this->MoveSpeed = 500.0f;
	this->isBiasedDirection = false;

	PrimaryActorTick.bCanEverTick = false;
}

void AUnreal_Robot_Maze_5APawn::Update(float DeltaSeconds)
{
	bool hasWallForward = this->Ray(GetActorForwardVector(), 150, FColor::Red);

	if (hasWallForward && this->isBiasedDirection)
		this->isBiasedDirection = false;

	if (!this->isBiasedDirection)
	{
		bool hasWallLeft = Ray(-GetActorRightVector(), 150, FColor::Blue);

		if (!hasWallLeft && hasWallLeftOld != hasWallLeft)
			this->currentDirection = -GetActorRightVector();
		else if (!hasWallForward)
			this->currentDirection = GetActorForwardVector();
		else
			this->currentDirection = GetActorRightVector();

		hasWallLeftOld = hasWallLeft;
	}

	const FVector Movement = this->currentDirection * MoveSpeed * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}

bool AUnreal_Robot_Maze_5APawn::Ray(FVector Direction, float distance, FColor color)
{
	FVector back = -this->GetActorForwardVector();
	back.Normalize();

	FVector Start = GetActorLocation() + back * 50;
	const FVector endLocation = Start + (Direction * distance);

	FHitResult hit;
	FCollisionQueryParams TraceParams(TEXT("LineOfSight_Trace"), false, this);

	bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, Start, endLocation, ECollisionChannel::ECC_Visibility, TraceParams, FCollisionResponseParams::DefaultResponseParam);
	//DrawDebugLine(GetWorld(), Start, endLocation, color, false, 0.f, 0.f, 10);

	return actorHit && hit.GetActor() != NULL;
}

void AUnreal_Robot_Maze_5APawn::SetBiasedDirection(FVector direction)
{
	this->isBiasedDirection = true;
	this->currentDirection = direction;
}

void AUnreal_Robot_Maze_5APawn::UnbiasDirection()
{
	this->isBiasedDirection = false;
}
