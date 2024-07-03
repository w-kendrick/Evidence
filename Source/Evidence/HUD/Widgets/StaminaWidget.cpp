// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Evidence/Character/EvidenceCharacter.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StaminaBar->SetPercent(1.f);
	StaminaText->SetText(FText::FromString(FString(TEXT("100"))));

	if (GetOwningPlayer())
	{
		if (GetOwningPlayer()->GetCharacter())
		{
			SetupDelegate(nullptr, GetOwningPlayer()->GetCharacter());
		}
		else
		{
			GetOwningPlayer()->OnPossessedPawnChanged.AddDynamic(this, &UStaminaWidget::SetupDelegate);
		}
	}
}

void UStaminaWidget::OnStaminaChanged(float NewStamina)
{
	if (!Char) return;

	StaminaBar->SetPercent(NewStamina / Char->GetMaxStamina());
	StaminaText->SetText(FText::FromString(FString::SanitizeFloat(NewStamina)));
}

void UStaminaWidget::SetupDelegate(APawn* OldPawn, APawn* NewPawn)
{
	Char = Cast<AEvidenceCharacter>(NewPawn);
	if (Char)
	{
		Char->StaminaDelegate.AddUObject(this, &ThisClass::OnStaminaChanged);
	}
}
