// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseRPGCharacter.generated.h"

UCLASS()
class UNTITLEDRPG_API ABaseRPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseRPGCharacter();

	//BP_Menu options
	UPROPERTY(EditAnywhere)
	bool bMelee; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by axis binds
	void MoveForward(float);
	void MoveSideways(float);
	// Called by attack bind
	void InvokeAttack();
};
