// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "PlayermMouseController.h"
#include "BaseRPGCharacter.h"

APlayermMouseController::APlayermMouseController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bAttacking = false;
}

void APlayermMouseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetBasicAttacking", IE_Pressed, this, &APlayermMouseController::StartBasicAttacking);
	InputComponent->BindAction("SetBasicAttacking", IE_Released, this, &APlayermMouseController::EndBasicAttacking);

}

void APlayermMouseController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	if (bAttacking)
	{
		APawn* const MyPawn = GetPawn();
		if (MyPawn) {
			//UE_LOG(LogTemp, Warning, TEXT("MyPawn Worked"));
			FVector PawnLoaction;
			PawnLoaction = MyPawn->GetMovementComponent()->GetActorLocation();

			FHitResult Cursor;
			this->GetHitResultUnderCursor(ECC_Visibility, true, Cursor);
			FVector CursorLocation;
			CursorLocation = Cursor.Location;

			FVector LookDirection = CursorLocation - PawnLoaction;
			MyPawn->SetActorRotation(LookDirection.Rotation(), ETeleportType::TeleportPhysics);
		}
	}
}

void APlayermMouseController::StartBasicAttacking()
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	CharacterPawn->GetCharacterMovement()->bOrientRotationToMovement = false;
	CharacterPawn->BoxCollisionDefault->SetCollisionProfileName("MeleeAttack");

	bAttacking = true;
}

void APlayermMouseController::EndBasicAttacking()
{
	ABaseRPGCharacter* CharacterPawn = Cast<ABaseRPGCharacter>(GetCharacter());
	CharacterPawn->GetCharacterMovement()->bOrientRotationToMovement = true;
	CharacterPawn->BoxCollisionDefault->SetCollisionProfileName("NoCollision");

	bAttacking = false;
}