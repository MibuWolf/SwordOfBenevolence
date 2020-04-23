// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEquip.h"
#include "../GameObject/GameObject.h"

AGameEquip::AGameEquip()
	:Super()
{

}

void AGameEquip::BindGameObject(AGameObject * ownerObject)
{
	Owner = ownerObject;

	if (Owner != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(Owner);
		AttachToActor(TargetActor, FAttachmentTransformRules(LocationRule, RotationRule, ScaleRule, bWeldSimulatedBodies), SocketName);
	}
}

void AGameEquip::UnbindGameObject()
{
	if (Owner != nullptr)
	{
		AActor* TargetActor = Cast<AActor>(Owner);
		DetachFromActor(FDetachmentTransformRules(EDetachmentRule(), EDetachmentRule(), EDetachmentRule(), true));
	}
}

UObjectAttribute * AGameEquip::GetAttribute()
{
	return Attribute;
}

void AGameEquip::BeginPlay()
{
	BindGameObject(Owner);
}
