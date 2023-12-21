// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character_Base.h"
#include "behaviortree/BehaviorTree.h"
#include "behaviortree/blackboarddata.h"
#include "../../UI/DamageTextActor.h"
#include "Monster_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API AMonster_Base : public ACharacter_Base
{
	GENERATED_BODY()
public:
	AMonster_Base();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmDamageText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADamageTextActor> DamageTextActor;

protected:
	// 사용할 행동트리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_BehaviorTree;

	// 사용할 블랙보드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardData* m_Blackboard;

public:
	UFUNCTION(BlueprintCallable)
	virtual void PrintDamage(float _Damage, bool _bCritical);


	virtual void PostDamaged(AActor* who, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) override;
};
