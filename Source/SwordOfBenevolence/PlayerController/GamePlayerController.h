// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFBENEVOLENCE_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AGamePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// 设置玩家操作方式(动作模式/3D模式)动作模式是指转鼠标相机角色一起转动，3D模式左键转相机右键一起转
	void	SetActionOperationMode(bool isActionMode);

	// 获取当前是否时动作模式
	bool	GetActionOperationMode();

	// 帧循环
	virtual void PlayerTick(float DeltaTime);


protected:

	virtual void BeginPlayingState();

protected:

	// 注册按键事件
	virtual void	SetupInputComponent();

	// 侦听WASD行走
	void	OnMoveForwardEvent(float Value);
	void	OnMoveRightEvent(float Value);

	// 侦听鼠标旋转
	void	OnTurnCameraEvent(float Value);
	void	OnLookUpCameraEvent(float Value);

	// 鼠标滚轮
	void	OnCameraWheelEvent(float Value);
	// 更新相机与角色距离
	void	OnUpdateCameraArmLength(float deltTime);

	// 侦听鼠标按键
	void	OnRMouseBtnDownEvent();
	void	OnRMouseBtnUpEvent();
	void	OnLMouseBtnDownEvent();

	// 侦听切换操作模式
	void	OnOPChangedEvent();


protected:

	uint32		bActionMode : 1;		// 当前是否时动作操作模式
	uint32		bRMouseBtn : 1;			// 当前鼠标右键是否按下
	uint32		bChangeCaramaArm : 1;	// 当前是否需要更新相机手臂
	float		targetCameraLength;		// 等待缓动的相机推进距离		
};
