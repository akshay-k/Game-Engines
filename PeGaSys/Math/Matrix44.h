#pragma once

#include "Vector4.h"

namespace Math3D {

	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
			float m8, float m9, float ma, float mb, float mc, float md, float me, float mf);
		Matrix44(Vector4 vec4X, Vector4 vec4Y, Vector4 vec4Z, Vector4 vec4W);

		/**
		 * Costructor for Matrix33
		 * Note: 4th component of each vec4X, vec4Y, vec4Z should be 0.0f 
		 * (Here we are representing a Vector3 as a Vector4. So the 4th component W should be 0.0f) 
		 */
		Matrix44(Vector4 vec4X, Vector4 vec4Y, Vector4 vec4Z);
		~Matrix44();
		// Accesors
		Vector4 getVec4X() const;
		Vector4 getVec4Y() const;
		Vector4 getVec4Z() const;
		Vector4 getVec4W() const;
		// Mutators
		void setVec4X(const Vector4 & vec);
		void setVec4Y(const Vector4 & vec);
		void setVec4Z(const Vector4 & vec);
		void setVec4W(const Vector4 & vec);
		void Matrix44::setVec4X(float a, float b, float c, float d);
		void Matrix44::setVec4Y(float a, float b, float c, float d);
		void Matrix44::setVec4Z(float a, float b, float c, float d);
		void Matrix44::setVec4W(float a, float b, float c, float d);
		
		Matrix44 & operator*=(float f);
		Matrix44 operator*(float f) const;
		friend Matrix44 operator*(float f, const Matrix44 & m4);
		Matrix44 operator/(float f) const;
		Vector4 operator*(const Vector4 & v4) const;

		static float degreesToRadians(const float degrees); // helper to convert degrees to radians
		const float* convertToFloatArray(); // helper for loading matrices into gl



		/** Transform a vector by the transpose of a matrix.
		 *	param v4 Vector to transform
		 *	param m4 Transformation matrix
		 *	return Transformed vector.
		 */
		static friend Vector4 operator* (const Vector4 & v4, const Matrix44 & m4);


		/**
		*  Transform a vector by the upper 3x3 (rotation and scale part) of a transformation matrix.
		*/
		Vector4 TransformNormal(const Vector4 & v4) const;

		void TransformNormalByUpper3x3Transpose(Vector4 & out, const Vector4 & v4) const;
		Vector4 TransformNormalByUpper3x3Transpose(const Vector4 & in) const;

		/** Transform a plane (in Hessian normal form) by a transformation matrix.
		 *  \param vPlane xyz components are the plane normal, which this routine assumes is normalized.
		 *  w component is the distance of the plane from the origin, along
		 *  the direction of the normal. This is Hessian normal form.
		 *  \param m4 Transformation matrix.
		 *  \return Transformed plane as a 4-vector (same format as vPlane).
		 */
		Vector4 TransformPlane(const Vector4 & vPlane) const;

		Matrix44 operator+(const Matrix44 & rhs) const;	
		Matrix44 operator-(const Matrix44 & rhs) const;
		Matrix44 & operator+=(const Matrix44 & rhs);
		Matrix44 & operator-=(const Matrix44 & rhs);

		/** Return a matrix that is the result of matrix-matrix multiplication.
		 *  \note This concatenation is backwards from the usual mathematical notation.
		 *  In typical math notation, (T2 * T1) * v means the same as T2 * (T1 * v)
		 *  which means "transform v by T1, then by T2."
		 *  But for Ma44 and Vec4, (T1 * T2) * v ~= T2 * (T1 * v).
		 *  The following would lead to similar results for v1_2 and v12:
		 *  const Vec4 v0( ... ) ;
		 *  const Mat44 t1( ... ) , t2( ... ) ;
		 *  const Vec4 v1 = T1 * v ;
		 *  const Vec4 v1_2 = T2 * v1 ;
		 *  const Mat44 t12 = T1 * T2 ;
		 *  const Vec4 v12 = t12 * v0 ; // matches v1_2 to within numerical accuracy
		 */
		Matrix44 operator*(const Matrix44 & rhs) const; // Matrix-matrix multiplication
		Matrix44 GetTranspose() const;
		bool isDiagonal() const;

		// 3x3 Matrix routines
		float Determinant() const;
		Matrix44 Inverse() const;

		// Matrix Setters
		void SetScale(float scaleX, float scaleY, float scaleZ);

		/** Assign rightward unit vector part of transformation matrix.
		 *  \param v3Right - vector3 pointing along transformed space +x axis
		 */
		void SetRight(const Vector4 & v3Right);

		/** Assign upward unit vector part of transformation matrix.
		 *  \param v3Up - vector3 pointing along transformed space +y axis
		 */
		void SetUp(const Vector4 & v3Up);

		/** Assign forward unit vector part of transformation matrix.
		 *  \param vForward - vector3 pointing along transformed space +z axis
		 */
		void SetForward(const Vector4 & v3Forward);

		void SetTranslation(const Vector4 & transVec3);

		/** Assign rotation matrix through angle about X axis.
		 *  \param angle - angle (in radians) to rotate
		 */
		void SetRotationX(float angle);

		/** Assign rotation matrix through angle about Y axis.
		 *  \param angle - angle (in radians) to rotate
		 */
		void SetRotationY(float angle);

		/** Assign rotation matrix through angle about Z axis.
		 *  \param angle - angle (in radians) to rotate
		 */
		void SetRotationZ(float angle);

		/** Assign rotation matrix from angles about X, Y and Z axes.
		 *  \param angles Angles (in radians) to rotate about X, Y and Z axes
		 *  angles is a vector3
		 */
		void SetRotationXYZ(const Vector4 & anglesAsVec3);

		/** Assign rotation matrix from axis and angle.
		 *  \param axis - axis about which to rotate. Must have unit length.
		 *  \param angle - angle (in radians) to rotate
		 */
		void SetRotation(const Vector4 & axisAsVec3, float angle);

		/** Assign the rotation part of this matrix based on the given 3-by-3 matrix.
		 * o33 is a Matrix33 represented as a Matrix44. The function has assert statements which verifies if
		 * o33 is a Matrix33
		 */
		void SetRotation(const Matrix44 & o33);

		/** Assign view matrix for given camera parameters.
		 *  \param eye Eye position in world space
		 *  \param lookAtAsVec3 Look-at position in world space 
		 *  \param upApproximateAsVec3 Approximate direction, in world space, toward which camera top points. Should not be parallel to (eye-lookAt).
		 */
		void SetView(const Vector4 & eye, const Vector4 & lookAtAsVec3, const Vector4 & upApproximateAsVec3);

		/** Extract camera position from (this) view matrix.
		 *  Position is retured as vector3 i.e 4th component will be 0.0f
		*/
		Vector4 CameraPositionFromViewMatrix() const;

		/*
			Given a v3 vector (x, y, z) returns the cross product matrix notation
			| 0 -z  y|
			| z  0 -x|
			|-y  x  0|
		*/
		static Matrix44 CrossProductMatrix(Vector4 v3Vector);

		void SetProjection(float n, float f, float t, float b, float r, float l);

		void SetProjection(float angle, float fov, float n, float f);

		void OrthonormalizeM33();
		void print();
	private:
		Vector4 mVec4X; 
		Vector4 mVec4Y;
		Vector4 mVec4Z;
		Vector4 mVec4W;

		// Utility routine to compute an element of a matrix-matrix product.
		float RowDotCol(int row, const Matrix44 & m4, int col) const;
	};
	typedef Matrix44 * Matrix44Ptr;
}