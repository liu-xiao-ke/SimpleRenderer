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
    //PIs:
    static constexpr Float Pi = 3.14159265358979323846;
    static constexpr Float InvPi = 0.31830988618379067154;
    static constexpr Float Inv2Pi = 0.15915494309189533577;
    static constexpr Float Inv4Pi = 0.07957747154594766788;
    static constexpr Float PiOver2 = 1.57079632679489661923;
    static constexpr Float PiOver4 = 0.78539816339744830961;
    static constexpr Float Sqrt2 = 1.41421356237309504880;

    static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
    static constexpr Float MinFloat = std::numeric_limits<Float>::min();
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

    class MediumInterface;

    template<typename T>
    class Bounds2;

    template<typename T>
    class Bounds3;

    class Bounds2iIterator;

    class Matrix4x4;

    class Transform;

    class Interaction;

    class SurfaceInteraction;

    class Shape;

    template<int nSpectrumSamples>
    class CoefficientSpectrum;

    class RGBSpectrum;



    typedef RGBSpectrum Spectrum;

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

    //degree2radians
    inline Float Radians(Float degree) { return (degree / 180) * Pi; }
    //radians2degree
    inline Float Degrees(Float radian){ return radian * InvPi * 180; }

    //clamp between low and high
    template<typename T, typename U, typename V>
    inline T Clamp(T val, U lo, V hi){
        return val < lo ? lo : (val > hi ? hi : val);
    }

}

#endif //SIMPLERENDERER_SR_H
