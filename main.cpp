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

	Vector3 points[3]{};
	points[0] = { 0.0f,1.0f,-1.0f };
	points[1] = { 0.5f,1.0f,1.0f };
	points[2] = { -0.5f,1.0f,1.0f };
	Vector3 v1 = points[1] - points[0];
	Vector3 v2 = points[2] - points[1];
	Vector3 normal = Normalize(Cross(v1, v2));

	Plane plane{
		normal,
		Dot(points[0],normal)
	};

	Sphere sphere{
		{0,0,0},
		1.0f
	};
	unsigned int color = WHITE;


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

		CameraControl(keys, cameraPosition, cameraRotate);

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		if (isCollideSpherePlane(sphere, plane)) {
			color = RED;
		}
		else {
			color = WHITE;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, BLUE);

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, color);

		ImGui::Begin("Debug Window");
		ImGui::DragFloat3("CameraTranslate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("Plane.normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("Plane.distance", &plane.distance, 0.01f);
		ImGui::DragFloat3("Sphere.center", &sphere.center.x, 0.01f);
		ImGui::DragFloat("Sphere.radius", &sphere.radius, 0.01f);
		ImGui::End();
		plane.normal = Normalize(plane.normal);

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
