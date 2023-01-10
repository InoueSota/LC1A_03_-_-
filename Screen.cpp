#include "Screen.h"
#include "MatVec.h"
#include "Quad.h"
#include "Function.h"
#include "Key.h"



void Screen::Init() {
	mWorldCenter = { 0.0f, kWindowHeight };
	mScroll.setZero();
	mZoom = 1.0f;
	mScreenShake.setZero();
};

void Screen::SetShake(int min, int max, bool condition) {

	if (condition == true)
	{
		mScreenShake.x = RAND(min, max);
		mScreenShake.y = RAND(min, max);
	}
	else
	{
		mScreenShake = { 0.0f, 0.0f };
	}

}

void Screen::SetShake(int minX, int maxX, int minY, int maxY, bool condition) {

	if (condition == true)
	{
		mScreenShake.x = RAND(minX, maxX);
		mScreenShake.y = RAND(minY, maxY);
	}
	else
	{
		mScreenShake = { 0.0f, 0.0f };
	}

}

void Screen::SetScroll(Player& player) {

}

void Screen::SetZoom() {

	if (Key::IsPress(DIK_UP))
	{
		mZoom += 0.01f;
	}
	else if (Key::IsPress(DIK_DOWN))
	{
		mZoom -= 0.01f;
	}

}


//--------------------------------------------------------------------------------------------//


void Screen::DrawLine(Vec2 startposition, Vec2 endposition, unsigned int color) {
	startposition = ScreenTransform(startposition);
	endposition = ScreenTransform(endposition);
	Novice::DrawLine((int)startposition.x, (int)startposition.y, (int)endposition.x, (int)endposition.y, color);
}


void Screen::DrawBox(Vec2 Position, float w, float h, float angle, unsigned int color, FillMode fillMode) {
	Position = ScreenTransform(Position);
	Novice::DrawBox((int)Position.x, (int)Position.y, w * mZoom, h * mZoom, angle, color, fillMode);
}


void Screen::DrawEllipse(Vec2 Position, float radiusX, float radiusY, float angle, unsigned int color, FillMode fillMode) {
	Position = ScreenTransform(Position);
	Novice::DrawEllipse((int)Position.x, (int)Position.y, radiusX * mZoom, radiusY * mZoom, angle, color, fillMode);
}


void Screen::DrawCircle(Vec2 Position, float radius, unsigned int color, FillMode fillMode) {
	DrawEllipse(Position, radius, radius, 0.0f, color, fillMode);
}


void Screen::DrawRectAngle(Vec2 Position, float Width, float Height, unsigned int color, FillMode fillMode) {
	Quad OriginalPosition = RectAssign(Width, Height);
	Quad Rect = Transform(OriginalPosition, MakeAffineMatrix({ mZoom, mZoom }, 0.0f, ScreenTransform(Position)));
	if (fillMode == kFillModeSolid) {
		Novice::DrawQuad((int)Rect.LeftTop.x, (int)Rect.LeftTop.y, (int)Rect.RightTop.x, (int)Rect.RightTop.y, (int)Rect.LeftBottom.x, (int)Rect.LeftBottom.y, (int)Rect.RightBottom.x, (int)Rect.RightBottom.y, 0, 0, 0, 0, 0, color);
	}
	else {
		Novice::DrawLine((int)Rect.LeftTop.x, (int)Rect.LeftTop.y, (int)Rect.RightTop.x, (int)Rect.RightTop.y, color);
		Novice::DrawLine((int)Rect.LeftTop.x, (int)Rect.LeftTop.y, (int)Rect.LeftBottom.x, (int)Rect.LeftBottom.y, color);
		Novice::DrawLine((int)Rect.RightTop.x, (int)Rect.RightTop.y, (int)Rect.RightBottom.x, (int)Rect.RightBottom.y, color);
		Novice::DrawLine((int)Rect.LeftBottom.x, (int)Rect.LeftBottom.y, (int)Rect.RightBottom.x, (int)Rect.RightBottom.y, color);
	}
}


void Screen::DrawSquare(Vec2 Position, float size, unsigned int color, FillMode fillMode) {
	DrawRectAngle(Position, size, size, color, fillMode);
}


void Screen::DrawPicture(Vec2 Position, float width, float height, float angle, float srcW, float srcH, float textureHandle, unsigned int color) {
	Quad OriginalPosition = RectAssign(width, height);
	Quad Rect = Transform(OriginalPosition, MakeAffineMatrix({ mZoom, mZoom }, angle, ScreenTransform(Position)));
	Novice::DrawQuad((int)Rect.LeftTop.x, (int)Rect.LeftTop.y, (int)Rect.RightTop.x, (int)Rect.RightTop.y, (int)Rect.LeftBottom.x, (int)Rect.LeftBottom.y, (int)Rect.RightBottom.x, (int)Rect.RightBottom.y, 0, 0, srcW, srcH, textureHandle, color);
}


void Screen::DrawPicture(Vec2 Position, float size, float angle, float srcW, float srcH, float textureHandle, unsigned int color) {
	DrawPicture(Position, size, size, angle, srcW, srcH, textureHandle, color);
}


void Screen::DrawAnime(Vec2 Position, float size, int srcX, int srcW, int srcH, int sheets, int frame, int& frameVariable, int textureHandle, unsigned int color, Vec2 scaling) {
	Quad OriginalPosition = RectAssign(size, size);
	Quad Rect = Transform(OriginalPosition, MakeAffineMatrix(scaling, 0.0f, ScreenTransform(Position)));
	srcX = srcW * (frameVariable / frame);
	if (srcX >= srcW * sheets) {
		frameVariable = 0;
		srcX = 0;
	}
	Novice::DrawQuad((int)Rect.LeftTop.x, (int)Rect.LeftTop.y, (int)Rect.RightTop.x, (int)Rect.RightTop.y, (int)Rect.LeftBottom.x, (int)Rect.LeftBottom.y, (int)Rect.RightBottom.x, (int)Rect.RightBottom.y, srcX, 0, srcW, srcH, textureHandle, color);
}


//--------------------------------------------------------------------------------------------//


Vec2 Screen::ScreenTransform(Vec2 Position) {

	return{
		Position.x * mZoom - mScroll.x + mWorldCenter.x + mScreenShake.x,
		Position.y * mZoom * -1 - mScroll.y + mWorldCenter.y + mScreenShake.y
	};
}