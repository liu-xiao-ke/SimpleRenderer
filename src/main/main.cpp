#include <iostream>
#include "../core/geometry.h"
using namespace sr;


int main() {
    auto o = Point3i(0, 0, 0);
    auto p = Point3f(3, 0, 4);
    std::cout << Distance(Point3f(o), p);
    return 0;
}
