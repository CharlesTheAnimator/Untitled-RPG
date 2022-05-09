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

public:
	APlayermMouseController();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bAttacking;


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
