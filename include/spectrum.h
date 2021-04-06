//
// Created by 18310 on 2021/4/6.
//

#ifndef SIMPLERENDERER_SPECTRUM_H
#define SIMPLERENDERER_SPECTRUM_H

#include "sr.h"

namespace sr {
    template<int nSpectrumSamples>
    class CoefficientSpectrum {
    public:
        CoefficientSpectrum(Float v = 0.0f) {
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] = v;
            }
        }

        bool HasNans() const {
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                if (std::isnan(c[i])) {
                    return true;
                }
            }
            return false;
        }

        CoefficientSpectrum operator-() const {
            assert(!HasNans());
            CoefficientSpectrum &res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res[i] = -c[i];
            }
            return res;
        }

        CoefficientSpectrum &operator+=(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] += cs[i];
            }
            return *this;
        }

        CoefficientSpectrum operator+(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            CoefficientSpectrum &res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res[i] += cs[i];
            }
            return res;
        }

        CoefficientSpectrum &operator-=(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            *this += -cs;
            return *this;
        }

        CoefficientSpectrum operator-(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            return *this += -cs;
        }

        CoefficientSpectrum &operator*=(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] *= cs[i];
            }
            return *this;
        }
        

    protected:
        Float c[nSpectrumSamples];
    };
}
#endif //SIMPLERENDERER_SPECTRUM_H
