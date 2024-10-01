// Fill out your copyright notice in the Description page of Project Settings.


#include "EvidenceLobbyMenu.h"
#include "Components/Button.h"

void UEvidenceLobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (LoadButton)
	{
		LoadButton->OnClicked.AddDynamic(this, &ThisClass::LoadButtonClicked);
	}
}

void UEvidenceLobbyMenu::LoadButtonClicked()
{
}
