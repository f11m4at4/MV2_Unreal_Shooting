// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyGOD.generated.h"

// �����ð��� �ѹ��� ���� ����� �ʹ�.
// �ʿ�Ӽ� : �����ð�, ����ð�, ������
UCLASS()
class SHOOTING_API ACEnemyGOD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyGOD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// �ʿ�Ӽ� : �����ð�, ����ð�, ������
	UPROPERTY(EditAnywhere, Category="Enemy")
	float createTime = 2;
	UPROPERTY()
	float currentTime = 0;
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class ACEnemy> enemyFactory;
};
