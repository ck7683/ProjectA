// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "../UI/MonsterHpBarWidget.h"

// Sets default values
ACharacter_Base::ACharacter_Base()
	: StopSprint(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmHpBar = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmHpBar"));
	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidget"));

	SpringArmHpBar->SetupAttachment(GetCapsuleComponent());
	SpringArmHpBar->bInheritPitch = false;
	SpringArmHpBar->bInheritRoll = false;
	SpringArmHpBar->bInheritYaw = false;
	HpBarWidget->SetupAttachment(SpringArmHpBar);
	HpBarWidget->SetDrawSize(FVector2D(100.f, 30.f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	this->OnTakeAnyDamage.AddDynamic(this, &ACharacter_Base::Damaged);
	GetCharacterMovement()->MaxWalkSpeed = GetCurrentMaxSpeed();
}

void ACharacter_Base::OnConstruction(const FTransform& Transform)
{

	// 데이터 테이블 안에서 몬스터 타입에 맞는 행 정보를 가져와서
	FCharacterStat* pInfo = nullptr;

	if (IsValid(m_MonTableRow.DataTable) && !m_MonTableRow.RowName.IsNone())
	{
		pInfo = m_MonTableRow.DataTable->FindRow<FCharacterStat>(m_MonTableRow.RowName, TEXT(""));

		// 몬스터의 m_Info 에 값을 넣어준다.
		if (nullptr != pInfo)
			CharacterStat = *pInfo;
	}
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACharacter_Base::GetCurrentMaxSpeed()
{
	if (IsSprint && !StopSprint) {
		return CharacterStat.SprintSpeed;
	} else {
		return CharacterStat.WalkSpeed;
	}
}

void ACharacter_Base::Move(FVector dir)
{
	GetCharacterMovement()->AddInputVector(dir);
}

void ACharacter_Base::Look(FVector LookLocation)
{
	if (!IsSprint || StopSprint) {
		LookRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookLocation);
		LookRotator.Pitch = LookRotator.Roll = 0;
	} else {
		LookForward();
	}
	SetActorRotation(LookRotator);
}

void ACharacter_Base::LookForward()
{
	FVector Velocity = GetCharacterMovement()->Velocity;
	FVector VelocityInWorld = GetActorRotation().UnrotateVector(Velocity);
	LookRotator = VelocityInWorld.Rotation();
	LookRotator.Pitch = LookRotator.Roll = 0;
}

void ACharacter_Base::Sprint(bool IsSprintInput)
{
	IsSprint = IsSprintInput;
	GetCharacterMovement()->MaxWalkSpeed = GetCurrentMaxSpeed();
}

void ACharacter_Base::Damaged(AActor* who, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CharacterStat.CurHp = CharacterStat.CurHp - Damage;
	if (CharacterStat.CurHp <= 0) {
		Destroy();
	}

	//m_Info.CurHP -= Damage;
	//UMonInfo_Base* pMonInfoWidget = Cast<UMonInfo_Base>((m_WidgetComponent->GetWidget()));
	//if (IsValid(pMonInfoWidget)) {
	//	pMonInfoWidget->SetHPRatio(m_Info.CurHP / m_Info.MaxHP);
	//}
	//if (m_State != EMON_STATE::DEAD) {
	//	FActorSpawnParameters param = {};
	//	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	param.OverrideLevel = GetLevel();
	//	param.bDeferConstruction = false;	// 지연생성(BeginPlay 호출 X)
	//	AFloatDamageHolder* uFloatDMG = GetWorld()->SpawnActor<AFloatDamageHolder>(m_FloatDamage, FVector(0, 0, 20), FRotator(), param);
	//	if (IsValid(uFloatDMG)) {
	//		uFloatDMG->SetDamage(Damage);
	//		FAttachmentTransformRules rule(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	//		uFloatDMG->AttachToComponent(GetCapsuleComponent(), rule);
	//		uFloatDMG->SetActorRelativeLocation(FVector(0, 0, 0));
	//	}
	//}
	//if (m_Info.CurHP <= 0) {
	//	GetMesh()->SetSimulatePhysics(true);
	//	AAIController* pAIController = Cast<AAIController>(GetController());
	//	if (IsValid(pAIController) && IsValid(pAIController->BrainComponent)) {
	//		pAIController->BrainComponent.Get()->StopLogic(FString(TEXT("Death")));
	//		pAIController->BrainComponent.Get()->Deactivate();
	//		pAIController->UnPossess();
	//		pAIController->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	//	}
	//	DetachFromControllerPendingDestroy();
	//	FTimerHandle timer;
	//	if (m_State != EMON_STATE::DEAD) {
	//		GetWorldTimerManager().SetTimer(timer, this, &AMonster_Base::Death, 1, true, 10);
	//		ChangeState(EMON_STATE::DEAD);
	//	}
	//}
	PostDamaged(who, Damage, DamageType, InstigatedBy, DamageCauser);
}

void ACharacter_Base::PostDamaged(AActor* who, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (UMonsterHpBarWidget* HpBarWidgetInst = Cast<UMonsterHpBarWidget>(HpBarWidget->GetWidget())) {
		if (CharacterStat.MaxHp != 0) {
			HpBarWidgetInst->SetHpPer(CharacterStat.CurHp / CharacterStat.MaxHp);
		} else {
			HpBarWidgetInst->SetHpPer(0);
		}
	}
}
