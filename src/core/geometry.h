//
// Created by 18310 on 2021/3/9.
//

#ifndef SIMPLERENDERER_GEOMETRY_H
#define SIMPLERENDERER_GEOMETRY_H

#include "sr.h"

namespace sr {

    template<typename T>
    class Vector2 {
    public:
        T x, y;

        Vector2() : x(0), y(0) {}

        Vector2(T _x, T _y) : x(_x), y(_y) {
            assert(!HasNans());
        }

        T operator[](std::size_t i) const {
            assert(i >= 0 && i < 2);
            return i == 0 ? x : y;
        }

        T &operator[](std::size_t i) {
            assert(i >= 0 && i < 2);
            return i == 0 ? x : y;
        }

        bool HasNans() const {
            return std::isnan(x) || std::isnan(y);
        }

        Vector2<T> operator+(const Vector2<T> &v) const {
            return Vector2(x + v.x, y + v.y);
        }

        Vector2<T> &operator+=(const Vector2<T> &v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector2<T> operator-() const {
            return Vector2(-x, -y);
        }

        Vector2<T> operator-(const Vector2<T> &v) const {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2<T> &operator-=(const Vector2<T> &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        Vector2<T> operator*(const T s) const {
            return Vector2(x * s, y * s);
        }

        Vector2<T> &operator*=(const T s) {
            x *= s;
            y *= s;
            return *this;
        }

        Vector2<T> operator/(const T s) const {
            assert(s != 0);
            auto inv = (Float) 1 / s;
            return Vector2<T>(x * inv, y * inv);
        }

        Vector2<T> &operator/=(const T s) {
            assert(s != 0);
            auto inv = (Float) 1 / s;
            x *= inv;
            y *= inv;
            return *this;
        }

        Float LengthSquared() const { return x * x + y * y; }

        Float Length() const { return std::sqrt(LengthSquared()); }

    };

/*************************************************Vector2 functions****************************************************/
    template<typename T>
    inline Vector2<T> operator*(const T s, Vector2<T> &v) {
        return v * s;
    }

    template<typename T>
    inline Vector2<T> Abs(const Vector2<T> &v) {
        return Vector2<T>(std::abs(v.x), std::abs(v.y));
    }

    template<typename T>
    inline T Dot(const Vector2<T> &v1, const Vector2<T> &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template<typename T>
    inline T AbsDot(const Vector2<T> &v1, const Vector2<T> &v2) {
        return std::abs(Dot(v1, v2));
    }

    template<typename T>
    inline Vector2<T> Normalize(const Vector2<T> &v) {
        return v / v.Length();
    }

    template<typename T>
    T MinComponent(const Vector2<T> &v) {
        return std::min(v.x, v.y);
    }

    template<typename T>
    T MaxComponent(const Vector2<T> &v) {
        return std::max(v.x, v.y);
    }

    template<typename T>
    int MaxDimension(const Vector2<T> &v) {
        return v.x > v.y ? 0 : 1;
    }

    template<typename T>
    Vector2<T> Permute(const Vector2<T> &v, int x, int y) {
        return Vector2<T>(v[x], v[y]);
    }

    template<typename T>
    inline void CoordinateSystem(const Vector2<T> &v1, Vector2<T> *v2) {
        *v2 = Normalize(Vector2<T>(-v1.y, v1.x));
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, const Vector2<T> &v) {
        out << "[ " << v.x << ", " << v.y << " ]";
        return out;
    }


/**********************************************************************************************************************/
    template<typename T>
    class Normal3;

    template<typename T>
    class Vector3 {
    public:
        T x, y, z;

        Vector3() : x(0), y(0), z(0) {}

        Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {
            assert(!HasNans());
        }

        explicit Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {
            assert(n.HasNans());
        }

        T operator[](std::size_t i) const {
            assert(i >= 0 && i < 3);
            return i == 0 ? x : (i == 1 ? y : z);
        }

        T &operator[](std::size_t i) {
            assert(i >= 0 && i < 3);
            return i == 0 ? x : (i == 1 ? y : z);
        }

        bool HasNans() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        }

        Vector3<T> operator+(const Vector3<T> &v) const {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        Vector3<T> &operator+=(const Vector3<T> &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3<T> operator-() const {
            return Vector3(-x, -y, -z);
        }

        Vector3<T> operator-(const Vector3<T> &v) const {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3<T> &operator-=(const Vector3<T> &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        Vector3<T> operator*(const T s) const {
            return Vector3(x * s, y * s, z * s);
        }

        Vector3<T> &operator*=(const T s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        Vector3<T> operator/(const T s) const {
            assert(s != 0);
            auto inv = (Float) 1 / s;
            return Vector3<T>(x * inv, y * inv, z * inv);
        }

        Vector3<T> &operator/=(const T s) {
            assert(s != 0);
            auto inv = (Float) 1 / s;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }

        Float LengthSquared() const {
            return x * x + y * y + z * z;
        }

        Float Length() const {
            return std::sqrt(LengthSquared());
        }

    };

/***************************************************Vector3 functions**************************************************/
    template<typename T>
    inline Vector3<T> operator*(const T s, Vector3<T> &v) {
        return v * s;
    }

    template<typename T>
    inline Vector3<T> Abs(const Vector3<T> &v) {
        return Vector3<T>(std::abs(v.x, v.y, v.z));
    }

    template<typename T>
    inline T Dot(const Vector3<T> &v1, const Vector3<T> &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template<typename T>
    inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2) {
        return std::abs(Dot(v1, v2));
    }

    template<typename T>
    inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2) {
        double v1x = v1.x, v1y = v1.y, v1z = v1.z;
        double v2x = v2.x, v2y = v2.y, v2z = v2.z;
        return Vector3<T>(v1y * v2z - v1z * v2y, v1z * v2x - v1x * v2z, v1x * v2y - v1y * v2x);
    }

    template<typename T>
    inline Vector3<T> Normalize(const Vector3<T> &v) {
        return v / v.Length();
    }

    template<typename T>
    T MinComponent(const Vector3<T> &v) {
        return std::min(v.x, std::min(v.y, v.z));
    }

    template<typename T>
    T MaxComponent(const Vector3<T> &v) {
        return std::max(v.x, std::max(v.y, v.z));
    }

    template<typename T>
    int MaxDimension(const Vector3<T> &v) {
        return (v.x > v.y) ? (v.x > v.z ? 0 : 2) : (v.y > v.z ? 1 : 2);
    }

    template<typename T>
    Vector3<T> Min(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
    }

    template<typename T>
    Vector3<T> Max(const Vector3<T> &v1, const Vector3<T> &v2) {
        return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
    }

    template<typename T>
    Vector3<T> Permute(const Vector3<T> v, int x, int y, int z) {
        return Vector3<T>(v[x], v[y], v[z]);
    }

    //assume v1 has been normalized
    template<typename T>
    inline void CoordinateSystem(const Vector3<T> &v1, Vector3<T> *v2, Vector3<T> *v3) {
        if (std::abs(v1.x) > std::abs(v1.y))
            *v2 = Normalize(Vector3<T>(-v1.z, 0, v1.x));
        else
            *v2 = Normalize(Vector3<T>(0, -v1.z, v1.y));
        *v3 = Cross(v1, *v2);
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, Vector3<T> &v) {
        out << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
        return out;
    }

/***********************************************Vector:typedef*********************************************************/

    typedef Vector2<int> Vector2i;
    typedef Vector2<Float> Vector2f;
    typedef Vector3<int> Vector3i;
    typedef Vector3<Float> Vector3f;

/************************************************class point***********************************************************/
    template<typename T>
    class Point2 {
    public:
        T x, y;

        Point2() : x(0), y(0) {}

        Point2(T _x, T _y) : x(_x), y(_y) { assert(!HasNans()); }

        template<typename U>
        explicit Point2(const Point3<U> &p) : x((U) p.x), y((U) p.y) { assert(!HasNans()); }

        template<typename U>
        explicit operator Vector2<U>() const {
            return Vector2<U>(x, y);
        }

        bool HasNans() const {
            return std::isnan(x) || std::isnan(y);
        }

        Point2<T> operator+(const Vector2<T> &v) const {
            return Point2<T>(x + v.x, y + v.y);
        }

        Point2<T> operator+=(const Vector2<T> &v) {
            x += v.x;
            y + v.y;
            return *this;
        }

        Vector2<T> operator-(const Point2<T> &p) const {
            return Vector2<T>(x - p.x, y - p.y);
        }

        Point2<T> operator-(const Vector2<T> &v) const {
            return Point2<T>(x - v.x, y - v.y);
        }

        Point2<T> &operator-=(const Vector2<T> &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }


    };

    template<typename T>
    class Point3 {
    public:
        T x, y, z;

        Point3() : x(0), y(0), z(0) {}

        Point3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) { assert(!HasNans()); }

        //avoid implicit conversion from point<U> to point<T>
        template<typename U>
        explicit Point3(const Point3<U> &p): x((T) p.x), y((T) p.y), z((T) p.z) { assert(!HasNans()); }

        //avoid implicit conversion like: point = Vector3
        template<typename U>
        explicit operator Vector3<U>() const {
            return Vector3<U>(x, y, z);
        }

        bool HasNans() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        }

        Point3<T> operator+(const Vector3<T> &v) const {
            return Point3<T>(x + v.x, y + v.y, z + v.z);
        }

        Point3<T> &operator+=(const Vector3<T> &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3<T> operator-(const Point3<T>& p) const{
            return Vector3<T>(x - p.x, y - p.y, z - p.z);
        }

        Point3<T> operator-(const Vector3<T>& v) const{
            return Point3<T>(x - v.x, y - v.y, z - v.z);
        }

        Point3<T> operator-=(const Vector3<T>& v){
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

    };

/************************************************Point typedef*********************************************************/

    typedef Point2<int> Point2i;
    typedef Point2<Float> Point2f;
    typedef Point3<int> Point3i;
    typedef Point3<Float> Point3f;

/************************************************Point functions*******************************************************/

    template<typename T>
    inline Float Distance(const Point2<T> &p1, const Point2<T> &p2) {
        return (p2 - p1).Length();
    }

    template<typename T>
    inline Float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
        return (p2 - p1).LengthSquared();
    }

    template<typename T>
    inline Float Distance(const Point3<T> &p1, const Point3<T> &p2) {
        return (p2 - p1).Length();
    }

    template<typename T>
    inline Float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
        return (p2 - p1).LengthSquared();
    }

    template<typename T>
    inline Point2<T> Lerp(Float t, const Point2<T> &p0, const Point2<T> &p1) {
        return (1 - t) * p0 + t * p1;
    }

    template<typename T>
    inline Point3<T> Lerp(Float t, const Point3<T> &p0, const Point3<T> &p1) {
        return (1 - t) * p0 + t * p1;
    }

    template<typename T>
    inline Point2<T> Min(const Point2<T> &p0, const Point2<T> &p1) {
        return Point2<T>(std::min(p0.x, p1.x), std::min(p0.y, p1.y));
    }

    template<typename T>
    inline Point3<T> Min(const Point3<T> &p0, const Point3<T> &p1) {
        return Point3<T>(std::min(p0.x, p1.x), std::min(p0.y, p1.y), std::min(p0.z, p1.z));
    }

    template<typename T>
    inline Point2<T> Max(const Point2<T> &p0, const Point2<T> &p1) {
        return Point2<T>(std::max(p0.x, p1.x), std::max(p0.y, p1.y));
    }

    template<typename T>
    inline Point3<T> Max(const Point3<T> &p0, const Point3<T> &p1) {
        return Point3<T>(std::max(p0.x, p1.x), std::max(p0.y, p1.y), std::max(p0.z, p1.z));
    }

    template<typename T>
    inline Point2<T> Floor(const Point2<T> &p) {
        return Point2<T>(std::floor(p.x), std::floor(p.y));
    }

    template<typename T>
    inline Point3<T> Floor(const Point3<T> &p) {
        return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
    }

    template<typename T>
    inline Point2<T> Ceil(const Point2<T> &p) {
        return Point2<T>(std::ceil(p.x), std::ceil(p.y));
    }

    template<typename T>
    inline Point3<T> Ceil(const Point3<T> &p) {
        return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
    }

    template<typename T>
    inline Point2<T> Abs(const Point2<T> &p) {
        return Point2<T>(std::abs(p.x), std::abs(p.y));
    }

    template<typename T>
    inline Point3<T> Abs(const Point3<T> &p) {
        return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
    }

    template<typename T>
    inline Point2<T> Permute(const Point2<T> &p, int x, int y) {
        return Point2<T>(p[x], p[y]);
    }

    template<typename T>
    inline Point3<T> Permute(const Point3<T> &p, int x, int y, int z) {
        return Point3<T>(p[x], p[y], p[z]);
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, const Point2<T> &p) {
        out << "[ " << p.x << ", " << p.y << " ]";
        return out;
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, const Point3<T> &p) {
        out << "[ " << p.x << ", " << p.y << ", " << p.z << " ]";
        return out;
    }

/***************************************************class Normal*******************************************************/
    template<typename T>
    class Normal3 {
    public:
        T x, y, z;

        Normal3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {
            assert(!HasNans());
        }

        explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {
            assert(!v.HasNans());
        }

        T operator[](std::size_t i) const {
            assert(i >= 0 && i < 3);
            return i == 0 ? x : (i == 1 ? y : z);
        }

        T &operator[](std::size_t i) {
            assert(i >= 0 && i < 3);
            return i == 0 ? x : (i == 1 ? y : z);
        }

        bool HasNans() const {
            return std::isnan(x) || std::isnan(y) || std::isnan(z);
        }

        Normal3<T> operator+(const Normal3<T> &n) const {
            return Normal3<T>(x + n.x, y + n.y, z + n.z);
        }

        Normal3<T> &operator*(const Normal3<T> &n) const {
            x += n.x;
            y += n.y;
            z += n.z;
            return *this;
        }

        Normal3<T> operator-() const {
            return Normal3<T>(-x, -y, -z);
        }

        Normal3<T> operator-(const Normal3<T> &n) const {
            return Normal3<T>(x - n.x, y - n.y, z - n.z);
        }

        Normal3<T> operator-=(const Normal3<T> &n) {
            x -= n.x;
            y -= n.y;
            z -= n.z;
            return *this;
        }

        Normal3<T> operator*(const T s) const {
            return Normal3<T>(x * s, y * s, z * s);
        }

        Normal3<T> &operator*=(const T s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        Normal3<T> operator/(const T f) const {
            assert(f != 0);
            auto inv = (Float) 1 / f;
            return Normal3<T>(x * inv, y * inv, z * inv);
        }

        Normal3<T> operator/=(const T f) {
            assert(f != 0);
            auto inv = (Float) 1 / f;
            x *= inv;
            y *= inv;
            z *= inv;
            return *this;
        }

        Float LengthSquared() const {
            return x * x + y * y + z * z;
        }

        Float Length() const {
            return std::sqrt(LengthSquared());
        }


    };

/**************************************************typedef Normal******************************************************/
    typedef Normal3<Float> Normal3f;
    typedef Normal3<int> Normal3i;

/**************************************************Normal Function*****************************************************/
    template<typename T>
    inline Normal3<T> operator*(const T s, const Normal3<T> &n) {
        return n * s;
    }

    template<typename T>
    inline Normal3<T> Abs(const Normal3<T> &n) {
        return Normal3<T>(std::abs(n.x), std::abs(n.y), std::abs(n.z));
    }

    template<typename T>
    inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2) {
        return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
    }

    template<typename T>
    inline T AbsDot(const Normal3<T> &n1, const Normal3<T> &n2) {
        return Abs(Dot(n1, n2));
    }

    template<typename T>
    inline Normal3<T> Normalize(const Normal3<T> &n) {
        return n / n.Length();
    }

    template<typename T>
    inline T Dot(const Normal3<T> &n, const Vector3<T> &v) {
        return n.x * v.x + n.y * v.y + n.z * v.z;
    }

    template<typename T>
    inline T Dot(const Vector3<T> &v, const Normal3<T> &n) {
        return Dot(n, v);
    }

    template<typename T>
    inline T AbsDot(const Normal3<T> &n, const Vector3<T> &v) {
        return std::abs(Dot(n, v));
    }

    template<typename T>
    inline T AbsDot(const Vector3<T> &v, const Normal3<T> &n) {
        return AbsDot(n, v);
    }

    template<typename T>
    inline Normal3<T> FaceForward(const Normal3<T> &n, const Vector3<T> &v) {
        return Dot(n, v) < 0.f ? -n : n;
    }

    template<typename T>
    inline Vector3<T> FaceForward(const Vector3<T> &v, const Normal3<T> &n) {
        return Dot(n, v) < 0.f ? -v : v;
    }

    template<typename T>
    inline Normal3<T> FaceForward(const Normal3<T> &n, const Normal3<T> &n1) {
        return Dot(n, n1) < 0.f ? -n : n;
    }

    template<typename T>
    inline Vector3<T> FaceForward(const Vector3<T> &v, const Vector3<T> &v1) {
        return Dot(v, v1) < 0.f ? -v : v;
    }

    template<typename T>
    inline std::ostream &operator<<(std::ostream &out, const Normal3<T> &n) {
        out << "[ " << n.x << ", " << n.y << ", " << n.z << " ]";
        return out;
    }

/**************************************************class ray***********************************************************/

    class Ray {
    public:
        Point3f o;
        Vector3f d;
        mutable Float tMax;
        Float time;
        //Medium contains the origin
        const Medium *medium;

        Ray() : tMax(Infinity), time(0.f), medium(nullptr) {}

        Ray(const Point3f &o, const Vector3f &d, Float tMax = Infinity, Float time = 0.f,
            const Medium *medium = nullptr) : o(o), d(d), tMax(tMax), time(time), medium(medium) {}

        Point3f operator()(Float t) {
            return o + t * d;
        }
    };

    class RayDifferentials : Ray{

    };

/**************************************************class bound*********************************************************/


}
#endif //SIMPLERENDERER_GEOMETRY_H
