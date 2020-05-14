// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"
#include "../../Ability/AbilityInputID.h"
#include "../../DataTable/BaseAttributeTableData.h"
#include "../../DataTable/GameAttributeTableData.h"
#include "../../DataTable/CharacterLevelTableData.h"
#include "../../Ability/Attribute/PlayerAttribute.h"
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

	Attribute = CreateDefaultSubobject<UPlayerAttribute>(TEXT("UPlayerAttribute"));
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

	InitPlayerAttribute();
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

	UPlayerAttribute* playerAttribute = Cast<UPlayerAttribute>(Attribute);

	if (playerAttribute)
		playerAttribute->InitializeByPlayerLevel(level);

	LevelChangedHandle.Broadcast(oldLevel, Level);
}

void AGamePlayer::InitPlayerAttribute()
{
	UPlayerAttribute* playerAttribute = Cast<UPlayerAttribute>(Attribute);

	if (playerAttribute)
	{
		playerAttribute->InitializeByPlayerLevel(Level);

		AttributeChangedHandle.Broadcast(Attribute->GetHPAttribute(), 0.0f, Attribute->GetHP());
		AttributeChangedHandle.Broadcast(Attribute->GetMaxHpAttribute(), 0.0f, Attribute->GetMaxHp());
		AttributeChangedHandle.Broadcast(Attribute->GetMPAttribute(), 0.0f, Attribute->GetMP());
		AttributeChangedHandle.Broadcast(Attribute->GetMaxMpAttribute(), 0.0f, Attribute->GetMaxMp());
		AttributeChangedHandle.Broadcast(Attribute->GetATKAttribute(), 0.0f, Attribute->GetATK());
		AttributeChangedHandle.Broadcast(Attribute->GetDEFAttribute(), 0.0f, Attribute->GetDEF());
		AttributeChangedHandle.Broadcast(Attribute->GetCRTAttribute(), 0.0f, Attribute->GetCRT());
		AttributeChangedHandle.Broadcast(Attribute->GetCHDAttribute(), 0.0f, Attribute->GetCHD());
		AttributeChangedHandle.Broadcast(Attribute->GetMGKAttribute(), 0.0f, Attribute->GetMGK());
		AttributeChangedHandle.Broadcast(Attribute->GetMCRAttribute(), 0.0f, Attribute->GetMCR());
		AttributeChangedHandle.Broadcast(Attribute->GetRGSAttribute(), 0.0f, Attribute->GetRGS());
		AttributeChangedHandle.Broadcast(Attribute->GetMCDAttribute(), 0.0f, Attribute->GetMCD());
		AttributeChangedHandle.Broadcast(Attribute->GetSPDAttribute(), 0.0f, Attribute->GetSPD());
		AttributeChangedHandle.Broadcast(Attribute->GetATSAttribute(), 0.0f, Attribute->GetATS());
		AttributeChangedHandle.Broadcast(Attribute->GetEXPAttribute(), 0.0f, 0.0f);
		AttributeChangedHandle.Broadcast(Attribute->GetMAXEXPAttribute(), 0.0f, Attribute->GetMAXEXP());
	}
}

