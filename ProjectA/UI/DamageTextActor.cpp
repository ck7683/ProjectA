// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTextActor.h"
#include "Components/WidgetComponent.h"
#include "DamageTextWidget.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADamageTextActor::ADamageTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//	DamageTextWidget = CreateDefaultSubobject<UDamageTextWidget>(TEXT("DamageText"));
	DamageTextWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageText"));
//	DamageTextWidgetComponent->SetupAttachment(GetRootComponent());
	SetRootComponent(DamageTextWidgetComponent);
}

// Called when the game starts or when spawned
void ADamageTextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageTextActor::SetTextRandomLocation(float _Damage, bool _bCritical, float _LifeTime, float Range)
{
	float x = UKismetMathLibrary::RandomFloatInRange(-Range, Range);
	float y = UKismetMathLibrary::RandomFloatInRange(-Range, Range);
	FVector loc(x, y, 0);
	SetText(_Damage, _bCritical, _LifeTime, loc);
}

void ADamageTextActor::SetText(float _Damage, bool _bCritical, float _LifeTime, FVector _RelativeLocation)
{
	if(IsValid(DamageTextWidgetClass)) {
		UDamageTextWidget* DamageTextWidget = Cast<UDamageTextWidget>(CreateWidget(GetWorld(), DamageTextWidgetClass));
		if (IsValid(DamageTextWidget)) {
			DamageTextWidgetComponent->SetWidget(DamageTextWidget);
			DamageTextWidget->SetText(_Damage, _bCritical);
		}
	}
	SetActorRelativeLocation(_RelativeLocation);
	SetLifeSpan(_LifeTime);
}

