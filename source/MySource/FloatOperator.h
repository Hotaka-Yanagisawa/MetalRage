////////////////////////////////
//ì¬ÒF–ö‘ò”¿‹M
//
//2020/12/10 ì¬
////////////////////////////////
#pragma once

#include <DirectXMath.h>

class Float2
{
public:
	Float2(float v) :x(v), y(v){}
	Float2(float x, float y) :x(x), y(y) {}
	~Float2() {}

	DirectX::XMFLOAT2 DXFloat2() { return DirectX::XMFLOAT2(x, y); }

	//‘ã“ü‰‰Zq
	Float2 &operator =(const Float2 &r)
	{
		x = r.x;
		y = r.y;
		return *this;
	}

	Float2 &operator =(const float &v)
	{
		x = v;
		y = v;
		return *this;
	}

	//Zp‰‰Zq
	Float2& operator += (Float2 &ch)
	{
		x += ch.x;
		y += ch.y;
		return *this;
	}

	Float2& operator -= (Float2 &ch)
	{
		x -= ch.x;
		y -= ch.y;
		return *this;
	}


	float x, y;

	Float2() = default;
	//virtual ~Float3() {}
private:
};

class Float3
{
public:
	Float3(float v) :x(v), y(v), z(v) {}
	Float3(float x, float y, float z) :x(x), y(y), z(z) {}
	~Float3() {}

	DirectX::XMFLOAT3 DXFloat3() { return DirectX::XMFLOAT3(x, y, z); }

	//‘ã“ü‰‰Zq
	Float3 &operator =(const Float3 &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
		return *this;
	}

	Float3 &operator =(const float &v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}

	//Zp‰‰Zq
	Float3& operator += (Float3 &ch)
	{
		x += ch.x;
		y += ch.y;
		z += ch.z;
		return *this;
	}

	Float3& operator -= (Float3 &ch)
	{
		x -= ch.x;
		y -= ch.y;
		z -= ch.z;
		return *this;
	}

	Float3& operator *= (Float3 &ch)
	{
		x *= ch.x;
		y *= ch.y;
		z *= ch.z;
		return *this;
	}

	Float3& operator *= (float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	Float3& operator /= (Float3 &ch)
	{
		x /= ch.x;
		y /= ch.y;
		z /= ch.z;
		return *this;
	}

	float x, y, z;

	Float3() = default;
	//virtual ~Float3() {}
private:
};

class Float4
{
public:
	Float4(float v) :x(v), y(v), z(v), w(v) {}
	Float4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}
	~Float4() {}

	DirectX::XMFLOAT4 DXFloat4() { return DirectX::XMFLOAT4(x, y, z, w); }

	//‘ã“ü‰‰Zq
	Float4 &operator =(const Float4 &r)
	{
		x = r.x;
		y = r.y;
		z = r.z;
		w = r.w;
		return *this;
	}

	Float4 &operator =(const float &v)
	{
		x = v;
		y = v;
		z = v;
		w = v;
		return *this;
	}

	//Zp‰‰Zq
	Float4& operator += (Float4 &ch)
	{
		x += ch.x;
		y += ch.y;
		z += ch.z;
		w += ch.w;
		return *this;
	}

	Float4& operator -= (Float4 &ch)
	{
		x -= ch.x;
		y -= ch.y;
		z -= ch.z;
		w -= ch.w;
		return *this;
	}


	float x, y, z, w;

	Float4() = default;
	//virtual ~Float3() {}
private:
};
