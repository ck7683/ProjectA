// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier_AnimInstance.h"
#include "Soldier.h"

USoldier_AnimInstance::USoldier_AnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> montage(TEXT("/Script/Engine.AnimMontage'/Game/Blueprints/Character/Soldier/AM_Fire.AM_Fire'"));
	if (montage.Succeeded())
	{
		FireMontage = montage.Object;
	}
}

void USoldier_AnimInstance::PlayFire()
{
	if (!FireMontage.IsNull() && !IsReload) {
		Montage_Play(FireMontage.LoadSynchronous(), 1.f);
		Montage_JumpToSection(FName("Fire"), FireMontage.LoadSynchronous());
		FireBlend = 1.f;
	}
}

void USoldier_AnimInstance::PlayReload()
{
	if (!FireMontage.IsNull() && !IsReload) {
		IsReload = true;
		Montage_Play(FireMontage.LoadSynchronous(), 1.f);
		Montage_JumpToSection(FName("Reload"), FireMontage.LoadSynchronous());
		FireBlend = 1.f;
	}
}

void USoldier_AnimInstance::AnimNotify_Fire()
{
	Soldier->FireReaction();
}

void USoldier_AnimInstance::AnimNotify_FireEnd()
{
	FireBlend = 0.f;
}

void USoldier_AnimInstance::AnimNotify_ReloadEnd()
{
	IsReload = false;
	FireBlend = 0.f;
	Soldier->ReloadReaction();
}

void USoldier_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Soldier = Cast<ASoldier>(GetOwningActor());

}

void USoldier_AnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void USoldier_AnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{
	Super::NativeUpdateAnimation(_fDeltaTime);
	if(IsValid(Soldier)) {
		IsAim = Soldier->GetIsAim();
	}
}
