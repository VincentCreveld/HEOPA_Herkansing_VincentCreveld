// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProjectile.h"
#include "MyFPSProjectile.generated.h"

class AFPSBombActor;

/**
 * Deze class laat een FPSBombActor achter op de positie van collisie.
 */
UCLASS()
class FPSGAME_API AMyFPSProjectile : public AFPSProjectile
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSubclassOf<AFPSBombActor> FPSBombPrefab;

public:
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
