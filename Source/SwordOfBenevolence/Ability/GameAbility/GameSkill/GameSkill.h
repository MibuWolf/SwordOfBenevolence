#pragma once

#include "CoreMinimal.h"
#include "../GameAbility.h"
#include "GameSkill.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UGameSkill : public UGameAbility
{
	GENERATED_BODY()
	
public:

	UGameSkill();


public:


	// ���ؼ���ܷ���
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// ���ؽ�������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	// ��������
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:

	// ���õ�ǰ���ܵȼ�
	virtual void		SetLevel(int32 lv);


protected:

	bool	StopMontage();

	void	UpdateAttribute();

public:

	/**Skill Montage that Skill is playing */
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	UAnimMontage*		MontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	FName	SectionName;

	bool	IsPlaying = false;

	float	PlayRate = 1.0f;
};
