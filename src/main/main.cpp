#include <iostream>
#include "../core/geometry.h"
using namespace sr;


int main() {
    Bounds3f b(Point3f(0, 0, 0), Point3f(3, 4, 5));

    std::cout << b.MaximumExtent();
    return 0;
}
