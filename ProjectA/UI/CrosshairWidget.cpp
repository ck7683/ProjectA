// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UCrosshairWidget::SetCriticalRange(float Degree) {
	if (Degree < 0) Degree = 0;
	if (Degree > 360) Degree = 360;
	if (IsValid(RangeMaterial)) {
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(RangeMaterial, this);
		DynMaterial->SetScalarParameterValue(FName(TEXT("StartDegree")), 180 - Degree / 2);
		DynMaterial->SetScalarParameterValue(FName(TEXT("DegreeSize")), Degree);
		m_CriticalRangeImg->SetBrushFromMaterial(DynMaterial);
	}
	
	if (IsValid(RangeLineMaterial)) {
		UMaterialInstanceDynamic* DynMaterial1 = UMaterialInstanceDynamic::Create(RangeLineMaterial, this);
		DynMaterial1->SetScalarParameterValue(FName(TEXT("StartDegree")), 180 - Degree / 2);
		m_RangeLine1->SetBrushFromMaterial(DynMaterial1);

		UMaterialInstanceDynamic* DynMaterial2 = UMaterialInstanceDynamic::Create(RangeLineMaterial, this);
		float RangeLineSize;
		RangeLineMaterial->GetScalarParameterValue(FHashedMaterialParameterInfo(FName(TEXT("DegreeSize"))), RangeLineSize);
		DynMaterial2->SetScalarParameterValue(FName(TEXT("StartDegree")), 180 + Degree / 2 - RangeLineSize);
		m_RangeLine2->SetBrushFromMaterial(DynMaterial2);
	}
}
void UCrosshairWidget::SetCriticalLine(float Degree) {
	CriticalLineDegree = Degree;
	m_CriticalLineImg->SetRenderTransformAngle(CriticalLineDegree);
}
void UCrosshairWidget::PullCriticalLine(float Degree) {
	CriticalLineDegree -= Degree;
}

void UCrosshairWidget::SetAlpha(float _Alpha)
{
	CurAlpha = _Alpha;
	if (IsValid(m_CriticalBackgroundImg)) m_CriticalBackgroundImg->SetOpacity(_Alpha);
	if (IsValid(m_CriticalRangeImg)) m_CriticalRangeImg->SetOpacity(_Alpha);
	if (IsValid(m_Border1)) m_Border1->SetOpacity(_Alpha);
	if (IsValid(m_Border2)) m_Border2->SetOpacity(_Alpha);
}

void UCrosshairWidget::SetLineAlpha(float _Alpha)
{
	if (IsValid(m_CriticalLineImg)) m_CriticalLineImg->SetOpacity(_Alpha);
	if (IsValid(m_RangeLine1)) m_RangeLine1->SetOpacity(_Alpha);
	if (IsValid(m_RangeLine2)) m_RangeLine2->SetOpacity(_Alpha);
}

void UCrosshairWidget::SetCursorActivate(bool _Activiate)
{
	SetAlpha(_Activiate ? ActivateAlpha : DisactivateAlpha);
	SetLineAlpha(_Activiate ? ActivateAlpha : LineDisactivateAlpha);
}

void UCrosshairWidget::EmphasizeCritical()
{
	if (IsValid(m_CriticalRangeImg)) {
		RemainEmphasizeTime = EmphasizeTime;
		bEmphasize = true;
		m_CriticalRangeImg->SetColorAndOpacity(FLinearColor(1.f, .5f, .5f));
	}
}

void UCrosshairWidget::SetRounds(int _Rounds)
{
	if (IsValid(m_Rounds)) {
		FString text = FString::Printf(TEXT("%d"), _Rounds);
		m_Rounds->SetText(FText::FromString(text));
	}
}

void UCrosshairWidget::NativeConstruct() {
	Super::NativeConstruct();
	m_CriticalBackgroundImg = Cast<UImage>(GetWidgetFromName(FName("CriticalBackground")));
	m_CriticalRangeImg = Cast<UImage>(GetWidgetFromName(FName("CriticalRange")));
	m_CriticalLineImg = Cast<UImage>(GetWidgetFromName(FName("CriticalLine")));
	m_RangeLine1 = Cast<UImage>(GetWidgetFromName(FName("CriticalRangeLine1")));
	m_RangeLine2 = Cast<UImage>(GetWidgetFromName(FName("CriticalRangeLine2")));
	m_Border1 = Cast<UImage>(GetWidgetFromName(FName("CriticalBackgroundBorder1")));
	m_Border2 = Cast<UImage>(GetWidgetFromName(FName("CriticalBackgroundBorder2")));
	m_Rounds = Cast<UTextBlock>(GetWidgetFromName(FName("Rounds")));
	SetCursorActivate(false);
}

void UCrosshairWidget::NativeTick(const FGeometry& _geo, float _DT) {
	Super::NativeTick(_geo, _DT);
	//CriticalLineDegree += _DT * 360;
	//CriticalLineDegree = FMath::Fmod(CriticalLineDegree, 360.f);
	//SetCriticalLine(CriticalLineDegree);
	if (bEmphasize) {
		RemainEmphasizeTime -= _DT;
		if (RemainEmphasizeTime < 0) {
			bEmphasize = false;
			m_CriticalRangeImg->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
		}
	}
}

void UCrosshairWidget::PostLoad()
{
	Super::PostLoad();
	SetCursorActivate(false);
}
