// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Soldier_AnimInstance.generated.h"

class ASoldier;

UCLASS()
class PROJECTA_API USoldier_AnimInstance : public UCharacter_AnimInstance
{
	GENERATED_BODY()
public:
	USoldier_AnimInstance();

public:
	void PlayFire();
	void PlayReload();

public:
	UPROPERTY(EditAnywhere, Category = "Animation")
	TSoftObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference")
	ASoldier* Soldier;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool IsReload;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	bool IsAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	float FireBlend;

public:
	bool GetIsReload() { return IsReload; };

	UFUNCTION()
	void AnimNotify_Fire();

	UFUNCTION()
	void AnimNotify_FireEnd();

	UFUNCTION()
	void AnimNotify_ReloadEnd();


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDeltaTime) override;
};
