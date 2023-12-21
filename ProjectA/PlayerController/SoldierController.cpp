// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Character/Character_Base.h"
#include "../Character/Soldier.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/CrosshairWidget.h"

ASoldierController::ASoldierController()
	:TurnSpeed(1.f)
{
//	DefaultMouseCursor = EMouseCursor::Default;

	ConstructorHelpers::FClassFinder<UUserWidget> CursorAim(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UMG/Crosshair/WBP_AIM.WBP_AIM_C'"));
	if (CursorAim.Succeeded()) {
		m_CursorAimWidgetClass = CursorAim.Class;
	}
}

void ASoldierController::PullCriticalLine(float _Degree)
{
	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->PullCriticalLine(_Degree);
	}
}

void ASoldierController::SetCriticalPercent(float _Percent)
{
	m_CriticalPercent = _Percent;
	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->SetCriticalRange(360 * m_CriticalPercent);
	}
}

bool ASoldierController::IsCriticalFire()
{
	return (1 - m_CriticalPercent) / 2 <= m_CurCriticalValue
		&& m_CurCriticalValue <= (1 - m_CriticalPercent) / 2 + m_CriticalPercent;
}

void ASoldierController::EmphasizeCritical()
{
	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->EmphasizeCritical();
	}
}

void ASoldierController::StopRotationLine(float _Time)
{
	RemainLineStopTime = _Time;
}

void ASoldierController::SetRounds(int _Rounds)
{
	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->SetRounds(_Rounds);
	}
}

void ASoldierController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ShootingMappingContext, 1);
	}

	//APlayerController* pController = GetWorld()->GetFirstPlayerController();

	if (IsValid(m_CursorAimWidgetClass)) {
		m_CursorAimWidget = Cast<UCrosshairWidget>(CreateWidget(GetWorld(), m_CursorAimWidgetClass));
		if (IsValid(m_CursorAimWidget)) {
			SetMouseCursorWidget(EMouseCursor::Default, m_CursorAimWidget);
			//m_CursorAimWidget->SetCriticalRange(180.f);
			SetCriticalPercent(m_CriticalPercent);
		}
	}
//	DefaultMouseCursor = Crosshair;
}

void ASoldierController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &ASoldierController::Fire);
		EnhancedInputComponent->BindAction(IA_Aim, ETriggerEvent::Triggered, this, &ASoldierController::Aim);
		EnhancedInputComponent->BindAction(IA_Reload, ETriggerEvent::Triggered, this, &ASoldierController::Reload);
		EnhancedInputComponent->BindAction(IA_Action, ETriggerEvent::Triggered, this, &ASoldierController::Action);

	}
}

void ASoldierController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Slow = 1.f;
	if (RemainLineStopTime > 0) {
		RemainLineStopTime -= DeltaTime;
		Slow = 0.25f;
	}
	{
		m_CurCriticalValue += TurnSpeed * DeltaTime * Slow;
		if (m_CurCriticalValue >= 1.f) {
			m_CurCriticalValue = 0;
		}
	}

	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->SetCriticalLine(m_CurCriticalValue * 360);
	}
}

void ASoldierController::Fire(const FInputActionInstance& _Instance)
{
	APawn* ControlledPawn = GetPawn();
	if (ASoldier* Soldier = Cast<ASoldier>(ControlledPawn))
	{
		bool IsFireInput = _Instance.GetValue().Get<bool>();
		if (IsFireInput) {
			Soldier->FireOrder(FVector(0,0,0));
		}
	}
}

void ASoldierController::Aim(const FInputActionInstance& _Instance)
{
	bool IsAimInput = _Instance.GetValue().Get<bool>();
	APawn* ControlledPawn = GetPawn();
	if (ASoldier* Soldier = Cast<ASoldier>(ControlledPawn))
	{
		Soldier->Aim(IsAimInput);
	}

	if (IsValid(m_CursorAimWidget)) {
		m_CursorAimWidget->SetCursorActivate(IsAimInput);
	}
	
	//TSharedPtr<SWidget> CursorWidget = GetWorld()->GetGameViewport()->GetSoftwareCursorWidget(EMouseCursor::Default);
	//UCrosshairWidget* CrosshairWidget = Cast<UCrosshairWidget>(CursorWidget.Get());
	//if (IsValid(CrosshairWidget)) {
	//	CrosshairWidget->SetCursorActivate(IsAimInput);
	//}
}

void ASoldierController::Reload(const FInputActionInstance& _Instance)
{
	APawn* ControlledPawn = GetPawn();
	if (ASoldier* Soldier = Cast<ASoldier>(ControlledPawn))
	{
		Soldier->ReloadOrder();
	}
}

void ASoldierController::Action(const FInputActionInstance& _Instance)
{
}
