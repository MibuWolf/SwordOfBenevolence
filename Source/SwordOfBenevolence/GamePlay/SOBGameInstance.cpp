#include "SOBGameInstance.h"


USOBGameInstance::USOBGameInstance()
{
	
}


void USOBGameInstance::Init()
{
	Super::Init();
	pUIViewManager = Cast<UUIManager>(UIViewManager.GetDefaultObject());

	if (pUIViewManager)
		pUIViewManager->InitGameInstance(this);
}

void USOBGameInstance::ShowUIView(FString ViewName)
{
	if (pUIViewManager)
		pUIViewManager->ShowView(ViewName);
}

void USOBGameInstance::HideUIView(FString ViewName)
{
	if (pUIViewManager)
		pUIViewManager->HideView(ViewName);
}

void USOBGameInstance::DestoryUIView(FString ViewName)
{
	if (pUIViewManager)
		pUIViewManager->DestoryView(ViewName);
}
