// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeInfoWidget.h"

void UEscapeInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	for (int i = 0; i < 100; i++) {
		FString TextBlockName = FString::Printf(TEXT("Escape1_%d"), i);
		auto TextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TextBlockName)));
		if (IsValid(TextBlock)) {
			EscapeHelicopter.Add(TextBlock);
		} else {
			break;
		}
	}

	for (int i = 0; i < 100; i++) {
		FString TextBlockName = FString::Printf(TEXT("Escape2_%d"), i);
		auto TextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TextBlockName)));
		if (IsValid(TextBlock)) {
			EscapeBattleship.Add(TextBlock);
		} else {
			break;
		}
	}

	for (int i = 0; i < 100; i++) {
		FString TextBlockName = FString::Printf(TEXT("Escape3_%d"), i);
		auto TextBlock = Cast<UTextBlock>(GetWidgetFromName(FName(TextBlockName)));
		if (IsValid(TextBlock)) {
			Sacrifice.Add(TextBlock);
		} else {
			break;
		}
	}
}

void UEscapeInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(EscapeHelicopter[1])) {
		EscapeHelicopter[1]->SetColorAndOpacity(ActiveColor);
	}
	if (IsValid(EscapeBattleship[1])) {
		EscapeBattleship[1]->SetColorAndOpacity(ActiveColor);
	}
	if (IsValid(Sacrifice[1])) {
		Sacrifice[1]->SetColorAndOpacity(ActiveColor);
	}
}

void UEscapeInfoWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UEscapeInfoWidget::ChangeState(EEscapeType MainId, int SubId, EState _State)
{
	if (MainId == EEscapeType::HELICOPTER) {
		if (SubId < EscapeHelicopter.Num()) {
			EscapeHelicopter[SubId]->SetColorAndOpacity(GetColor(_State));
		}
	}
	else if (MainId == EEscapeType::BATTLESHIP) {
		if (SubId < EscapeBattleship.Num()) {
			EscapeBattleship[SubId]->SetColorAndOpacity(GetColor(_State));
		}
	}
	else if (MainId == EEscapeType::SACRIFICE) {
		if (SubId < Sacrifice.Num()) {
			Sacrifice[SubId]->SetColorAndOpacity(GetColor(_State));
		}
	}
}

 FSlateColor UEscapeInfoWidget::GetColor(EState _State)
{
	switch (_State) {
	case EState::SUCCESS:
		return SuccessColor;

	case EState::FAILURE:
		return FailureColor;

	case EState::ACTIVE:
		return ActiveColor;

	case EState::DISACTIVE:
		return DisactiveColor;
	}
	return DisactiveColor;
}
