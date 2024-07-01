#pragma once
#include <Novice.h>
#include <cassert>
#include <numbers>
#include <cmath>
#include <math.h>
#include <iostream>
#include <imgui.h>
#include <algorithm>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

static inline const float deltaTime = 1.0f / 60.0f;

struct Vector2Int {
	int x, y;
};
struct Vector2 {
	float x, y;
};
struct Vector3 {
	float x, y, z;

	Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return*this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return*this; }
};

struct Matrix4x4 {
	float m[4][4];
};

struct Sphere {
	Vector3 center;
	float radius;
};

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

struct Plane {
	Vector3 normal;
	float distance;
};

struct Triangle {
	Vector3 vertics[3];
};

struct AABB {
	Vector3 min;
	Vector3 max;
};

struct OBB {
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

struct Spring {
	Vector3 anchor;
	float naturalLength;
	float stiffness;
	float dampingCoefficient;
};
struct Ball {
	Vector3 position;
	Vector3 velocity;
	Vector3 accerleration;
	float mass;
	float radius;
	uint32_t color;
};

struct CircularPoint {
	Vector3 p;
	float angle;
	float radiusFromCenter;
	bool start;
};

struct Pendulum {
	Vector3 anchor;
	float length;
	float angle;
	float angularVelocity;
	float angularAcceration;
};

struct ConicalPendulum {
	Vector3 anchor;
	float length;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};

void CameraControl(char* keys, Vector3& cameraPosition, Vector3& cameraRotate);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
float Length(const Vector2Int& v);
Vector2 Normalize(const Vector2Int& v);

Vector3 operator+(const Vector3& v);
Vector3 operator-(const Vector3& v);
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator+(const Vector3& v, const float num);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float scalar, const Vector3& v);
Vector3 operator*(const Vector3& v, float scalar);
Vector3 operator/(float s, const Vector3& v);
Vector3 operator/(const Vector3& v, float s);

float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t);
Vector3 Catmull(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t);
Vector3 Perpendicular(const Vector3& vector);

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
void DrawSegment(const Segment& segment, Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void DrawCatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void StartSpring(const Spring& spring, Ball& ball);
void DrawSpring(const Spring& spring, Ball& ball, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void StartCircularMotion(const Sphere& sphere, CircularPoint& point);
void DrawCircularMotion(const Sphere& sphere, CircularPoint& point, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void StartPendulumMotion(Pendulum& pendulum, Vector3& center);
void DrawPendulum(const Pendulum& pendulum, const Vector3& center, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
void StartConicalPendulumMotion(ConicalPendulum& conicalPendulum, Vector3& center);
void DrawConicalPendulum(const ConicalPendulum& conicalPendulum, const Vector3& center, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
template <int32_t N>
void Hierarchy3points(const Vector3(&scales)[N], const Vector3(&rotates)[N], const Vector3(&translates)[N]);
template <int32_t N>
void DrawHierarchy3points(const Vector3(&translates)[N], const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

bool IsCollideSphere(const Sphere& sphere1, const Sphere& sphere2);
bool IsCollideSpherePlane(const Sphere& sphere, const Plane& plane);
bool IsCollideSegmentPlane(const Segment& segment, const Plane& plane);
bool IsCollideTriangleSegment(const Triangle& triangle, const Segment& segment);
bool IsCollideAABB(const AABB& a, const AABB& b);
bool IsCollideAABBSphere(const AABB& aabb, const Sphere& sphere);
bool IsCollideAABBSegment(const AABB& aabb, const Segment& segment);
bool IsCollideOBBSphere(OBB& obb, const Sphere& sphere, Matrix4x4& rotateMatrix);

template<int32_t N>
inline void Hierarchy3points(const Vector3(&scales)[N], const Vector3(&rotates)[N], const Vector3(&translates)[N])
{
	Matrix4x4 shoulderWorldMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
	Matrix4x4 elbowLocalMatrix = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
	Matrix4x4 elbowWorldMatrix = elbowLocalMatrix * shoulderWorldMatrix;
	Matrix4x4 handLocalMatrix = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
	Matrix4x4 handWorldMatrix = handLocalMatrix * elbowWorldMatrix;
}

template<int32_t N>
inline void DrawHierarchy3points(const Vector3(&translates)[N], const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	Vector3 screenTranslate[3]{};
	for (int i = 0; i < N; i++) {
		screenTranslate[i]= Transform(Transform(translates[i], viewProjectionMatrix), viewportMatrix);
	}
	DrawSphere({ translates[0],0.05f }, viewProjectionMatrix, viewportMatrix, RED);
	DrawSphere({ translates[1],0.05f }, viewProjectionMatrix, viewportMatrix, GREEN);
	DrawSphere({ translates[2],0.05f }, viewProjectionMatrix, viewportMatrix, BLUE);
	Novice::DrawLine(int(screenTranslate[0].x), int(screenTranslate[0].y), int(screenTranslate[1].x), int(screenTranslate[1].y), WHITE);
	Novice::DrawLine(int(screenTranslate[1].x), int(screenTranslate[1].y), int(screenTranslate[2].x), int(screenTranslate[2].y), WHITE);
}
