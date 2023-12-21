// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTextWidget.h"
#include "DamageTextActor.generated.h"

UCLASS()
class PROJECTA_API ADamageTextActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* DamageTextWidgetComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageTextWidget> DamageTextWidgetClass;

public:	
	// Sets default values for this actor's properties
	ADamageTextActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetTextRandomLocation(float _Damage, bool _bCritical, float _LifeTime, float Range);
	void SetText(float _Damage, bool _bCritical, float _LifeTime, FVector _RelativeLocation);

};
