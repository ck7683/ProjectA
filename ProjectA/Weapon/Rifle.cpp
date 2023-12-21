// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ARifle::ARifle()
	: Rounds(0)
	, m_FireParticle(nullptr)
	, Critical(.1f)
{
}

bool ARifle::Fire(FVector _TargetLocation, bool _bCritical)
{
	if (WaitingFireSecond >= 0 && Rounds > 0) {
		FVector MuzzleLocation = m_Mesh->GetSocketLocation(FName(TEXT("Muzzle")));
		FRotator MuzzleRotator = m_Mesh->GetSocketRotation(FName(TEXT("Muzzle")));
		FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(MuzzleLocation, _TargetLocation);

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(MuzzleLocation);

		if (IsValid(BulletType)) {
			FActorSpawnParameters param = {};
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			param.OverrideLevel = GetLevel();
			param.bDeferConstruction = true;	// 지연생성(BeginPlay 호출 X)

			FAttachmentTransformRules rule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);
			AProjectile_Base* bullet = Cast<AProjectile_Base>(GetWorld()->SpawnActor(BulletType, &MuzzleLocation, &MuzzleRotator, param));
			if (IsValid(bullet)) {
				FProjectileInfo info;
				info.Direction = Direction;
				info.Speed = 5000.f;
				float Rand = UKismetMathLibrary::RandomFloatInRange(0.8f, 1.2f);
				info.Damage = _bCritical ? Rand * Damage * 5 : Rand * Damage;
				info.bCritical = _bCritical;
				info.Moa = Moa;
				bullet->Init(info);
			}
			WaitingFireSecond = -FireRate;
			bullet->FinishSpawning(SpawnTransform);
			Rounds--;
		}

		if (IsValid(m_FireParticle)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_FireParticle, MuzzleLocation, MuzzleRotator, true);
		} else if (IsValid(m_FireNiagara)) {

		}

		if (IsValid(m_AttSoundCue)) {
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), m_AttSoundCue, MuzzleLocation);
		}
		return true;
	}
	return false;
}

#if WITH_EDITOR
void ARifle::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == TEXT("RPM")) {
		if (RPM < 1) RPM = 1;
		FireRate = 60.f / RPM;
	}
}
#endif

void ARifle::BeginPlay()
{
	Super::BeginPlay();
}

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	WaitingFireSecond += DeltaTime;
}
