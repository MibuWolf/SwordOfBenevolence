#pragma once
#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 3 num 1
	Ability1		UMETA(DisplayName = "Ability1"),
	// 4 num 2
	Ability2		UMETA(DisplayName = "Ability2"),
	// 5 num 3
	Ability3		UMETA(DisplayName = "Ability3"),
	// 6 num 4
	Ability4		UMETA(DisplayName = "Ability4"),
	// 9 Jump
	Jump			UMETA(DisplayName = "Jump")
};