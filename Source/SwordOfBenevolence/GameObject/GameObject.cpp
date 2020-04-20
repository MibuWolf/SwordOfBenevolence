// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"

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
	HPPercent = 100.0f;
	Buff_NoMove = 0;
	IsSkill = false;
}

// Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->AutoGiveAbilites();
	
		FString SkillTag = TEXT("Ability.Skill.Attacked.Normal");
		FGameplayTagContainer tagContainer;
		tagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName(*SkillTag)));
		EventHandle = AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName(*SkillTag))).AddUObject(this, &AGameObject::OnGameplayTagCallback);
	}
}

void AGameObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AbilitySystemComponent && EventHandle.IsValid())
	{
		FString SkillTag = TEXT("Ability.Skill.Attacked.Normal");
		AbilitySystemComponent->UnregisterGameplayTagEvent(EventHandle, FGameplayTag::RequestGameplayTag(FName(*SkillTag)));
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

float AGameObject::GetHPPercent()
{
	return HPPercent;
}

void AGameObject::SetHPPercent(float Value)
{
	HPPercent = Value;
}

int32 AGameObject::GetBuffNoMove()
{
	return Buff_NoMove;
}

void AGameObject::SetBuffNoMove(int32 Value)
{
	Buff_NoMove = Value;
}

bool AGameObject::IsInSkill()
{
	return IsSkill;
}

void AGameObject::SetInSkill(bool Value)
{
	IsSkill = Value;
}


void AGameObject::OnGameplayTagCallback(const FGameplayTag InTag, int32 NewCount)
{
	OnAttacked(InTag);
}

