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
        Matrix4x4(){}
        Matrix4x4(Float _m[4][4]);
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
        Transform();
        Transform(const Float[4][4]);
        Transform(const Matrix4x4 _m):m(_m), mInv(Inverse(m)){}
        Transform(const Matrix4x4& m, const Matrix4x4& minv):m(m), mInv(minv){}
        friend Transform Inverse(const Transform& t);
        friend Transform Transpose(const Transform& t);
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

}
#endif //SIMPLERENDERER_TRANSFORM_H
