// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterController.h"
#include "SoldierController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ASoldierController : public ACharacterController
{
	GENERATED_BODY()
private:
	ASoldierController();

protected:
	TSubclassOf<UUserWidget> m_CursorAimWidgetClass;
	UCrosshairWidget* m_CursorAimWidget;

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* ShootingMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Aim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float TurnSpeed;

private:
	float m_CurCriticalValue;
	float m_CriticalPercent;
	float RemainLineStopTime;
	
public:
	void PullCriticalLine(float _Degree);
	void SetCriticalPercent(float _Percent);
	float GetCriticalPercent() { return m_CriticalPercent; }
	bool IsCriticalFire();
	void EmphasizeCritical();
	void StopRotationLine(float _Time);
	void SetRounds(int _Rounds);

protected:
	virtual void BeginPlay();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

private:
	void Fire(const FInputActionInstance& _Instance);
	void Aim(const FInputActionInstance& _Instance);
	void Reload(const FInputActionInstance& _Instance);
	void Action(const FInputActionInstance& _Instance);
};
