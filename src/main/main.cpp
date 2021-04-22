#include <iostream>
#include "geometry.h"
#include "transform.h"
#include "sphere.h"
#include "spectrum.h"

using namespace sr;


int main() {

    Vector3f v(1, 1, 1);
    std::cout << RotateX(90)(v);
    return 0;
}
