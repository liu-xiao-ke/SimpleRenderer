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


namespace sr{

#ifdef SIMPLERENDERER_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif


// class
//geometry.h
template<typename T>
class Vector2;

template<typename T>
class Vector3;

}

#endif //SIMPLERENDERER_SR_H
