// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "Components/Button.h"
#include "Evidence/Character/Components/InventoryComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UInventorySlotWidget::ButtonLeftClicked()
{
	AActor* const CharActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CharActor, FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.EquipFromInventory"))), Payload);
}

void UInventorySlotWidget::ButtonRightClicked()
{
	AActor* const CharActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FGameplayAbilityTargetData_SingleTargetHit* const Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult.FaceIndex = Index;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	FGameplayEventData Payload;
	Payload.TargetData = Handle;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CharActor, FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.DropFromInventory"))), Payload);
}

void UInventorySlotWidget::SpawnInitialize(UInventoryComponent* Comp, AEquipment* NewEquipment, const uint8 InventoryIndex)
{
	InventoryComp = Comp;
	Equipment = NewEquipment;
	Index = InventoryIndex;
}
