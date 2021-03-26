//
// Created by 18310 on 2021/3/9.
//

#include "geometry.h"
namespace sr {
    template<typename T>
    bool Bounds3<T>::IntersectP(const Ray &ray, Float *hitt0, Float *hitt1) const {
        const int Dim = 3; //three planes: x, y, z
        Float t0 = *hitt0, t1 = *hitt1;
        for (unsigned int i = 0; i < Dim; ++i) {
            Float invd = 1.0 / ray.d[i]; //d[i] is zero also ok.
            Float tNear = (pMin[i] - ray.o[i]) * invd; //may be NAN
            Float tFar = (pMax[i] - ray.o[i]) * invd;

            //any condition contains NAN is always false
            if (tNear > tFar) std::swap(tNear, tFar);
            t0 = tNear > t0 ? tNear : t0; //NAN t0 remains unchanged
            t1 = tFar < t1 ? tFar : t1; //NAN t1 remains unchanged
            if (t0 > t1) return false; //leave this condition judgement unchanged
        }
        if (hitt0) *hitt0 = t0;
        if (hitt1) *hitt1 = t1;

        return true;
    }

    //avoid computing the inversion of dir and reduce the comparing times
    //improve 15% performance
    template<typename T>
    bool Bounds3<T>::IntersectP(const Ray &ray, const Vector3f &invDir, const int *dirIsNeg) const {
        const Bounds3f &bounds = *this;

        Float tMin = (bounds[dirIsNeg[0]].x - ray.o.x) * invDir[0];
        Float tMax = (bounds[1 - dirIsNeg[0]].x - ray.o.x) * invDir[0];
        Float tMiny = (bounds[dirIsNeg[0]].y - ray.o.y) * invDir[1];
        Float tMaxy = (bounds[1 - dirIsNeg[0]].y - ray.o.y) * invDir[1];

        if (tMin > tMaxy || tMiny > tMax) return false;
        if (tMiny > tMin) tMin = tMiny;
        if (tMax > tMaxy) tMax = tMaxy;

        Float tMinz = (bounds[dirIsNeg[0]].z - ray.o.z) * invDir[2];
        Float tMaxz = (bounds[1 - dirIsNeg[0]].z - ray.o.z) * invDir[2];

        if (tMin > tMaxz || tMinz > tMax) return false;
        if (tMinz > tMin) tMin = tMinz;
        if (tMaxz < tMax) tMax = tMaxz;

        //[tMin, tMax] has intersection with ray (0, tMax)
        return (tMin < ray.tMax) && tMax > 0;
    }
}