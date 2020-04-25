// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "GameItem.generated.h"

UCLASS()
class SWORDOFBENEVOLENCE_API AGameItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:

	/** ½ºÄÒÌå */
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent*	CapsuleComponent;

	/** Ä£ÐÍ */
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

};
