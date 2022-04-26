// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayermMouseController.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

APlayermMouseController::APlayermMouseController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

}

void APlayermMouseController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*Set up input component*/
	//TODO

}

void APlayermMouseController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	if (true) {
		//Call mouse track
	}
}

void APlayermMouseController::MouseTrack()
{
	//float mouseX, mouseY;
	//APlayerController* controller = Cast<APlayerController>(GetController());
	//controller->GetMousePosition(mouseX, mouseY);


	//FVector2D* screenPos = new FVector2D(mouseX, mouseY);
	//controller->GetHitResultAtScreenPosition(*screenPos, ECC_Visibility, false, Hit);
}
