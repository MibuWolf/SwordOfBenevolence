// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystemComponent.h"
#include "../GamePlay/SOBGameInstance.h"
#include "../DataTable/SkillTableData.h"
#include "GameAbility/GameSkill/GameSkill.h"
#include "UObject/UObjectGlobals.h"

UGameAbilitySystemComponent::UGameAbilitySystemComponent()
{

}

void UGameAbilitySystemComponent::AutoGiveAbilites()
{
	AddSkill(10000);
	AddSkill(10001);
	AddSkill(10002);
	AddSkill(10003);
	AddSkill(10004);
	for (const TPair<int32, TSubclassOf<UGameAbility>>& Pair : AllPossibleAbilities)
	{
		UGameAbility* pAbility = Cast<UGameAbility>(Pair.Value.GetDefaultObject());
		if (pAbility->CanAutoGive())
		{
			GiveAbility(FGameplayAbilitySpec(Pair.Value, pAbility->GetSkillLevel(), int32(pAbility->GetAbilityInputID()), GetOwner()));
		}
	}

	// ³õÊ¼»¯±»»÷
	UGameplayAbility* pHitAbility = BeHitAbility.GetDefaultObject();
	if (pHitAbility != nullptr)
	{
		GiveAbility(FGameplayAbilitySpec(BeHitAbility, 1, -1, GetOwner()));
	}
}


void UGameAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
	// Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
	if (IsGenericConfirmInputBound(InputID))
	{
		LocalInputConfirm();
		return;
	}

	if (IsGenericCancelInputBound(InputID))
	{
		LocalInputCancel();
		return;
	}

	// ---------------------------------------------------------
	int32 count = 0;
	bool bCombo = false;

	if (!AbilityComboCount.Contains(EAbilityInputID(InputID)))
		AbilityComboCount.Add(EAbilityInputID(InputID), 0);

	if (ResponseCombo.Contains(EAbilityInputID(InputID)) && ResponseCombo[EAbilityInputID(InputID)])
	{
		AbilityComboCount[EAbilityInputID(InputID)] = AbilityComboCount[EAbilityInputID(InputID)] + 1;
		bCombo = true;

		int32 comboCount = GetAbilityCountByInputID(EAbilityInputID(InputID));
		if (AbilityComboCount[EAbilityInputID(InputID)] >= comboCount)
			AbilityComboCount[EAbilityInputID(InputID)] = 0;
	}

	ABILITYLIST_SCOPE_LOCK();
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.InputID == InputID)
		{
			if (count != AbilityComboCount[EAbilityInputID(InputID)])
			{
				count++;
				continue;
			}

			if (Spec.Ability)
			{
				Spec.InputPressed = true;
				if (Spec.IsActive())
				{
					if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
					{
						ServerSetInputPressed(Spec.Handle);
					}

					AbilitySpecInputPressed(Spec);

					// Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
				}
				else
				{
					if (!bCombo && count != 0)
					{
						AbilityComboCount[EAbilityInputID(InputID)] = 0;
						AbilityLocalInputPressed(InputID);
						return;
					}
					// Ability is not active, so try to activate it
					TryActivateAbility(Spec.Handle);
				}

				return;
			}
		}
	}
}

void UGameAbilitySystemComponent::SetAbilityResponseCombo(EAbilityInputID InputID, bool canResponse)
{
	if (!ResponseCombo.Contains(InputID))
		ResponseCombo.Add(InputID, canResponse);
	else
		ResponseCombo[InputID] = canResponse;
}

void UGameAbilitySystemComponent::AddSkill(int32 skillID)
{
	if (AllPossibleAbilities.Contains(skillID))
		return;

	UWorld* pWorld = GetWorld();
	if (!pWorld)
		return;

	USOBGameInstance* pGameInstance = Cast<USOBGameInstance>(pWorld->GetGameInstance());

	if (!pGameInstance)
		return;

	FString strSkillID = FString::FromInt(skillID);
	FSkillTableData* pSkillTable = pGameInstance->GetSkillTableData(strSkillID);

	if (!pSkillTable)
		return;

	FString skillPath = FString::Printf(TEXT("/Game/Characters/%s"), *(pSkillTable->SkillBlueprint));//"/Game/Characters/Blueprint/Ability/Warrior/NormalAttack/GA_NormalAttackA.GA_NormalAttackA_C";//pSkillTable->SkillBlueprint;  // TEXT("Blueprint'/Game/BluePrint/TestObj.TestObj'")
	UClass* loadObj = StaticLoadClass(UGameAbility::StaticClass(), NULL, *skillPath);
	if (loadObj != nullptr)
	{
		UGameAbility* pGameSkill = loadObj->GetDefaultObject <UGameAbility>();
		
		if (pGameSkill != nullptr)
		{
			AllPossibleAbilities.Add(skillID, pGameSkill->GetClass());

			if (pGameSkill->CanAutoGive())
			{
				GiveAbility(FGameplayAbilitySpec(pGameSkill, 1, int32(pGameSkill->GetAbilityInputID()), GetOwner()));
			}
			//UE_LOG(LogClass, Log, TEXT("Success"));
		}
	}
}

int32 UGameAbilitySystemComponent::GetAbilityCountByInputID(EAbilityInputID InputID)
{
	int32 count = 0;
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.InputID == (int32)InputID)
			count++;
	}

	return count;
}
