#include <Novice.h>
#include "Function.h"
#include <imgui.h>

const char kWindowTitle[] = "GC2A_08_チョウ_テンロウ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 rotate{};
	Vector3 translate{ 0,0,0 };
	Vector3 cameraRotate{ 0.26f,0,0 };
	Vector3 cameraPosition{ 0.0f,1.9f,-6.49f };

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.7f,0.0f},
		{0.3f,0.0f,0.0f},
	};
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 shoulderWorldMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 elbowLocalMatrix = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 elbowWorldMatrix = elbowLocalMatrix * shoulderWorldMatrix;
		Matrix4x4 handLocalMatrix = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		Matrix4x4 handWorldMatrix = handLocalMatrix * elbowWorldMatrix;

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix4x4 elbowWorldViewProjectionMatrix = elbowWorldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 handWorldViewProjectionMatrix = handWorldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		CameraControl(keys, cameraPosition, cameraRotate);

		Hierarchy3points(scales, rotates, translates);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawHierarchy3points(translates, viewProjectionMatrix, viewportMatrix);

		ImGui::Begin("Debug Window");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("Translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("Translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("Translates[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("Rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("Rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("Rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("Scales[0]", &scales[0].x, 0.01f);
		ImGui::DragFloat3("Scales[1]", &scales[1].x, 0.01f);
		ImGui::DragFloat3("Scales[2]", &scales[2].x, 0.01f);
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
