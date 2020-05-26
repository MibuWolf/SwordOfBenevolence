#include "BirthPointObject.h"
#include "Kismet/GameplayStatics.h"


ABirthPointObject::ABirthPointObject()
	:Super()
{
	CurrentObject = nullptr;
	WaitTime = 1.0f;
	PrimaryActorTick.bCanEverTick = true;
}


void ABirthPointObject::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	if(AutoBirth && (AllPossibleObject.Num() == 0 || WaitTime <= 0.01))
		PrimaryActorTick.bCanEverTick = false;
}

void ABirthPointObject::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

}

bool ABirthPointObject::CheckAutoBirthNewObject()
{
	if(AllPossibleObject.Num() == 0 || !AutoBirth || CurrentObject != nullptr)
		return false;

	if (WaitTime < 0)
		return true;

	return false;
}

void ABirthPointObject::AutoSpwanGameObject(float DeltaTime)
{
	WaitTime -= DeltaTime;

	if (CheckAutoBirthNewObject())
	{
		WaitTime = CDTime;
		SpwanNewGameObject();
	}
}

void ABirthPointObject::SpwanNewGameObject()
{
	int32 percentage = FMath::FRandRange(0, 10000);

	for (auto& Pair : AllPossibleObject)
	{
		if (percentage <= Pair.Value)
		{
			UWorld* World = GetWorld();

			if (World)
			{
				FTransform tm = GetTransform();
				CurrentObject = World->SpawnActorDeferred<AGameObject>(Pair.Key, tm);
				CurrentObject->FinishSpawning(tm);
			}
			return;
		}
	}
}

void ABirthPointObject::Tick(float DeltaTime)
{
	AutoSpwanGameObject(DeltaTime);
}
