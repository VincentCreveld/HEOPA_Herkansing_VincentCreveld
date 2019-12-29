// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBombActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ExplosionDelay = 2.0f;
}

// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &AFPSBombActor::Explode, ExplosionDelay);

	MatInst = MeshComp->CreateAndSetMaterialInstanceDynamic(0);
	if (MatInst)
	{
		CurColor = MatInst->K2_GetVectorParameterValue("Color");
	}

	TargetColor = FLinearColor::MakeRandomColor();
}

void AFPSBombActor::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	FCollisionShape CollShape;
	CollShape.SetSphere(500.0f);

	TArray<FOverlapResult> OutOverlaps;
	GetWorld()->OverlapMultiByObjectType(OutOverlaps, GetActorLocation(), FQuat::Identity, QueryParams, CollShape);

	for (FOverlapResult Result : OutOverlaps)
	{
		UPrimitiveComponent* Overlap = Result.GetComponent();
		if (Overlap && Overlap->IsSimulatingPhysics())
		{
			FVector direction = GetActorLocation() - Result.GetActor()->GetActorLocation();
			direction.Normalize();
			Overlap->AddImpulseAtLocation(-direction * 1000000.0f, GetActorLocation());
			UMaterialInstanceDynamic* MaterialInst = Overlap->CreateAndSetMaterialInstanceDynamic(0);
			if (MaterialInst)
			{
				MaterialInst->SetVectorParameterValue("Color", TargetColor);
			}
		}
	}

	Destroy();
}

// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MatInst)
	{
		float Progress = (GetWorld()->TimeSeconds - CreationTime) / ExplosionDelay;

		FLinearColor NewColor = FLinearColor::LerpUsingHSV(CurColor, TargetColor, Progress);

		MatInst->SetVectorParameterValue("Color", NewColor);
	}

}

