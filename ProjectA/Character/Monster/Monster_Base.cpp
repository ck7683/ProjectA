// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"
#include "../../AI/AIController_Melee.h"
#include "../../Damage/DamageType_PointCritical.h"

AMonster_Base::AMonster_Base()
{
	// 빙의 방식 - 월드에 배치 or 스폰될 때
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 빙의할 컨트롤러 UClass
	AIControllerClass = AAIController_Melee::StaticClass();
	SpringArmDamageText = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmDamageText"));

	
	SpringArmDamageText->SetupAttachment(GetCapsuleComponent());
	SpringArmDamageText->bInheritPitch = false;
	SpringArmDamageText->bInheritRoll = false;
	SpringArmDamageText->bInheritYaw = false;

//	DamageTextWidget
}

void AMonster_Base::PrintDamage(float _Damage, bool _bCritical)
{
	if (IsValid(DamageTextActor)) {
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		param.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
		param.OverrideLevel = GetLevel();
		auto SpawnedDamageActor = Cast<ADamageTextActor>(GetWorld()->SpawnActor(DamageTextActor, (const FVector*)0, (const FRotator*)0, param));
		FAttachmentTransformRules rule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		SpawnedDamageActor->AttachToComponent(SpringArmDamageText, rule);
		SpawnedDamageActor->SetTextRandomLocation(_Damage, _bCritical, 0.5f, 50);
		FVector loc(0, 0, 0);
		SpawnedDamageActor->FinishSpawning(FTransform(loc));
	}
}

void AMonster_Base::PostDamaged(AActor* who, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::PostDamaged(who, Damage, DamageType, InstigatedBy, DamageCauser);
	if (Cast<UDamageType_PointCritical>(DamageType)) {
		PrintDamage(Damage, true);
	} else {
		PrintDamage(Damage, false);
	}
}
