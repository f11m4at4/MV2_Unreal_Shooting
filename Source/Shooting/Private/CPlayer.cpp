// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include <Components/BoxComponent.h>
#include "CBullet.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Boxcomp
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// root ������Ʈ�� ����
	RootComponent = BoxComp;
	// ũ�� ����
	BoxComp->SetBoxExtent(FVector(20));
	BoxComp->SetCollisionProfileName(TEXT("Player"));

	// BodyMesh ������Ʈ�� �߰��ϰ� �ʹ�.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh")); 

	// RootComponent �� �ڽ� ������Ʈ�� ���̱�
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// ����, ȸ��, ũ�� ����
	BodyMesh->SetRelativeLocation(FVector(0, 0, 20));
	BodyMesh->SetRelativeRotation(FRotator(0, 90, 90));
	BodyMesh->SetRelativeScale3D(FVector(8));

	// BodyMesh ���� ����� StaticMesh ������ ���� �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingAssets/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	// ���� ���������� �ε��� �ƴٸ�
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh �� StaticMesh �� �Ҵ��ϰ� �ʹ�.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	

	// �Ѿ��� �̸� ���� źâ�� �߰��ϰ� �ʹ�.
	// 1. �ݺ������� źâ ũ�⸸ŭ
	for(int i=0;i<bulletPoolSize;i++)
	{
		// 2. �Ѿ��ʿ��ϴ�.
		// �Ѿ˰��忡�� �Ѿ��� ������ �Ѵ�.
		UWorld* World = GetWorld();
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACBullet* bullet = World->SpawnActor<ACBullet>(BulletFactory, Param);
		// 3. źâ�� �Ѿ��� �߰��ϰ� �ʹ�.
		bulletPool.Add(bullet);

		// �Ѿ��� ���������
		// ��Ȱ��ȭ ó��
		bullet->SetActive(false);
	}
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// �÷��̾ ���������� ��� �̵���Ű�� �ʹ�.
	// 2. �̵���Ű�� �ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P, true);


}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ����ڰ� ����س��� �Է°� ó�� �Լ��� ��������.
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);

	// �߻��ư ó�����
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	Direction.Y = value;
}

void ACPlayer::Vertical(float value)
{
	Direction.Z = value;
}

void ACPlayer::Fire()
{
	// �Ѿ� �Ҹ� ������ �ϰ�ʹ�.
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
	// �Ѿ��� �߻��ϰ� �ʹ�.
	// 1. �Ѿ˰��忡�� �Ѿ��� ������ �Ѵ�.
	UWorld* World = GetWorld();
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride =  ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ACBullet* Bullet = World->SpawnActor<ACBullet>(BulletFactory, Param);
	// 2. �Ѿ��� �߻�(��ġ)�ϰ� �ʹ�.
	// ���� �Ѿ��� ���������� �� ��������ٸ�
	if (Bullet != nullptr)
	{
		Bullet->SetActorLocation(GetActorLocation());
	}
}

