// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() 
{

}

void UTriggerComponent::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Alive!"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}