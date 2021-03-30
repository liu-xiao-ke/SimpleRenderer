//
// Created by 18310 on 2021/3/10.
//

#ifndef SIMPLERENDERER_MEDIUM_H
#define SIMPLERENDERER_MEDIUM_H


namespace sr{
    class Medium {

    };

    class MediumInterface{
    public:
        MediumInterface(): outside(nullptr), inside(nullptr){}
        MediumInterface(const Medium* medium): outside(medium), inside(medium){}
        const Medium *outside, *inside;
    };
}


#endif //SIMPLERENDERER_MEDIUM_H
