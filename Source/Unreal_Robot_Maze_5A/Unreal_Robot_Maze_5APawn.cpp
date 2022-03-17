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

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1,0.f, FColor::Green, FString::Printf(TEXT(text), fstring))


AUnreal_Robot_Maze_5APawn::AUnreal_Robot_Maze_5APawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Movement
	this->MoveSpeed = 500.0f;
	this->isBiasedDirection = false;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	bCanFire = true;
}

void AUnreal_Robot_Maze_5APawn::Tick(float DeltaSeconds)
{
	//this->BatteryLife -= 0.1 * DeltaSeconds;
	//printFString("BatteryLife : %d", this->BatteryLife);
	bool hasWallForward = this->Ray(GetActorForwardVector(), 150, FColor::Red);

	if (hasWallForward && this->isBiasedDirection)
		this->isBiasedDirection = false;

	// TD : trouver la condition d'arr�t de biais
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

	// Calculate  movement
	const FVector Movement = this->currentDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
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

void AUnreal_Robot_Maze_5APawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector Start = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AUnreal_Robot_Maze_5AProjectile>(Start, FireRotation);
			}

			bCanFire = false;

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
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
	DrawDebugLine(GetWorld(), Start, endLocation, color, false, 0.f, 0.f, 10);
	if (hit.GetActor() != NULL) {
		//GEngine->AddOnScreenDebugMessage(-1,2.0f, color, hit.GetActor()->GetFName().ToString());
		return true;
	}

	return false;
}

void AUnreal_Robot_Maze_5APawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AUnreal_Robot_Maze_5APawn::SetBiasedDirection(FVector direction)
{
	this->isBiasedDirection = true;
	this->currentDirection = direction;
}

void AUnreal_Robot_Maze_5APawn::SetIsBiasedDirection(bool isBiased)
{
	this->isBiasedDirection = isBiased;
}

bool AUnreal_Robot_Maze_5APawn::GetIsBiasedDirection()
{
	return this->isBiasedDirection;
}

