//
// Created by 18310 on 2021/3/14.
//

#ifndef SIMPLERENDERER_TRANSFORM_H
#define SIMPLERENDERER_TRANSFORM_H

#include "sr.h"
#include "geometry.h"


namespace sr{

    class Matrix4x4{
    public:
        Float m[4][4]{};

        Matrix4x4();
        Matrix4x4(const Float _m[4][4]);
        Matrix4x4(Float t00, Float t01, Float t02, Float t03, Float t10, Float t11, Float t12, Float t13,
                  Float t20, Float t21, Float t22, Float t23, Float t30, Float t31, Float t32, Float t33);
        static Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2);
        bool operator==(const Matrix4x4& m2) const;
        bool operator!=(const Matrix4x4& m2) const;
    };

    //Matrix function
    std::ostream& operator<<(std::ostream& out, const Matrix4x4& m);
    Matrix4x4 Transpose(const Matrix4x4 & m);
    Matrix4x4 Inverse(const Matrix4x4& m);

    class Transform{
    public:
        Transform(const Float[4][4]);
        Transform(const Matrix4x4 _m):m(_m), mInv(Inverse(m)){}
        Transform(const Matrix4x4& m, const Matrix4x4& minv):m(m), mInv(minv){}
        friend Transform Inverse(const Transform& t);
        friend Transform Transpose(const Transform& t);

        bool HasScale() const;
        template<typename T>
        inline Point3<T> operator()(const Point3<T>& p) const;

        template<typename T>
        inline Vector3<T> operator()(const Vector3<T>& v) const;

        template<typename T>
        inline Normal3<T> operator()(const Normal3<T>& n) const;

        inline Ray operator()(const Ray& r) const;

        //template function's definition and declaration must be inside one .h file
        //or leads to linking error!
        template<typename T>
        Bounds3<T> operator()(const Bounds3<T>& b) const;

        SurfaceInteraction operator()(const SurfaceInteraction& si) const;

        Transform operator*(const Transform& t2) const;

        bool SwapsHandedness() const;
    private:
        Matrix4x4 m, mInv;
    };

    //Transform function
    Transform Translate(const Vector3f& delta);
    Transform Scale(Float x, Float y, Float z);
    Transform RotateX(Float theta);
    Transform RotateY(Float theta);
    Transform RotateZ(Float theta);
    Transform Rotate(Float theta, const Vector3f& axis);
    //Change from world coordinate to camera coordinate
    Transform LookAt(const Point3f& pos, const Point3f& look, const Vector3f& up);


    template<typename T>
    Point3<T> Transform::operator()(const Point3<T> &p) const {
        T x = p.x, y = p.y, z = p.z;
        T _x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
        T _y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
        T _z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
        T _w = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
        if (_w == 1) return Point3<T>(_x, _y, _z);
        else return Point3<T>(_x, _y, _z) / _w;
    }

    template<typename T>
    Vector3<T> Transform::operator()(const Vector3<T> &v) const {
        T x = v.x, y = v.y, z = v.z;
        return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                          m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                          m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
    }


    template<typename T>
    Normal3<T> Transform::operator()(const Normal3<T> &n) const {
        Matrix4x4 nm = Transpose(mInv);
        T x = n.x, y = n.y, z = n.z;
        return Normal3<T>(nm.m[0][0] * x + nm.m[0][1] * y + nm.m[0][2] * z,
                          nm.m[1][0] * x + nm.m[1][1] * y + nm.m[1][2] * z,
                          nm.m[2][0] * x + nm.m[2][1] * y + nm.m[2][2] * z);
    }

    //todo
    Ray Transform::operator()(const Ray &r) const {
        return r;
    }

    template<typename T>
    Bounds3<T> Transform::operator()(const Bounds3<T> &b) const {
        constexpr int corners = (1 << 3);
        const Transform &M = *this;
        Point3<T> pMin = M(b.pMin), pMax = M(b.pMax);
        for (size_t i = 0; i < corners; ++i) {
            auto temp_point = M(b.Corner(i));
            pMin = Min(pMin, temp_point);
            pMax = Max(pMax, temp_point);
        }
        return Bounds3f(pMin, pMax);
    }


}
#endif //SIMPLERENDERER_TRANSFORM_H
