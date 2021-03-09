#include <iostream>
#include "../core/sr.h"
#include "../core/geometry.h"
using namespace sr;


int main() {
    auto v1 = Vector3i(1, 0, 0);
    Vector3i v2, v3;
    CoordinateSystem(v1, &v2, &v3);
    return 0;
}
