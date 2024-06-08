// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentBenchWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Evidence/Character/EvidenceCharacter.h"
#include "Evidence/Items/Equipment.h"
#include "AttachmentWidget.h"
#include "Components/VerticalBox.h"

void UAttachmentBenchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AEvidenceCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Character)
	{
		CurrentEquipment = Character->GetEquipped();

		if (CurrentEquipment)
		{
			const TMap<EAttachmentType, UAttachmentComponent*>& Attachments = CurrentEquipment->GetAttachments();

			for (const TPair<EAttachmentType, UAttachmentComponent*>& Elem : Attachments)
			{
				UAttachmentWidget* const Widget = CreateWidget<UAttachmentWidget>(this, AttachmentWidgetClass);

				if (Widget)
				{
					Widget->SpawnInitialize(Elem.Key, Elem.Value);
					AttachmentBox->AddChild(Widget);
				}
			}
		}
	}
}
