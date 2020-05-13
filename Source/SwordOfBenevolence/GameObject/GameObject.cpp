// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"
#include "../GamePlay/SOBGameInstance.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameObject::AGameObject()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	//Attribute = CreateDefaultSubobject<UGDAttributeSetBase>(TEXT("UGDAttributeSetBase"));
	Attribute = CreateDefaultSubobject<UObjectAttribute>(TEXT("UObjectAttribute"));

	Dirction = FVector(0.0f, 0.0f, 0.0f);

	HUDComponent = CreateDefaultSubobject<UWidgetComponent>(FName("HUDComponent"));
	HUDComponent->SetupAttachment(RootComponent);
	HUDComponent->SetRelativeLocation(FVector(0, 0, 120));
	HUDComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HUDComponent->SetDrawAtDesiredSize(true);
	HUDComponent->SetDrawSize(FVector2D(200, 50));

}

// Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
	Super::BeginPlay();

	// 技能/能力初始化
	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->AutoGiveAbilites();
	
		/*FString SkillTag = TEXT("Ability.Skill.Attacked.Normal");
		FGameplayTagContainer tagContainer;
		tagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(*SkillTag)));
		EventHandle = AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName(*SkillTag))).AddUObject(this, &AGameObject::OnGameplayTagCallback);*/

		InitAllAttributeChangedHandle();
	}

	UWorld* pWorld = GetWorld(); // get a reference to the world 
	// 绑定装备
	for (const TPair<EEquipType, TSubclassOf<AGameEquip>>& Pair : EquipTypes)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bDeferConstruction = 1;  // 设置异步的原因是在场景激活时BeginPlay创建新的Actor同步会导致两次激活（同步加载完成激活一次同步加载完后将该Actor加到场景，场景所有对象激活循环又会激活一次）
		AGameEquip* pEquip = pWorld->SpawnActor<AGameEquip>(Pair.Value,FVector(), FRotator(), SpawnParams);
		if (pEquip != nullptr)
		{
			pEquip->AttachToComponent(GetMesh(), pEquip->GetAttachmentRules(), pEquip->GetSocketName());
			Equips.Add(Pair.Key, pEquip);
		}
	}

	// HUD初始化
	if (HeadHPBarClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		HeadHPBar = CreateWidget<UHeadHPBarWidgetBase>(PC, HeadHPBarClass, "HeadHPBarWidgetBase");

		if (HeadHPBar)
		{
			HeadHPBar->Initialization(this);
			HUDComponent->SetWidget(HeadHPBar);
		}
	}

	SetLevel(Level);

}

void AGameObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AbilitySystemComponent && EventHandle.IsValid())
	{
		/*FString SkillTag = TEXT("Ability.Skill.Attacked.Normal");
		AbilitySystemComponent->UnregisterGameplayTagEvent(EventHandle, FGameplayTag::RequestGameplayTag(FName(*SkillTag)));*/
	}
}

// Called every frame
void AGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UObjectAttribute * AGameObject::GetAttribute()
{
	return Attribute;
}

UAbilitySystemComponent * AGameObject::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AGameObject::GetDirction()
{
	return Dirction;
}

void AGameObject::SetDirctionX(float Value)
{
	Dirction.X = Value;
}

void AGameObject::SetDirctionY(float Value)
{
	Dirction.Y = Value;
}

void AGameObject::WearEquip(AGameEquip * pEquip)
{
	if (pEquip == nullptr)
		return;

	EEquipType type = pEquip->GetEquipType();

	TakeOffEquip(type);
	
	pEquip->AttachToComponent(GetMesh(), pEquip->GetAttachmentRules(), pEquip->GetSocketName());
}

void AGameObject::TakeOffEquip(EEquipType type)
{
	if (Equips.Contains(type))
	{
		AGameEquip * pEquip = Equips[type];
		Equips.Remove(type);

		if (pEquip != nullptr)
		{
			pEquip->DetachFromActor(FDetachmentTransformRules(EDetachmentRule(), EDetachmentRule(), EDetachmentRule(), true));
			pEquip->Destroy(true, true);
		}
	}
}

void AGameObject::InitAllAttributeChangedHandle()
{
	/*AllAttributeChangeHandle.Add(EAttributeType::HP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MaxHp, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHpAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MaxMp, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxMpAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::ATK, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetATKAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::DEF, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetDEFAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::CRT, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetCRTAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::STR, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetSTRAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::VIT, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetVITAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::TEN, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetTENAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::AGI, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetAGIAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MGK, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMGKAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MCR, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMCRAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::RGS, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetRGSAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::WIS, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetWISAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::SPT, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetSPTAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::CTN, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetCTNAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::SPD, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetSPDAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::CON, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetCONAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::EXP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetEXPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MAXEXP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMAXEXPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));*/
}

void AGameObject::OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	OnAttacked(InTag);
}


void		AGameObject::SetLevel(int32 level)
{
	Level = level;
}

int32		AGameObject::GetLevel()
{
	return Level;
}

void		AGameObject::SetName(FString NewName)
{
	FString oldName = Name;
	Name = NewName;

	NameChangedHandle.Broadcast(oldName, Name);
}

FString		AGameObject::GetName()
{
	return Name;
}


void AGameObject::OnAttributeChanged(const FOnAttributeChangeData & CallbackData)
{
	AttributeChangedHandle.Broadcast(CallbackData.Attribute, CallbackData.OldValue, CallbackData.NewValue);
}