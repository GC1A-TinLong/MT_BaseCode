#pragma once
#include <Novice.h>
#include <cassert>
#include <numbers>
#include <cmath>
#include <math.h>
#include <iostream>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Vector2Int {
	int x, y;
};
struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

void CameraControl(Vector3& cameraPosition, Vector3& cameraRotate);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

// For Line
struct Line {
	Vector3 origin;
	Vector3 diff;
};
struct Ray {
	Vector3 origin;
	Vector3 diff;
};
struct Segment {
	Vector3 origin;
	Vector3 diff;
};

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
float Length(const Vector2Int& v);
Vector2 Normailize(const Vector2Int& v);

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float scalar, const Vector3& v);

float Dot(Vector3& v1, Vector3& v2);
float Length(const Vector3& v);
Vector3 Normailize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

struct Matrix4x4 {
	float m[4][4];
};
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRotateXMatrix(const float& radian);
Matrix4x4 MakeRotateYMatrix(const float& radian);
Matrix4x4 MakeRotateZMatrix(const float& radian);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

struct Sphere {
	Vector3 center;
	float radius;
};
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
bool isCollideSphere(Sphere& sphere1, Sphere& sphere2);