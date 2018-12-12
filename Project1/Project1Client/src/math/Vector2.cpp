#include "stdafx.h"
#include <cassert>
#include "Vector2.h"

template<typename T>
app::math::Vector2<T>::Vector2()
	: x(zero)
	, y(zero)
{
}

template<typename T>
app::math::Vector2<T>::Vector2(T const & _x, T const & _y)
	: x(_x)
	, y(_y)
{
}

/************************************************************************/
/*************************** Member functions ***************************/
/************************************************************************/

template<typename T>
app::math::Vector2<T> const app::math::Vector2<T>::unit(Vector2<T> const & v)
{
	auto const length = v.magnitude();
	assert(length != app::math::Vector2<T>::zero);
	return Vector2<T>(v.x / length, v.y / length);
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator+=(Vector2 const & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator+=(T const & t)
{
	this->x += t;
	this->y += t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator-=(Vector2 const & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator-=(T const & t)
{
	this->x -= t;
	this->y -= t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator*=(Vector2 const & v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator*=(T const & t)
{
	this->x *= t;
	this->y *= t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator/=(Vector2 const & v)
{
	assert(v.x != app::math::Vector2<T>::zero && v.y != app::math::Vector2<T>::zero);
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator/=(T const & t)
{
	assert(t != app::math::Vector2<T>::zero);
	this->x /= t;
	this->y /= t;
	return *this;
}

template<typename T>
T app::math::Vector2<T>::magnitudeSqr() const
{
	return (this->x * this->x) + (this->y * this->y);
}

template<typename T>
T app::math::Vector2<T>::magnitude() const
{
	return static_cast<T>(std::sqrt(magnitudeSqr()));
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::unit()
{
	auto const length = this->magnitude();
	assert(length != app::math::Vector2<T>::zero);
	this->x /= length;
	this->y /= length;
	return *this;
}

template<typename T>
app::math::Vector2<T>::operator std::string()
{
	auto msg = std::string();
	msg.reserve(10);
	msg.append("(")
		.append(std::to_string(this->x))
		.append(",")
		.append(std::to_string(this->y))
		.append(")");
	return std::move(msg);
}

/************************************************************************/
/*************************** Static functions ***************************/
/************************************************************************/

template<typename T>
app::math::Vector2<T> app::math::operator+(Vector2<T> const & leftV, Vector2<T> const & rightV)
{
	return Vector2(leftV.x + rightV.x, leftV.y + rightV.y);
}

template<typename T>
app::math::Vector2<T> app::math::operator+(Vector2<T> const & v, T const & t)
{
	return Vector2(v.x + t, v.y + t);
}

template<typename T>
app::math::Vector2<T> app::math::operator+(T const & t, Vector2<T> const & v)
{
	return Vector2(v.x + t, v.y + t);
}

template<typename T>
app::math::Vector2<T> app::math::operator-(Vector2<T> const & leftV, Vector2<T> const & rightV)
{
	return Vector2(leftV.x - rightV.x, leftV.y - rightV.y);
}

template<typename T>
app::math::Vector2<T> app::math::operator-(Vector2<T> const & v, T const & t)
{
	return Vector2(v.x - t, v.y - t);
}

template<typename T>
app::math::Vector2<T> app::math::operator-(T const & t, Vector2<T> const & v)
{
	return Vector2(t - v.x, t - v.y);
}

template<typename T>
app::math::Vector2<T> app::math::operator*(Vector2<T> const & leftV, Vector2<T> const & rightV)
{
	return Vector2(leftV.x * rightV.x, leftV.y * rightV.y);
}

template<typename T>
app::math::Vector2<T> app::math::operator*(Vector2<T> const & v, T const & t)
{
	return Vector2(v.x * t, v.y * t);
}

template<typename T>
app::math::Vector2<T> app::math::operator*(T const & t, Vector2<T> const & v)
{
	return Vector2(v.x * t, v.y * t);
}

template<typename T>
app::math::Vector2<T> app::math::operator/(Vector2<T> const & leftV, Vector2<T> const & rightV)
{
	assert(rightV.x != app::math::Vector2<T>::zero && rightV.y != app::math::Vector2<T>::zero);
	return Vector2(leftV.x / rightV.x, leftV.y / rightV.y);
}

template<typename T>
app::math::Vector2<T> app::math::operator/(Vector2<T> const & v, T const & t)
{
	assert(t != app::math::Vector2<T>::zero);
	return Vector2(v.x / t, v.y / t);
}

template<typename T>
app::math::Vector2<T> app::math::operator/(T const & t, Vector2<T> const & v)
{
	assert(v.x != app::math::Vector2<T>::zero && v.y != app::math::Vector2<T>::zero);
	return Vector2(t / v.x, t / v.y);
}

template<typename T>
constexpr bool app::math::operator==(Vector2<T> const & leftV, Vector2<T> const & rightV)
{
	return leftV.x == rightV.x && leftV.y == rightV.y;
}

template<typename T>
constexpr bool app::math::operator==(Vector2<T> const & v, T const & t)
{
	return v.x == t && v.y == t;
}

template<typename T>
constexpr bool app::math::operator==(T const & t, Vector2<T> const & v)
{
	return t == v.x && t == v.y;
}

template<typename T>
constexpr bool app::math::operator!=(Vector2<T> const & leftV, Vector2<T> const rightV)
{
	return leftV.x != rightV.x && leftV.y != rightV.y;
}

template<typename T>
constexpr bool app::math::operator!=(Vector2<T> const & v, T const & t)
{
	return v.x != t && v.y != t;
}

template<typename T>
constexpr bool app::math::operator!=(T const & t, Vector2<T> const & v)
{
	return t != v.x && t != v.y;
}

template class app::math::Vector2<double>;
template class app::math::Vector2<float>;
template class app::math::Vector2<int32_t>;
template class app::math::Vector2<uint32_t>;
