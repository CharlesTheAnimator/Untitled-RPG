// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseRPGCharacter.h"
#include "PlayermMouseController.h"

#include "Components/InputComponent.h"
#include "Components/DecalComponent.h"

#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h" 

#include "UObject/ConstructorHelpers.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h" 
#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

#include "Materials/Material.h"

// Sets default values
ABaseRPGCharacter::ABaseRPGCharacter()
{
	/*Initialize Socket FName*/
	MeleeSocket = TEXT("URPGDefautlSocket");
	
	/*Init Skeletal Mesh Component*/
	//TODO

	/*Init Pawn controller Setting*/
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/*Initialize UboxComponents*/
	ROOT = this->GetRootComponent();
	BoxCollisionDefault = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionDefault"));
	BoxCollisionDefault->SetupAttachment(ROOT);
	BoxCollisionDefault->SetCollisionProfileName("NoCollision");

	/* Init a decal in the world to show the cursor's location*/
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(ROOT);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}

	/*Initialize Movement & Starting Orientation settings*/
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

// Called when the game starts or when spawned
void ABaseRPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/*Init FAttachmentTransformRules*/
	const FAttachmentTransformRules BoxCollisionDefaultAttachmentRules(
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::SnapToTarget, 
		EAttachmentRule::KeepWorld, false);

	/*Attach melee collision box to socket*/
	BoxCollisionDefault->AttachToComponent(
		GetMesh(), 
		BoxCollisionDefaultAttachmentRules, 
		(TEXT("URPGDefautlSocket")));

	/*Spawn Decal Asset*/
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

// Called every frame
void ABaseRPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CursorToWorld != nullptr) {
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

// Called to bind functionality to input
void ABaseRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{ 
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*Locomotion binding*/
	InputComponent->BindAxis("MoveForward", this, &ABaseRPGCharacter::MoveForward);
	InputComponent->BindAxis("MoveSideways", this, &ABaseRPGCharacter::MoveSideways);

}

void ABaseRPGCharacter::MoveForward(float AxisValue)
{
	//Controller should be oriented to world axis
	//Only need yaw rotation Pitch and roll do not effect move forward or backward
	if (Controller != nullptr && AxisValue != 0) {
		const FRotator Roto = Controller->GetControlRotation();		
		const FRotator YawRoto(0, Roto.Yaw, 0);						
		
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