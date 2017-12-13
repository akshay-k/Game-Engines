#include "Matrix44.h"
#include<assert.h>
#include<iostream>

namespace Math3D {
	Matrix44::Matrix44() : mVec4X(1.0f, 0.0f, 0.0f, 0.0f), mVec4Y(0.0f, 1.0f, 0.0f, 0.0f), 
		mVec4Z(0.0f, 0.0f, 1.0f, 0.0f), mVec4W(0.0f, 0.0f, 0.0f, 1.0f){}

	Matrix44::Matrix44(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
		float m8, float m9, float ma, float mb, float mc, float md, float me, float mf) : mVec4X(m0, m1, m2, m3), mVec4Y(m4, m5, m6, m7),
		mVec4Z(m8, m9, ma, mb), mVec4W(mc, md, me, mf) {
		assert(!isnan(m0));
		assert(!isnan(m1));
		assert(!isnan(m2));
		assert(!isnan(m3));
		assert(!isnan(m4));
		assert(!isnan(m5));
		assert(!isnan(m6));
		assert(!isnan(m7));
		assert(!isnan(m8));
		assert(!isnan(m9));
		assert(!isnan(ma));
		assert(!isnan(mb));
		assert(!isnan(mc));
		assert(!isnan(md));
		assert(!isnan(me));
		assert(!isnan(mf));
	}

	Matrix44::Matrix44(Vector4 vec4X, Vector4 vec4Y, Vector4 vec4Z, Vector4 vec4W) : mVec4X(vec4X), mVec4Y(vec4Y), mVec4Z(vec4Z), mVec4W(vec4W){}

	Matrix44::Matrix44(Vector4 vec4X, Vector4 vec4Y, Vector4 vec4Z) : mVec4X(vec4X), mVec4Y(vec4Y), mVec4Z(vec4Z){
		assert(vec4X.getW() == 0.0f);
		assert(vec4Y.getW() == 0.0f);
		assert(vec4Z.getW() == 0.0f);
	}

	Matrix44::~Matrix44(){}

	Vector4 Matrix44::getVec4X() const
	{
		return mVec4X;
	}

	Vector4 Matrix44::getVec4Y() const
	{
		return mVec4Y;
	}

	Vector4 Matrix44::getVec4Z() const
	{
		return mVec4Z;
	}

	Vector4 Matrix44::getVec4W() const
	{
		return mVec4W;
	}

	void Matrix44::setVec4X(const Vector4 & vec)
	{
		mVec4X = vec;
	}

	void Matrix44::setVec4Y(const Vector4 & vec)
	{
		mVec4Y = vec;
	}

	void Matrix44::setVec4Z(const Vector4 & vec)
	{
		mVec4Z = vec;
	}

	void Matrix44::setVec4W(const Vector4 & vec)
	{
		mVec4W = vec;
	}

	void Matrix44::setVec4X(float a, float b, float c, float d)
	{
		Vector4 vec(a, b, c, d);
		mVec4X = vec;
	}

	void Matrix44::setVec4Y(float a, float b, float c, float d)
	{
		Vector4 vec(a, b, c, d);
		mVec4Y = vec;
	}

	void Matrix44::setVec4Z(float a, float b, float c, float d)
	{
		Vector4 vec(a, b, c, d);
		mVec4Z = vec;
	}

	void Matrix44::setVec4W(float a, float b, float c, float d)
	{
		Vector4 vec(a, b, c, d);
		mVec4W = vec;
	}

	Matrix44 & Matrix44::operator*=(float f)
	{
		mVec4X *= f;
		mVec4Y *= f;
		mVec4Z *= f;
		mVec4W *= f;
		return *this;
	}

	Matrix44 Matrix44::operator*(float f) const
	{	
		return Matrix44(f*mVec4X, f*mVec4Y, f*mVec4Z, f*mVec4W);
	}

	Matrix44 Matrix44::operator/(float f) const
	{
		assert(f != 0);
		assert(!isnan(f));
		return (*this)*(1.0f)/f;
	}

	Vector4 Matrix44::operator*(const Vector4 & v4) const
	{
		return Vector4(v4.getX() * mVec4X.getX() + v4.getY() * mVec4Y.getX() + v4.getZ() * mVec4Z.getX() + v4.getW() * mVec4W.getX(),
			v4.getX() * mVec4X.getY() + v4.getY() * mVec4Y.getY() + v4.getZ() * mVec4Z.getY() + v4.getW() * mVec4W.getY(),
			v4.getX() * mVec4X.getZ() + v4.getY() * mVec4Y.getZ() + v4.getZ() * mVec4Z.getZ() + v4.getW() * mVec4W.getZ(),
			v4.getX() * mVec4X.getW() + v4.getY() * mVec4Y.getW() + v4.getZ() * mVec4Z.getW() + v4.getW() * mVec4W.getW());
	}

	float Matrix44::degreesToRadians(const float degrees)
	{
		const float PI_F = 3.141592653589793238462643383f;
		return (PI_F*degrees) / 180.0f;
	}

	const float * Matrix44::convertToFloatArray()
	{
		const float matGL[] = {
			getVec4X().getX(), getVec4X().getY(), getVec4X().getZ(), getVec4X().getW(),
			getVec4Y().getX(), getVec4Y().getY(), getVec4Y().getZ(), getVec4Y().getW(),
			getVec4Z().getX(), getVec4Z().getY(), getVec4Z().getZ(), getVec4Z().getW(),
			getVec4W().getX(), getVec4W().getY(), getVec4W().getZ(), getVec4W().getW()
		};
		return matGL;
	}

	Vector4 Matrix44::TransformNormal(const Vector4 & v4) const
	{
		return Vector4(v4.getX()*mVec4X.getX() + v4.getY()*mVec4Y.getX() + v4.getZ()*mVec4Z.getX(),
			v4.getX()*mVec4X.getY() + v4.getY()*mVec4Y.getY() + v4.getZ()*mVec4Z.getY(),
			v4.getX()*mVec4X.getZ() + v4.getY()*mVec4Y.getZ() + v4.getZ()*mVec4Z.getZ());
	}

	void Matrix44::TransformNormalByUpper3x3Transpose(Vector4 & out, const Vector4 & v4) const
	{
		assert(0.0f == v4.getW());
		//assert(IsSE3()); ToDo
		out = Vector4(v4.getX() * mVec4X.getX() + v4.getY() * mVec4X.getY() + v4.getZ() * mVec4X.getZ(),
			v4.getX() * mVec4Y.getX() + v4.getY() * mVec4Y.getY() + v4.getZ() * mVec4Y.getZ(),
			v4.getX() * mVec4Z.getX() + v4.getY() * mVec4Z.getY() + v4.getZ() * mVec4Z.getZ());
		assert(out.getW() == 0.0f);
	}

	Vector4 Matrix44::TransformNormalByUpper3x3Transpose(const Vector4 & in) const
	{
		Vector4 out;
		TransformNormalByUpper3x3Transpose(out, in);
		return out;
	}

	Vector4 Matrix44::TransformPlane(const Vector4 & vPlane) const
	{
		//PERF_BLOCK( Mat44__TransformPlane ) ;
		const Vector4 & vPlaneNormalOrig = Vector4(vPlane.getX(), vPlane.getY(), vPlane.getZ());
		const float & fDistAlongDirOrig = vPlane.getW();
		Vector4 vPlaneNormalXformed = TransformNormal(vPlaneNormalOrig);
		vPlaneNormalXformed.Normalize();
		const Vector4 v3PointOnPlaneOrig = -vPlaneNormalOrig * fDistAlongDirOrig;
		const Vector4 vPointOnPlaneOrig = Vector4(v3PointOnPlaneOrig.getX(), v3PointOnPlaneOrig.getY(), v3PointOnPlaneOrig.getZ(), 1.0f);
		const Vector4 vPointOnPlaneXformed = (*this) * vPointOnPlaneOrig;
		const Vector4 v3PointOnPlaneXformed = Vector4(vPointOnPlaneXformed.getX(), vPointOnPlaneXformed.getY(), vPointOnPlaneXformed.getZ());
		const float fDistAlongDirXformed = vPlaneNormalXformed * v3PointOnPlaneXformed;
		return Vector4(vPlaneNormalXformed.getX(), vPlaneNormalXformed.getY(), vPlaneNormalXformed.getZ(), -fDistAlongDirXformed);
	}

	Matrix44 Matrix44::operator+(const Matrix44 & rhs) const
	{
		return Matrix44(mVec4X+rhs.getVec4X(), mVec4Y + rhs.getVec4Y(), mVec4Z + rhs.getVec4Z(), mVec4W + rhs.getVec4W());
	}

	Matrix44 Matrix44::operator-(const Matrix44 & rhs) const
	{
		return (*this) + (-1.0f * rhs);
	}

	Matrix44 & Matrix44::operator+=(const Matrix44 & rhs)
	{
		(*this) = (*this) + rhs;
		return *this;
	}

	Matrix44 & Matrix44::operator-=(const Matrix44 & rhs)
	{
		(*this) = (*this) + (-1.0f * rhs);
		return *this;
	}

	Matrix44 Matrix44::operator*(const Matrix44 & rhs) const
	{
		return  Matrix44(RowDotCol(0, rhs, 0), RowDotCol(0, rhs, 1), RowDotCol(0, rhs, 2), RowDotCol(0, rhs, 3),
			RowDotCol(1, rhs, 0), RowDotCol(1, rhs, 1), RowDotCol(1, rhs, 2), RowDotCol(1, rhs, 3),
			RowDotCol(2, rhs, 0), RowDotCol(2, rhs, 1), RowDotCol(2, rhs, 2), RowDotCol(2, rhs, 3),
			RowDotCol(3, rhs, 0), RowDotCol(3, rhs, 1), RowDotCol(3, rhs, 2), RowDotCol(3, rhs, 3));
	}

	Matrix44 Matrix44::GetTranspose() const
	{
		return Matrix44(mVec4X.getX(), mVec4Y.getX(), mVec4Z.getX(), mVec4W.getX(),
			mVec4X.getY(), mVec4Y.getY(), mVec4Z.getY(), mVec4W.getY(), 
			mVec4X.getZ(), mVec4Y.getZ(), mVec4Z.getZ(), mVec4W.getZ(), 
			mVec4X.getW(), mVec4Y.getW(), mVec4Z.getW(), mVec4W.getW());
	}

	bool Matrix44::isDiagonal() const
	{
		return 0.0f == mVec4X.getY() && 0.0f == mVec4X.getZ() && 0.0f == mVec4X.getW()
			&& 0.0f == mVec4Y.getX() && mVec4Y.getZ() && 0.0f == mVec4Y.getW()
			&& 0.0f == mVec4Z.getX() && mVec4Z.getY() && 0.0f == mVec4Z.getW()
			&& 0.0f == mVec4W.getX() && 0.0f == mVec4W.getY() && 0.0f == mVec4W.getZ();
	}

	float Matrix44::Determinant() const
	{
		const Vector4 v3 = mVec4Y ^ mVec4Z;
		const float determinant = mVec4X * v3;
		return determinant;
	}

	Matrix44 Matrix44::Inverse() const
	{
		const Vector4 v0 = mVec4Y ^ mVec4Z;
		const Vector4 v1 = mVec4Z ^ mVec4X;
		const Vector4 v2 = mVec4X ^ mVec4Y;
		const float determinant = mVec4X * v0;
		assert(determinant > 0.0f);
		const float oneOverDeterminant = 1.0f / determinant;
		Matrix44 inverseMatrix33(Vector4(v0.getX(), v1.getX(), v2.getX()) * oneOverDeterminant
			, Vector4(v0.getY(), v1.getY(), v2.getY()) * oneOverDeterminant
			, Vector4(v0.getZ(), v1.getZ(), v2.getZ()) * oneOverDeterminant);
		return inverseMatrix33;
	}

	void Matrix44::SetScale(float scaleX, float scaleY, float scaleZ)
	{
		Vector4 vecX(scaleX, 0.0f, 0.0f, 0.0f);
		Vector4 vecY(0.0f, scaleY, 0.0f, 0.0f);
		Vector4 vecZ(0.0f, 0.0f, scaleZ, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRight(const Vector4 & v3Right)
	{
		Vector4 vecX(v3Right.getX(), 0.0f, 0.0f);
		Vector4 vecY(v3Right.getY(), 0.0f, 0.0f);
		Vector4 vecZ(v3Right.getZ(), 0.0f, 0.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
	}

	void Matrix44::SetUp(const Vector4 & v3Up)
	{
		Vector4 vecX(0.0f, v3Up.getX(),  0.0f);
		Vector4 vecY(0.0f, v3Up.getY(), 0.0f);
		Vector4 vecZ(0.0f, v3Up.getZ(), 0.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
	}

	void Matrix44::SetForward(const Vector4 & v3Forward)
	{
		Vector4 vecX(0.0f, 0.0f, v3Forward.getX());
		Vector4 vecY(0.0f, 0.0f, v3Forward.getY());
		Vector4 vecZ(0.0f, 0.0f, v3Forward.getZ());
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
	}

	void Matrix44::SetTranslation(const Vector4 & transVec3)
	{
		Vector4 vecX(1.0f, 0.0f, 0.0f, 0.0f);
		Vector4 vecY(0.0f, 1.0f, 0.0f, 0.0f);
		Vector4 vecZ(0.0f, 0.0f, 1.0f, 0.0f);
		Vector4 vecW(transVec3.getX(), transVec3.getY(), transVec3.getZ(), 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotationX(float angle)
	{
		//PERF_BLOCK(Mat44__SetRotationX);
		const float c = cosf(angle);
		const float s = sinf(angle);
		Vector4 vecX(1.0f, 0.0f, 0.0f, 0.0f);
		Vector4 vecY(0.0f, c, s, 0.0f);
		Vector4 vecZ(0.0f, -s, c, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotationY(float angle)
	{
		//PERF_BLOCK(Mat44__SetRotationY);
		const float c = cosf(angle);
		const float s = sinf(angle);
		Vector4 vecX(c, 0.0f, -s, 0.0f);
		Vector4 vecY(0.0f, 1.0f, 0.0f, 0.0f);
		Vector4 vecZ(s, 0.0f, c, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotationZ(float angle)
	{
		//PERF_BLOCK(Mat44__SetRotationY);
		const float c = cosf(angle);
		const float s = sinf(angle);
		Vector4 vecX(c, s, 0.0f, 0.0f);
		Vector4 vecY(-s, c, 0.0f, 0.0f);
		Vector4 vecZ(0.0f, 0.0f, 1.0f, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotationXYZ(const Vector4 & anglesAsVec3)
	{
		//PERF_BLOCK(Mat44__SetRotationXYZ);
		const float cx = cosf(anglesAsVec3.getX());
		const float sx = sinf(anglesAsVec3.getX());
		const float cy = cosf(anglesAsVec3.getY());
		const float sy = sinf(anglesAsVec3.getY());
		const float cz = cosf(anglesAsVec3.getZ());
		const float sz = sinf(anglesAsVec3.getZ());

		const float cxsy = cx * sy;
		const float sxsy = sx * sy;

		Vector4 vecX(cy * cz, sxsy * cz + cx * sz, -cxsy * cz + sx * sz, 0.0f);
		Vector4 vecY(-cy * sz, -sxsy * sz + cx * cz, cxsy * sz + sx * cz, 0.0f);
		Vector4 vecZ(sy, -sx * cy, cx * cy, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotation(const Vector4 & axisAsVec3, float angle)
	{
		//PERF_BLOCK(Mat44__SetRotation);
		assert(axisAsVec3.IsNormalized());
		const float c = cosf(angle);
		const float omc = 1.0f - c;
		const float s = sinf(angle);
		const float xs = axisAsVec3.getX() * s;
		const float ys = axisAsVec3.getY() * s;
		const float zs = axisAsVec3.getZ() * s;
		const float x1mc = axisAsVec3.getX() * omc;
		const float y1mc = axisAsVec3.getY() * omc;
		const float z1mc = axisAsVec3.getZ() * omc;
		
		Vector4 vecX(c + axisAsVec3.getX() * x1mc, axisAsVec3.getY() * x1mc + zs, axisAsVec3.getZ() * x1mc - ys, 0.0f);
		Vector4 vecY(axisAsVec3.getX() * y1mc - zs, c + axisAsVec3.getY() * y1mc, axisAsVec3.getZ() * y1mc + xs, 0.0f);
		Vector4 vecZ(axisAsVec3.getX() * z1mc + ys, axisAsVec3.getY() * z1mc - xs, c + axisAsVec3.getZ() * z1mc, 0.0f);
		Vector4 vecW(0.0f, 0.0f, 0.0f, 1.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetRotation(const Matrix44 & o33)
	{
		Vector4 zeroVec;
		assert(o33.getVec4X().getW() == 0.0f);
		assert(o33.getVec4Y().getW() == 0.0f);
		assert(o33.getVec4Z().getW() == 0.0f);
		assert(o33.getVec4W().Resembles(zeroVec));

		Vector4 vecX(o33.getVec4X().getX(), o33.getVec4X().getY(), o33.getVec4X().getZ(), 0.0f);
		Vector4 vecY(o33.getVec4Y().getX(), o33.getVec4Y().getY(), o33.getVec4Y().getZ(), 0.0f);
		Vector4 vecZ(o33.getVec4Z().getX(), o33.getVec4Z().getY(), o33.getVec4Z().getZ(), 0.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
	}

	void Matrix44::SetView(const Vector4 & eye, const Vector4 & lookAtAsVec3, const Vector4 & upApproximateAsVec3)
	{
		assert(1.0f == eye.getW());
		assert(0.0f == lookAtAsVec3.getW());
		assert(0.0f == lookAtAsVec3.getW());
		// Compute camera coordinate system unit vectors.
		Vector4 forwardAsVec3 = eye - lookAtAsVec3;
		forwardAsVec3.setW(0.0f);
		forwardAsVec3.Normalizev3();
		assert(forwardAsVec3.IsNormalizedv3());
		Vector4 rightAsVec3 = upApproximateAsVec3 ^ forwardAsVec3;
		rightAsVec3.Normalizev3();
		assert(rightAsVec3.IsNormalizedv3()); // If this fails, probably because upApproximate and forward are aligned.
		Vector4 upOrthoNormalAsVec3 = forwardAsVec3 ^ rightAsVec3; // this up direction has unit length and is mutually orthogonal to vForward and vRight
		assert(upOrthoNormalAsVec3.IsNormalizedv3());
		// Set up this matrix as the rotation-only portion of the view matrix.
		SetRight(rightAsVec3);
		SetUp(upOrthoNormalAsVec3);
		SetForward(forwardAsVec3);
		SetTranslation(Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		// Compute the translation column of the view matrix.
		const Vector4 trans = -(*this * eye);
		SetTranslation(Vector4(trans.getX(), trans.getY(), trans.getZ(), 1.0f));
	}

	Vector4 Matrix44::CameraPositionFromViewMatrix() const
	{
		//PERF_BLOCK(Mat44__CameraPositionFromViewMatrix);
		Vector4 vPos = TransformNormalByUpper3x3Transpose(-getVec4W());
		assert(vPos.getW() == 0.0f);
		return vPos;
	}

	Matrix44 Matrix44::CrossProductMatrix(Vector4 v3Vector)
	{
		float x = v3Vector.getX();
		float y = v3Vector.getY();
		float z = v3Vector.getZ();
		Vector4 v3X(0.0f, -z, y);
		Vector4 v3Y(z, 0.0f, -x);
		Vector4 v3Z(-y, x, 0.0f);
		Vector4 v3W(0.0f, 0.0f, 0.0f);
		Matrix44 m33CrossProductMatrix(v3X, v3Y, v3Z, v3W);
		return m33CrossProductMatrix;
	}

	void Matrix44::SetProjection(float n, float f, float t, float b, float r, float l)
	{
		float E = (2 * n) / (r - l);
		float A = (r + l) / (r - l);
		float F = (2 * n) / (t - b);
		float B = (t + b) / (t - b);
		float C = (f + n) / (n - f);
		float D = (2 * f * n) / (n - f);
		Math3D::Vector4 vecX = Math3D::Vector4(E, 0.0f, A, 0.0f);
		Math3D::Vector4 vecY = Math3D::Vector4(0.0f, F, B, 0.0f);
		Math3D::Vector4 vecZ = Math3D::Vector4(0.0f, 0.0f, C, D);
		Math3D::Vector4 vecW = Math3D::Vector4(0.0f, 0.0f, -1.0f, 0.0f);

		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::SetProjection(float angle, float fov, float zNear, float zFar)
	{
		float tan_half = tan(angle / 2.0f);

		Math3D::Vector4 vecX = Math3D::Vector4(1/(fov*tan_half), 0.0f, 0.0f, 0.0f);
		Math3D::Vector4 vecY = Math3D::Vector4(0.0f, 1 / (tan_half), 0.0f, 0.0f);
		Math3D::Vector4 vecZ = Math3D::Vector4(0.0f, 0.0f, -(zFar+zNear)/(zFar-zNear), -1.0f);
		Math3D::Vector4 vecW = Math3D::Vector4(0.0f, 0.0f, -(2.0f * zFar * zNear) / (zFar - zNear), 0.0f);
		setVec4X(vecX);
		setVec4Y(vecY);
		setVec4Z(vecZ);
		setVec4W(vecW);
	}

	void Matrix44::OrthonormalizeM33()
	{
		Vector4 row1 = getVec4X();
		Vector4 row2 = getVec4Y();
		Vector4 row3 = getVec4Z();
		Vector4 col1(row1.getX(), row2.getX(), row3.getX());
		Vector4 col2(row1.getY(), row2.getY(), row3.getY());
		Vector4 col3;

		col1.Normalizev3();
		col3 = col1^col2;
		col3.Normalizev3();
		col2 = col3^col1;
		col2.Normalizev3();

		row1 = Vector4(col1.getX(), col2.getX(), col3.getX());
		row2 = Vector4(col1.getY(), col2.getY(), col3.getY());
		row3 = Vector4(col1.getZ(), col2.getZ(), col3.getZ());

		setVec4X(row1);
		setVec4Y(row2);
		setVec4Z(row3);
	}

	void Matrix44::print()
	{
		Math3D::Vector4 v = getVec4X(); v.print();
		v = getVec4Y(); v.print();
		v = getVec4Z(); v.print();
		v = getVec4W(); v.print();
	}

	Matrix44 operator*(float f, const Matrix44 & m4)
	{
		return m4*f;
	}

	Vector4 operator*(const Vector4 & v4, const Matrix44 & m4)
	{
		return Vector4(v4.getX() * m4.getVec4X().getX() + v4.getY() * m4.getVec4X().getY() + v4.getZ() * m4.getVec4X().getZ() + v4.getW() * m4.getVec4X().getW(),
			v4.getX() * m4.getVec4Y().getX() + v4.getY() * m4.getVec4Y().getY() + v4.getZ() * m4.getVec4Y().getZ() + v4.getW() * m4.getVec4Y().getW(),
			v4.getX() * m4.getVec4Z().getX() + v4.getY() * m4.getVec4Z().getY() + v4.getZ() * m4.getVec4Z().getZ() + v4.getW() * m4.getVec4Z().getW(),
			v4.getX() * m4.getVec4W().getX() + v4.getY() * m4.getVec4W().getY() + v4.getZ() * m4.getVec4W().getZ() + v4.getW() * m4.getVec4W().getW());
	}

	float Matrix44::RowDotCol(int row, const Matrix44 & m4, int col) const
	{
		Vector4 vRow;
		assert(row >= 0);
		assert(row <= 3);
		assert(col >= 0);
		assert(col <= 3);

		switch (row) {
		case 0:
			vRow = mVec4X;
			break;
		case 1:
			vRow = mVec4Y;
			break;
		case 2:
			vRow = mVec4Z;
			break;
		case 3:
			vRow = mVec4W;
			break;
		}

		if (col == 0) {
			return vRow.getX() * m4.getVec4X().getX()
			+vRow.getY() * m4.getVec4Y().getX()
				+ vRow.getZ() * m4.getVec4Z().getX()
				+ vRow.getW() * m4.getVec4W().getX();
		}
		else if (col == 1) {
			return vRow.getX() * m4.getVec4X().getY()
			+vRow.getY() * m4.getVec4Y().getY()
				+ vRow.getZ() * m4.getVec4Z().getY()
				+ vRow.getW() * m4.getVec4W().getY();
		}
		else if (col == 2) {
			return vRow.getX() * m4.getVec4X().getZ()
			+vRow.getY() * m4.getVec4Y().getZ()
				+ vRow.getZ() * m4.getVec4Z().getZ()
				+ vRow.getW() * m4.getVec4W().getZ();
		}
		else {
			return vRow.getX() * m4.getVec4X().getW()
			+vRow.getY() * m4.getVec4Y().getW()
				+ vRow.getZ() * m4.getVec4Z().getW()
				+ vRow.getW() * m4.getVec4W().getW();
		}
	}

}