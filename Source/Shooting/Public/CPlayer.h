// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

// �÷��̾ ���������� ��� �̵���Ű�� �ʹ�.
// ������� �Է��� �޾Ƽ� �����¿�� �̵���Ű�� �ʹ�.
UCLASS()
class SHOOTING_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// �ʿ�Ӽ� : �̵��ӵ�
	UPROPERTY(EditAnywhere, Category="Settings")
	float speed = 500;

	FVector Direction;

	// ����� �¿��̵� ó�� �Լ�
	void Horizontal(float value);
	void Vertical(float value);

	// �߻�ó�� �Լ�
	void Fire();
	// �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	TSubclassOf<class ACBullet> BulletFactory;

public:
	// ����� ������Ʈ �߰�(����)
	// BoxComp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	
	// BodyMesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;

	// �Ѿ� �߻��� �� ���� ������ �ϰ� �ʹ�.
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	class USoundBase* bulletSound;

public:
	// źâ(������ƮǮ �� �迭)
	UPROPERTY()
	TArray<class ACBullet*> bulletPool;
	// �ʿ�Ӽ� : ���?
	UPROPERTY(EditAnywhere, Category="Bullet")
	int32 bulletPoolSize = 10;

	// ���� ������ �ѱ� �߰�
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* leftFirePosition;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* rightFirePosition;

	// �Ѿ� �߻� �Լ�
	void FireBulletAtLocation(FVector location, FRotator rotation);

	UPROPERTY(EditAnywhere)
	int32 degree = 30;
};
