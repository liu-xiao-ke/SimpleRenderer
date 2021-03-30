#include <iostream>
#include "geometry.h"
#include "transform.h"
#include "sphere.h"

using namespace sr;


int main() {
    Float f[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    Matrix4x4 m(f);
    Transform trans(m);
    Sphere s(&trans, &trans, false, 1, -1, 1, 270);
    std::cout << s.ObjectBound();
    return 0;
}
