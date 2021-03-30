//
// Created by 18310 on 2021/3/26.
//

#ifndef SIMPLERENDERER_SPHERE_H
#define SIMPLERENDERER_SPHERE_H

#include "shape.h"

namespace sr{
    class Sphere : public Shape {
    public:
        Sphere(const Transform *ObjectToWorld, const Transform *WorldToObject, bool reverseOrientation, Float radius,
               Float zMin, Float zMax, Float phiMax) : Shape(ObjectToWorld, WorldToObject, reverseOrientation),
                                                       radius(radius),
                                                       zMin(Clamp(std::min(zMin, zMax), -radius, radius)),
                                                       zMax(Clamp(std::max(zMin, zMax), -radius, radius)),
                                                       phiMax(Radians(Clamp(phiMax, 0, 360))),
                                                       thetaMin(std::acos(Clamp(zMin / radius, -1, 1))),
                                                       thetaMax(std::acos(Clamp(zMax / radius, -1, 1))) {}
        Bounds3f ObjectBound() const override;

        bool Intersect(const Ray &ray, Float *tHit, SurfaceInteraction *isect, bool testAlphaTexture = true) const override;

        Float Area() const override;

    private:
        const Float radius;
        const Float zMin, zMax;
        const Float thetaMin, thetaMax, phiMax;
    };
}


#endif //SIMPLERENDERER_SPHERE_H
