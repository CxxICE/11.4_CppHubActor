// Fill out your copyright notice in the Description page of Project Settings.

#include "CppHubActor.h"

#include "CppBaseActor.h"
#include "TimerManager.h"

// Sets default values
ACppHubActor::ACppHubActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACppHubActor::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACppHubActor::OnTimeToSpawn, SpawnTimerRate, true);
}

void ACppHubActor::OnTimeToSpawn()
{
	UE_LOG(LogTemp, Display, TEXT("OnTimeToSpawn"));
	if (++CurrentTimerCount <= TotalTimerCount)
	{
		const FVector Location = GetActorLocation() + FVector(FMath::FRandRange(200.0f, 1000.0f), FMath::FRandRange(200.0f, 1000.0f), 0.0f);
		const FRotator Rotation = FRotator::ZeroRotator;
		ACppBaseActor* SpawnOnject = GetWorld()->SpawnActor<ACppBaseActor>(CppClass, Location, Rotation);
		if (SpawnOnject)
		{
			SpawnedObjects.Add(SpawnOnject);
			UE_LOG(LogTemp, Display, TEXT("SpawnOnject"));
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		// for (int i = TotalTimerCount; i >= 1; --i)//по-моему это лишнее
		{
			GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ACppHubActor::OnTimeToDestroy, DestroyTimerRate, true);
		}
	}
}

void ACppHubActor::OnTimeToDestroy()
{

	if (!SpawnedObjects.IsEmpty())
	{
		SpawnedObjects.Top()->Destroy();
		SpawnedObjects.Pop();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}
}

// Called every frame
void ACppHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
