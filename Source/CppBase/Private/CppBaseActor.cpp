// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "Engine/Engine.h"

std::atomic<int32_t> ACppBaseActor::instanceID = 0;

// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	PlayerName = GetClass()->GetName();
	PlayerName += "_";
	PlayerName.AppendInt(instanceID++);
	EnemyNum = 0;
	IsAlive = true;

	/*Amplitude = 150.0f;
	Frequency = 4.0f;*/
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	//InitialLocation = GetActorLocation();
}

/*void ACppBaseActor::SinMovement()
{
	float Z = InitialLocation.Z + Amplitude * FMath::Sin(Frequency * GetWorld()->GetTimeSeconds());
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, Z));
}
*/
// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACppBaseActor::showInformation()
{
	UE_LOG(LogTemp, Display, TEXT("ID Name: %s"), *GetName());
	UE_LOG(LogTemp, Display, TEXT("Actor Label: %s"), *GetActorLabel());
	UE_LOG(LogTemp, Display, TEXT("Имя игрока: %s"), *PlayerName);
	UE_LOG(LogTemp, Display, TEXT("Кол-во врагов: %i"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("Жив: %i"), IsAlive);
}

