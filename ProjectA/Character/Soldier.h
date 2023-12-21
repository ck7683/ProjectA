// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "../Weapon/Weapon_Base.h"
#include "Soldier_AnimInstance.h"
#include "Soldier.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API ASoldier : public ACharacter_Base
{
	GENERATED_BODY()
public:
	ASoldier();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* m_Cam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* m_Arm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TArray<TSubclassOf<AWeapon_Base>> Weapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TArray<AWeapon_Base*> UseWeapon;

private:
	bool IsAim;
	int UseWeaponIdx;

public:
	bool GetIsAim() { return IsAim; }

protected:
	virtual float GetCurrentMaxSpeed() override;

public:
	void FireOrder(FVector targetLocation);
	void ReloadOrder();
	void Aim(bool IsInputAim);
	void FireReaction();
	void ReloadReaction();
};
