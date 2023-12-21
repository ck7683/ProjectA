// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "Projectile_Base.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FProjectileInfo {
	GENERATED_BODY()

	float Speed;
	FVector Direction;
	float Damage;
	int Team;
	bool bCritical;
	float Moa;
};

UCLASS()
class PROJECTA_API AProjectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Base();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comopnent")
	USphereComponent* m_Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comopnent")
	UProjectileMovementComponent* m_ProjtileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UParticleSystemComponent* m_PSC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNiagaraComponent* m_NC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* m_Mesh;

private:
	FProjectileInfo m_Info;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Init(const FProjectileInfo& info);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, FVector  _vNormalImpulse, const FHitResult& _Hit);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index, bool _bFromSweep, const FHitResult& _HitResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* _PrimitiveCom, AActor* _OtherActor, UPrimitiveComponent* _OtherPrimitiveCom
		, int32 _Index);
};
