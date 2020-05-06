// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"
#include "../../Ability/AbilityInputID.h"
#include "../../GamePlay/SOBGameInstance.h"
#include "../../DataTable/AttributeTableData.h"
#include "../../DataTable/CharacterLevelTableData.h"
// Sets default values
AGamePlayer::AGamePlayer()
	:Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 默认绑定相机等组件（后面拆分主角/非主角）
	// 不响应Control的旋转，旋转由CharacterMovement控制
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	// 设置角色移动组件移动旋转相关参数
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// 添加相机手臂组件
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 300.0f;
	springArm->SocketOffset.Z = 50.0f;
	springArm->bUsePawnControlRotation = true;

	// 添加相机组件
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
	camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	// 注册侦听覆盖进入回调
	UCapsuleComponent* pCapsule = GetCapsuleComponent();

	if (pCapsule != nullptr)
	{
		pCapsule->OnComponentBeginOverlap.AddDynamic(this, &AGamePlayer::OnBeginOverlap);
	}

	AGamePlayerController *playerController = Cast <AGamePlayerController>(GetController());

	if (playerController != nullptr)
	{
		playerController->SetActionOperationMode(false);
	}

	SetLevel(Level);
}

// Called every frame
void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
		FString("CancelTarget"), FString("EAbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
}

void AGamePlayer::StopJumping()
{
	if (JumpCurrentCount >= JumpMaxCount)
		Super::StopJumping();
}

void AGamePlayer::OnBeginOverlap(UPrimitiveComponent * hitComponet, AActor * otherActor, UPrimitiveComponent * otherComponet, int32 otherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (otherActor == nullptr)
		return;

	if (otherActor->ActorHasTag(TEXT("GameItem")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided with GameItem"));
	}
}

void AGamePlayer::SetLevel(int32 level)
{
	int32 oldLevel = Level;
	Super::SetLevel(level);

	UpdateBasicAttribute();

	LevelChangedHandle.Broadcast(oldLevel, Level);
}

void AGamePlayer::UpdateBasicAttribute()
{
	UWorld* pWorld = GetWorld();
	if (!pWorld)
		return;

	USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

	if (pGameInstance == nullptr || Attribute == nullptr)
		return;

	FString characterLevel = FString::FromInt(Level);
	FCharacterLevelTableData* pCharacterLevel = pGameInstance->GetCharacterLevelTableData(characterLevel);
	if (pCharacterLevel == nullptr)
		return;

	FAttributeTableData* pAttribute = pGameInstance->GetAttributeTableData(pCharacterLevel->AttributeID);
	if (pAttribute == nullptr)
		return;

	Attribute->MaxHp = pAttribute->MaxHp;
	Attribute->HP = pAttribute->MaxHp;
	Attribute->MaxMp = pAttribute->MaxMp;
	Attribute->MP = pAttribute->MaxMp;
	Attribute->ATK = pAttribute->ATK;
	Attribute->DEF = pAttribute->DEF;
	Attribute->CRT = pAttribute->CRT;
	Attribute->STR = pAttribute->STR;
	Attribute->VIT = pAttribute->VIT;
	Attribute->TEN = pAttribute->TEN;
	Attribute->AGI = pAttribute->AGI;
	Attribute->MGK = pAttribute->MGK;
	Attribute->RGS = pAttribute->RGS;
	Attribute->WIS = pAttribute->WIS;
	Attribute->SPT = pAttribute->SPT;
	Attribute->CTN = pAttribute->CTN;
	Attribute->SPD = pAttribute->SPD;
	Attribute->CON = pAttribute->CON;

	if (Attribute->CUREXP.GetBaseValue() >= Attribute->EXP.GetBaseValue())
	{
		Attribute->CUREXP.SetBaseValue(Attribute->CUREXP.GetBaseValue() - Attribute->EXP.GetBaseValue());
		Attribute->CUREXP.SetCurrentValue(Attribute->CUREXP.GetBaseValue() - Attribute->EXP.GetBaseValue());
	}
	Attribute->EXP = pAttribute->EXP;
}

