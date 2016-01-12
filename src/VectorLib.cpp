#include "VectorLib.h"
#include <array>
#include <stdexcept>

namespace ObjViewer {
	namespace VectorLib {

		using namespace std;

		const static unsigned int R1C1 = 0;
		const static unsigned int R1C2 = 4;
		const static unsigned int R1C3 = 8;
		const static unsigned int R1C4 = 12;
		const static unsigned int R2C1 = 1;
		const static unsigned int R2C2 = 5;
		const static unsigned int R2C3 = 9;
		const static unsigned int R2C4 = 13;
		const static unsigned int R3C1 = 2;
		const static unsigned int R3C2 = 6;
		const static unsigned int R3C3 = 10;
		const static unsigned int R3C4 = 14;
		const static unsigned int R4C1 = 3;
		const static unsigned int R4C2 = 7;
		const static unsigned int R4C3 = 11;
		const static unsigned int R4C4 = 15;

		struct Matrix4::Matrix4Impl {
			// contents of matrix, in column-major order
			array<float, SIZE> m;
		};

		void SetIdentity(array<float, Matrix4::SIZE>& mat)
		{
			mat[R1C1] = mat[R2C2] = mat[R3C3] = mat[R4C4] = 1.0f;
			mat[R1C2] = mat[R1C3] = mat[R1C4] =
			mat[R2C1] = mat[R2C3] = mat[R2C4] =
			mat[R3C1] = mat[R3C2] = mat[R3C4] =
			mat[R4C1] = mat[R4C2] = mat[R4C3] = 0;
		}

		Matrix4::Matrix4() : pImpl(new Matrix4Impl)
		{
			SetIdentity(pImpl->m);
		}

		Matrix4::Matrix4(float mat[SIZE]) : pImpl(new Matrix4Impl)
		{
			array<float, SIZE>& m = pImpl->m;
			for (int i = 0; i < SIZE; ++i) {
				m[i] = mat[i];
			}
		}

		Matrix4::Matrix4(array<float, SIZE> mat) : Matrix4(mat.data()) {}

		Matrix4::Matrix4(const Matrix4& other) : Matrix4(other.pImpl->m) {}

		Matrix4& Matrix4::operator=(Matrix4 rhs)
		{
			swap(rhs);
			return *this;
		}

		void Matrix4::swap(Matrix4& other)
		{
			using std::swap;
			swap(pImpl, other.pImpl);
		}

		const float& Matrix4::operator()(const unsigned int row, const unsigned int col) const
		{
			return (*this)[4 * col + row];
		}

		float& Matrix4::operator()(const unsigned int row, const unsigned int col)
		{
			return const_cast<float&>(static_cast<const Matrix4&>(*this)(row, col));
		}

		const float& Matrix4::operator[](const unsigned int index) const
		{
			if (index >= SIZE)
				throw out_of_range("Matrix4");
			return pImpl->m[index];
		}

		float& Matrix4::operator[](const unsigned int index)
		{
			return const_cast<float&>(static_cast<const Matrix4&>(*this)[index]);
		}

		const float * Matrix4::GetColumnMajor() const
		{
			return pImpl->m.data();
		}

		Matrix4 operator*(const Matrix4& lhs, const Matrix4& rhs)
		{
			return Matrix4({
				lhs[R1C1] * rhs[R1C1] + lhs[R1C2] * rhs[R2C1] + lhs[R1C3] * rhs[R3C1] + lhs[R1C4] * rhs[R4C1],
				lhs[R2C1] * rhs[R1C1] + lhs[R2C2] * rhs[R2C1] + lhs[R2C3] * rhs[R3C1] + lhs[R2C4] * rhs[R4C1],
				lhs[R3C1] * rhs[R1C1] + lhs[R3C2] * rhs[R2C1] + lhs[R3C3] * rhs[R3C1] + lhs[R3C4] * rhs[R4C1],
				lhs[R4C1] * rhs[R1C1] + lhs[R4C2] * rhs[R2C1] + lhs[R4C3] * rhs[R3C1] + lhs[R4C4] * rhs[R4C1],
				lhs[R1C1] * rhs[R1C2] + lhs[R1C2] * rhs[R2C2] + lhs[R1C3] * rhs[R3C2] + lhs[R1C4] * rhs[R4C2],
				lhs[R2C1] * rhs[R1C2] + lhs[R2C2] * rhs[R2C2] + lhs[R2C3] * rhs[R3C2] + lhs[R2C4] * rhs[R4C2],
				lhs[R3C1] * rhs[R1C2] + lhs[R3C2] * rhs[R2C2] + lhs[R3C3] * rhs[R3C2] + lhs[R3C4] * rhs[R4C2],
				lhs[R4C1] * rhs[R1C2] + lhs[R4C2] * rhs[R2C2] + lhs[R4C3] * rhs[R3C2] + lhs[R4C4] * rhs[R4C2],
				lhs[R1C1] * rhs[R1C3] + lhs[R1C2] * rhs[R2C3] + lhs[R1C3] * rhs[R3C3] + lhs[R1C4] * rhs[R4C3],
				lhs[R2C1] * rhs[R1C3] + lhs[R2C2] * rhs[R2C3] + lhs[R2C3] * rhs[R3C3] + lhs[R2C4] * rhs[R4C3],
				lhs[R3C1] * rhs[R1C3] + lhs[R3C2] * rhs[R2C3] + lhs[R3C3] * rhs[R3C3] + lhs[R3C4] * rhs[R4C3],
				lhs[R4C1] * rhs[R1C3] + lhs[R4C2] * rhs[R2C3] + lhs[R4C3] * rhs[R3C3] + lhs[R4C4] * rhs[R4C3],
				lhs[R1C1] * rhs[R1C4] + lhs[R1C2] * rhs[R2C4] + lhs[R1C3] * rhs[R3C4] + lhs[R1C4] * rhs[R4C4],
				lhs[R2C1] * rhs[R1C4] + lhs[R2C2] * rhs[R2C4] + lhs[R2C3] * rhs[R3C4] + lhs[R2C4] * rhs[R4C4],
				lhs[R3C1] * rhs[R1C4] + lhs[R3C2] * rhs[R2C4] + lhs[R3C3] * rhs[R3C4] + lhs[R3C4] * rhs[R4C4],
				lhs[R4C1] * rhs[R1C4] + lhs[R4C2] * rhs[R2C4] + lhs[R4C3] * rhs[R3C4] + lhs[R4C4] * rhs[R4C4]
			});
		}

		Matrix4 RotMatrix(float theta, Vector3 axis)
		{
			float ct = cos(theta);
			float st = sin(theta);
			float inv = (1 - ct);
			return Matrix4({
				ct + axis.x * axis.x * inv,
				axis.y * axis.x * inv + axis.z * st,
				axis.z * axis.x * inv - axis.y * st,
				0,
				axis.x * axis.y * inv,
				ct + axis.y * axis.y * inv,
				axis.z * axis.y * inv + axis.x * st,
				0,
				axis.x * axis.z * inv + axis.y * st,
				axis.y * axis.z * inv - axis.x * st,
				ct + axis.z * axis.z * inv,
				0,
				0, 0, 0, 1.0f
			});
		}

	}
}

namespace std {
	template<>
	void swap<ObjViewer::VectorLib::Matrix4>(
		ObjViewer::VectorLib::Matrix4& a,
		ObjViewer::VectorLib::Matrix4& b)
	{
		a.swap(b);
	}
}
