// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewBase.h"


void UViewBase::InitView(FString Name, int32 Layer, bool bAutoShow)
{
	ViewName = Name;
	UILayer = Layer;

	if (bAutoShow)
		ShowView();
}

void UViewBase::ShowView()
{
	if(!bShow)
		AddToViewport(UILayer);

	bShow = true;
}

void UViewBase::HideView()
{
	if(bShow)
		RemoveFromViewport();

	bShow = false;
}

void UViewBase::DestoryView()
{

}

bool UViewBase::IsShow()
{
	return bShow;
}
