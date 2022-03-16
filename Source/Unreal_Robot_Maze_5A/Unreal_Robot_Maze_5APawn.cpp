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


const FName AUnreal_Robot_Maze_5APawn::MoveForwardBinding("MoveForward");
const FName AUnreal_Robot_Maze_5APawn::MoveRightBinding("MoveRight");
const FName AUnreal_Robot_Maze_5APawn::FireForwardBinding("FireForward");
const FName AUnreal_Robot_Maze_5APawn::FireRightBinding("FireRight");

AUnreal_Robot_Maze_5APawn::AUnreal_Robot_Maze_5APawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 500.0f;

}

void AUnreal_Robot_Maze_5APawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AUnreal_Robot_Maze_5APawn::Tick(float DeltaSeconds)
{
	bool hasWallForward = this->Ray(GetActorForwardVector(), 150, FColor::Red);
	bool hasWallLeft = Ray(-GetActorRightVector(), 150, FColor::Blue);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	FVector MoveDirection;
	if(!hasWallLeft && hasWallLeftOld != hasWallLeft)
		MoveDirection = -GetActorRightVector();
	else if(!hasWallForward)
		MoveDirection = GetActorForwardVector();
	else 
		MoveDirection = GetActorRightVector();

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

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
	hasWallForwardOld = hasWallForward;
	hasWallLeftOld = hasWallLeft;

}

bool AUnreal_Robot_Maze_5APawn::Ray(FVector Direction, float distance, FColor color)
{
	FVector back = -this->GetActorForwardVector();
	back.Normalize();
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, back.ToString());

	FVector Start = GetActorLocation() + back * 50;
	const FVector endLocation = Start + (Direction*distance);

	FHitResult hit;
	FCollisionQueryParams TraceParams(TEXT("LineOfSight_Trace"), false, this);

	bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, Start, endLocation, ECollisionChannel::ECC_Visibility, TraceParams, FCollisionResponseParams::DefaultResponseParam);
	DrawDebugLine(GetWorld(), Start, endLocation, color, false, 0.f, 0.f, 10);
	if (hit.GetActor() != NULL) {
		 GEngine->AddOnScreenDebugMessage(-1,2.0f, color, hit.GetActor()->GetFName().ToString());
		 return true;
	}

	return false;
}


