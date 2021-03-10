#include <iostream>
#include "../core/geometry.h"
using namespace sr;


int main() {
    Ray r(Point3f(0, 0, 0), Vector3f(1, 2, 3));
    std::cout << r(1.7);
    return 0;
}
