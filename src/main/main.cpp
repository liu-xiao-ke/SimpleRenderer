#include <iostream>
#include "../core/geometry.h"
#include "../core/transform.h"

using namespace sr;


int main() {
    Float m1[4][4] = {1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1};
    std::cout << Inverse(Matrix4x4(m1));
    return 0;
}
