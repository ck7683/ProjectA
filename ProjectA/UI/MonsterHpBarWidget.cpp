// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHpBarWidget.h"
#include "Components/ProgressBar.h"


void UMonsterHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CurHpPer = CurBackHpPer = 1.f;
	InterpSpeed = 5.f;
	m_HpBar = Cast<UProgressBar>(GetWidgetFromName(FName("HpBar")));
	m_BackHpBar = Cast<UProgressBar>(GetWidgetFromName(FName("BackHpBar")));
	if (IsValid(m_HpBar)) {
		SetHpPer(CurHpPer);
	}
	if (IsValid(m_BackHpBar)) {
		SetBackHpPer(CurBackHpPer);
	}

}

void UMonsterHpBarWidget::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
	if (CurBackHpPer != CurHpPer) {
		float NextPercent = FMath::FInterpTo(CurBackHpPer, CurHpPer, _DT, InterpSpeed);
		SetBackHpPer(NextPercent);
	}
}

void UMonsterHpBarWidget::SetHpPer(float _Percent)
{
	if (_Percent < 0.f) _Percent = 0.f;
	else if (_Percent > 1.f) _Percent = 1.f;
	CurHpPer = _Percent;
	if (IsValid(m_HpBar)) {
		m_HpBar->SetPercent(CurHpPer);
	}
}

void UMonsterHpBarWidget::SetBackHpPer(float _Percent)
{
	if (_Percent < 0.f) _Percent = 0.f;
	else if (_Percent > 1.f) _Percent = 1.f;
	CurBackHpPer = _Percent;
	if (IsValid(m_BackHpBar)) {
		m_BackHpBar->SetPercent(CurBackHpPer);
	}
}
