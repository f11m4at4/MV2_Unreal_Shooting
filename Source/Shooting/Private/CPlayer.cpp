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
	// root 컴포넌트로 설정
	RootComponent = BoxComp;
	// 크기 설정
	BoxComp->SetBoxExtent(FVector(20));
	BoxComp->SetCollisionProfileName(TEXT("Player"));

	// BodyMesh 컴포넌트를 추가하고 싶다.
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh")); 

	// RootComponent 의 자식 컴포넌트로 붙이기
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 위지, 회전, 크기 설정
	BodyMesh->SetRelativeLocation(FVector(0, 0, 20));
	BodyMesh->SetRelativeRotation(FRotator(0, 90, 90));
	BodyMesh->SetRelativeScale3D(FVector(8));

	// BodyMesh 에서 사용할 StaticMesh 데이터 동적 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/ShootingAssets/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	// 만약 성공적으로 로딩이 됐다면
	if (TempMesh.Succeeded())
	{
		// -> BodyMesh 의 StaticMesh 에 할당하고 싶다.
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	

	// 총알을 미리 만들어서 탄창에 추가하고 싶다.
	// 1. 반복적으로 탄창 크기만큼
	for(int i=0;i<bulletPoolSize;i++)
	{
		// 2. 총알필요하다.
		// 총알공장에서 총알을 만들어야 한다.
		UWorld* World = GetWorld();
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACBullet* bullet = World->SpawnActor<ACBullet>(BulletFactory, Param);
		// 3. 탄창에 총알을 추가하고 싶다.
		bulletPool.Add(bullet);

		// 총알이 만들어지면
		// 비활성화 처리
		bullet->SetActive(false);
	}
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 플레이어를 오른쪽으로 계속 이동시키고 싶다.
	// 2. 이동시키고 싶다.
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

	// 사용자가 등록해놓은 입력과 처리 함수를 묶어주자.
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);

	// 발사버튼 처리등록
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
	// 총알 소리 나도록 하고싶다.
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
	// 총알을 발사하고 싶다.
	// 1. 총알공장에서 총알을 만들어야 한다.
	UWorld* World = GetWorld();
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride =  ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ACBullet* Bullet = World->SpawnActor<ACBullet>(BulletFactory, Param);
	// 2. 총알을 발사(위치)하고 싶다.
	// 만약 총알이 정상적으로 잘 만들어졌다면
	if (Bullet != nullptr)
	{
		Bullet->SetActorLocation(GetActorLocation());
	}
}

