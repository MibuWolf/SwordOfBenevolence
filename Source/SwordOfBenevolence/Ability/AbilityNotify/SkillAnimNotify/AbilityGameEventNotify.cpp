// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityGameEventNotify.h"
#include "../../../GameObject/GameObject.h"


void UAbilityGameEventNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp == nullptr)
		return;

	AActor* Actor = MeshComp->GetOwner();

	if (Actor == nullptr || Actor->IsPendingKill())
		return;

	AGameObject* GameObject = Cast<AGameObject>(Actor);

	if (GameObject == nullptr)
		return;

	UAbilitySystemComponent* AbilitySystemComponent = GameObject->GetAbilitySystemComponent();

	if (AbilitySystemComponent && !AbilitySystemComponent->IsPendingKill())
	{
		AbilitySystemComponent->HandleGameplayEvent(GameplayTag, &Payload);
	}
	else
	{
		ABILITY_LOG(Error, TEXT("UAbilitySystemBlueprintLibrary::SendGameplayEventToActor: Invalid ability system component retrieved from Actor %s. EventTag was %s"), *Actor->GetName(), *GameplayTag.ToString());
	}
}

