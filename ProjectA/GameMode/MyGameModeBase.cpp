// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase()
{
	//ConstructorHelpers::FClassFinder<UUserWidget> CursorAim(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UMG/Crosshair/BP_AIM.BP_AIM_C'"));
	//if (CursorAim.Succeeded()) {
	//	m_CursorAimWidgetClass = CursorAim.Class;
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Failure Cursor Class"));
	//}
}

AMyGameModeBase::~AMyGameModeBase()
{
}


void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//APlayerController* pController = GetWorld()->GetFirstPlayerController();

	//FInputModeGameAndUI gameUiMode;
	//pController->SetInputMode(gameUiMode);
	//pController->bShowMouseCursor = true;
	//if (IsValid(m_CursorAimWidgetClass)) {
	//	m_CursorAimWidget = Cast<UCrosshairWidget>(CreateWidget(GetWorld(), m_CursorAimWidgetClass));
	//	if (IsValid(m_CursorAimWidget)) {
	//		m_CursorAimWidget->SetCursor(EMouseCursor::Default);
	//		UE_LOG(LogTemp, Warning, TEXT("Success Cursor Widget"));
	//		m_CursorAimWidget->PullCriticalLine(33.f);
	//	}
	//	else {

	//		UE_LOG(LogTemp, Warning, TEXT("Failure Cursor Widget"));
	//	}
	//}
	//else {

	//	UE_LOG(LogTemp, Warning, TEXT("Failure Cursor Class2"));
	//}
}