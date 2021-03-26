//
// Created by 18310 on 2021/3/23.
//
#include "shape.h"
#include "interaction.h"

namespace sr{

    Bounds3f Shape::WorldBound() const {
        const Transform& M = *ObjectToWorld;
        return M(ObjectBound());
    }

    bool Shape::IntersectP(const Ray &ray, bool testAlphaTexture) {
        Float tMax = ray.tMax;
        SurfaceInteraction isect;
        return Intersect(ray, &tMax, &isect, testAlphaTexture);
    }
}
