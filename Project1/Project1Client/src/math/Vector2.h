#ifndef _MATH_VECTOR_H
#define _MATH_VECTOR_H

namespace app::math
{
	template<typename T>
	class Vector2
	{
	public: // Constructors/Destructor/Assignments
		Vector2();
		Vector2(T const & _x, T const & _y);

		~Vector2() = default;

		Vector2(Vector2 const &) = default;
		Vector2 & operator=(Vector2 const &) = default;

		Vector2(Vector2 &&) = default;
		Vector2 & operator=(Vector2 &&) = default;

	public: // Public Static Functions
		static Vector2<T> const unit(Vector2<T> const & v);
	public: // Public Member Functions
		Vector2 & operator+=(Vector2 const & v);
		Vector2 & operator+=(T const & t);

		Vector2 & operator-=(Vector2 const & v);
		Vector2 & operator-=(T const & t);

		Vector2 & operator*=(Vector2 const & v);
		Vector2 & operator*=(T const & t);

		Vector2 & operator/=(Vector2 const & v);
		Vector2 & operator/=(T const & t);

		T magnitudeSqr() const;
		T magnitude() const;
		Vector2<T> & unit();

		operator std::string();

	public: // Public Static Variables
	public: // Public Member Variables
		T x, y;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		constexpr static T const zero = static_cast<T>(0);
	private: // Private Member Variables
	};

	// Plus operators

	template<typename T> Vector2<T> operator+(Vector2<T> const & leftV, Vector2<T> const & rightV);
	template<typename T> Vector2<T> operator+(Vector2<T> const & v, T const & t);
	template<typename T> Vector2<T> operator+(T const & t, Vector2<T> const & v);

	// Minus operators

	template<typename T> Vector2<T> operator-(Vector2<T> const & leftV, Vector2<T> const & rightV);
	template<typename T> Vector2<T> operator-(Vector2<T> const & v, T const & t);
	template<typename T> Vector2<T> operator-(T const & t, Vector2<T> const & v);

	// Multiplication operators

	template<typename T> Vector2<T> operator*(Vector2<T> const & leftV, Vector2<T> const & rightV);
	template<typename T> Vector2<T> operator*(Vector2<T> const & v, T const & t);
	template<typename T> Vector2<T> operator*(T const & t, Vector2<T> const & v);

	// Division operators

	template<typename T> Vector2<T> operator/(Vector2<T> const & leftV, Vector2<T> const & rightV);
	template<typename T> Vector2<T> operator/(Vector2<T> const & v, T const & t);
	template<typename T> Vector2<T> operator/(T const & t, Vector2<T> const & v);

	// Equality operators

	template<typename T> constexpr bool operator==(Vector2<T> const & leftV, Vector2<T> const & rightV);
	template<typename T> constexpr bool operator==(Vector2<T> const & v, T const & t);
	template<typename T> constexpr bool operator==(T const & t, Vector2<T> const & v);

	// Inequality operators

	template<typename T> constexpr bool operator!=(Vector2<T> const & leftV, Vector2<T> const rightV);
	template<typename T> constexpr bool operator!=(Vector2<T> const & v, T const & t);
	template<typename T> constexpr bool operator!=(T const & t, Vector2<T> const & v);

	typedef Vector2<double> Vector2d;
	typedef Vector2<float> Vector2f;
	typedef Vector2<int32_t> Vector2i;
	typedef Vector2<uint32_t> Vector2u;
}

#endif // !_MATH_VECTOR_H
