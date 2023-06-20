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
	
	// ���� �ε����� �� �̺�Ʈ�� ���
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
		// źâ�� �־�����
		// 1. �÷��̾ �ʿ��ϴ�.
		ACPlayer* Player = Cast<ACPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		// 2. źâ�� �ʿ��ϴ�.
		Player->bulletPool.Add(BT);
		BT->SetActive(false);
	}
	else
	{
		OtherActor->Destroy();
	}
}

