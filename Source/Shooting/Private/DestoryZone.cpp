// Fill out your copyright notice in the Description page of Project Settings.


#include "DestoryZone.h"
#include <Components/BoxComponent.h>
#include "CBullet.h"
#include "CPlayer.h"
#include <Kismet/GameplayStatics.h>

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
	
	// 나랑 부딪혔을 때 이벤트를 등록
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ADestoryZone::OnComponentBeginOverlap);
}

// Called every frame
void ADestoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestoryZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACBullet* BT = Cast<ACBullet>(OtherActor);
	if (BT != nullptr)
	{
		// 탄창에 넣어주자
		// 1. 플레이어가 필요하다.
		ACPlayer* Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		// 2. 탄창이 필요하다.
		Player->bulletPool.Add(BT);
		BT->SetActive(false);
	}
	else
	{
		OtherActor->Destroy();
	}
}

