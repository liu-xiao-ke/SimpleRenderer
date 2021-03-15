//
// Created by 18310 on 2021/3/9.
//

#ifndef SIMPLERENDERER_SR_H
#define SIMPLERENDERER_SR_H

//C++ interior library
#include <cassert>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>

namespace sr {

#ifdef SIMPLERENDERER_FLOAT_AS_DOUBLE
    typedef double Float;
#else
    typedef float Float;
#endif

//Global Constants
    static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
    static constexpr Float Infinity = std::numeric_limits<Float>::infinity();


// class
    template<typename T>
    class Vector2;

    template<typename T>
    class Vector3;

    template<typename T>
    class Point2;

    template<typename T>
    class Point3;

    template<typename T>
    class Normal3;

    class Ray;

    class Medium;

    template<typename T>
    class Bounds2;

    template<typename T>
    class Bounds3;

    class Bounds2iIterator;

    class Matrix4x4;
    //functions
    //Lerp of two values
    inline Float Lerp(Float t, Float v1, Float v2) { return (1 - t) * v1 + v2; }

    //solve quadratic equation: at²+bt+c=0
    inline bool Quadratic(Float a, Float b, Float c, Float *t0, Float *t1){
        double discrim = (double) b * b - 4 * (double)a * (double) c;
        if(discrim < 0) return false;
        double rootDiscrim = std::sqrt(discrim);
        double q;

        //a more precision for solving equation
        //avoid cancellation error
        //x1 = q / a, x2 = c / q;
        if(b < 0) q = -0.5 * (b - rootDiscrim);
        else q = -0.5 * (b + rootDiscrim);
        *t0 = q / a;
        *t1 = c / q;
        if(*t0 > *t1) std::swap(*t0, *t1);
        return true;
    }

}

#endif //SIMPLERENDERER_SR_H
