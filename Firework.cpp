#include "Firework.h"
#include "Easing.h"
#include "Key.h"
#include "Player.h"



//花火
void Firework::Init() {

	for (int i = 0; i < kMaxLength; i++) {
		emitter[i].Init();
		particle[i].Init();
	}
}
void Firework::Update(Player& player) {

	for (int i = 0; i < kMaxLength; i++) {
		if (!emitter[i].mIsActive) {
			emitter[i].Make(player);
			break;
		}
	}
	for (int i = 0; i < kMaxLength; i++) {
		if (emitter[i].mIsActive) {
			emitter[i].Move();
			if (!particle[i].mIsActive && emitter[i].mEasingt == 1.0f) {
				particle[i].Make(emitter[i]);
				break;
			}
			if (particle[i].mIsActive) {
				particle[i].Move();
			}
			if (particle[i].mFinishCount == Particle::kMaxLength) {
				emitter[i].Init();
				particle[i].Init();
			}
		}
	}
}
void Firework::Draw(Screen& screen) {

	for (int i = 0; i < kMaxLength; i++){
		emitter[i].Draw(screen);
		particle[i].Draw(screen);
	}
}



//エミッター
void Emitter::Init() {
	mRadius = 10;
	mColor = WHITE;
	mIsActive = false;
	mEasingt = 0.0f;
}
void Emitter::Make(Player& player) {

	if (Key::IsTrigger(DIK_SPACE)){
		mStartPosition.x = player.mPosition.x;
		mStartPosition.y = player.mPosition.y;
		mEndPosition.x = mStartPosition.x;
		mEndPosition.y = mStartPosition.y + (RAND(6, 12) * 50);
		mEasingt = 0.0f;
		mColor = WHITE;
		mIsActive = true;
	}
}
void Emitter::Move() {

	mEasingt = EasingClamp(0.01f, mEasingt);
	mPosition = EasingMove(mStartPosition, mEndPosition, easeOutCirc(mEasingt));
	mColor = ColorEasingMove(WHITE, 0xFFFFFF00, easeInExpo(mEasingt));

}
void Emitter::Draw(Screen& screen) {

	if (!mIsLoadTexture){
		emitter = Novice::LoadTexture("./Resources/particle.png");
		mIsLoadTexture = true;
	}

	if (mIsActive){
		screen.DrawPicture(mPosition, mRadius, 0.0f, 80, 80, emitter, mColor);
	}
}



//パーティクル
void Particle::Init() {
	mRadius = 8;
	mIsActive = false;
	mFrame = 0;
	mFinishCount = 0;
	for (int i = 0; i < kMaxLength; i++){
		mIsFinish[i] = false;
		mAlphat[i] = 0.0f;
		mColor[i] = WHITE;
	}
}
void Particle::Make(Emitter& emitter) {

	mFrame = 0;
	mFinishCount = 0;
	for (int i = 0; i < kMaxLength; i++) {
		PositionInCircle(mPosition[i], emitter);
		mIsFinish[i] = false;
		mLife[i] = 120 + (RAND(0, 6) * 20);
		mAlphat[i] = 0.0f;
		mColor[i] = WHITE;
	}
	mIsActive = true;
}
void Particle::Move() {

	mFrame++;
	for (int i = 0; i < kMaxLength; i++) {
		if (mLife[i] < mFrame) {
			mAlphat[i] = EasingClamp(0.01f, mAlphat[i]);
			mColor[i] = ColorEasingMove(WHITE, 0xFFFFFF00, easeLinear(mAlphat[i]));
			if (mAlphat[i] == 1.0f && !mIsFinish[i]) {
				mFinishCount++;
				mIsFinish[i] = true;
			}
		}
	}
}
void Particle::PositionInCircle(Vec2& position, Emitter& emitter) {

	position.x = RAND(emitter.mPosition.x - kSpawnRadius, emitter.mPosition.x + kSpawnRadius);
	position.y = RAND(emitter.mPosition.y - kSpawnRadius, emitter.mPosition.y + kSpawnRadius);

	float distance = position.DistanceFrom(emitter.mPosition);

	if (kSpawnRadius < distance){
		PositionInCircle(position, emitter);
	}
}
void Particle::Draw(Screen& screen) {

	if (!mIsLoadTexture) {
		particle = Novice::LoadTexture("./Resources/particle.png");
		mIsLoadTexture = true;
	}

	if (mIsActive){
		for (int i = 0; i < kMaxLength; i++) {
			screen.DrawPicture(mPosition[i], mRadius, 0.0f, 80, 80, particle, mColor[i]);
		}
	}
}