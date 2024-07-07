// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Net/UnrealNetwork.h"
#include "Attachments/ExtendedMagazine.h"

AGun::AGun()
{
	EquipmentName = FString(TEXT("Gun"));
	MaxClipSize = 8;

	Attachments.Add(EAttachmentType::Underbarrel, nullptr);
	Attachments.Add(EAttachmentType::Scope, nullptr);
	Attachments.Add(EAttachmentType::Magazine, nullptr);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentClip(GetMaxClipSize());
}

void AGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGun, CurrentClip);
}

void AGun::OnRep_CurrentClip(const uint8 OldClip)
{
	OnAmmoChanged.Broadcast(CurrentClip);
}

void AGun::AddAmmoToClip(const uint8 Addition)
{
	SetCurrentClip(CurrentClip + Addition);
}

void AGun::SetCurrentClip(const uint8 NewClip)
{
	CurrentClip = FMath::Clamp(NewClip, 0, GetMaxClipSize());
	OnAmmoChanged.Broadcast(CurrentClip);
}

uint8 AGun::GetMaxClipSize() const
{
	const AExtendedMagazine* const ExtendedMagazine = Cast<AExtendedMagazine>(GetAttachment(EAttachmentType::Magazine));

	if (ExtendedMagazine)
	{
		return ExtendedMagazine->GetExtendedMagazineSize();
	}

	return MaxClipSize;
}
