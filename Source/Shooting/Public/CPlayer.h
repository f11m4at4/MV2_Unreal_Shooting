// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

// 플레이어를 오른쪽으로 계속 이동시키고 싶다.
// 사용자의 입력을 받아서 상하좌우로 이동시키고 싶다.
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
	// 필요속성 : 이동속도
	UPROPERTY(EditAnywhere, Category="Settings")
	float speed = 500;

	FVector Direction;

	// 사용자 좌우이동 처리 함수
	void Horizontal(float value);
	void Vertical(float value);

	// 발사처리 함수
	void Fire();
	// 총알공장
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	TSubclassOf<class ACBullet> BulletFactory;

public:
	// 사용할 컴포넌트 추가(선언)
	// BoxComp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	
	// BodyMesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;
};
