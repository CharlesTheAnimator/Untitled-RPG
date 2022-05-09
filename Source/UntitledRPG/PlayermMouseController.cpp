// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayermMouseController.h"
#include "BaseRPGCharacter.h"

#include "Kismet/GameplayStatics.h"

#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Math/Vector.h" 

APlayermMouseController::APlayermMouseController()
{
	/*Init Controller variables*/
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bAttacking = false;
	LookDirection = FVector(0.0f, 0.0f, 0.0f);
}

void APlayermMouseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*Init Action Bindings*///TODO: Rename to more modular calls
	//LMB
	InputComponent->BindAction("SetBasicAttacking", IE_Pressed, this, &APlayermMouseController::StartBasicAttacking);
	InputComponent->BindAction("SetBasicAttacking", IE_Released, this, &APlayermMouseController::EndBasicAttacking);
	//E
	InputComponent->BindAction("DashActivate", IE_Pressed, this, &APlayermMouseController::DashInDirection);
	//Q
	InputComponent->BindAction("ShiledBuffActivate", IE_Pressed, this, &APlayermMouseController::InvokeShieldBuff);

	/*Init Axis Bindings*/
	//WASD
	InputComponent->BindAxis("MoveForward", this, &APlayermMouseController::MoveForward);
	InputComponent->BindAxis("MoveSideways", this, &APlayermMouseController::MoveSideways);
}

/*Tick Calls*/
void APlayermMouseController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bAttacking)
	{/*true: orient to cursor*/
		RotateToCursor();
	}
}

/*WASD Locomotion calls to character class*/
void APlayermMouseController::MoveForward(float AxisValue)
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	if (CharacterPawn)
	{
		CharacterPawn->MoveForward(AxisValue);
	}
}

void APlayermMouseController::MoveSideways(float AxisValue)
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	if (CharacterPawn)
	{
		CharacterPawn->MoveSideways(AxisValue);
	}
}

/*LMB Basic Attack Function Definitions*/
void APlayermMouseController::StartBasicAttacking()
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	if (CharacterPawn)
	{
		CharacterPawn->GetCharacterMovement()->bOrientRotationToMovement = false;
		CharacterPawn->BoxCollisionDefault->SetCollisionProfileName("MeleeAttack");
		CharacterPawn->PlayAnimMontage(CharacterPawn->BasicAtkAnimMont);
	}

	bAttacking = true;
}
void APlayermMouseController::EndBasicAttacking()
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	if (CharacterPawn)
	{
		CharacterPawn->GetCharacterMovement()->bOrientRotationToMovement = true;
		CharacterPawn->BoxCollisionDefault->SetCollisionProfileName("NoCollision");
	}
	
	bAttacking = false;

}

/*E Action Bound Function Definition*/
void APlayermMouseController::DashInDirection()
{
	RotateToCursor();

	/*Invoke MovementComponent Velocity*/
	ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
	if (PlayerCharacter) {
		PlayerCharacter->BoxCollisionDefault->SetCollisionProfileName("MeleeAttack");
		FVector DashDirection = PlayerCharacter->GetActorForwardVector();
		if (DashDirection.Normalize()) {
			PlayerCharacter->GetMovementComponent()->Velocity = DashDirection * DashDistance;
		}
	}

	/*Time delayed Collision to NoCollision*/
	FTimerDelegate TimerCallback;
	FTimerHandle Handle;
	TimerCallback.BindLambda([&]
	{ 
		ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
		if (PlayerCharacter) {
			PlayerCharacter->BoxCollisionDefault->SetCollisionProfileName("NoCollision");
		}
	});
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 0.1f, false);
}

/*Q Action bond Function Definition*/
void APlayermMouseController::InvokeShieldBuff()
{
	/*Invoke Q Character Ability*/
	ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
	if (PlayerCharacter) {
		PlayerCharacter->ShieldMesh->SetVisibility(true);
		/*set Collision change TODO*/
	}

	/*Time delayed visibility switch to false*/
	FTimerDelegate TimerCallback;
	FTimerHandle Handle;
	TimerCallback.BindLambda([&]
	{
		ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
		if (PlayerCharacter) {
			PlayerCharacter->ShieldMesh->SetVisibility(false);
			/*set Collision change TODO*/
		}
	});
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 2.0f, false);
}

/*Rotate to Cursor Definition*/
void APlayermMouseController::RotateToCursor()
{
	/*Rotate Character to face hit space beneath cursor*/
	APawn* const MyPawn = GetPawn();
	if (MyPawn) {
		FVector PawnLocation;
		PawnLocation = MyPawn->GetMovementComponent()->GetActorLocation();

		FHitResult Cursor;
		this->GetHitResultUnderCursor(ECC_Visibility, true, Cursor);
		FVector CursorLocation;
		CursorLocation = Cursor.Location;

		LookDirection = CursorLocation - PawnLocation;
		LookDirection.Normalize();
		MyPawn->SetActorRotation(LookDirection.Rotation(), ETeleportType::TeleportPhysics);
	}
}


