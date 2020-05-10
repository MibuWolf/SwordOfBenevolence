// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewBase.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

/**
 * 
 */
class USOBGameInstance;
UCLASS()
class SWORDOFBENEVOLENCE_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:

	// 初始化
	void		InitGameInstance(USOBGameInstance* instance);

	// 显示界面
	void		ShowView(FString ViewName);

	// 隐藏界面显示
	void		HideView(FString ViewName);

	// 销毁界面
	void		DestoryView(FString ViewName);

protected:

	TMap<FString, TSubclassOf<UViewBase>> AllViews;

	USOBGameInstance* pGameInstance;

};
