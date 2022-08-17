// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableTrap.generated.h"

class UTrapInteractionComponent;

UCLASS()
class UE_MAZEGAME_API AInteractableTrap : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AInteractableTrap();

protected:
	UPROPERTY(EditAnywhere, NoClear)
		UTrapInteractionComponent* TrapInteractionComponent;
};
