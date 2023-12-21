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
	// 소유 플레이어 알아내기
	ACharacter_Base* pPlayer = Cast<ACharacter_Base>(TryGetPawnOwner());
	if (!IsValid(pPlayer))
		return;

	// 발 위치 소켓의 시작지점과, 땅을 뚫고 내려간 위치, Trace 끝 지점
	FVector vSockStartPos = pPlayer->GetMesh()->GetSocketLocation(*_strSockName);
	FVector vSockEndPos = vSockStartPos + FVector(0.f, 0.f, -100.f);

	// 충돌 결과를 받을 Result 구조체
	FHitResult hitresult = {};

	// 충돌 옵션 설정 Parameter 구조체
	FCollisionQueryParams param = {};
	param.bReturnPhysicalMaterial = true;	// Trace 충돌 성공 시, 해당 물체의 물리재질 받아오기 옵션
	param.AddIgnoredActor(pPlayer);			// Trace 무시할 액터 등록

	// LineTrace 진행, ECC_GameTraceChannel6 는 Trace_Landscae 채널
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitresult, vSockStartPos, vSockEndPos, ECC_GameTraceChannel6, param);
	
	if (bHit && pPlayer->GetCharacterMovement()->Velocity.Length() > 300.f)
	{
		// 충돌 결과 물리재질을 UPhysicalMaterial_Landscape 로 캐스팅
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