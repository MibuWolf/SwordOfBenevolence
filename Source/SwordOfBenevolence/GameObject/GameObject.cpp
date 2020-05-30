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

	// ����/������ʼ��
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
	// ��װ��
	for (const TPair<EEquipType, TSubclassOf<AGameEquip>>& Pair : EquipTypes)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.bDeferConstruction = 1;  // �����첽��ԭ�����ڳ�������ʱBeginPlay�����µ�Actorͬ���ᵼ�����μ��ͬ��������ɼ���һ��ͬ��������󽫸�Actor�ӵ��������������ж��󼤻�ѭ���ֻἤ��һ�Σ�
		AGameEquip* pEquip = pWorld->SpawnActor<AGameEquip>(Pair.Value,FVector(), FRotator(), SpawnParams);
		if (pEquip != nullptr)
		{
			pEquip->AttachToComponent(GetMesh(), pEquip->GetAttachmentRules(), pEquip->GetSocketName());
			Equips.Add(Pair.Key, pEquip);
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
	AllAttributeChangeHandle.Add(EAttributeType::HP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MaxHp, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHpAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MaxMp, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxMpAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::ATK, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetATKAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::DEF, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetDEFAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::CRT, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetCRTAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::CHD, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetCHDAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MGK, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMGKAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MCR, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMCRAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::RGS, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetRGSAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MCD, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMCDAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::SPD, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetSPDAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::ATS, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetATSAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::EXP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetEXPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
	AllAttributeChangeHandle.Add(EAttributeType::MAXEXP, AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMAXEXPAttribute()).AddUObject(this, &AGameObject::OnAttributeChanged));
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

bool		AGameObject::IsDeath()
{
	if (Attribute == nullptr)
		return false;

	if (Attribute->GetHP() <= 0)
		return true;

	return false;
}


void AGameObject::OnAttributeChanged(const FOnAttributeChangeData & CallbackData)
{
	AttributeChangedHandle.Broadcast(CallbackData.Attribute, CallbackData.OldValue, CallbackData.NewValue);

	if (CallbackData.Attribute == Attribute->GetHPAttribute() && CallbackData.NewValue <= 0.0f)
	{
		OnDeath();
	}

}

void AGameObject::OnDeath()
{
}
