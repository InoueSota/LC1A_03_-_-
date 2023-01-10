#pragma once
#include <Novice.h>
#include "Vec2.h"

class Player;
class Screen
{
public:

	static constexpr int kWindowWidth = 1280;
	static constexpr int kWindowHeight = 720;

	Screen() {
		Init();
	}

private:

	Vec2 mWorldCenter;	//���[���h�̒��S
	Vec2 mScreenShake;	//�V�F�C�N�l
	Vec2 mScroll;		//�X�N���[���l
	float mZoom;		//�Y�[���l

public:


	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �J�����V�F�C�N�i X�� �� Y�� �ǂ���������l �j
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <param name="condition">�V�F�C�N�������</param>
	void SetShake(int min, int max, bool condition);

	/// <summary>
	/// �J�����V�F�C�N�i X�� �� Y �� �ʂ̒l �j
	/// </summary>
	/// <param name="minX">�ŏ��l�i X�� �j</param>
	/// <param name="maxX">�ő�l�i X�� �j</param>
	/// <param name="minY">�ŏ��l�i Y�� �j</param>
	/// <param name="maxY">�ő�l�i Y�� �j</param>
	/// <param name="condition">�V�F�C�N�������</param>
	void SetShake(int minX, int maxX, int minY, int maxY, bool condition);

	/// <summary>
	/// �X�N���[��
	/// </summary>
	void SetScroll(Player& player);

	/// <summary>
	/// �Y�[��
	/// </summary>
	void SetZoom();


	//--------------------------------------------------------------------------------------------//


	/// <summary>
	/// ����`�悷��
	/// </summary>
	/// <param name="startposition">�`�悷����̎n�_���W</param>
	/// <param name="endposition">�`�悷����̏I�_���W</param>
	/// <param name="color">�`�悷��l�p�`�̐F</param>
	void DrawLine(Vec2 startposition, Vec2 endposition, unsigned int color = WHITE);

	/// <summary>
	/// �l�p�`��`�悷��
	/// </summary>
	/// <param name="position">�`�悷��l�p�`�̍�����W</param>
	/// <param name="width">�`�悷��l�p�`�̉���</param>
	/// <param name="height">�`�悷��l�p�`�̏c��</param>
	/// <param name="angle">�`�悷��l�p�`�̉�]�p</param>
	/// <param name="color">�`�悷��l�p�`�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawBox(Vec2 position, float width, float height, float angle = 0.0f, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// �ȉ~��`�悷��
	/// </summary>
	/// <param name="position">�ȉ~�̒��S���W</param>
	/// <param name="radiusX">�ȉ~�̔��a (X����) </param>
	/// <param name="radiusY">�ȉ~�̔��a (Y����) </param>
	/// <param name="angle">�ȉ~�̉�]�p(rad)</param>
	/// <param name="color">�ȉ~�̐F</param>
	void DrawEllipse(Vec2 position, float radiusX, float radiusY, float angle = 0.0f, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// �~��`�悷��
	/// </summary>
	/// <param name="position">�~�̒��S���W</param>
	/// <param name="radius">�~�̔��a</param>
	/// <param name="color">�~�̐F</param>
	void DrawCircle(Vec2 position, float radius, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	//----- DrawBox �Ƃ̈Ⴂ �� Position �����S���W�ł���Ƃ��� -----//
	/// <summary>
	/// �����`��`�悷��
	/// </summary>
	/// <param name="position">���S���W</param>
	/// <param name="size">�傫��(= ���a)</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawSquare(Vec2 position, float size, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// �����`��`�悷��
	/// </summary>
	/// <param name="position">���S���W</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	/// <param name="fillMode">�h��Ԃ����[�h</param>
	void DrawRectAngle(Vec2 position, float width, float height, unsigned int color = WHITE, FillMode fillMode = kFillModeSolid);

	/// <summary>
	/// �Î~��i�����`�j��`�悷��
	/// </summary>
	/// <param name="position">���S���W</param>
	/// <param name="width">����</param>
	/// <param name="height">�c��</param>
	/// <param name="angle">�X��</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawPicture(Vec2 position, float width, float height, float angle, float srcW, float srcH, float textureHandle, unsigned int color = WHITE);

	/// <summary>
	/// �Î~��i�����`�j��`�悷��
	/// </summary>
	/// <param name="position">���S���W</param>
	/// <param name="size">�傫��(= ���a)</param>
	/// <param name="angle">�X��</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawPicture(Vec2 position, float size, float angle, float srcW, float srcH, float textureHandle, unsigned int color = WHITE);

	/// <summary>
	/// �A�ԉ摜�i�����`�j��`�悷��
	/// </summary>
	/// <param name="position">���S���W</param>
	/// <param name="size">�傫��(= ���a)</param>
	/// <param name="srcX">�摜��̕`�悵�����͈͍�����W X�i�ϐ��j</param>
	/// <param name="srcW">�摜��̕`�悵�����͈͉���</param>
	/// <param name="srcH">�摜��̕`�悵�����͈͏c��</param>
	/// <param name="sheets">�摜����</param>
	/// <param name="frame">���t���[���Ő؂�ւ��邩</param>
	/// <param name="frameVariable">���Z���Ă���t���[���̕ϐ�</param>
	/// <param name="textureHandle">�e�N�X�`���̃n���h��</param>
	/// <param name="color">�`�悷��X�v���C�g�̐F</param>
	void DrawAnime(Vec2 position, float size, int srcX, int srcW, int srcH, int sheets, int frame, int& frameVariable, int textureHandle, unsigned int color = WHITE, Vec2 scaling = { 1.0f, 1.0f });


	//--------------------------------------------------------------------------------------------//


	/// <summary>
	/// �X�N���[�����W�ɕϊ�����
	/// </summary>
	Vec2 ScreenTransform(Vec2 position);
};


