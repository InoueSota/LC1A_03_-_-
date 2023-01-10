#include "main.h"

const char kWindowTitle[] = "LC1A_03_";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, Screen::kWindowWidth, Screen::kWindowHeight);

	int ground = Novice::LoadTexture("./Resources/Ground.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {

		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		Key::Update();

		///
		/// ↓更新処理ここから
		///

		player.Update();
		firework.Update(player);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox(0, 0, Screen::kWindowWidth, Screen::kWindowHeight, 0.0f, BLACK, kFillModeSolid);
		screen.DrawPicture({ Screen::kWindowWidth / 2.0, 16.0 }, Screen::kWindowWidth, 32, 0.0f, Screen::kWindowWidth, 32, ground, WHITE);

		Novice::SetBlendMode(kBlendModeAdd);
		firework.Draw(screen);
		player.Draw(screen);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
