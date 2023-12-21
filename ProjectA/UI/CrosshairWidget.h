// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Character/Soldier.h"
#include "CrosshairWidget.generated.h"


UCLASS()
class PROJECTA_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* RangeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* RangeLineMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	float ActivateAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	float DisactivateAlpha;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = "true"))
	float LineDisactivateAlpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	float CriticalRangeSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	float CriticalLineDegree;

	class UImage* m_CriticalBackgroundImg;
	class UImage* m_CriticalRangeImg;
	class UImage* m_CriticalLineImg;
	class UImage* m_Border1;
	class UImage* m_Border2;
	class UImage* m_RangeLine1;
	class UImage* m_RangeLine2;
	class UTextBlock* m_Rounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	float EmphasizeTime;

	bool bEmphasize;
	float RemainEmphasizeTime;
	float CurAlpha;
public:
	UFUNCTION(BlueprintCallable)
	void SetCriticalRange(float Degree);
	
	UFUNCTION(BlueprintCallable)
	void SetCriticalLine(float Degree);

	UFUNCTION(BlueprintCallable)
	void PullCriticalLine(float Degree);

	void SetAlpha(float _Alpha);
	void SetLineAlpha(float _Alpha);
	void SetCursorActivate(bool _Activiate);
	void EmphasizeCritical();
	void SetRounds(int _Rounds);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
	virtual void PostLoad() override;
};
