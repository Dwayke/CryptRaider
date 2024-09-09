// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay() 
{
	Super::BeginPlay();
	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		UE_LOG(LogTemp, Display, TEXT("Unlocking"), *Actor->GetActorNameOrLabel());
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component)
		{
			Component->SetSimulatePhysics(false);
			Component->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		}
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag(AcceptableTag) && !Actor->ActorHasTag("Grabbed"))
		{
			UE_LOG(LogTemp, Display, TEXT("Secret Unlocked Using: %s"), *Actor->GetActorNameOrLabel());
			return Actor;
		}
	}
	return nullptr;
}
