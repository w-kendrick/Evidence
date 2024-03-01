// Fill out your copyright notice in the Description page of Project Settings.


#include "EnumLibrary.h"

FString UEnumLibrary::To_String(const EEquipmentID ID)
{
	switch (ID)
	{
	case EEquipmentID::Empty: return FString("Empty");
	case EEquipmentID::Test1: return FString("Test1");
	case EEquipmentID::Test2: return FString("Test2");
	case EEquipmentID::MAX:   return FString("MAX");
	default:				  return FString("Invalid");
	}
}
