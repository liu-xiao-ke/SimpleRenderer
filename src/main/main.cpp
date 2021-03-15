#include <iostream>
#include "../core/geometry.h"
#include "../core/transform.h"

using namespace sr;


int main() {
    Matrix4x4 m1(1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    std::cout << Transpose(m1);
    return 0;
}
