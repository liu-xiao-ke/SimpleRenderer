//
// Created by 18310 on 2021/3/26.
//

#include "../../include/sphere.h"
namespace sr {

    Bounds3f Sphere::ObjectBound() const {
        Point3f pMin(-radius, -radius, zMin), pMax(radius, radius, zMax);
        if (phiMax <= 3 * Pi / 2) {
            pMin = Point3f(radius * std::cos(phiMax), radius * std::sin(phiMax), zMin);
        }
        return Bounds3f(pMin, pMax);
    }

    bool Sphere::Intersect(const Ray &ray, Float *tHit, SurfaceInteraction *isect, bool testAlphaTexture) const {
        return false;
    }

    Float Sphere::Area() const {
        return 0;
    }


}