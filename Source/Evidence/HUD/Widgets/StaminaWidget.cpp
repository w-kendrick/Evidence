// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Character/EvidenceCharacter.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Char = Cast<AEvidenceCharacter>(GetOwningPlayerPawn());
	if (Char)
	{
		StaminaBar->SetPercent(1.f);
		StaminaText->SetText(FText::FromString(TEXT("100")));
		Char->StaminaDelegate.AddUObject(this, &ThisClass::OnStaminaChanged);
	}
}

void UStaminaWidget::OnStaminaChanged(float NewStamina)
{
	if (!Char) return;

	StaminaBar->SetPercent(NewStamina / Char->GetMaxStamina());
	StaminaText->SetText(FText::FromString(FString::SanitizeFloat(NewStamina)));
}
