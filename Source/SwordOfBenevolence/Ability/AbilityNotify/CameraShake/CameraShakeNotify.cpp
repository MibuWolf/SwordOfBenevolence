// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeNotify.h"
#include "Kismet/GameplayStatics.h"
#include "../../../GameObject/GameObject.h"


void UCameraShakeNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp == nullptr || GameraShake == nullptr)
		return;

	AActor* Actor = MeshComp->GetOwner();

	if (Actor == nullptr || Actor->IsPendingKill())
		return;

	UGameplayStatics::PlayWorldCameraShake(Actor, GameraShake, Actor->GetActorLocation(), InnerRadius, OuterRadius, Falloff, TowardsMesh);
}