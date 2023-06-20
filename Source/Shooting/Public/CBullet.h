// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class SHOOTING_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// ����� ������Ʈ �߰�(����)
	// BoxComp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	
	// BodyMesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;

	// �ʿ�Ӽ� : �ӵ�
	UPROPERTY(EditAnywhere, Category="Settings")
	float speed = 1000;

public:
	// �Ѿ��� Ȱ��ȭ���� ó�� �Լ�
	void SetActive(bool bActivation);
};
