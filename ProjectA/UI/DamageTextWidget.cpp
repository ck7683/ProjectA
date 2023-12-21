// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextWidget.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/TextBlock.h"



void UDamageTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DamageTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("DamageText")));
}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageTextWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UDamageTextWidget::SetText(float _Damage, bool _bCritical)
{
	if (IsValid(DamageTextBlock)) {
		DamageTextBlock->SetText(UKismetTextLibrary::Conv_IntToText((int)_Damage));
		if (_bCritical) {
			auto font = DamageTextBlock->GetFont();
			font.Size = 18;
			DamageTextBlock->SetFont(font);
			FSlateColor orange(FColor(255, 72, 0, 255));
			DamageTextBlock->SetColorAndOpacity(orange);
		}
	}
}
