#include <iostream>
#include "geometry.h"
#include "transform.h"
#include "sphere.h"
#include "spectrum.h"

using namespace sr;


int main() {

    Spectrum spec(3);
    std::cout << Sqrt(spec) << std::endl;
    std::cout << Pow(spec, 0.5) << std::endl;
    std::cout << Exp(spec) << std::endl;
    std::cout << spec.Clamp(4, 5) << std::endl;
    std::cout << Lerp(0.5, Spectrum(3), Spectrum(5)) << std::endl;
    return 0;
}
