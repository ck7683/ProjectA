// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_AnimInstance.h"
#include "../PhysicalMaterial/PhysicalMaterial_Landscape.h"
#include "NiagaraFunctionLibrary.h"

void UCharacter_AnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ACharacter_Base>(GetOwningActor());
	if (IsValid(Character)) {
		Movement = Character->GetCharacterMovement();
	}
}

void UCharacter_AnimInstance::NativeBeginPlay()
{
}

void UCharacter_AnimInstance::NativeUpdateAnimation(float _fDeltaTime)
{

}

void UCharacter_AnimInstance::AnimNotify_LeftStep()
{
	PlayPhysicalBasedSound(TEXT("Foot_L"));
}

void UCharacter_AnimInstance::AnimNotify_RightStep()
{
	PlayPhysicalBasedSound(TEXT("Foot_R"));
}

void UCharacter_AnimInstance::PlayPhysicalBasedSound(const FString& _strSockName)
{
	// ���� �÷��̾� �˾Ƴ���
	ACharacter_Base* pPlayer = Cast<ACharacter_Base>(TryGetPawnOwner());
	if (!IsValid(pPlayer))
		return;

	// �� ��ġ ������ ����������, ���� �հ� ������ ��ġ, Trace �� ����
	FVector vSockStartPos = pPlayer->GetMesh()->GetSocketLocation(*_strSockName);
	FVector vSockEndPos = vSockStartPos + FVector(0.f, 0.f, -100.f);

	// �浹 ����� ���� Result ����ü
	FHitResult hitresult = {};

	// �浹 �ɼ� ���� Parameter ����ü
	FCollisionQueryParams param = {};
	param.bReturnPhysicalMaterial = true;	// Trace �浹 ���� ��, �ش� ��ü�� �������� �޾ƿ��� �ɼ�
	param.AddIgnoredActor(pPlayer);			// Trace ������ ���� ���

	// LineTrace ����, ECC_GameTraceChannel6 �� Trace_Landscae ä��
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitresult, vSockStartPos, vSockEndPos, ECC_GameTraceChannel6, param);
	
	if (bHit && pPlayer->GetCharacterMovement()->Velocity.Length() > 300.f)
	{
		// �浹 ��� ���������� UPhysicalMaterial_Landscape �� ĳ����
		UPhysicalMaterial_Landscape* pPMT = Cast<UPhysicalMaterial_Landscape>(hitresult.PhysMaterial);
		if (!IsValid(pPMT))
			return;

		//pPMT->GetParticle();
		//pPMT->GetNiagara();

		USoundBase* pSound = pPMT->GetSound();
		if (IsValid(pSound))
		{
			// hitresult.ImpactPoint;
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), pSound, vSockStartPos);
		}
		
		FVector scale(3.f, 3.f, 3.f);
		UParticleSystem* FX_Foot = pPMT->GetParticle();
		if (IsValid(FX_Foot)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX_Foot, hitresult.Location, Character->GetActorRotation(), true);
		} else {
			UNiagaraSystem* SFX_Foot = pPMT->GetNiagara();
			if (IsValid(SFX_Foot)) {
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SFX_Foot, hitresult.Location, Character->GetActorRotation(), scale);
			}

		}
	}
}