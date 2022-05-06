// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Math/Vector.h" 

#include "PlayermMouseController.h"
#include "BaseRPGCharacter.h"

APlayermMouseController::APlayermMouseController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bAttacking = false;
	LookDirection = FVector(0.0f, 0.0f, 0.0f);
}

void APlayermMouseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetBasicAttacking", IE_Pressed, this, &APlayermMouseController::StartBasicAttacking);
	InputComponent->BindAction("SetBasicAttacking", IE_Released, this, &APlayermMouseController::EndBasicAttacking);

	InputComponent->BindAction("DashActivate", IE_Pressed, this, &APlayermMouseController::DashInDirection);

	InputComponent->BindAction("ShiledBuffActivate", IE_Pressed, this, &APlayermMouseController::InvokeShieldBuff);
}

void APlayermMouseController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bAttacking)
	{
		RotateToCursor();
	}
}

void APlayermMouseController::StartBasicAttacking()
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	if (CharacterPawn)
	{
		CharacterPawn->GetCharacterMovement()->bOrientRotationToMovement = false;
		CharacterPawn->BoxCollisionDefault->SetCollisionProfileName("MeleeAttack");
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

void APlayermMouseController::DashInDirection()
{
	RotateToCursor();

	ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
	if (PlayerCharacter) {
		PlayerCharacter->BoxCollisionDefault->SetCollisionProfileName("MeleeAttack");
		FVector DashDirection = PlayerCharacter->GetActorForwardVector();
		if (DashDirection.Normalize()) {
			PlayerCharacter->GetMovementComponent()->Velocity = DashDirection * 5000.0f;
			UE_LOG(LogTemp, Warning, TEXT("Vecotr Is normalizing"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("DashInDirection is being invoked"));

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([&]
	{ 
		ABaseRPGCharacter* PlayerCharacter = Cast<ABaseRPGCharacter>(GetCharacter());
		if (PlayerCharacter) {
			PlayerCharacter->BoxCollisionDefault->SetCollisionProfileName("NoCollision");
		}
	});

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, TimerCallback, 0.1f, false);
}

void APlayermMouseController::InvokeShieldBuff()
{

}

void APlayermMouseController::RotateToCursor()
{
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

