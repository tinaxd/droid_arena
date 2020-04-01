#pragma once

namespace da
{
    
template <typename T>
T zero() { static_assert([](){return false;}); }

template <>
int zero() { return 0; }

template <>
double zero() { return 0.0; }

template <>
float zero() { return 0.0f; }

 
template <typename T>
struct Vector2D
{
    Vector2D() : Vector2D(zero<T>(), zero<T>()) {}
    Vector2D(T x, T y) : x(x), y(y) {}
    
    Vector2D operator-() const {
        return Vector2D(-x, -y);
    }
    
    Vector2D& operator+=(const Vector2D<T>& a) {
        x += a.x;
        y += a.y;
        return *this;
    }
    
    Vector2D& operator-=(const Vector2D<T>& a) {
        x -= a.x;
        y -= a.y;
        return *this;
    }
    
    Vector2D& operator*=(T a) {
        x *= a;
        y *= a;
        return *this;
    }
    
    Vector2D& operator/=(T a) {
        x /= a;
        y /= a;
        return *this;
    }
    
    T x, y;
};

template <typename T>
Vector2D<T>
operator+(const Vector2D<T>& a, const Vector2D<T>& b)
{
    return Vector2D<T>(a.x + b.x, a.y + b.y);
}

template <typename T>
Vector2D<T>
operator-(const Vector2D<T>& a, const Vector2D<T>& b)
{
    return Vector2D<T>(a.x - b.x, a.y - b.y);
}

template <typename T>
Vector2D<T>
operator*(const Vector2D<T>& a, T m)
{
    return Vector2D<T>(a.x * m, a.y * m);
}

template <typename T>
Vector2D<T>
operator/(const Vector2D<T>& a, T m)
{
    return Vector2D<T>(a.x / m, a.y / m);
}

template <typename T>
bool
operator==(const Vector2D<T>& a, const Vector2D<T>& b)
{
    return a.x == b.x && a.y == b.y;
}

}
