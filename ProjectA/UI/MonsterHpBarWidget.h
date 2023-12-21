// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UMonsterHpBarWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	class UProgressBar* m_HpBar;
	class UProgressBar* m_BackHpBar;
	float CurHpPer;
	float CurBackHpPer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float InterpSpeed;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetHpPer(float _Percent);

	UFUNCTION(BlueprintCallable)
	void SetInterpSpeed(float _Speed) { InterpSpeed = _Speed; }

private:
	void SetBackHpPer(float _Percent);
};
