// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UI/CrosshairWidget.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//TSubclassOf<UUserWidget> m_CursorAimWidgetClass;
	//UCrosshairWidget* m_CursorAimWidget;
	
public:
	virtual void BeginPlay() override;

public:
	AMyGameModeBase();
	~AMyGameModeBase();
};
