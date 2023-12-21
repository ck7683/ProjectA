// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"
#include "Weapon_Base.generated.h"

UCLASS()
class PROJECTA_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference")
	USkeletalMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference")
	USoundBase* m_AttSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reference")
	USoundCue* m_AttSoundCue;
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
