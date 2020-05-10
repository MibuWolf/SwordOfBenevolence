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

	// ��ʼ��
	void		InitGameInstance(USOBGameInstance* instance);

	// ��ʾ����
	void		ShowView(FString ViewName);

	// ���ؽ�����ʾ
	void		HideView(FString ViewName);

	// ���ٽ���
	void		DestoryView(FString ViewName);

protected:

	TMap<FString, TSubclassOf<UViewBase>> AllViews;

	USOBGameInstance* pGameInstance;

};
