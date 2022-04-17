// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRPGCharacter.h"
#include "Components/InputComponent.h"

#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h" 

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h" 
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ABaseRPGCharacter::ABaseRPGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ABaseRPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ABaseRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{ 
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	/*Locomotion logic*/
	InputComponent->BindAxis("MoveForward", this, &ABaseRPGCharacter::MoveForward);
	InputComponent->BindAxis("MoveSideways", this, &ABaseRPGCharacter::MoveSideways);

}

void ABaseRPGCharacter::MoveForward(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0) {
		const FRotator Roto = Controller->GetControlRotation();		//Controller should be oriented to world axis
		const FRotator YawRoto(0, Roto.Yaw, 0);						//Only need yaw rotation (Pitch and roll do not effect move forward or backward
		
		const FVector Direction = FRotationMatrix(YawRoto).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void ABaseRPGCharacter::MoveSideways(float AxisValue)
{
	if (Controller != nullptr && AxisValue != 0) {
		const FRotator roto = Controller->GetControlRotation();
		const FRotator YawRoto(0, roto.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRoto).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

