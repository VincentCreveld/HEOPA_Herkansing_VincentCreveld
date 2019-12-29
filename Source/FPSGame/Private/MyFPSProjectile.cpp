// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFPSProjectile.h"
#include "FPSBombActor.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

void AMyFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	GetWorld()->SpawnActor<AFPSBombActor>(FPSBombPrefab, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

	Destroy();
}