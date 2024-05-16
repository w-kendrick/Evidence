// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioRecorder.h"
#include "Net/UnrealNetwork.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"

AAudioRecorder::AAudioRecorder()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing"));
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	
	PerceptionComponent->ConfigureSense(*Hearing);
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

	DOREPLIFETIME(AAudioRecorder, RecordStatus);
}

void AAudioRecorder::StartRecording()
{
	SetRecordStatus(ERecordStatus::Recording);
	GetWorldTimerManager().SetTimer(RecordHandle, this, &ThisClass::OnRecordingEnd, MaxLength, true);
}

void AAudioRecorder::StopRecording()
{
	OnRecordingEnd();
}

void AAudioRecorder::OnRecordingEnd()
{
	SetRecordStatus(ERecordStatus::PostRecording);
}

void AAudioRecorder::OnSense(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Sensed: " + Stimulus.Tag.ToString());
}

void AAudioRecorder::SetRecordStatus(const ERecordStatus NewStatus)
{
	RecordStatus = NewStatus;
	OnRecordingChanged.Broadcast(RecordStatus);
}

void AAudioRecorder::OnRep_RecordStatus(const ERecordStatus PrevStatus)
{
	OnRecordingChanged.Broadcast(RecordStatus);
}
