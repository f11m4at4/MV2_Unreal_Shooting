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
	// root ������Ʈ�� ����
	RootComponent = BoxComp;
	// ũ�� ����
	BoxComp->SetBoxExtent(FVector(32, 15, 32));
	BoxComp->SetCollisionProfileName(TEXT("Bullet"));

	// BodyMesh ������Ʈ�� �߰��ϰ� �ʹ�.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));

	// ����, ȸ��, ũ�� ����
	BodyMesh->SetRelativeLocation(FVector(0, 0, -20));
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.5f));
	// RootComponent �� �ڽ� ������Ʈ�� ���̱�
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh ���� ����� StaticMesh ������ ���� �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	// ���� ���������� �ε��� �ƴٸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� StaticMesh �� �Ҵ��ϰ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	// 2���Ŀ� ���ŵǵ��� ó��
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
	// ���� ��� �̵��ϰ� �ʹ�.
	// �ʿ�Ӽ� : �ӵ�
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	// ������ �ʿ��ϴ�.
	FVector vt = FVector::UpVector * speed * DeltaTime;
	// �̵��ϰ� �ʹ�.
	FVector P = P0 + vt;
	SetActorLocation(P);
}

