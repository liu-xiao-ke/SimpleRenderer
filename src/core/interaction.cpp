//
// Created by 18310 on 2021/3/22.
//

#include "interaction.h"

namespace sr {

    SurfaceInteraction::SurfaceInteraction(const Point3f &p, const Vector3f &pError, const Vector3f &wo, Float time,
                                           const Point2f &uv, const Vector3f &dpdu, const Vector3f &dpdv,
                                           const Normal3f &dndu, const Normal3f &dndv, const Shape *shape)
            : Interaction(p, Normal3f(Normalize(Cross(dpdu, dpdv))), pError, wo, time,
                          nullptr), uv(uv), dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv), shape(shape) {
        shading.n = n;
        shading.dpdu = dpdu;
        shading.dpdv = dpdv;
        shading.dndu = dndu;
        shading.dndv = dndv;

        if (shape && (shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
            n = -n;
            shading.n = -shading.n;
        }
    }

    void SurfaceInteraction::SetShadingGeometry(const Vector3f &dpdus, const Vector3f &dpdvs, const Normal3f &dndus,
                                                const Normal3f &dndvs, bool orientationIsAuthoritative) {
        shading.n = Normalize(Normal3f(Cross(dpdus, dpdvs)));
        if (shape && (shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
            shading.n = -shading.n;
        }

        //the shading normal is always at the same hemisphere with surface normal
        //orientationIsAuthoritative is true means the hemisphere is besed on the direction of n
        //false means the hemisphere is based on the direction of shading.n
        if (orientationIsAuthoritative) {
            n = FaceForward(n, shading.n);
        } else {
            shading.n = FaceForward(shading.n, n);
        }

        shading.dpdu = dpdus;
        shading.dpdv = dpdvs;
        shading.dndu = dndus;
        shading.dndv = dndvs;

    }
}
