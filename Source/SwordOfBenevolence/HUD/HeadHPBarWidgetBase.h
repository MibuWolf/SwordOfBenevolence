#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Ability/Attribute/ObjectAttribute.h"
#include "HeadHPBarWidgetBase.generated.h"

class  AGameObject;

/**
 *
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UHeadHPBarWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:

	// 初始化头顶血条拥有者
	void			Initialization(AGameObject* pOwner);

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
	void SetName(const FString& NewName);

protected:

	void OnLevelChanged(const int32& oldLevel, const int32& newLevel);

	void OnNameChanged(const FString& oldName, const FString& newName);

	void OnHPChanged(const FOnAttributeChangeData& CallbackData);

	void OnMaxHPChanged(const FOnAttributeChangeData& CallbackData);

	void OnMPChanged(const FOnAttributeChangeData& CallbackData);

	void OnMaxMPChanged(const FOnAttributeChangeData& CallbackData);

protected:

	AGameObject*			Owner;

	FDelegateHandle HPEventHandle;
	FDelegateHandle MaxHPEventHandle;
	FDelegateHandle MPEventHandle;
	FDelegateHandle MaxMPEventHandle;
	FDelegateHandle LevelHandle;
	FDelegateHandle NameHandle;

};
