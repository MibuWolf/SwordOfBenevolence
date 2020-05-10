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

	// ��ʼ��View������Ϣ
	void			InitView(FString Name, int32 Layer, bool bAutoShow = true);

	// ��ʾ����
	void			ShowView();

	// ���ؽ�����ʾ
	void			HideView();

	// ���ٽ���
	void			DestoryView();

	// ��ȡ��ǰ������ʾ״̬
	bool			IsShow();


protected:

	bool			bShow = false;
	
	FString			ViewName;

	int32			UILayer;
};
