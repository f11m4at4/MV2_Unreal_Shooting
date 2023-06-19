// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include <Components/BoxComponent.h>

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Boxcomp
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// root 컴포넌트로 설정
	RootComponent = BoxComp;
	// 크기 설정
	BoxComp->SetBoxExtent(FVector(32, 15, 32));
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

	// BodyMesh 컴포넌트를 추가하고 싶다.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));

	// 위지, 회전, 크기 설정
	BodyMesh->SetRelativeLocation(FVector(0, 0, -20));
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.5f));
	// RootComponent 의 자식 컴포넌트로 붙이기
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh 에서 사용할 StaticMesh 데이터 동적 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// 만약 성공적으로 로딩이 됐다면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 의 StaticMesh 에 할당하고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// 2초후에 제거되도록 처리
	SetLifeSpan(2);
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 위로 계속 이동하고 싶다.
	// 필요속성 : 속도
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	// 방향이 필요하다.
	FVector vt = FVector::UpVector * speed * DeltaTime;
	// 이동하고 싶다.
	FVector P = P0 + vt;
	SetActorLocation(P);
}

