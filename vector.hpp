#pragma once

#include <Windows.h>
#include <math.h>

struct Vector3
{
public:
	float x, y, z;

#define M_PI_2 1.57079632679489661923
#define M_PI 3.14159265358979323846
#define RAD_TO_DEG 180 / 3.141592654f


	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector3& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vector3 operator*=(float v)
	{
		x *= v; y *= v; z *= v;
		return *this;
	}

	Vector3 operator*(float v) const
	{
		return Vector3(x * v, y * v, z * v);
	}

	Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	float distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	float length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float dot(Vector3 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	bool operator==(const Vector3& v) const
	{
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return true;
		else
			return false;
	}

	bool operator!=(const Vector3& v) const
	{
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return false;
		else
			return true;
	}
};

struct Vector2
{
public:
	float x, y;

	Vector2()
	{
		x = y = 0.0f;
	}

	Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	Vector2(float X, float Y) {
		x = X; y = Y;
	}

	void operator -= (Vector2 other)
	{
		// Update this vector's values
		x -= other.x;
		y -= other.y;
	}

	Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	float distance(Vector2 b)
	{
		return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
	}

	bool zero() const
	{
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}

	Vector2 normalize()
	{

		if (x < -89)
			x = -89;


		else if (x > 89)
			x = 89;


		if (y < -360)
			y += 360;


		else if (y > 360)
			y -= 360;

		return { x,y };
	}
};


class Vector4
{
public:
	float x, y, z, w;

	Vector4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4 operator*(float v) const
	{
		return Vector4(x * v, y * v, z * v, w * v);
	}
};