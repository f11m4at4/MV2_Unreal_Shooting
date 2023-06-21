// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include <Components/BoxComponent.h>
#include "CBullet.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>


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


	// �ѱ� ������Ʈ �߰�
	leftFirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("leftFirePosition"));
	rightFirePosition = CreateDefaultSubobject<USceneComponent>(TEXT("rightFirePosition"));
	leftFirePosition->SetupAttachment(RootComponent);
	rightFirePosition->SetupAttachment(RootComponent);
	leftFirePosition->SetRelativeLocation(FVector(15, -97, 42));
	rightFirePosition->SetRelativeLocation(FVector(15, 97, 42));
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
	// �ѹ� �Է� �޾Ƽ� �ι� ��� �ʹ�.
	FireBulletAtLocation(leftFirePosition->GetComponentLocation(), leftFirePosition->GetComponentRotation());
	FireBulletAtLocation(rightFirePosition->GetComponentLocation(), rightFirePosition->GetComponentRotation());
}

void ACPlayer::FireBulletAtLocation(FVector location, FRotator rotation)
{
	// 1.�ð��� �귯�� �Ѵ�.
	// 2. �����ð��� �ƴٸ�
		// 3. �Ʒ� ���� ȣ���Ѵ�.
		// 4. ������ ������Ų��.
		// 5. ����ð��� �ʱ�ȭ �Ѵ�.
		
	// 1. theta �� radian �� �����ؾ� �Ѵ�.
	int angleRange = 360/ degree;
	float theta = 0;
	for (int i = 0; i < angleRange; i++)
	{
		theta = i* degree;
		// ȸ��ó��
		float thetaToRadian = FMath::DegreesToRadians(theta);
		// 2. z = sin theta
		float z = FMath::Sin(thetaToRadian);
		// 3. y = cos theta
		float y = FMath::Cos(thetaToRadian);
		// 4. Target �� �ʿ��ϴ�.
		FVector target;
		target.X = 0;
		target.Y = y;
		target.Z = z;
		//������ �ʿ��ϴ�.
		FVector dir = target - FVector::Zero();

		// �Ѿ��� �߻��ϰ� �ʹ�.
		// -> źâ���� �ѹ߲����� Ȱ��ȭ ��Ų��.
		// ���� źâ�ȿ� �Ѿ��� ���ٸ�?
		if (bulletPool.Num() <= 0)
		{
			// �ƹ��͵� ���Ѵ�.
			return;
		}
		// �Ѿ� �Ҹ� ������ �ϰ�ʹ�.
		UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

		// 1. źâ���� �Ѿ��� �ϳ� �̾ƾ��Ѵ�.
		auto Bullet = bulletPool[0];
		// 2. �Ѿ��� Ȱ��ȭ ��Ű�� �ʹ�.
		Bullet->SetActive(true);
		// 3. źâ���� �Ѿ��� �����Ѵ�.
		bulletPool.RemoveAt(0);

		// 4. �Ѿ��� �߻�(��ġ)�ϰ� �ʹ�.
		// ���� �Ѿ��� ���������� �� ��������ٸ�
		if (Bullet != nullptr)
		{
			Bullet->SetActorLocation(location);
			// rotation �� ���� ���� �������� ���ϰ� �ʹ�.
			// Direction �������� Actor �� ȸ���ϵ��� ó���ϰ� �ʹ�.
			FRotator Rot = UKismetMathLibrary::MakeRotFromZX(dir, GetActorForwardVector());
			Bullet->SetActorRotation(Rot);
		}
	}
}

