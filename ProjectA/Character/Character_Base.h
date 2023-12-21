// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EngineMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Data/CharacterStatData.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

#include "Character_Base.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HP")
	float MaxHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HP")
	float CurHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed")
	float SprintSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Speed")
	float WalkSpeed;
};


UCLASS()
class PROJECTA_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ACharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmHpBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HpBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (RowType = "Stat", AllowPrivateAccess = "true"))
	FCharacterStat CharacterStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (RowType = "CharacterStat", AllowPrivateAccess = "true"))
	FDataTableRowHandle		m_MonTableRow;

	bool IsSprint;
	bool StopSprint;
	FRotator LookRotator;

protected:
	virtual float GetCurrentMaxSpeed();

	UFUNCTION()
	void Damaged(AActor* who, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void PostDamaged(AActor* who, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	void Move(FVector dir);
	void Look(FVector LookLocation);
	void LookForward();
	void Sprint(bool IsSprintInput);
};
