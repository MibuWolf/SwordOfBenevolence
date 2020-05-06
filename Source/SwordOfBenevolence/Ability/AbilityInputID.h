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
	// 3 mouse LClick
	Ability1		UMETA(DisplayName = "Ability1"),
	// 4 num 1
	Ability2		UMETA(DisplayName = "Ability2"),
	// 5 num 2
	Ability3		UMETA(DisplayName = "Ability3"),
	// 6 num 3
	Ability4		UMETA(DisplayName = "Ability4"),
	// 7 Q
	Ability5		UMETA(DisplayName = "Ability5"),
	// 8 E
	Ability6		UMETA(DisplayName = "Ability6"),
	// 9 R
	Ability7		UMETA(DisplayName = "Ability7"),
	// 10 F
	Ability8		UMETA(DisplayName = "Ability8"),
	// 9 Jump
	Jump			UMETA(DisplayName = "Jump")
};