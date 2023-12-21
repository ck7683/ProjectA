// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "../Weapon/Rifle.h"
#include "Math/TransformNonVectorized.h"
#include "../PlayerController/SoldierController.h"

ASoldier::ASoldier()
	: IsAim(false)
	, UseWeaponIdx(-1)
{
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_Arm->SetupAttachment(GetCapsuleComponent());
	m_Cam->SetupAttachment(m_Arm);
}

void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	float WeaponCritical = 0.05f;
	if (Weapon.Num() > 0) {
		UseWeaponIdx = 0;

		FActorSpawnParameters param = {};
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		param.OverrideLevel = GetLevel();
		//param.bDeferConstruction = false;	// 지연생성(BeginPlay 호출 X)
		UseWeapon.Add(Cast<AWeapon_Base>(GetWorld()->SpawnActor(Weapon[0], (const FVector*)0, (const FRotator*)0, param)));
		FAttachmentTransformRules rule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
		UseWeapon[0]->AttachToComponent(GetMesh(), rule, FName(TEXT("AR4")));
	}

	if (ARifle* rifle = Cast<ARifle>(UseWeapon[0])) {
		if (ASoldierController* pController = Cast<ASoldierController>(GetController())) {
			pController->SetCriticalPercent(rifle->GetCritical());
			pController->SetRounds(rifle->GetRounds());
		}
	}
}

float ASoldier::GetCurrentMaxSpeed()
{
	bool IsReload = false;
	if (USoldier_AnimInstance* SoldierAnim = Cast<USoldier_AnimInstance>(GetMesh()->GetAnimInstance())) {
		IsReload = SoldierAnim->GetIsReload();
	}
	if (IsAim) {
		return 200.f;
	} else if (IsReload) {
		return 300.f;
	} else {
		return Super::GetCurrentMaxSpeed();
	}
}

void ASoldier::FireOrder(FVector targetLocation)
{
	if (IsAim) {
		if (ARifle* rifle = Cast<ARifle>(UseWeapon[0])) {
			if (USoldier_AnimInstance* SoldierAnim = Cast<USoldier_AnimInstance>(GetMesh()->GetAnimInstance())) {
				if (rifle->GetRounds() > 0) {
					SoldierAnim->PlayFire();
				}
				else {
					SoldierAnim->PlayReload();
				}
			}
		}
	}
}

void ASoldier::ReloadOrder()
{
	if (USoldier_AnimInstance* SoldierAnim = Cast<USoldier_AnimInstance>(GetMesh()->GetAnimInstance())) {
		SoldierAnim->PlayReload();
		GetCharacterMovement()->MaxWalkSpeed = GetCurrentMaxSpeed();
	}

}

void ASoldier::Aim(bool IsInputAim)
{
	IsAim = IsInputAim;
	StopSprint = IsAim;
	GetCharacterMovement()->MaxWalkSpeed = GetCurrentMaxSpeed();
}

void ASoldier::FireReaction()
{
	if (IsValid(UseWeapon[0])) {
		if (ARifle* rifle = Cast<ARifle>(UseWeapon[0])) {
			ASoldierController* pController = Cast<ASoldierController>(GetController());
			if (IsValid(pController)) {
				bool bCritical = pController->IsCriticalFire();
				auto tgLoc = pController->GetMouseCursorLocationOnWorld();
				tgLoc.Z += 50.f;
				bool isFired = rifle->Fire(tgLoc, bCritical);
				if (isFired) {
					pController->StopRotationLine(0.1f);
					pController->SetRounds(rifle->GetRounds());
					if (bCritical) {
						pController->EmphasizeCritical();
					}
				}
			}
		}
	}
}

void ASoldier::ReloadReaction()
{
	if (IsValid(UseWeapon[0])) {
		if (ARifle* rifle = Cast<ARifle>(UseWeapon[0])) {
			rifle->Reload();
			ASoldierController* pController = Cast<ASoldierController>(GetController());
			if (IsValid(pController)) {
				pController->SetRounds(rifle->GetRounds());
			}
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = GetCurrentMaxSpeed();
}
