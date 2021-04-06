//
// Created by 18310 on 2021/4/6.
//

#include "spectrum.h"
#include <algorithm>

namespace sr {
    bool SpectrumSamplesSorted(const Float *lambda, const Float *v, int n) {
        for (std::size_t i = 0; i < n - 1; ++i) {
            if (lambda[i + 1] < lambda[i]) {
                return false;
            }
        }
        return true;
    }

    void SortSpectrumSamples(Float *lambda, Float *v, int n) {
        std::vector<std::pair<Float, Float>> arr;
        for (std::size_t i = 0; i < n; ++i) {
            arr.emplace_back(lambda[i], v[i]);
        }
        std::sort(arr.begin(), arr.end());
        for (std::size_t i = 0; i < n; ++i) {
            lambda[i] = arr[i].first;
            v[i] = arr[i].second;
        }
    }

    //get average SDP of lambda's value in [lambdaStart, lambdaEnd]
    //sum and divide
    Float AverageSpectrumSamples(const Float *lambda, const Float *v, int n, Float lambdaStart, Float lambdaEnd) {
        //Deal with out-of-bounds range:
        if (lambdaEnd <= lambda[0]) return lambda[0];
        if (lambdaStart >= lambda[n - 1]) return lambda[n - 1];
        if (n == 1) return v[0];

        Float sum = 0.0;
        //take lambda out-of-bounds as constant value
        if (lambdaStart < lambda[0]) sum += v[0] * (lambda[0] - lambdaStart);
        if (lambdaEnd > lambda[n - 1]) sum += v[n - 1] * (lambdaEnd - lambda[n - 1]);

        int i = 0;
        while (lambdaStart > lambda[i]) i++;

        //interpolate to get the proper val for a w between l[i] and l[i+1]
        auto interp = [lambda, v](Float w, int i){
            return Lerp((w - lambda[i]) / (lambda[i + 1] - lambda[i]), v[i], v[i + 1]);
        };

        for(; i + 1 < n && lambdaEnd >= lambda[i]; ++i){
            Float segLambdaStart = std::max(lambdaStart, lambda[i]);
            Float segLambdaEnd = std::min(lambdaEnd, lambda[i + 1]);
            sum += 0.5 * (interp(segLambdaStart, i) + interp(segLambdaEnd, i)) * (segLambdaEnd - segLambdaStart);
        }
        return sum / (lambdaEnd - lambdaStart);
    }
}