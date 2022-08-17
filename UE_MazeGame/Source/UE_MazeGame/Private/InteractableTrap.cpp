// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTrap.h"
#include "TrapInteractionComponent.h"

AInteractableTrap::AInteractableTrap()
{
	TrapInteractionComponent = CreateDefaultSubobject<UTrapInteractionComponent>(TEXT("TrapInteractionComponent"));
}

