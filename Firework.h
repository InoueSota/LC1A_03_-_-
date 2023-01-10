#pragma once
#include "Screen.h"
#include "Vec2.h"
#include "Function.h"



class Player;

class Emitter
{
public:
	Emitter() {
		Init();
	}

	void Init();
	void Draw(Screen& screen);

	//パラメータ
	Vec2 mPosition;
	int mRadius;
	unsigned int mColor;

	//移動
	bool mIsActive;
	Vec2 mStartPosition;
	Vec2 mEndPosition;
	float mEasingt;
	void Make(Player& player);
	void Move();

	//画像
	bool mIsLoadTexture = false;
	int emitter;

};

class Particle
{
public:
	Particle() {
		Init();
	}

	void Init();
	void Draw(Screen& screen);

	//パラメータ
	static constexpr int kMaxLength = 50;
	Vec2 mPosition[kMaxLength];
	int mRadius;

	//生成
	static constexpr int kSpawnRadius = 150;
	bool mIsActive;
	void Make(Emitter& emitter);
	void PositionInCircle(Vec2& position, Emitter& emitter);

	//移動
	int mLife[kMaxLength];
	int mFrame;
	int mFinishCount;
	bool mIsFinish[kMaxLength];
	float mAlphat[kMaxLength];
	unsigned int mColor[kMaxLength];
	void Move();

	//画像
	bool mIsLoadTexture = false;
	int particle;

};

class Firework
{
public:
	Firework() {
		Init();
		SRAND();
	}

	void Init();
	void Update(Player& player);
	void Draw(Screen& screen);

	static constexpr int kMaxLength = 15;
	Emitter emitter[kMaxLength];
	Particle particle[kMaxLength];


};
