//
// Created by 18310 on 2021/3/22.
//

#ifndef SIMPLERENDERER_INTERACTION_H
#define SIMPLERENDERER_INTERACTION_H

#include "sr.h"
#include "geometry.h"
#include "medium.h"
#include "shape.h"


namespace sr {
    class Interaction {
    public:
        Interaction() { }

        Interaction(const Point3f &p, const Normal3f &n, const Vector3f &pError, const Vector3f &wo, Float time,
                    const MediumInterface &mediumInterface) :
                p(p), time(time), pError(pError), wo(wo), n(n), mediumInterface(mediumInterface) {}

        bool IsSurfaceInteraction() const { return n == Normal3f(); }

        Point3f p;
        Float time;
        Vector3f pError;
        Vector3f wo;

        //only when interaction on surface, n store the point's normal
        Normal3f n;
        MediumInterface mediumInterface;
    };

    class SurfaceInteraction : public Interaction {
    public:
        Point2f uv;
        Vector3f dpdu, dpdv;
        Normal3f dndu, dndv;
        const Shape *shape = nullptr;

        SurfaceInteraction(){}
        SurfaceInteraction(const Point3f &p, const Vector3f &pError, const Vector3f &wo, Float time, const Point2f &uv,
                           const Vector3f &dpdu, const Vector3f &dpdv, const Normal3f &dndu, const Normal3f &dndv,
                           const Shape *shape);

        //a relatively small perturbation of the geometric normal structure named shading:
        struct {
            Normal3f n;
            Vector3f dpdu, dpdv;
            Normal3f dndu, dndv;
        } shading;

        void SetShadingGeometry(const Vector3f& dpdus, const Vector3f& dpdvs, const Normal3f& dndus, const Normal3f& dndvs, bool orientationIsAuthoritative);
    };
}
#endif //SIMPLERENDERER_INTERACTION_H
