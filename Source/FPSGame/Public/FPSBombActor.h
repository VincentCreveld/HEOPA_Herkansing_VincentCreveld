// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBombActor.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class UMaterialInstanceDynamic;

UCLASS()
class FPSGAME_API AFPSBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBombActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UMaterialInstanceDynamic* MatInst;

	FLinearColor CurColor;
	FLinearColor TargetColor;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
		float ExplosionDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = "Particle")	
		UParticleSystem* ExplosionTemplate;

	UFUNCTION()
		void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
