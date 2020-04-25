// Fill out your copyright notice in the Description page of Project Settings.


#include "GameEquip.h"
#include "../GameObject/GameObject.h"

AGameEquip::AGameEquip()
	:Super()
{

}

EEquipType AGameEquip::GetEquipType()
{
	return EquipType;
}

FName AGameEquip::GetSocketName()
{
	switch (EquipType)
	{
	case EEquipType::Hair:
		return "";
	case EEquipType::Breastplate:
		return "";
	case EEquipType::Pants:
		return "";
	case EEquipType::Shoes:
		return "";
	case EEquipType::MainWeapon:
		return "R-WeaponSocket";
	case EEquipType::SubWeapon:
		return "L-WeaponSocket";
	}
	return "";
}

FAttachmentTransformRules AGameEquip::GetAttachmentRules()
{
	return FAttachmentTransformRules(LocationRule, RotationRule, ScaleRule, bWeldSimulatedBodies);
}

UObjectAttribute * AGameEquip::GetAttribute()
{
	return Attribute;
}

void AGameEquip::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Collided with GameItem"));
}
