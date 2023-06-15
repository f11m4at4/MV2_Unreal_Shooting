// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CPlayer.h"
#include <Kismet/KismetMathLibrary.h>

// BoxComp �� �ٸ� ��ü�� �浹���� ��
// ���� �װ� ���� �װ� �ϰ�ʹ�.
// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	// BoxComp �� �浹 ������ ����;
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh ���� ����� StaticMesh ������ ���� �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingAssets/Drone/Drone_low.Drone_low'"));
	// ���� ���������� �ε��� �ƴٸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� StaticMesh �� �Ҵ��ϰ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
}


// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	// BoxComp �� �ٸ� ��ü�� �浹���� ��
	// -> ó���� �ݹ� �Լ��� ����ϰ� �ʹ�.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	// Ÿ���� ã�Ƽ� Target ������ �־����.
	Target = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));

	// �¾�� ���� ���ϱ�
	// Ÿ���� ������ Ÿ��������
	// Ÿ���� ���� �� ������ 30% �� Ȯ���� Ÿ�������� �ƴϸ� �Ʒ���
	int percent = FMath::RandRange(1, 100);
	if (Target && percent < 30)
	{
		Direction = Target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
	// �׷��� ������ 
	else
	{
		// �Ʒ���
		Direction = FVector::DownVector;
	}

	// Direction �������� Actor �� ȸ���ϵ��� ó���ϰ� �ʹ�.
	FRotator Rot = UKismetMathLibrary::MakeRotFromZX(Direction, GetActorForwardVector());
	SetActorRotation(Rot);
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �÷��̾ ���������� ��� �̵���Ű�� �ʹ�.
	// 2. �̵���Ű�� �ʹ�.
	// P = P0 + vt
	
	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// ���� �װ� ���� �װ� �ϰ�ʹ�.
void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
	Destroy();
}

