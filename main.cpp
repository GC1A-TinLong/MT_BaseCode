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

	ConicalPendulum conicalPendulum{
		.anchor{0,1.0f,0},
		.length = 1.0f,
		.halfApexAngle = 0.7f,
		.angle = 0,
		.angularVelocity = 0,
	};
	Vector3 center{};

	bool start = false;

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

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;
		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		CameraControl(keys, cameraPosition, cameraRotate);

		ImGui::Begin("Debug Window");
		if (ImGui::Button("Start")) {
			start ^= true;
		}
		ImGui::DragFloat("Length", &conicalPendulum.length, 0.01f);
		ImGui::DragFloat("HalfApexAngle", &conicalPendulum.halfApexAngle, 0.01f);
		ImGui::InputFloat3("Center", &center.x,"%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		center.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
		center.y = conicalPendulum.anchor.y - height;
		center.z = conicalPendulum.anchor.z + std::sin(conicalPendulum.angle) * radius;

		conicalPendulum.length = std::clamp(conicalPendulum.length, 0.01f, std::numeric_limits<float>::infinity());
		conicalPendulum.halfApexAngle = std::clamp(conicalPendulum.halfApexAngle, -1.57f, 1.57f);
		if (start) {
			StartConicalPendulumMotion(conicalPendulum, center);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawConicalPendulum(conicalPendulum, center, viewProjectionMatrix, viewportMatrix, BLUE);

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
