//
// Created by 18310 on 2021/3/23.
//
#include "shape.h"


namespace sr{
    Bounds3f Shape::WorldBound() const {
        return (*ObjectToWorld)(ObjectBound());
    }
}
