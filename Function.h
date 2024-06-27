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

bool IsCollideSphere(const Sphere& sphere1, const Sphere& sphere2);
Vector3 Perpendicular(const Vector3& vector);
bool IsCollideSpherePlane(const Sphere& sphere, const Plane& plane);
bool IsCollideLinePlane(const Segment& segment, const Plane& plane);
bool IsCollideTriangleLine(const Triangle& triangle, const Segment& segment);
bool IsCollideAABB(const AABB& a, const AABB& b);
bool IsCollideAABBSphere(const AABB& aabb, const Sphere& sphere);
bool IsCollideAABBSegment(const AABB& aabb, const Segment& segment);
bool IsCollideOBBSphere(OBB& obb, const Sphere& sphere, Matrix4x4& rotateMatrix);