#include "Player.h"
#include "Key.h"
#include "Easing.h"
#include "Function.h"



void Player::Init() {

	//ステータス
	mSize = 32;
	mRadius = 0;

	//移動
	mSpeed = 3;

	//ジャンプ
	mIsJump = false;
	mJumpSpeed = 8;

	//ダッシュ
	mIsDush = false;
	mIsDushLeft = false;
	mIsDushRight = false;
	mCanDush = true;
	mDushStartPosition = { 0,0 };
	mDushEndPosition = { 0,0 };
	mDushEasingt = 0.0f;

	//重力
	mIsGround = false;
	mGravity = 0.0f;

	//拡縮
	mScaling = { 1.0f, 1.0f };
	mIsScaling = false;
	mIsLanding = false;
	mIsDushScaling = false;

	//画像読み込みフラグ
	mIsLoadTexture = false;
	mTextureFrame = 0;
	mPlayerSrcX = 0;

}

void Player::Update() {

	Dush();
	Jump();
	Move();
	Gravity();

}



////////////  移動  ////////////

void Player::Move() {

	//左右移動
	if (Key::IsPress(DIK_LEFT)) {
		mPosition.x -= mSpeed;
		Direction = LEFT;
	}
	if (Key::IsPress(DIK_RIGHT)) {
		mPosition.x += mSpeed;
		Direction = RIGHT;
	}
}



////////////ジャンプ////////////

void Player::Jump() {

	//地面にいる時はジャンプが発動される
	if (mIsGround == true && mIsJump == false) {

		//ジャンプフラグを立てる
		if (Key::IsTrigger(DIK_C)) {
			mIsJump = true;
			mIsGround = false;
		}
	}

	//ジャンプ
	if (mIsJump == true) {

		//ダッシュを発動するとジャンプを中止する
		if (mIsDush == true){
			mIsJump = false;
		}

		if (mIsDush == false){
			mPosition.y += mJumpSpeed;
		}
	}
}



////////////ダッシュ////////////

void Player::Dush() {

	//空中にいる時はダッシュが発動される
	if (mIsGround == false && mCanDush == true) {

		//ダッシュフラグを立てる
		if (Key::IsTrigger(DIK_C)) {
			
			mDushStartPosition = mPosition;

			if (Direction == LEFT) {
				mDushEndPosition = { mPosition.x - kDushValue, mPosition.y };
				mIsDushLeft = true;
				mIsDushRight = false;
			}
			if (Direction == RIGHT) {
				mDushEndPosition = { mPosition.x + kDushValue, mPosition.y };
				mIsDushLeft = false;
				mIsDushRight = true;
			}

			mDushEasingt = 0.0f;
			mIsDush = true;
			mCanDush = false;
		}
	}

	if (mIsDush == true){

		mDushEasingt += 0.02f;
		mDushEasingt = Clamp(mDushEasingt, 0.0f, 1.0f);
		mPosition = EasingMove(mDushStartPosition, mDushEndPosition, easeOutSine(mDushEasingt));

		if (mDushEasingt >= 0.85f){
			mIsDush = false;
		}
	}

	//地面についたらダッシュが再びできるようになる
	if (mIsGround == true){
		mCanDush = true;
	}
}




////////////  重力  ////////////

void Player::Gravity() {

	//地面にいる時 || ダッシュしている時　重力の値を初期化する
	if (mIsGround == true || mIsDush == true) {
		mGravity = 0.0f;
	}

	//地面にいない時 ＝ 空中にいる時　重力の値を増やす
	if (mIsGround == false) {
		mGravity += 0.2f;
		mPosition.y -= mGravity;
	}

	//下当たり判定
	mPosition.x = Clamp(mPosition.x, mSize / 2, Screen::kWindowWidth - (mSize / 2));
	mPosition.y = Clamp(mPosition.y, 48, Screen::kWindowHeight - (mSize / 2));

	if (mPosition.y == 48){
		mIsDush = false;
		mIsJump = false;
		mIsScaling = false;
		mIsDushScaling = false;

		if (mGravity >= 10.0f) {
			ScalingAssign();
			mIsLanding = true;
		}

		mIsGround = true;
	}
}


////////////  プレイヤーに動きをつける  ////////////

void Player::ScalingAssign() {

	mScalingEasingt = 0.0f;
	mScalingStart.x = 1.5f;
	mScalingStart.y = 0.5f;
	mScalingEnd.x = 1.0f;
	mScalingEnd.y = 1.0f;
}

void Player::Animation() {

	//拡縮代入
	if (Key::IsTrigger(DIK_C) != 0 && mIsScaling == false) {

		ScalingAssign();
		mIsScaling = true;
	}

	//ダッシュ
	if (mIsDush == true && mIsGround == false && mIsDushScaling == false) {

		ScalingAssign();
		mIsDushScaling = true;
	}

	//拡縮処理
	if (mIsLanding == true || mIsScaling == true || mIsDushScaling == true){

		mScalingEasingt += 0.02f;
		mScalingEasingt = Clamp(mScalingEasingt, 0.0f, 1.0f);
		mScaling = EasingMove(mScalingStart, mScalingEnd, easeOutExpo(mScalingEasingt));
	}

	//地面に着いたときは初期化する
	if (mIsLanding == false && mIsGround == true){
		mScaling = { 1.0f, 1.0f };
	}

	//拡縮の中心を場合によってずらす
	//着地 || ジャンプ
	if (mIsLanding == true || mIsScaling == true){
		mRadius = 16;
	}
	//ダッシュ
	if (mIsDushScaling == true){
		mRadius = 0;
	}

}


void Player::Draw(Screen& screen) {

	mTextureFrame++;

	if (mIsLoadTexture == false){
		mPlayerLeft = Novice::LoadTexture("./Resources/Player/playerleft.png");
		mPlayerRight = Novice::LoadTexture("./Resources/Player/playerright.png");
		mIsLoadTexture = true;
	}

	Animation();

	//中心からの四点（Radiusの値で変わる）
	if (Direction == LEFT) {
		screen.DrawAnime(mPosition, mSize, mPlayerSrcX, 32, 32, 2, 20, mTextureFrame, mPlayerLeft, WHITE, mScaling);
	}
	else {
		screen.DrawAnime(mPosition, mSize, mPlayerSrcX, 32, 32, 2, 20, mTextureFrame, mPlayerRight, WHITE, mScaling);
	}


}
