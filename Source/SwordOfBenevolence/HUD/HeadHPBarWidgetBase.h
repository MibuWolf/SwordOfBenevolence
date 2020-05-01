#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeadHPBarWidgetBase.generated.h"

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UHeadHPBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHP(float HP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHP(float MaxHP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentMP(float MP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxMP(float MaxMP);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetLevel(int Level);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetName(const FText& NewName);

};
