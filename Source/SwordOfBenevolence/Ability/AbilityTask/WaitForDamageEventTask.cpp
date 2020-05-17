#include "WaitForDamageEventTask.h"
#include "../GameAbilitySystemComponent.h"

UWaitForDamageEventTask::UWaitForDamageEventTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


void UWaitForDamageEventTask::Activate()
{
	UGameAbilitySystemComponent* GameAbilitySystem = Cast<UGameAbilitySystemComponent>(AbilitySystemComponent);

	if (GameAbilitySystem)
	{
		GameAbilitySystem->OnDamage.AddDynamic(this, &UWaitForDamageEventTask::OnDamageReceived);
	}
}

void UWaitForDamageEventTask::OnDamageReceived(const FGameplayTag & HitTag, AActor * SourceActor)
{
	OnDamaged.Broadcast(HitTag, SourceActor);
}

UWaitForDamageEventTask * UWaitForDamageEventTask::WaitForDamageEvent(UGameplayAbility * OwningAbility)
{
	UWaitForDamageEventTask* thisTask = NewAbilityTask<UWaitForDamageEventTask>(OwningAbility);

	return thisTask;
}

void UWaitForDamageEventTask::OnDestroy(bool AbilityIsEnding)
{
	UGameAbilitySystemComponent* GameAbilitySystem = Cast<UGameAbilitySystemComponent>(AbilitySystemComponent);

	if (GameAbilitySystem)
	{
		GameAbilitySystem->OnDamage.RemoveDynamic(this, &UWaitForDamageEventTask::OnDamageReceived);
	}
}
