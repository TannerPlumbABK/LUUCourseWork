// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapInteractionComponent.h"
#include "Engine/TriggerBox.h"

// Sets default values for this component's properties
UTrapInteractionComponent::UTrapInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTrapInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTrapInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
		{
			PlayerPawn->SetActorLocation(FVector(-2160.0, 2240.0, 112.000687));
			PlayerPawn->SetActorRotation(FRotator(0, 0, 0));
		}
	}
}

