// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitForDamageEventTask.generated.h"

class UGameAbilitySystemComponent;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitForDamageEventDelegate, const FGameplayTag&, EventTag, AActor*, SourceActor);

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UWaitForDamageEventTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	// Constructor and overrides
	UWaitForDamageEventTask(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;

	virtual void OnDestroy(bool AbilityEnded) override;

	UFUNCTION()
	void OnDamageReceived(const FGameplayTag& HitTag, AActor* SourceActor);

	// Wait until the ability owner receives damage.
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UWaitForDamageEventTask* WaitForDamageEvent(UGameplayAbility* OwningAbility);

public:

	UPROPERTY(BlueprintAssignable)
	FWaitForDamageEventDelegate	OnDamaged;

};
