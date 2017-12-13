#pragma once

namespace Math3D {
	bool Resembles(float x, float otherX, float tolerance = 0.00001f);
	bool Resembles(double x, double otherX, double tolerance = 0.00001f);
	class  __declspec(align(16)) Vector4
	{
	public:

		Vector4();
		Vector4(float x, float y, float z);
		Vector4(float x, float y, float z, float w);
		~Vector4();
		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);
		Vector4 & operator= (const Vector4 & rhs);
		bool operator== (const Vector4 & rhs) const;
		bool operator != (const Vector4 & rhs) const;
		Vector4 & operator += (const Vector4 & rhs);
		Vector4 & operator -= (const Vector4 & rhs);
		Vector4 & operator *= (float f);
		Vector4 & operator /= (float f);
		// Unary operators.
		Vector4 operator + () const;
		Vector4 operator - () const;
		// Binary operators.
		Vector4 operator + (const Vector4 & rhs) const;
		Vector4 operator - (const Vector4 & rhs) const;
		Vector4 operator * (float f) const;
		Vector4 operator / (float f) const;
		friend Vector4 operator * (float f, const Vector4 & v);
		// Dot Product
		float operator*(const Vector4 & rhs) const;
		// Cross Product
		Vector4 operator^(const Vector4 & rhs) const;
		// Magnitude of the vector
		float Magnitude2() const;
		float Magnitude() const;
		float Magnitude2v3() const;
		float Magnitudev3() const;
		// Checks if two vectors resemble. Resembles if the absolute difference of components is less than tolerance
		bool Resembles(const Vector4 & other, const float tolerance = 0.00001f) const;
		bool Resemblesv3(const Vector4 & other, const float tolerance = 0.00001f) const;
		// Normalize
		void Normalize();
		void Vector4::Normalizev3();
		bool IsNormalized() const;
		bool IsNormalizedv3() const;
		void Zero();
		Math3D::Vector4 Vector4::GetDir() const;
		void print();

	private:
		float mX;
		float mY;
		float mZ;
		float mW;
	};
	typedef Vector4 * Vector4Ptr;
}
