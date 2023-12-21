// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Character/Character_Base.h"
#include "Kismet/KismetSystemLibrary.h"

ACharacterController::ACharacterController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

FVector ACharacterController::GetMouseCursorLocationOnWorld()
{
	FVector MouseLocation, MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	TArray<AActor*, FDefaultAllocator> tAry;
	FHitResult hitResult;
	ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel7);
	bool isHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), MouseLocation, MouseLocation + MouseDirection * 5000.f
		, MyTraceType, false, tAry, EDrawDebugTrace::None, hitResult, true);
	if (isHit) {
		return hitResult.Location;
	}
	return MouseLocation;
}


void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ACharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACharacterController::Move);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ACharacterController::Sprint);

	}
}

void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Look();
}

void ACharacterController::Move(const FInputActionInstance& _Instance)
{
	APawn* ControlledPawn = GetPawn();
	if (ACharacter_Base* character = Cast<ACharacter_Base>(ControlledPawn))
	{
		FVector2D vInput = _Instance.GetValue().Get<FVector2D>();
		FVector dir(vInput, 0.f);

		character->Move(dir);
	}
}

void ACharacterController::Look()
{
	APawn* ControlledPawn = GetPawn();
	if (ACharacter_Base* character = Cast<ACharacter_Base>(ControlledPawn))
	{
		float MouseX, MouseY;
		GetMousePosition(MouseX, MouseY);
		FVector2D MousePosition(MouseX, MouseY);
		FHitResult HitResult;
		if (GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, true, HitResult)) {
			character->Look(HitResult.Location);
		}
	}
}

void ACharacterController::Sprint(const FInputActionInstance& _Instance)
{
	APawn* ControlledPawn = GetPawn();
	if (ACharacter_Base* character = Cast<ACharacter_Base>(ControlledPawn))
	{
		bool IsSprintInput = _Instance.GetValue().Get<bool>();
		character->Sprint(IsSprintInput);
	}
}
