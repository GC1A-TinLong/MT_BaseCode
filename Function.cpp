#include "Function.h"

void CameraControl(char* keys, Vector3& cameraPosition, Vector3& cameraRotate) {
	if (keys[DIK_Q]) {
		cameraPosition.y += 0.06f;
	}
	if (keys[DIK_E]) {
		cameraPosition.y -= 0.06f;
	}
	if (keys[DIK_A] && !keys[DIK_LSHIFT]) {
		cameraPosition.x -= 0.05f;
	}
	if (keys[DIK_D] && !keys[DIK_LSHIFT]) {
		cameraPosition.x += 0.05f;
	}
	if (keys[DIK_W] && !keys[DIK_LSHIFT]) {
		cameraPosition.z += 0.05f;
	}
	if (keys[DIK_S] && !keys[DIK_LSHIFT]) {
		cameraPosition.z -= 0.05f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_W]) {
		cameraRotate.x -= 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_S]) {
		cameraRotate.x += 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_A]) {
		cameraRotate.y -= 0.02f;
	}
	if (keys[DIK_LSHIFT] && keys[DIK_D]) {
		cameraRotate.y += 0.02f;
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, (y + row * kRowHeight) + kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2)
{
	return {
		v1.x - v2.x,
		v1.y - v2.y
	};
}

float Length(const Vector2Int& v)
{
	return sqrtf(float(v.x * v.x + v.y * v.y));
}

Vector2 Normalize(const Vector2Int& v)
{
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
	};
}

Vector3 operator+(const Vector3& v)
{
	return v;
}

Vector3 operator-(const Vector3& v)
{
	return { -v.x,-v.y,-v.z };
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 operator+(const Vector3& v, const float num)
{
	return { v.x + num,v.y + num,v.z + num };
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 operator*(float scalar, const Vector3& v)
{
	Vector3 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

Vector3 operator*(const Vector3& v, float scalar)
{
	Vector3 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

Vector3 operator/(float s, const Vector3& v)
{
	return v * (1.0f / s);
}

Vector3 operator/(const Vector3& v, float s)
{
	return v * (1.0f / s);
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float Length(const Vector3& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v)
{
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
		v.z / Length(v)
	};
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return { (v1.y * v2.z) - (v1.z * v2.y) , (v1.z * v2.x) - (v1.x * v2.z),(v1.x * v2.y) - (v1.y * v2.x) };
}

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
	return Dot(v1, Normalize(v2)) * Normalize(v2);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
	Vector3 project = Project(point - segment.origin, segment.diff);
	return segment.origin + project;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
	return{
		(t * v1.x + (1.0f - t) * v2.x),
		(t * v1.y + (1.0f - t) * v2.y),
		(t * v1.z + (1.0f - t) * v2.z),
	};
}

Vector3 Bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, float t)
{
	Vector3 p0p1 = Lerp(p0, p1, t);
	Vector3 p1p2 = Lerp(p1, p2, t);
	return Lerp(p0p1, p1p2, t);
}

Vector3 Catmull(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{
	Vector3 result{};
	result.x = 0.5f * ((-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * powf(t, 3.0f) + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * powf(t, 2.0f) +
		(-p0.x + p2.x) * t + (2 * p1.x));
	result.y = 0.5f * ((-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * powf(t, 3.0f) + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * powf(t, 2.0f) +
		(-p0.y + p2.y) * t + (2 * p1.y));
	result.z = 0.5f * ((-p0.z + 3 * p1.z - 3 * p2.z + p3.z) * powf(t, 3.0f) + (2 * p0.z - 5 * p1.z + 4 * p2.z - p3.z) * powf(t, 2.0f) +
		(-p0.z + p2.z) * t + (2 * p1.z));
	return result;
}

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result{};
	float det =
		(m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])
		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])
		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	result.m[0][0] = ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])) / det;
	result.m[0][1] = (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])) / det;
	result.m[0][2] = ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])) / det;
	result.m[0][3] = (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])) / det;

	result.m[1][0] = (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2])) / det;
	result.m[1][1] = ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2])) / det;
	result.m[1][2] = (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2])) / det;
	result.m[1][3] = ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2])) / det;

	result.m[2][0] = ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])) / det;
	result.m[2][1] = (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])) / det;
	result.m[2][2] = ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])) / det;
	result.m[2][3] = (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])) / det;

	result.m[3][0] = (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1])) / det;
	result.m[3][1] = ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1])) / det;
	result.m[3][2] = (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1])) / det;
	result.m[3][3] = ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1])) / det;

	return result;
}

Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
}

Matrix4x4 MakeIdentity4x4()
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result = MakeIdentity4x4();
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Matrix4x4 MakeRotateXMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 MakeRotateYMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cosf(radian);
	result.m[0][2] = -sinf(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 MakeRotateZMatrix(const float& radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Matrix4x4 result = MakeTranslateMatrix(translate);
	Matrix4x4 rotateXmatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYmatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZmatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZmatrix = rotateXmatrix * rotateYmatrix * rotateZmatrix;
	result.m[0][0] = scale.x * rotateXYZmatrix.m[0][0];
	result.m[0][1] = scale.x * rotateXYZmatrix.m[0][1];
	result.m[0][2] = scale.x * rotateXYZmatrix.m[0][2];
	result.m[1][0] = scale.y * rotateXYZmatrix.m[1][0];
	result.m[1][1] = scale.y * rotateXYZmatrix.m[1][1];
	result.m[1][2] = scale.y * rotateXYZmatrix.m[1][2];
	result.m[2][0] = scale.z * rotateXYZmatrix.m[2][0];
	result.m[2][1] = scale.z * rotateXYZmatrix.m[2][1];
	result.m[2][2] = scale.z * rotateXYZmatrix.m[2][2];
	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result{};
	result.m[0][0] = 2 / (right - left);
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;
	return result;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result{};
	assert(nearClip != 0);
	result.m[0][0] = (1 / tanf(fovY / 2)) / aspectRatio;
	result.m[1][1] = 1 / tanf(fovY / 2);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = -(nearClip * farClip) / (farClip - nearClip);
	return result;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result{};
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;
	return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;	//Gridの半分の幅
	const uint32_t kSubDivision = 10;	//分割数
	const float kGridEveryLength = (kGridHalfWidth * 2.0f) / float(kSubDivision);//1つ分の長さ = 0.4

	for (uint32_t xIndex = 0; xIndex <= kSubDivision; xIndex++)
	{
		// -半分、+Gridの半分
		float x = -kGridHalfWidth + (xIndex * kGridEveryLength);
		Vector3 start = { x,0.0f,-kGridHalfWidth };
		Vector3 end = { x,0.0f,kGridHalfWidth };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, 0xAAAAAAFF);
		if (xIndex == 5) {
			Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, BLACK);
		}
	}
	for (uint32_t zIndex = 0; zIndex <= kSubDivision; zIndex++)
	{
		// -半分、+Gridの半分
		float z = -kGridHalfWidth + (zIndex * kGridEveryLength);
		Vector3 start = { -kGridHalfWidth,0.0f,z };
		Vector3 end = { kGridHalfWidth,0.0f,z };

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, 0xAAAAAAFF);
		if (zIndex == 5) {
			Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, BLACK);
		}
	}
}

void DrawSegment(const Segment& segment, Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Transform(Transform(segment.origin + segment.diff, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const float pi = (float)std::numbers::pi;
	const uint32_t kSubDivision = 16;//分割数
	const float kLonEvery = pi / kSubDivision;;//経度分割1つ分の角度
	const float kLatEvery = (2 * pi) / kSubDivision;;//緯度分割1つ分の角度
	//緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubDivision; latIndex++) {
		float lat = (-pi / 2.0f) + (kLatEvery * latIndex);//現在の緯度
		//経度の方向に分割 0～2π
		for (uint32_t lonIndex = 0; lonIndex < kSubDivision; lonIndex++) {
			float lon = lonIndex * kLonEvery;//現在の経度

			//World座標系でのa,b,cを求める

			Vector3 a, b, c;
			a = { sphere.radius * (cosf(lat) * cosf(lon)) + sphere.center.x,sphere.radius * (sinf(lat)) + sphere.center.y,
				sphere.radius * (cosf(lat) * sinf(lon)) + sphere.center.z };
			b = { sphere.radius * (cosf(lat + kLatEvery) * cosf(lon)) +
				sphere.center.x,sphere.radius * (sinf(lat + kLatEvery)) + sphere.center.y,
				sphere.radius * (cosf(lat + kLatEvery) * sinf(lon)) + sphere.center.z };
			c = { sphere.radius * (cosf(lat) * cosf(lon + kLonEvery)) + sphere.center.x,sphere.radius * (sinf(lat)) + sphere.center.y,
				sphere.radius * (cosf(lat) * sinf(lon + kLonEvery)) + sphere.center.z };
			//a,b,cをScreen座標系まで変換
			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
			//ab,bcで線を引く
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = plane.distance * plane.normal;
	Vector3 perpendiculars[4]{};
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4]{};
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = 2.0f * perpendiculars[index];
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenVertics[3]{};
	for (int i = 0; i < 3; i++) {
		screenVertics[i] = Transform(Transform(triangle.vertics[i], viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawTriangle(int(screenVertics[0].x), int(screenVertics[0].y), int(screenVertics[1].x), int(screenVertics[1].y),
		int(screenVertics[2].x), int(screenVertics[2].y), color, kFillModeWireFrame);
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 bot[4]{};
	for (int i = 0; i < 4; i++) {
		bot[i] = aabb.min;
	}
	bot[1].z += aabb.max.z;
	bot[2] = { aabb.min.x + aabb.max.x, aabb.min.y, aabb.min.z + aabb.max.z };
	bot[3].x += aabb.max.x;

	Vector3 top[4]{};
	for (int i = 0; i < 4; i++) {
		top[i] = aabb.min;
		top[i].y = aabb.max.y;
	}
	top[1].z += aabb.max.z;
	top[2] = { aabb.min.x + aabb.max.x,aabb.max.y,aabb.min.z + aabb.max.z };
	top[3].x += aabb.max.x;

	Vector3 screenBot[4]{};
	Vector3 screenTop[4]{};
	for (int i = 0; i < 4; i++) {
		screenBot[i] = Transform(Transform(bot[i], viewProjectionMatrix), viewportMatrix);
		screenTop[i] = Transform(Transform(top[i], viewProjectionMatrix), viewportMatrix);
	}

	for (int i = 0; i < 3; i++) {
		Novice::DrawLine(int(screenBot[i].x), int(screenBot[i].y), int(screenBot[i + 1].x), int(screenBot[i + 1].y), color);
		Novice::DrawLine(int(screenTop[i].x), int(screenTop[i].y), int(screenTop[i + 1].x), int(screenTop[i + 1].y), color);
	}
	Novice::DrawLine(int(screenBot[3].x), int(screenBot[3].y), int(screenBot[0].x), int(screenBot[0].y), color);
	Novice::DrawLine(int(screenTop[3].x), int(screenTop[3].y), int(screenTop[0].x), int(screenTop[0].y), color);
	for (int i = 0; i < 4; i++) {
		Novice::DrawLine(int(screenBot[i].x), int(screenBot[i].y), int(screenTop[i].x), int(screenTop[i].y), color);
	}
}

void DrawBezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const int kSegmentNum = 16;
	for (int i = 0; i < kSegmentNum; i++) {
		float t0 = i / (float)kSegmentNum;
		float t1 = (i + 1) / (float)kSegmentNum;

		Vector3 bezier0 = Bezier(p0, p1, p2, t0);
		Vector3 bezier1 = Bezier(p0, p1, p2, t1);

		Vector3 screenBezier0 = Transform(Transform(bezier0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenBezier1 = Transform(Transform(bezier1, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(screenBezier0.x), int(screenBezier0.y), int(screenBezier1.x), int(screenBezier1.y), color);
		if (i == 0) {
			Novice::DrawEllipse(int(screenBezier0.x), int(screenBezier0.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
		if (i == (kSegmentNum / 2) - 1 || i == kSegmentNum - 1) {
			Novice::DrawEllipse(int(screenBezier1.x), int(screenBezier1.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
	}
}

void StartSpring(const Spring& spring, Ball& ball)
{
	float deltaTime = 1.0f / 60.0f;

	Vector3 diff = ball.position - spring.anchor;
	float length = Length(diff);
	if (length != 0) {
		Vector3 direction = Normalize(diff);
		Vector3 resetPosition = spring.anchor + direction * spring.naturalLength;
		Vector3 displacement = length * (ball.position - resetPosition);
		Vector3 restoringForce = -spring.stiffness * displacement;
		Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
		Vector3 force = restoringForce + dampingForce;
		ball.accerleration = force / ball.mass;
	}
	const Vector3 gravity = { 0.0f,-9.8f,0.0f };
	ball.velocity += (ball.accerleration + gravity) * deltaTime;
	ball.position += ball.velocity * deltaTime;
}

void DrawSpring(const Spring& spring, Ball& ball, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	Vector3 diff = ball.position - spring.anchor;

	Vector3 screenAnchor = Transform(Transform(spring.anchor, viewProjectionMatrix), viewportMatrix);
	Vector3 screenBallPos = Transform(Transform(ball.position, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(screenAnchor.x), int(screenAnchor.y), int(screenBallPos.x), int(screenBallPos.y), WHITE);
	DrawSphere({ ball.position,ball.radius }, viewProjectionMatrix, viewportMatrix, ball.color);
}

void StartCircularMotion(const Sphere& sphere, CircularPoint& point)
{
	float deltaTime = 1.0f / 60.0f;
	float angularVelocity = 3.14f;
	point.angle += angularVelocity * deltaTime;

	point.p = {
		sphere.center.x + std::cos(point.angle) * point.radiusFromCenter,
		sphere.center.y + std::sin(point.angle) * point.radiusFromCenter,
		sphere.center.z,
	};
}

void DrawCircularMotion(const Sphere& sphere, CircularPoint& point, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	if (point.start) {
		DrawSphere({ point.p,sphere.radius }, viewProjectionMatrix, viewportMatrix, color);
	}
	else {
		Vector3 origin = sphere.center;
		origin.x = sphere.center.x + point.radiusFromCenter;
		DrawSphere({ origin,sphere.radius }, viewProjectionMatrix, viewportMatrix, color);
	}
}

void DrawPendulum(const Pendulum& pendulum, const Vector3& center, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenAnchor = Transform(Transform(pendulum.anchor, viewProjectionMatrix), viewportMatrix);
	Vector3 screenCenter = Transform(Transform(center, viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(screenAnchor.x), int(screenAnchor.y), int(screenCenter.x), int(screenCenter.y), WHITE);
	DrawSphere({ center,0.1f }, viewProjectionMatrix, viewportMatrix, color);
}

void DrawCatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const int kSegmentNum = 16;
	for (int i = 0; i < kSegmentNum; i++) {
		float t0 = i / (float)kSegmentNum;
		float t1 = (i + 1) / (float)kSegmentNum;

		Vector3 catmull0 = Catmull(p0, p0, p1, p2, t0);
		Vector3 catmull1 = Catmull(p0, p0, p1, p2, t1);

		Vector3 screenCatmull0 = Transform(Transform(catmull0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenCatmull1 = Transform(Transform(catmull1, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenCatmull0.x, (int)screenCatmull0.y, (int)screenCatmull1.x, (int)screenCatmull1.y, color);
		if (i == 0) {
			Novice::DrawEllipse(int(screenCatmull0.x), int(screenCatmull0.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
	}
	for (int i = 0; i < kSegmentNum; i++) {
		float t0 = i / (float)kSegmentNum;
		float t1 = (i + 1) / (float)kSegmentNum;

		Vector3 catmull0 = Catmull(p0, p1, p2, p3, t0);
		Vector3 catmull1 = Catmull(p0, p1, p2, p3, t1);

		Vector3 screenCatmull0 = Transform(Transform(catmull0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenCatmull1 = Transform(Transform(catmull1, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenCatmull0.x, (int)screenCatmull0.y, (int)screenCatmull1.x, (int)screenCatmull1.y, color);
		if (i == 0) {
			Novice::DrawEllipse(int(screenCatmull0.x), int(screenCatmull0.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
	}
	for (int i = 0; i < kSegmentNum; i++) {
		float t0 = i / (float)kSegmentNum;
		float t1 = (i + 1) / (float)kSegmentNum;

		Vector3 catmull0 = Catmull(p1, p2, p3, p3, t0);
		Vector3 catmull1 = Catmull(p1, p2, p3, p3, t1);

		Vector3 screenCatmull0 = Transform(Transform(catmull0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenCatmull1 = Transform(Transform(catmull1, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine((int)screenCatmull0.x, (int)screenCatmull0.y, (int)screenCatmull1.x, (int)screenCatmull1.y, color);
		if (i == 0) {
			Novice::DrawEllipse(int(screenCatmull0.x), int(screenCatmull0.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
		else if (i == kSegmentNum - 1) {
			Novice::DrawEllipse(int(screenCatmull1.x), int(screenCatmull1.y), 3, 3, 0.0f, BLACK, kFillModeSolid);
		}
	}
}

bool IsCollideSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	float distance = Length(sphere2.center - sphere1.center);
	if (distance <= sphere1.radius + sphere2.radius) {
		return true;
	}
	return false;
}

Vector3 Perpendicular(const Vector3& vector)
{
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

bool IsCollideSpherePlane(const Sphere& sphere, const Plane& plane)
{
	float distance = (Dot(plane.normal, sphere.center) - plane.distance);
	if (fabsf(distance) - sphere.radius <= 0) {
		return true;
	}
	return false;
}

bool IsCollideLinePlane(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) { return false; }	// when perpendicular -> never colliding

	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	if (t >= 0 && t <= 1.0f) {
		return true;
	}
	return false;
}

bool IsCollideTriangleLine(const Triangle& triangle, const Segment& segment)
{
	// cross(vector1,vector2)↓
	Vector3 normal = Normalize(Cross((triangle.vertics[1] - triangle.vertics[0]), (triangle.vertics[2] - triangle.vertics[1])));
	float dot = Dot(normal, segment.diff);
	if (dot == 0.0f) { return false; }	// when perpendicular -> never colliding
	float t = (Dot(triangle.vertics[0], normal) - Dot(segment.origin, normal)) / dot;

	Vector3 p = segment.origin + t * segment.diff;
	Vector3 v01 = triangle.vertics[1] - triangle.vertics[0];
	Vector3 v12 = triangle.vertics[2] - triangle.vertics[1];
	Vector3 v20 = triangle.vertics[0] - triangle.vertics[2];
	Vector3 v0p = p - triangle.vertics[0];
	Vector3 v1p = p - triangle.vertics[1];
	Vector3 v2p = p - triangle.vertics[2];

	Vector3 cross01 = Cross(v01, v1p);
	Vector3 cross12 = Cross(v12, v2p);
	Vector3 cross20 = Cross(v20, v0p);

	if (Dot(cross01, normal) >= 0.0f && Dot(cross12, normal) >= 0.0f && Dot(cross20, normal) >= 0.0f) {
		return true;
	}
	return false;
}

bool IsCollideAABB(const AABB& a, const AABB& b)
{
	if ((a.min.x <= b.min.x + b.max.x && a.min.x + a.max.x >= b.min.x) &&
		(a.min.y <= b.min.y + b.max.y && a.min.y + a.max.y >= b.min.y) &&
		(a.min.z <= b.min.z + b.max.z && a.min.z + a.max.z >= b.min.z))
	{
		return true;
	}
	else { return false; }
}

bool IsCollideAABBSphere(const AABB& aabb, const Sphere& sphere)
{
	Vector3 closestPoint{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y) ,
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z) };
	float distance = Length(closestPoint - sphere.center);

	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

bool IsCollideAABBSegment(const AABB& aabb, const Segment& segment)
{
	float txMin = (aabb.min.x - segment.origin.x) / segment.diff.x;
	float txMax = (aabb.min.x + aabb.max.x - segment.origin.x) / segment.diff.x;
	float tyMin = (aabb.min.y - segment.origin.y) / segment.diff.y;
	float tyMax = (aabb.min.y + aabb.max.y - segment.origin.y) / segment.diff.y;
	float tzMin = (aabb.min.z - segment.origin.z) / segment.diff.z;
	float tzMax = (aabb.min.z + aabb.max.z - segment.origin.z) / segment.diff.z;

	float tNearX = min(txMin, txMax);
	float tNearY = min(tyMin, tyMax);
	float tNearZ = min(tzMin, tzMax);
	float tFarX = max(txMin, txMax);
	float tFarY = max(tyMin, tyMax);
	float tFarZ = max(tzMin, tzMax);

	// setting it to infinite for however small/big it is, it still able to track down the number (closest/furthest)
	float tmin = -std::numeric_limits<float>::infinity();
	float tmax = +std::numeric_limits<float>::infinity();

	if (segment.diff.x != 0) {
		tmin = max(tmin, tNearX);
		tmax = min(tmax, tFarX);
	}
	else {
		if (segment.origin.x<aabb.min.x || segment.origin.x>aabb.min.x + aabb.max.x) {
			return false;
		}
	}
	if (segment.diff.y != 0) {
		tmin = max(tmin, tNearY);
		tmax = min(tmax, tFarY);
	}
	else {
		if (segment.origin.y<aabb.min.y || segment.origin.y>aabb.min.y + aabb.max.y) {
			return false;
		}
	}
	if (segment.diff.z != 0) {
		tmin = max(tmin, tNearZ);
		tmax = min(tmax, tFarZ);
	}
	else {
		if (segment.origin.z<aabb.min.z || segment.origin.z>aabb.min.z + aabb.max.z) {
			return false;
		}
	}

	return tmin <= tmax && tmax >= 0;
}

bool IsCollideOBBSphere(OBB& obb, const Sphere& sphere, Matrix4x4& rotateMatrix)
{
	obb.orientations[0].x = rotateMatrix.m[0][0];
	obb.orientations[0].y = rotateMatrix.m[0][1];
	obb.orientations[0].z = rotateMatrix.m[0][2];

	obb.orientations[1].x = rotateMatrix.m[1][0];
	obb.orientations[1].y = rotateMatrix.m[1][1];
	obb.orientations[1].z = rotateMatrix.m[1][2];

	obb.orientations[2].x = rotateMatrix.m[2][0];
	obb.orientations[2].y = rotateMatrix.m[2][1];
	obb.orientations[2].z = rotateMatrix.m[2][2];

	Matrix4x4 obbWorldMatrix = {
		obb.orientations[0].x,obb.orientations[0].y,obb.orientations[0].z,0,
		obb.orientations[1].x,obb.orientations[1].y,obb.orientations[1].z,0,
		obb.orientations[2].x,obb.orientations[2].y,obb.orientations[2].z,0,
		0,0,0,1.0f
	};
	Matrix4x4 inverseObbWorldMatrix = Transpose(obbWorldMatrix);

	Vector3 centerInObbLocalSpace = Transform(sphere.center, inverseObbWorldMatrix);

	AABB aabbObbLocal = {
		obb.size * -1.0f,
		aabbObbLocal.min + obb.size
	};
	Sphere sphereObbLocal = {
		centerInObbLocalSpace,
		sphere.radius
	};

	return IsCollideAABBSphere(aabbObbLocal, sphereObbLocal);
}