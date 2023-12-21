// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Styling/SlateColor.h"
#include "EscapeInfoWidget.generated.h"


UENUM(BlueprintType)
enum class EState : uint8
{
	SUCCESS,
	FAILURE,
	ACTIVE,
	DISACTIVE,
};

UENUM(BlueprintType)
enum class EEscapeType : uint8
{
	HELICOPTER,
	BATTLESHIP,
	SACRIFICE,
};


UCLASS()
class PROJECTA_API UEscapeInfoWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FSlateColor SuccessColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FSlateColor FailureColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FSlateColor ActiveColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color", meta = (AllowPrivateAccess = "true"))
	FSlateColor DisactiveColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Escape", meta = (AllowPrivateAccess = "true"))
	TArray<UTextBlock*> EscapeHelicopter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Escape", meta = (AllowPrivateAccess = "true"))
	TArray<UTextBlock*> EscapeBattleship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Escape", meta = (AllowPrivateAccess = "true"))
	TArray<UTextBlock*> Sacrifice;

public:
	UFUNCTION(BlueprintCallable)
	void ChangeState(EEscapeType MainId, int SubId, EState _State);

private:
	FSlateColor GetColor(EState _State);
};
