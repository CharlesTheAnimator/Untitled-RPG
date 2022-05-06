// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollisionDefault;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	// Private base character data
	int BasicTimeDelay = 1;
	FName MeleeSocket;
	class USceneComponent* ROOT;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by axis binds
	void MoveForward(float);
	void MoveSideways(float);


	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/*Skeletal Mesh Component*/
	//TODO
};
