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

public:

	APlayermMouseController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAttacking;

protected:

	//Protected Actor & Pawn base class overrides
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:

	bool bAttackCollide;
	bool bMeshCollide;
	float DashDistance = 5000;
	FVector LookDirection;

	void StartBasicAttacking();
	void EndBasicAttacking();
	void DashInDirection();
	void InvokeShieldBuff();

	void RotateToCursor();
};
