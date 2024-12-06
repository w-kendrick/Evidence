// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioRecorder.h"
#include "Net/UnrealNetwork.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Evidence/Structs/EvidentialInfo.h"
#include "Evidence/Structs/EvidentialCapture.h"
#include "Evidence/Libraries/EvidentialFunctionLibrary.h"
#include "Evidence/Interfaces/Evidential.h"

AAudioRecorder::AAudioRecorder()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	
	PerceptionComponent->ConfigureSense(*Hearing);

	MaxLength = 10.f;
	isRecording = false;

	EquipmentAbbreviation = FString(TEXT("AUD"));
}

void AAudioRecorder::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnSense);
	}
}

void AAudioRecorder::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAudioRecorder, isRecording);
}

void AAudioRecorder::StartRecording()
{
	SetIsRecording(true);
	Recording.Empty();
	GetWorldTimerManager().SetTimer(RecordHandle, this, &ThisClass::OnRecordingEnd, MaxLength, true);
	Count = 0;
}

void AAudioRecorder::StopRecording()
{
	OnRecordingEnd();
}

void AAudioRecorder::OnRecordingEnd()
{
	SetIsRecording(false);
	GetWorldTimerManager().ClearTimer(RecordHandle);

	const FEvidentialCapture Capture = FEvidentialCapture(EEvidentialMedium::Audio, Recording);
	AddCapture(Capture);
}

void AAudioRecorder::OnSense(AActor* Actor, FAIStimulus Stimulus)
{
	if (isRecording)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Actor->GetName());
		const IEvidential* const Evidential = Cast<IEvidential>(Actor);
		if (Evidential)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Sensed evidential"));
			const FEvidentialInfo Info = FEvidentialInfo(Evidential->GetType(), Count);
			Recording.Add(Info);
			Count++;
		}
	}
}

void AAudioRecorder::SetIsRecording(const bool NewIsRecording)
{
	isRecording = NewIsRecording;
	OnRecordingChanged.Broadcast(isRecording);
}

void AAudioRecorder::OnRep_IsRecording(const bool PrevIsRecording)
{
	OnRecordingChanged.Broadcast(isRecording);
}