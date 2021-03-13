#include <iostream>
#include "../core/geometry.h"
using namespace sr;


int main() {
    Bounds3i b(Point3i(0, 0, 0), Point3i(2, 2, 2));
    for(auto p : b){
        std::cout << p;
    }
    return 0;
}
