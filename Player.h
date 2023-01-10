#pragma once
#include "Screen.h"

class Player
{

public:

	Player() {
		Init();
	};

	void Init();
	void Update();
	void Draw(Screen& screen);

	///////////ステータス///////////
	int mSize;
	float mRadius;
	Vec2 mPosition;
	enum DIRECTION {
		LEFT,
		RIGHT
	};
	DIRECTION Direction = RIGHT;



	////////////  移動  ////////////
	int mSpeed;
	void Move();

	////////////ジャンプ////////////
	bool mIsJump;
	int mJumpSpeed;
	void Jump();

	////////////ダッシュ////////////
	static constexpr int kDushValue = 300;
	bool mIsDush;
	bool mIsDushLeft;
	bool mIsDushRight;
	bool mCanDush;
	Vec2 mDushStartPosition;
	Vec2 mDushEndPosition;
	float mDushEasingt;
	void Dush();

	////////////  重力  ////////////
	bool mIsGround;
	float mGravity;
	void Gravity();

	////////////  拡縮  ////////////
	Vec2 mScaling;
	Vec2 mScalingStart;
	Vec2 mScalingEnd;
	bool mIsScaling;
	float mScalingEasingt;
	//着地
	bool mIsLanding;
	//ダッシュ
	bool mIsDushScaling;
	//拡縮代入
	void ScalingAssign();

	////////////  プレイヤーに動きをつける  ////////////
	void Animation();

	////////////  画像関係  ////////////
	bool mIsLoadTexture;
	int mTextureFrame;
	int mPlayerSrcX;
	int mPlayerLeft;
	int mPlayerRight;

};


