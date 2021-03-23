//
// Created by 18310 on 2021/3/22.
//

#ifndef SIMPLERENDERER_SHAPE_H
#define SIMPLERENDERER_SHAPE_H

#include "transform.h"

namespace sr {
    class Shape {
    public:
        const Transform *ObjectToWorld, *WorldToObject;
        const bool reverseOrientation;
        const bool transformSwapsHandedness;

        Shape(const Transform *ObjectToWorld, const Transform *WorldToObject, bool reverseOrientation) : ObjectToWorld(
                ObjectToWorld), WorldToObject(WorldToObject), reverseOrientation(reverseOrientation),
                                                                                                         transformSwapsHandedness(
                                                                                                                 ObjectToWorld->SwapsHandedness()) {}
        virtual Bounds3f ObjectBound() const = 0;
        Bounds3f WorldBound() const;
    };
}
#endif //SIMPLERENDERER_SHAPE_H
