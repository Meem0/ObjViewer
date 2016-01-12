#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

#include <memory>
#include <array>

namespace ObjViewer {
	namespace VectorLib {

		struct Vector3 {
			Vector3() : x(0), y(0), z(0) {}
			Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
			float x, y, z;
		};

		class Matrix4
		{
		public:
			// number of elements in matrix
			const static unsigned int SIZE = 16;

			// initializes matrix to identity
			Matrix4();
			// initialize matrix with array in column-major order
			Matrix4(float mat[SIZE]);
			Matrix4(std::array<float, SIZE> mat);
			Matrix4(const Matrix4&);

			virtual ~Matrix4() {}

			Matrix4& operator=(Matrix4);

			void swap(Matrix4& other);

			// get/set element by row/column access
			const float& operator()(const unsigned int row, const unsigned int col) const;
			float& operator()(const unsigned int row, const unsigned int col);
			// get/set element by index in column-major order
			const float& operator[](const unsigned int index) const;
			float& operator[](const unsigned int index);

			const float* GetColumnMajor() const;
		private:
			struct Matrix4Impl;
			std::shared_ptr<Matrix4Impl> pImpl;
		};

		Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs);

		Matrix4 RotMatrix(float theta, Vector3 axis);
	}
}

namespace std {
	template<>
	void swap<ObjViewer::VectorLib::Matrix4>(
		ObjViewer::VectorLib::Matrix4& a,
		ObjViewer::VectorLib::Matrix4& b);
}

#endif
