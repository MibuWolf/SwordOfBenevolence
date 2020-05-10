#pragma once
#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "CostExecutionCalculation.generated.h"


/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UCostExecutionCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UCostExecutionCalculation();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
