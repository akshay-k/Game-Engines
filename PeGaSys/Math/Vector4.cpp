#include<iostream>
#include"Vector4.h"
#include<assert.h>

namespace Math3D {
	
	void Vector4::print() {
		std::cout << getX() <<" "<< getY() << " " << getZ() << " " << getW() << std::endl;
	}

	bool Resembles(float x, float otherX, float tolerance) {
		return (std::abs(x - otherX) < std::abs(tolerance));
	}

	bool Resembles(double x, double otherX, double tolerance) {
		return (std::abs(x - otherX) < std::abs(tolerance));
	}

	Vector4::Vector4() :mX(0.0f), mY(0.0f), mZ(0.0f), mW(0.0f) {};

	Vector4::Vector4(float x, float y, float z)
	{
		assert(!isnan(x));
		assert(!isnan(y));
		assert(!isnan(z));
		mX = x;
		mY = y;
		mZ = z;
		mW = 0.0f;
	}

	Vector4::Vector4(float x, float y, float z, float w)
	{
		assert(!isnan(x));
		assert(!isnan(y));
		assert(!isnan(z));
		assert(!isnan(w));
		mX = x;
		mY = y;
		mZ = z;
		mW = w;
	}


	Vector4::~Vector4()
	{
	}
	float Vector4::getX() const
	{
		return mX;
	}
	float Vector4::getY() const
	{
		return mY;
	}
	float Vector4::getZ() const
	{
		return mZ;
	}
	float Vector4::getW() const
	{
		return mW;
	}
	void Vector4::setX(float x)
	{
		assert(!isnan(x));
		mX = x;
	}
	void Vector4::setY(float y)
	{
		assert(!isnan(y));
		mY = y;
	}
	void Vector4::setZ(float z)
	{
		assert(!isnan(z));
		mZ = z;
	}
	void Vector4::setW(float w)
	{
		assert(!isnan(w));
		mW = w;
	}
	Vector4 & Vector4::operator=(const Vector4 & rhs)
	{
		mX = rhs.getX();
		mY = rhs.getY();
		mZ = rhs.getZ();
		mW = rhs.getW();
		return *this;
	}

	bool Vector4::operator==(const Vector4 & rhs) const
	{
		return ((mX == rhs.getX()) && (mY == rhs.getY())
			&& (mZ == rhs.getZ()) && (mW == rhs.getW()));
	}

	bool Vector4::operator!=(const Vector4 & rhs) const
	{
		return ((mX != rhs.getX()) || (mY != rhs.getY()) ||
			(mZ != rhs.getZ()) || (mW != rhs.getW()));
	}

	bool Vector4::Resembles(const Vector4 & other, const float tolerance) const
	{
		return ::Math3D::Resembles(mX, other.getX(), tolerance)
			&& ::Math3D::Resembles(mY, other.getY(), tolerance)
			&& ::Math3D::Resembles(mZ, other.getZ(), tolerance)
			&& ::Math3D::Resembles(mW, other.getW(), tolerance);
	}

	bool Vector4::Resemblesv3(const Vector4 & other, const float tolerance) const
	{
		return ::Math3D::Resembles(mX, other.getX(), tolerance)
			&& ::Math3D::Resembles(mY, other.getY(), tolerance)
			&& ::Math3D::Resembles(mZ, other.getZ(), tolerance);
	}

	Vector4 & Vector4::operator+=(const Vector4 & rhs)
	{
		mX += rhs.getX();
		mY += rhs.getY();
		mZ += rhs.getZ();
		mW += rhs.getW();
		return *this;
	}

	Vector4 & Vector4::operator-=(const Vector4 & rhs)
	{
		mX -= rhs.getX();
		mY -= rhs.getY();
		mZ -= rhs.getZ();
		mW -= rhs.getW();
		return *this;
	}

	Vector4 & Vector4::operator*=(float f)
	{
		assert(!isnan(f));
		mX *= f;
		mY *= f;
		mZ *= f;
		mW *= f;
		return *this;
	}

	Vector4 & Vector4::operator/=(float f)
	{
		assert(f != 0.0f);
		assert(!isnan(f));
		(*this) *= (1.0f / f);
		return *this;
	}

	Vector4 Vector4::operator+() const
	{
		return *this;
	}

	Vector4 Vector4::operator-() const
	{
		return Vector4(-mX, -mY, -mZ, -mW);
	}

	Vector4 Vector4::operator+(const Vector4 & rhs) const
	{
		return Vector4(mX + rhs.getX(), mY + rhs.getY(), mZ + rhs.getZ(), mW + rhs.getW());
	}

	Vector4 Vector4::operator-(const Vector4 & rhs) const
	{
		return Vector4(mX - rhs.getX(), mY - rhs.getY(), mZ - rhs.getZ(), mW - rhs.getW());
	}

	Vector4 Vector4::operator*(float f) const
	{
		assert(!isnan(f));
		return Vector4(mX * f, mY * f, mZ * f, mW * f);
	}

	Vector4 Vector4::operator/(float f) const
	{
		assert(f != 0.0f);
		assert(!isnan(f));
		return (*this)*(1.0f / f);
	}

	float Vector4::operator*(const Vector4 & rhs) const
	{
		return (mX*rhs.getX() + mY*rhs.getY() + mZ*rhs.getZ() + mW*rhs.getW());
	}

	Vector4 Vector4::operator^(const Vector4 & rhs) const
	{
		return Vector4((mY * rhs.getZ() - mZ * rhs.getY()), (mZ * rhs.getX() - mX * rhs.getZ()),
			(mX * rhs.getY() - mY * rhs.getX()), 0.0f);
	}

	float Vector4::Magnitude2() const
	{
		return mX*mX + mY*mY + mZ*mZ + mW*mW;
	}

	float Vector4::Magnitude() const
	{
		return std::sqrt(Magnitude2());
	}

	float Vector4::Magnitude2v3() const
	{
		return mX*mX + mY*mY + mZ*mZ;
	}

	float Vector4::Magnitudev3() const
	{
		return std::sqrt(Magnitude2v3());
	}


	void Vector4::Normalize()
	{
		const float mag = Magnitude();
		assert(mag != 0);
		assert(!isnan(mag));
		(*this) /= mag;
	}

	void Vector4::Normalizev3()
	{
		const float mag = Magnitudev3();
		assert(mag != 0);
		assert(!isnan(mag));
		mX /= mag;
		mY /= mag;
		mZ /= mag;
	}

	bool Vector4::IsNormalized() const
	{
		const float mag2 = Magnitude2();
		assert(!isnan(mag2));
		return ::Math3D::Resembles(mag2, 1.0f);
	}

	bool Vector4::IsNormalizedv3() const
	{
		const float mag2v3 = Magnitude2v3();
		assert(!isnan(mag2v3));
		return ::Math3D::Resembles(mag2v3, 1.0f);
	}

	void Vector4::Zero()
	{
		setX(0.0f);
		setY(0.0f);
		setZ(0.0f);
		setW(0.0f);
	}

	Vector4 operator*(float f, const Vector4 & v)
	{
		assert(!isnan(f));
		return Vector4(v.getX()*f, v.getY()*f, v.getZ()*f, v.getW()*f);
	}

	Math3D::Vector4 Vector4::GetDir() const
	{
		Math3D::Vector4 dirVect = *this;
		const float mag = Magnitude();
		dirVect = dirVect / mag;
		return dirVect;
	}
}

