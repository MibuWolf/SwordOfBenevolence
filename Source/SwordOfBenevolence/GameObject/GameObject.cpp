// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"
#include "../GamePlay/SOBGameInstance.h"
// Sets default values
AGameObject::AGameObject()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	Attribute = CreateDefaultSubobject<UObjectAttribute>(TEXT("UObjectAttribute"));

	Dirction = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->AutoGiveAbilites();
	
		/*FString SkillTag = TEXT("Ability.Skill.Attacked.Normal");
		FGameplayTagContainer tagContainer;
		tagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(*SkillTag)));
		EventHandle = AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName(*SkillTag))).AddUObject(this, &AGameObject::OnGameplayTagCallback);*/
	}

	UWorld* const pWorld = GetWorld(); // get a reference to the world 
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


void AGameObject::OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	OnAttacked(InTag);
}

