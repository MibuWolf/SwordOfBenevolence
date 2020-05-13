// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "../GamePlay/SOBGameInstance.h"


void UUIManager::InitGameInstance(USOBGameInstance* instance)
{
	pGameInstance = instance;
}

void UUIManager::ShowView(FString ViewName)
{
	if (AllViews.Contains(ViewName))
	{
		UViewBase* pView = Cast<UViewBase>(AllViews[ViewName]);

		if (pView)
			pView->ShowView();
	}
	else
	{
		if (!pGameInstance)
			return;

		FUIViewTableData* pUIViewTable = pGameInstance->GetUIViewTableData(ViewName);

		if (!pUIViewTable)
			return;

		FString uiPath = FString::Printf(TEXT("/Game/HUD/%s"), *(pUIViewTable->Path));//"/Game/HUD/HUD_MainUI.HUD_MainUI_C";
		UClass* loadObj = StaticLoadClass(UViewBase::StaticClass(), NULL, *uiPath);
		if (loadObj != nullptr)
		{
			UViewBase* pUIView = CreateWidget<UViewBase>(pGameInstance, loadObj);

			if (pUIView != nullptr)
			{
				pUIView->InitView(ViewName, pUIViewTable->Layer);
			}
		}
	}
}

void UUIManager::HideView(FString ViewName)
{
	if (AllViews.Contains(ViewName))
	{
		UViewBase* pView = Cast<UViewBase>(AllViews[ViewName]);

		if (pView)
			pView->HideView();
	}
}

void UUIManager::DestoryView(FString ViewName)
{
	if (AllViews.Contains(ViewName))
	{
		UViewBase* pView = Cast<UViewBase>(AllViews[ViewName]);
		AllViews.Remove(ViewName);

		if (pView)
			pView->DestoryView();
	}
}
