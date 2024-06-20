#include <Novice.h>
#include "Function.h"
#include <imgui.h>
#include <algorithm>


const char kWindowTitle[] = "GC2A_08_チョウ_テンロウ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 worldRotate{};
	Vector3 translate{ 0,0,0 };
	Vector3 cameraRotate{ 0.26f,0,0 };
	Vector3 cameraPosition{ 0.0f,1.9f,-6.49f };

	Vector3 rotate{};
	OBB obb{
		.center{-1.0f,0.0f,0.0f},
		.orientations = {
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f}
		},
		.size{0.5f,0.5f,0.5f}
	};
	uint32_t obbColor = WHITE;

	AABB aabb{
		obb.size * -1,
		obb.size
	};

	Sphere sphere{
		.center{0.0f,0.0f,0.0f},
		.radius{0.5f}
	};
	uint32_t sphereColor = WHITE;

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

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, worldRotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		CameraControl(keys, cameraPosition, cameraRotate);

		if (IsCollideOBBSphere(obb, sphere, rotate)) {
			obbColor = RED;
		}
		else { obbColor = WHITE; }

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawAABB(aabb, viewProjectionMatrix, viewportMatrix, obbColor);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, sphereColor);

		ImGui::Begin("Debug Window");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat("RotateX", &rotate.x, 0.01f);
		ImGui::DragFloat("RotateY", &rotate.y, 0.01f);
		ImGui::DragFloat("RotateZ", &rotate.z, 0.01f);
		ImGui::DragFloat3("OBB.orientations[0]", &obb.orientations[0].x, 0.01f);
		ImGui::DragFloat3("OBB.orientations[1]", &obb.orientations[1].x, 0.01f);
		ImGui::DragFloat3("OBB.orientations[2]", &obb.orientations[2].x, 0.01f);
		ImGui::DragFloat3("OBB.size", &obb.size.x, 0.01f);
		ImGui::DragFloat3("Sphere.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("Sphere.radius", &sphere.radius, 0.01f);
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
