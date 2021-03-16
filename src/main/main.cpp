#include <iostream>
#include "../core/geometry.h"
#include "../core/transform.h"

using namespace sr;


int main() {
    Float m1[4][4] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    Float m2[4][4] = {1, 2, 3, 4, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    std::cout << Matrix4x4::Mul(Inverse(m2), m2);
    return 0;
}
