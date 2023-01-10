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

	///////////�X�e�[�^�X///////////
	int mSize;
	float mRadius;
	Vec2 mPosition;
	enum DIRECTION {
		LEFT,
		RIGHT
	};
	DIRECTION Direction = RIGHT;



	////////////  �ړ�  ////////////
	int mSpeed;
	void Move();

	////////////�W�����v////////////
	bool mIsJump;
	int mJumpSpeed;
	void Jump();

	////////////�_�b�V��////////////
	static constexpr int kDushValue = 300;
	bool mIsDush;
	bool mIsDushLeft;
	bool mIsDushRight;
	bool mCanDush;
	Vec2 mDushStartPosition;
	Vec2 mDushEndPosition;
	float mDushEasingt;
	void Dush();

	////////////  �d��  ////////////
	bool mIsGround;
	float mGravity;
	void Gravity();

	////////////  �g�k  ////////////
	Vec2 mScaling;
	Vec2 mScalingStart;
	Vec2 mScalingEnd;
	bool mIsScaling;
	float mScalingEasingt;
	//���n
	bool mIsLanding;
	//�_�b�V��
	bool mIsDushScaling;
	//�g�k���
	void ScalingAssign();

	////////////  �v���C���[�ɓ���������  ////////////
	void Animation();

	////////////  �摜�֌W  ////////////
	bool mIsLoadTexture;
	int mTextureFrame;
	int mPlayerSrcX;
	int mPlayerLeft;
	int mPlayerRight;

};


