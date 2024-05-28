// Fill out your copyright notice in the Description page of Project Settings.


#include "Tripod.h"
#include "Net/UnrealNetwork.h"

ATripod::ATripod()
{

}

void ATripod::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATripod, EmplacedEquipment);
	DOREPLIFETIME(ATripod, isPlaced);
}

void ATripod::Plant()
{
	isPlaced = true;
}

void ATripod::Pickup(AEvidenceCharacter* Char)
{
	Super::Pickup(Char);
	isPlaced = false;
}
