#include "AbilityComboNotify.h"
#include "../../GameAbilitySystemComponent.h"
#include "../../../GameObject/GameObject.h"


void UAbilityComboNotify::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (MeshComp == nullptr)
		return;

	AActor* Actor = MeshComp->GetOwner();

	if (Actor == nullptr || Actor->IsPendingKill())
		return;

	AGameObject* GameObject = Cast<AGameObject>(Actor);

	if (GameObject == nullptr)
		return;

	UGameAbilitySystemComponent* AbilitySystemComponent = Cast<UGameAbilitySystemComponent>(GameObject->GetAbilitySystemComponent());

	if (AbilitySystemComponent && !AbilitySystemComponent->IsPendingKill())
	{
		AbilitySystemComponent->SetAbilityResponseCombo(InputID, true);
	}
	else
	{
		ABILITY_LOG(Error, TEXT("UAbilitySystemBlueprintLibrary::SendGameplayEventToActor: Invalid ability system component retrieved from Actor %s"), *Actor->GetName());
	}
}

void UAbilityComboNotify::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{

}

void UAbilityComboNotify::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (MeshComp == nullptr)
		return;

	AActor* Actor = MeshComp->GetOwner();

	if (Actor == nullptr || Actor->IsPendingKill())
		return;

	AGameObject* GameObject = Cast<AGameObject>(Actor);

	if (GameObject == nullptr)
		return;

	UGameAbilitySystemComponent* AbilitySystemComponent = Cast<UGameAbilitySystemComponent>(GameObject->GetAbilitySystemComponent());

	if (AbilitySystemComponent && !AbilitySystemComponent->IsPendingKill())
	{
		AbilitySystemComponent->SetAbilityResponseCombo(InputID, false);
	}
	else
	{
		ABILITY_LOG(Error, TEXT("UAbilitySystemBlueprintLibrary::SendGameplayEventToActor: Invalid ability system component retrieved from Actor %s"), *Actor->GetName());
	}
}
