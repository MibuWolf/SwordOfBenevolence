// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ViewBase.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API UViewBase : public UUserWidget
{
	GENERATED_BODY()

public:

	// 初始化View界面信息
	void			InitView(FString Name, int32 Layer, bool bAutoShow = true);

	// 显示界面
	void			ShowView();

	// 隐藏界面显示
	void			HideView();

	// 销毁界面
	void			DestoryView();

	// 获取当前界面显示状态
	bool			IsShow();


protected:

	bool			bShow = false;
	
	FString			ViewName;

	int32			UILayer;
};
