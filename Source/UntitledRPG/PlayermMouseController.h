// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayermMouseController.generated.h"

/*
 * 
 */
UCLASS()
class UNTITLEDRPG_API APlayermMouseController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	void MouseTrack();

public:
	APlayermMouseController();



};
