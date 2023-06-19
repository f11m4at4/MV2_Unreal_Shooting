// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

// 5초후에 사라지게 하고 싶다.
// 필요속성 : 제거시간, 경과시간


UCLASS()
class SHOOTING_API ACEnemy : public AActor
{
	GENERATED_BODY()

public:
	// 필요속성 : 제거시간, 경과시간
	UPROPERTY(EditAnywhere, Category="Settings")
	float destroyTime = 5;
	UPROPERTY()
	float currentTime = 0;
public:	
	// Sets default values for this actor's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 사용할 컴포넌트 추가(선언)
	// BoxComp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	
	// BodyMesh
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, Category="Settings")
	float speed = 500;

	FVector Direction;

	// Target 방향으로 이동하고 싶다.
	UPROPERTY()
	class ACPlayer* Target;

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 폭발효과
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	class UParticleSystem* explosionFactory;
};
