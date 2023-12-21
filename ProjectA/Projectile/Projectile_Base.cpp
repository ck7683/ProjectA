// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Base.h"
#include <Kismet/GameplayStatics.h>
#include "../Damage/DamageType_PointCritical.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	m_PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	m_NC = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	SetRootComponent(m_Sphere);
	m_PSC->SetupAttachment(m_Sphere);
	m_NC->SetupAttachment(m_Sphere);
	m_Mesh->SetupAttachment(m_Sphere);
	// ----
	m_ProjtileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	m_Sphere->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnHit);
	m_Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile_Base::BeginOverlap);
	m_Sphere->OnComponentEndOverlap.AddDynamic(this, &AProjectile_Base::EndOverlap);
	SetLifeSpan(5.f);
	
}

// Called every frame
void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_Base::Init(const FProjectileInfo& _info)
{
	m_Info = _info;
	m_ProjtileMovement->MaxSpeed = m_Info.Speed;
	FVector vDirection = m_Info.Direction;
	vDirection.Normalize();
	float cx = UKismetMathLibrary::RandomFloatInRange(-m_Info.Moa / 100, m_Info.Moa / 100);
	float cy = UKismetMathLibrary::RandomFloatInRange(-m_Info.Moa / 100, m_Info.Moa / 100);
	float cz = UKismetMathLibrary::RandomFloatInRange(-m_Info.Moa / 100, m_Info.Moa / 100);

	vDirection.X += cx;
	vDirection.Y += cy;
	vDirection.Z += cz;
	vDirection.Normalize();

	m_ProjtileMovement->Velocity = vDirection * m_Info.Speed;

	FString ProjectilePresetString = FString::Printf(TEXT("Team%dProjectile"), m_Info.Team);
	m_Sphere->SetCollisionProfileName(*ProjectilePresetString);
}

void AProjectile_Base::OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, FVector _vNormalImpulse, const FHitResult& _Hit)
{
	Destroy();
}

void AProjectile_Base::BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult)
{
	if (m_Info.bCritical) {
		UGameplayStatics::ApplyDamage(_OtherActor, m_Info.Damage, nullptr, nullptr, UDamageType_PointCritical::StaticClass());
	} else {
		UGameplayStatics::ApplyDamage(_OtherActor, m_Info.Damage, nullptr, nullptr, NULL);
	}
	Destroy();
}

void AProjectile_Base::EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom, int32 _Index)
{
	UE_LOG(LogTemp, Warning, TEXT("EndOverlap"));
}

