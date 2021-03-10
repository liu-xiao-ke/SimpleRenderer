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

}

#endif //SIMPLERENDERER_SR_H
