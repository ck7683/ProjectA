// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTA_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* DamageTextBlock;

protected:
//	UDamageTextWidget();
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void SetText(float _Damage, bool _bCritical = true);
};
