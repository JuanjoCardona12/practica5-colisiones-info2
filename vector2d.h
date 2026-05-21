#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D {
public:
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& o) const { return {x + o.x, y + o.y}; }
    Vector2D operator-(const Vector2D& o) const { return {x - o.x, y - o.y}; }
    Vector2D operator*(double s)          const { return {x * s,   y * s};   }
    Vector2D operator/(double s)          const { return {x / s,   y / s};   }
    Vector2D& operator+=(const Vector2D& o) { x += o.x; y += o.y; return *this; }

    double magnitud()     const { return std::sqrt(x*x + y*y); }
    double magnitudCuad() const { return x*x + y*y; }
    double punto(const Vector2D& o) const { return x*o.x + y*o.y; }

    Vector2D normalizar() const {
        double m = magnitud();
        return (m > 1e-9) ? (*this / m) : Vector2D(0, 0);
    }
};

#endif // VECTOR2D_H
