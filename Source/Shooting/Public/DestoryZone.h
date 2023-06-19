// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestoryZone.generated.h"

// 나랑 부딪힌 물체를 없애고 싶다.
// 필요속성 : 박스 충돌체
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


	// 필요속성 : 박스 충돌체
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* boxComp;

	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
