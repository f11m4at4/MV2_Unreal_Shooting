// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyGOD.h"
#include "CEnemy.h"

// ���� �ð� ���ݿ� �ѹ��� ���� �����ϰ� �ʹ�.

// Sets default values
ACEnemyGOD::ACEnemyGOD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyGOD::BeginPlay()
{
	Super::BeginPlay();
	createTime = FMath::RandRange(minTime, maxTime);
}

// Called every frame
void ACEnemyGOD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	// 1. �ð��� �귶���ϱ�.
	currentTime += DeltaTime;
	// 2. �����ð��� �����ϱ�
	// ->���� ����ð��� �����ð��� �ʰ��ߴٸ�
	if (currentTime > createTime)
	{
		// 3. ���� ������Ѵ�.
		// 4. ���� ��ġ�ϰ� �ʹ�.
		GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), FRotator());

		currentTime = 0;
		// �����ð��� �����ϰ� �ٽ� ��������.
		createTime = FMath::RandRange(minTime, maxTime);
	}
}

