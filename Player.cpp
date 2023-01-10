#include "Player.h"
#include "Key.h"
#include "Easing.h"
#include "Function.h"



void Player::Init() {

	//�X�e�[�^�X
	mSize = 32;
	mRadius = 0;

	//�ړ�
	mSpeed = 3;

	//�W�����v
	mIsJump = false;
	mJumpSpeed = 8;

	//�_�b�V��
	mIsDush = false;
	mIsDushLeft = false;
	mIsDushRight = false;
	mCanDush = true;
	mDushStartPosition = { 0,0 };
	mDushEndPosition = { 0,0 };
	mDushEasingt = 0.0f;

	//�d��
	mIsGround = false;
	mGravity = 0.0f;

	//�g�k
	mScaling = { 1.0f, 1.0f };
	mIsScaling = false;
	mIsLanding = false;
	mIsDushScaling = false;

	//�摜�ǂݍ��݃t���O
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



////////////  �ړ�  ////////////

void Player::Move() {

	//���E�ړ�
	if (Key::IsPress(DIK_LEFT)) {
		mPosition.x -= mSpeed;
		Direction = LEFT;
	}
	if (Key::IsPress(DIK_RIGHT)) {
		mPosition.x += mSpeed;
		Direction = RIGHT;
	}
}



////////////�W�����v////////////

void Player::Jump() {

	//�n�ʂɂ��鎞�̓W�����v�����������
	if (mIsGround == true && mIsJump == false) {

		//�W�����v�t���O�𗧂Ă�
		if (Key::IsTrigger(DIK_C)) {
			mIsJump = true;
			mIsGround = false;
		}
	}

	//�W�����v
	if (mIsJump == true) {

		//�_�b�V���𔭓�����ƃW�����v�𒆎~����
		if (mIsDush == true){
			mIsJump = false;
		}

		if (mIsDush == false){
			mPosition.y += mJumpSpeed;
		}
	}
}



////////////�_�b�V��////////////

void Player::Dush() {

	//�󒆂ɂ��鎞�̓_�b�V�������������
	if (mIsGround == false && mCanDush == true) {

		//�_�b�V���t���O�𗧂Ă�
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

	//�n�ʂɂ�����_�b�V�����Ăтł���悤�ɂȂ�
	if (mIsGround == true){
		mCanDush = true;
	}
}




////////////  �d��  ////////////

void Player::Gravity() {

	//�n�ʂɂ��鎞 || �_�b�V�����Ă��鎞�@�d�͂̒l������������
	if (mIsGround == true || mIsDush == true) {
		mGravity = 0.0f;
	}

	//�n�ʂɂ��Ȃ��� �� �󒆂ɂ��鎞�@�d�͂̒l�𑝂₷
	if (mIsGround == false) {
		mGravity += 0.2f;
		mPosition.y -= mGravity;
	}

	//�������蔻��
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


////////////  �v���C���[�ɓ���������  ////////////

void Player::ScalingAssign() {

	mScalingEasingt = 0.0f;
	mScalingStart.x = 1.5f;
	mScalingStart.y = 0.5f;
	mScalingEnd.x = 1.0f;
	mScalingEnd.y = 1.0f;
}

void Player::Animation() {

	//�g�k���
	if (Key::IsTrigger(DIK_C) != 0 && mIsScaling == false) {

		ScalingAssign();
		mIsScaling = true;
	}

	//�_�b�V��
	if (mIsDush == true && mIsGround == false && mIsDushScaling == false) {

		ScalingAssign();
		mIsDushScaling = true;
	}

	//�g�k����
	if (mIsLanding == true || mIsScaling == true || mIsDushScaling == true){

		mScalingEasingt += 0.02f;
		mScalingEasingt = Clamp(mScalingEasingt, 0.0f, 1.0f);
		mScaling = EasingMove(mScalingStart, mScalingEnd, easeOutExpo(mScalingEasingt));
	}

	//�n�ʂɒ������Ƃ��͏���������
	if (mIsLanding == false && mIsGround == true){
		mScaling = { 1.0f, 1.0f };
	}

	//�g�k�̒��S���ꍇ�ɂ���Ă��炷
	//���n || �W�����v
	if (mIsLanding == true || mIsScaling == true){
		mRadius = 16;
	}
	//�_�b�V��
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

	//���S����̎l�_�iRadius�̒l�ŕς��j
	if (Direction == LEFT) {
		screen.DrawAnime(mPosition, mSize, mPlayerSrcX, 32, 32, 2, 20, mTextureFrame, mPlayerLeft, WHITE, mScaling);
	}
	else {
		screen.DrawAnime(mPosition, mSize, mPlayerSrcX, 32, 32, 2, 20, mTextureFrame, mPlayerRight, WHITE, mScaling);
	}


}
