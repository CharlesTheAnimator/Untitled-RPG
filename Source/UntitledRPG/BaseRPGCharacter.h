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

	//BP Properties
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ROOT;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	class UBoxComponent* BoxCollisionDefault;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animations)
	UStaticMeshComponent* ShieldMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* BasicAtkAnimMont;
	UPROPERTY(EditAnywhere)
	bool bMelee;

protected:

	//Protected Actor & Pawn base class overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:

	//Private BP Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
	/*Skeletal Mesh Component*/
	//TODO
	/*Actor GameplayClass Component*/
	//TODO

public:

	//Actor & Pawn base class overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Called by axis binding in controller 
	void MoveForward(float);
	void MoveSideways(float);

	//Forceinline header functions
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:

	//Private Methods
	void UpdateCursorDecal();

};
