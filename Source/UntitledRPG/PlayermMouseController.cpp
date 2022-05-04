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
	//TODO mv importan relevant binding to here

}

void APlayermMouseController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

}
