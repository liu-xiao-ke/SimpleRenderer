//
// Created by 18310 on 2021/3/26.
//

#include "sphere.h"
namespace sr {

    //tighten the bounding box of sphere
    Bounds3f Sphere::ObjectBound() const {
        Point3f pMin, pMax(radius, radius, zMax);
        if(phiMax <= PiOver2){
            pMax.y = radius * std::sin(phiMax);
        } else if(phiMax <= Pi){
            pMin = Point3f(radius * std::cos(phiMax), 0, zMin);
        } else if(phiMax <= 3 * PiOver2){
            pMin = Point3f(-radius, radius * std::sin(phiMax), zMin);
        } else{
            pMin = Point3f(-radius, -radius, zMin);
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