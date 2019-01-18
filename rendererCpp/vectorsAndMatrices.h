#pragma once

#include <xmmintrin.h>  
#include <smmintrin.h>

using namespace std;

struct vector4;
struct float4x4;

//represents vector and rgb color
struct vector3
{
	vector3();
	vector3(float x, float y, float z);
	vector3(float x, float y, float z, bool normalize);
	vector3(const vector3 &vector);
	vector3(__m128 vector);

	string toString();

	vector3 operator - () const;
	vector3 operator * (float const &k) const;
	vector3 operator / (float const &k) const;
	vector3 operator + (vector3 const &b) const;
	vector3 & operator += (vector3 const &b);
	vector3 operator - (vector3 const &b) const;
	vector3 & operator -=(vector3 const &b);
	vector3 operator * (vector3 const &b) const;
	vector3 operator / (vector3 const &b) const;
	vector3 operator *= (float4x4 & matrix);
	float & operator [] (int i);
	void operator = (vector3 const &b);
	//alignment operators
	void * operator new (size_t x)
	{
		return _aligned_malloc(x, 16);
	}
	void operator delete (void * x)
	{
		free(x);
	}
	void * operator new[](size_t x)
	{
		return _aligned_malloc(x, 16);
	}
		void operator delete[](void * x)
	{
		free(x);
	}

	//vector funcions
	vector3 normalize();
	float length() const;
	float lengthSquare() const;
	float dot(vector3 const &b) const;
	vector3 reflect(vector3 normal);
	vector3 cross(vector3 const &b) const;

	//color functions
	void scaleToOne(); //scales whole colour to value between 0 and 1
	void saturate(); //cuts value to between 0 and 1
	void toEightBit();
	int toInt();
	float distanceSquare(vector3 secondVector);

	union {
		__m128 vector;

		struct {
			union {
				float x;
				float r;
			};
			union {
				float y;
				float g;
			};
			union {
				float z;
				float b;
			};
		};
	};
};

//represents vector and rgba color
struct vector4
{
	vector4();
	vector4(float x, float y, float z);
	vector4(float x, float y, float z, float w);
	vector4(float x, float y, float z, float w, bool normalize);
	vector4(const vector4 &vector);
	vector4(const vector3 &vector);
	vector4(unsigned int argb);
	vector4(__m128 vector);

	string toString();

	vector4 operator - () const;
	vector4 operator * (float const &k) const;
	vector4 operator / (float const &k) const;
	vector4 operator + (vector4 const &b) const;
	vector4 operator - (vector4 const &b) const;
	vector4 operator * (vector4 const &b) const;
	vector4 operator / (vector4 const &b) const;
	vector4 operator *= (float4x4 & matrix);
	float& operator [] (int i);
	void operator = (vector4 const &b);
	void operator = (unsigned int const &argb);

	//vector functions
	void normalize();
	float length() const;
	float lengthSquare() const;
	float dot(vector4 const &b) const; //in spaces with number of dimensions different than 3 or 7 there is no cross product

	//color functions
	void scaleToOne(); //scales whole colour to value between 0 and 1
	void saturate(); //cuts value to between 0 and 1
	void toEightBit();
	int toInt();

	union {
		__m128 vector;

		struct {
			union {
				float x;
				float r;
			};
			union {
				float y;
				float g;
			};
			union {
				float z;
				float b;
			};
			union {
				float w;
				float a;
			};
		};
	};
	
};

//implemented in row-major order
struct float4x4
{
	float4x4();
	//each vector represents one row of the matrix
	float4x4(const vector4 &row1, const vector4 &row2, const vector4 &row3, const vector4 &row4);

	void operator = (float4x4 const &B);
	float4x4 operator * (float4x4 B);
	vector4& operator [] (int i);

	string toString();
	float4x4 transpose();
	static float4x4 identity();

	vector4 row1, row2, row3, row4;
};

