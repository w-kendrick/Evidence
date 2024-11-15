// Fill out your copyright notice in the Description page of Project Settings.


#include "LockerSlotDragDropOperation.h"

void ULockerSlotDragDropOperation::SpawnInitialize(const uint8 NewIndex, ALocker* NewLocker, ULockerSlotWidget* Source)
{
	Index = NewIndex;
	Locker = NewLocker;
	WidgetSource = Source;
}
