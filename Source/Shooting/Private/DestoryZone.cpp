// Fill out your copyright notice in the Description page of Project Settings.


#include "DestoryZone.h"
#include <Components/BoxComponent.h>

// Sets default values
ADestoryZone::ADestoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = boxComp;

}

// Called when the game starts or when spawned
void ADestoryZone::BeginPlay()
{
	Super::BeginPlay();
	
	// ³ª¶û ºÎµúÇûÀ» ¶§ ÀÌº¥Æ®¸¦ µî·Ï
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADestoryZone::OnComponentBeginOverlap);
}

// Called every frame
void ADestoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestoryZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

