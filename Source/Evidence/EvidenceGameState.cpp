// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceGameState.h"
#include "Items/Equipment.h"

TSubclassOf<AEquipment> AEvidenceGameState::GetEquipmentClass(const EEquipmentID ID) const
{
	if (ID_To_Class.Contains(ID))
	{
		return ID_To_Class[ID];
	}
	return nullptr;
}

EEquipmentID AEvidenceGameState::GetEquipmentID(const TSubclassOf<AEquipment> Class) const
{
	if (Class_To_ID.Contains(Class))
	{
		return Class_To_ID[Class];
	}
	return EEquipmentID::Empty;
}
