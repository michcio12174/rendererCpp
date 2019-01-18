#include "stdafx.h"
#include "vectorsAndMatrices.h"
#include <iomanip>

const static float epsilon = 0.000001f; //u¿ywany do sprawdzania, czy normalizowany wektor nie jest za ma³y

//================================================================================================================================================================================
//================================================================================================================================================================================
//================================================================================================================================================================================
//SSE implementation

//------------------------------------------------------------vector3------------------------------------------------------------

vector3::vector3() :
	vector(_mm_setzero_ps())
{
}

vector3::vector3(float x, float y, float z) :
	vector(_mm_set_ps(0, z, y, x))
{
}

vector3::vector3(float x, float y, float z, bool normalize) :
	vector(_mm_set_ps(0, z, y, x))
{
	if (normalize) this->normalize();
}

vector3::vector3(const vector3 & vector) :
	x(vector.x),
	y(vector.y),
	z(vector.z)
{
}

vector3::vector3(__m128 vector):
	vector(vector)
{
}

string vector3::toString()
{
	return "vector3(" + to_string(this->x) + ", " + to_string(this->y) + ", " + to_string(this->z) + ")";
}

vector3 vector3::operator-() const
{
	return vector3(-this->x, -this->y, -this->z);
}

vector3 vector3::operator*(float const &k) const
{
	return _mm_mul_ps(vector, _mm_set1_ps(k));
}

vector3 vector3::operator/(float const &k) const
{
	return _mm_div_ps(vector, _mm_set1_ps(k));
}

vector3 vector3::operator+(vector3 const &b) const
{
	return _mm_add_ps(vector, b.vector);
}

vector3 & vector3::operator+=(vector3 const & b)
{
	this->vector = _mm_add_ps(vector, b.vector);
	return *this;
}

vector3 vector3::operator-(vector3 const &b) const
{
	return _mm_sub_ps(vector, b.vector);
}

vector3 & vector3::operator-=(vector3 const & b)
{
	this->vector = _mm_sub_ps(vector, b.vector);
	return *this;
}

vector3 vector3::operator*(vector3 const &b) const
{
	return _mm_mul_ps(vector, b.vector);
}

vector3 vector3::operator/(vector3 const &b) const
{
	return _mm_div_ps(vector, b.vector);
}

vector3 vector3::operator*=(float4x4 & matrix)
{
	this->x = (matrix[0][0] * this->x) + (matrix[0][1] * this->y) + (matrix[0][2] * this->z) + (matrix[0][3] * 1);
	this->y = (matrix[1][0] * this->x) + (matrix[1][1] * this->y) + (matrix[1][2] * this->z) + (matrix[1][3] * 1);
	this->z = (matrix[2][0] * this->x) + (matrix[2][1] * this->y) + (matrix[2][2] * this->z) + (matrix[2][3] * 1);

	return *this;
}

float & vector3::operator[](int i)
{
	switch (i) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	default:
		return z;
		break;
	}
}

void vector3::operator=(vector3 const & b)
{
	vector = b.vector;
}

float vector3::length() const
{
	return _mm_cvtss_f32(
		_mm_sqrt_ss(_mm_dp_ps(vector, vector, 0x71))
	);
}

float vector3::lengthSquare() const
{
	return _mm_cvtss_f32(
		_mm_dp_ps(vector, vector, 0x71)
	);
}

//_mm_dp_ps performs dot product, saves it in the single float value and _mm_cvtss_f32 extracts it
float vector3::dot(vector3 const &b) const
{
	return _mm_cvtss_f32(_mm_dp_ps(vector, b.vector, 0x71));
}

//_mm_shuffle_ps tworzy wektor _m128, w który wk³ada 2 elementy z pierwszego argumentu i 2 elementy z drugiego argumentu
//wiêc jeœli chcemy przemieszaæ kolejnoœæ jednego wektora, to podajemy go dwa razy do funkcji
//_MM_SHUFFLE(3, 0, 2, 1) okreœla jak zostan¹ ustawione elementy
//w tym wypadku:
//-wziête z drugiego wektora - na ostatnim miejscu bêdzie element czwarty i ostatni (3), na trzecim element pierwszy (0),
//-wziête z pierwszego wektora - na drugim miejscu element trzeci (2), a na pierwszym element drugi (1)
//pamiêtajmy, ¿e kolejnoœæ elementów w wypadku tych funkcji jest odwrócona - st¹r pierwszy argument _MM_SHUFFLE, czyli 3, odnosi siê do ostatniego elementu wektora
vector3 vector3::cross(vector3 const &b) const
{
	return vector3(_mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(vector, vector, _MM_SHUFFLE(3, 0, 2, 1)),
			_mm_shuffle_ps(b.vector, b.vector, _MM_SHUFFLE(3, 1, 0, 2)))
		,
		_mm_mul_ps(
			_mm_shuffle_ps(vector, vector, _MM_SHUFFLE(3, 1, 0, 2)),
			_mm_shuffle_ps(b.vector, b.vector, _MM_SHUFFLE(3, 0, 2, 1)))
	));
}

void vector3::scaleToOne()
{
	float maximum = max(r, max(g, b));
	if (maximum > 1) {
		r = r / maximum;
		g = g / maximum;
		b = b / maximum;
	}
	//if (r < 0)r = 0;
	//if (g < 0)g = 0;
	//if (b < 0)b = 0;
}

void vector3::saturate()
{
	r = max(0.0f, min(1.0f, r));
	g = max(0.0f, min(1.0f, g));
	b = max(0.0f, min(1.0f, b));
}

void vector3::toEightBit()
{
	scaleToOne();
	r = r * 255;
	g = g * 255;
	b = b * 255;
}

int vector3::toInt()
{
	toEightBit();
	int result = 0;
	result |= ((unsigned char)255 << 24); //alfa
	result |= ((unsigned char)this->r << 16);
	result |= ((unsigned char)this->g << 8);
	result |= ((unsigned char)this->b);
	return result;
}

float vector3::distanceSquare(vector3 secondVector)
{
	return ((secondVector.r - r)*(secondVector.r - r) +
		(secondVector.g - g)*(secondVector.g - g) +
		(secondVector.b - b)*(secondVector.b - b));
}

vector3 vector3::normalize()
{
	//_mm_dp_ps calculates dot of 3 first numbers of vector (number 7 in mask) and writes it to all floats in resulting vector (number F in mask)
	vector = _mm_div_ps(
		vector, _mm_sqrt_ps(_mm_dp_ps(vector, vector, 0x7F))
	);
	return *this;
}

vector3 vector3::reflect(vector3 normal)
{
	return *this - normal * (normal.dot(*this) * 2);
}

//------------------------------------------------------------vector4------------------------------------------------------------

vector4::vector4() :
	vector(_mm_setzero_ps())
{
}

vector4::vector4(float x, float y, float z) :
	vector(_mm_set_ps(1, z, y, x))
{
}

vector4::vector4(float x, float y, float z, float w) :
	vector(_mm_set_ps(w, z, y, x))
{
}

vector4::vector4(float x, float y, float z, float w, bool normalize) :
	vector(_mm_set_ps(w, z, y, x))
{
	if (normalize) this->normalize();
}

vector4::vector4(const vector4 & vector) :
	vector(vector.vector)
{
}

vector4::vector4(const vector3 & vector) :
	vector(_mm_set_ps(1, vector.z, vector.y, vector.x))
{
}

vector4::vector4(unsigned int argb)
{
	this->a = argb >> 24 & 255;
	this->r = argb >> 16 & 255;
	this->g = argb >> 8 & 255;
	this->b = argb & 255;
	scaleToOne();
}

vector4::vector4(__m128 vector):
	vector(vector)
{
}

string vector4::toString()
{
	string a = "vector4(" + to_string(this->x) + ", "
		+ to_string(this->y) + ", "
		+ to_string(this->z) + ", "
		+ to_string(this->w) + ")";
	return a;
}

vector4 vector4::operator-() const
{
	return vector4(-this->x, -this->y, -this->z, -this->w);
}

vector4 vector4::operator*(float const &k) const
{
	return _mm_mul_ps(vector, _mm_set1_ps(k));
}

vector4 vector4::operator/(float const &k) const
{
	return _mm_div_ps(vector, _mm_set1_ps(k));
}

vector4 vector4::operator+(vector4 const &b) const
{
	return _mm_add_ps(vector, b.vector);
}

vector4 vector4::operator-(vector4 const &b) const
{
	return _mm_sub_ps(vector, b.vector);
}

vector4 vector4::operator*(vector4 const &b) const
{
	return _mm_mul_ps(vector, b.vector);
}

vector4 vector4::operator/(vector4 const &b) const
{
	return _mm_div_ps(vector, b.vector);
}

vector4 vector4::operator*=(float4x4 & matrix)
{
	vector4 temp(*this);

	this->x = (matrix[0][0] * temp.x) + (matrix[0][1] * temp.y) + (matrix[0][2] * temp.z) + (matrix[0][3] * temp.w);
	this->y = (matrix[1][0] * temp.x) + (matrix[1][1] * temp.y) + (matrix[1][2] * temp.z) + (matrix[1][3] * temp.w);
	this->z = (matrix[2][0] * temp.x) + (matrix[2][1] * temp.y) + (matrix[2][2] * temp.z) + (matrix[2][3] * temp.w);
	this->w = (matrix[3][0] * temp.x) + (matrix[3][1] * temp.y) + (matrix[3][2] * temp.z) + (matrix[3][3] * temp.w);

	return *this;
}

float& vector4::operator[](int i)
{
	switch (i) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		return w;
		break;
	}
}

void vector4::operator=(vector4 const & b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;
	this->w = b.w;
}

void vector4::operator=(unsigned int const & argb)
{
	this->a = argb >> 24 & 255;
	this->r = argb >> 16 & 255;
	this->g = argb >> 8 & 255;
	this->b = argb & 255;
	scaleToOne();
}

//todo, czy w pasce powinno byæ F = 15?
float vector4::length() const
{
	return _mm_cvtss_f32(
		_mm_sqrt_ss(_mm_dp_ps(vector, vector, 0xF1))
	);
}

float vector4::lengthSquare() const
{
	return _mm_cvtss_f32(
		_mm_dp_ps(vector, vector, 0xF1)
	);
}

//_mm_dp_ps performs dot product, saves it in the single float value and _mm_cvtss_f32 extracts it
float vector4::dot(vector4 const &b) const
{
	return _mm_cvtss_f32(_mm_dp_ps(vector, b.vector, 0xF1));
}

void vector4::scaleToOne()
{
	float maximum = max(r, max(g, b));
	if (maximum > 1) {
		r = r / maximum;
		g = g / maximum;
		b = b / maximum;
	}
	if (r < 0)r = 0;
	if (g < 0)g = 0;
	if (b < 0)b = 0;

	a = max(0.0f, min(1.0f, a)); //alfy nie skalujê z reszt¹ koloru - jeœli jest wiêksza od 1 ustawiam na 1
}

void vector4::saturate()
{
	r = max(0.0f, min(1.0f, r));
	g = max(0.0f, min(1.0f, g));
	b = max(0.0f, min(1.0f, b));
	a = max(0.0f, min(1.0f, a));
}

void vector4::toEightBit()
{
	scaleToOne();
	r = r * 255;
	g = g * 255;
	b = b * 255;
	a = a * 255;
}

int vector4::toInt()
{
	toEightBit();
	int result = 0;
	result |= ((unsigned char)this->a << 24); //alfa
	result |= ((unsigned char)this->r << 16);
	result |= ((unsigned char)this->g << 8);
	result |= ((unsigned char)this->b);
	return result;
}

void vector4::normalize()
{
	//_mm_dp_ps calculates dot of 4 first numbers of vector (number F in mask) and writes it to all floats in resulting vector (second number F in mask)
	vector = _mm_div_ps(
		vector, _mm_sqrt_ps(_mm_dp_ps(vector, vector, 0xFF))
	);
}

//------------------------------------------------------------float4x4------------------------------------------------------------

float4x4::float4x4()
{
	row1 = vector4(0, 0, 0, 0);
	row2 = vector4(0, 0, 0, 0);
	row3 = vector4(0, 0, 0, 0);
	row4 = vector4(0, 0, 0, 0);
}

float4x4::float4x4(const vector4 &row1, const vector4 &row2, const vector4 &row3, const vector4 &row4):
	row1(row1),
	row2(row2),
	row3(row3),
	row4(row4)
{}

void float4x4::operator=(float4x4 const &B)
{
	row1 = B.row1;
	row2 = B.row2;
	row3 = B.row3;
	row4 = B.row4;
}

float4x4 float4x4::operator*(float4x4 B)
{
	float4x4 C;
	int i, j; //i - kolumna, j - rz¹d
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			C[i][j] = (*this)[i][0] * B[0][j] +
				(*this)[i][1] * B[1][j] +
				(*this)[i][2] * B[2][j] +
				(*this)[i][3] * B[3][j];
		}
	}
	return C;
}

vector4& float4x4::operator[](int i)
{
	if (i == 0) return row1;
	else if (i == 1) return row2;
	else if (i == 2) return row3;
	else if (i == 3) return row4;
	else {
		return row4;
		cout << "a row of number higher that 4 was requested from 4x4 matrix, fourth row returned" << endl;
	}
}

float4x4 float4x4::transpose()
{
	float4x4 temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp[j][i] = (*this)[i][j];
		}
	}
	*this = temp;

	return *this;
}

string float4x4::toString()
{
	string matrix;
	int i, j;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			matrix += to_string((int)(*this)[i][j]) + " "; //liczby ca³kowite zajmuj¹ mniej miejsca - ³atwiej czytaæ output
			//matrix += to_string((*this)[i][j]) + " ";
		}
		matrix += "\n";
	}
	return matrix;
}

float4x4 float4x4::identity()
{
	float4x4 s(vector4(1, 0, 0, 0),
		vector4(0, 1, 0, 0),
		vector4(0, 0, 1, 0),
		vector4(0, 0, 0, 1));
	return s;
}