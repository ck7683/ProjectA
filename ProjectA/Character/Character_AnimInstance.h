// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include <GameFramework/CharacterMovementComponent.h>
#include "Character_Base.h"

#include "Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UCharacter_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Reference")
	ACharacter_Base* Character;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Reference")
	UCharacterMovementComponent* Movement;
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDeltaTime) override;

public:
	UFUNCTION()
	void AnimNotify_LeftStep();

	UFUNCTION()
	void AnimNotify_RightStep();


	void PlayPhysicalBasedSound(const FString& _strSockName);

};
