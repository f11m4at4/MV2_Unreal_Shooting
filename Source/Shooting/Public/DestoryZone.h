// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestoryZone.generated.h"

// ���� �ε��� ��ü�� ���ְ� �ʹ�.
// �ʿ�Ӽ� : �ڽ� �浹ü
UCLASS()
class SHOOTING_API ADestoryZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestoryZone();
	  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// �ʿ�Ӽ� : �ڽ� �浹ü
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
