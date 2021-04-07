//
// Created by 18310 on 2021/4/6.
//

#ifndef SIMPLERENDERER_SPECTRUM_H
#define SIMPLERENDERER_SPECTRUM_H

#include "sr.h"
#include <vector>

namespace sr {

    //Spectrum utility declarations:
    //Wavelength lambda from 400 to 700 is the range where human visual system is most sensitive
    static const int sampledLambdaStart = 400;
    static const int sampledLambdaEnd = 700;
    static const int nSpectralSamples = 60;

    //CIE standard: samples from 360nm to 830nm, 1nm as interval.
    static const int nCIESamples = 471;
    extern const Float CIE_X[nCIESamples];
    extern const Float CIE_Y[nCIESamples];
    extern const Float CIE_Z[nCIESamples];
    extern const Float CIE_lambda[nCIESamples];
    static const Float CIE_Y_integral = 106.856895;

    extern bool SpectrumSamplesSorted(const Float *lambda, const Float *v, int n);

    extern void SortSpectrumSamples(Float *lambda, Float *v, int n);

    extern Float AverageSpectrumSamples(const Float *lambda, const Float *v, int n, Float lambdaStart, Float lambdaEnd);


    //samples' wavelengths and lambda
    static const int nRGB2SpectSamples = 32;
    extern const Float RGB2SpectLambda[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectWhite[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectCyan[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectMagenta[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectYellow[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectRed[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectGreen[nRGB2SpectSamples];
    extern const Float RGBRefl2SpectBlue[nRGB2SpectSamples];


    //D65 spectral power distribution
    extern const Float RGBIllum2SpectWhite[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectCyan[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectMagenta[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectYellow[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectRed[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectGreen[nRGB2SpectSamples];
    extern const Float RGBIllum2SpectBlue[nRGB2SpectSamples];


    enum class SpectrumType {
        Reflectance, Illuminant
    };

    inline void XYZToRGB(const Float xyz[3], Float rgb[3]) {
        rgb[0] = 3.240479f * xyz[0] - 1.537150f * xyz[1] - 0.498535f * xyz[2];
        rgb[1] = -0.969256f * xyz[0] + 1.875991f * xyz[1] + 0.041556f * xyz[2];
        rgb[2] = 0.055648f * xyz[0] - 0.204043f * xyz[1] + 1.057311f * xyz[2];
    }

    inline void RGBToXYZ(const Float rgb[3], Float xyz[3]) {
        xyz[0] = 0.412453f * rgb[0] + 0.357580f * rgb[1] + 0.180423f * rgb[2];
        xyz[1] = 0.212671f * rgb[0] + 0.715160f * rgb[1] + 0.072169f * rgb[2];
        xyz[2] = 0.019334f * rgb[0] + 0.119193f * rgb[1] + 0.950227f * rgb[2];
    }

    template<int nSpectrumSamples>
    class CoefficientSpectrum {
        template<int n>
        friend inline CoefficientSpectrum<n> Sqrt(const CoefficientSpectrum<n> &cs);

        template<int n>
        friend inline CoefficientSpectrum<n> Exp(const CoefficientSpectrum<n> &cs);

        template<int n>
        friend inline CoefficientSpectrum<n> Pow(CoefficientSpectrum<n> &cs, Float e);

    public:

        static const int nSamples = nSpectrumSamples;

        CoefficientSpectrum(Float v = 0.0f) {
            assert(!std::isnan(v));
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] = v;
            }
        }

        CoefficientSpectrum(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] = cs[i];
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
//        //Cannot give value to c[i] directly, only the friend function can do this;
//        Float &operator[](int i) {
//            assert(i >= 0 && i < nSpectrumSamples);
//            return c[i];
//        }

        Float operator[](int i) const {
            assert(i >= 0 && i < nSpectrumSamples);
            return c[i];
        }

        CoefficientSpectrum operator-() const {
            CoefficientSpectrum res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res.c[i] = -c[i];
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
            CoefficientSpectrum res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res.c[i] += cs[i];
            }
            return res;
        }

        CoefficientSpectrum &operator-=(const CoefficientSpectrum &cs) {
            assert(!cs.HasNans());
            *this += -cs;
            return *this;
        }

        CoefficientSpectrum operator-(const CoefficientSpectrum &cs) const {
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

        CoefficientSpectrum operator*(const CoefficientSpectrum &cs) const {
            assert(!cs.HasNans());
            CoefficientSpectrum res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res[i] = c[i] * cs[i];
            }
            return res;
        }

        CoefficientSpectrum &operator*=(Float t) {
            assert(!std::isnan(t));
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                c[i] *= t;
            }
            return *this;
        }

        CoefficientSpectrum operator*(Float t) const {
            assert(!std::isnan(t));
            CoefficientSpectrum res = *this;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res.c[i] = c[i] * t;
            }
            return res;
        }

        friend CoefficientSpectrum operator*(Float t, const CoefficientSpectrum &cs) {
            assert(!std::isnan(t) && !cs.HasNans());
            return cs * t;
        }

        CoefficientSpectrum &operator/=(Float t) {
            assert(!std::isnan(t) && t != 0);
            Float invt = 1.0f / t;
            *this *= invt;
            return *this;
        }

        CoefficientSpectrum operator/(Float t) const {
            assert(!std::isnan(t) && t != 0);
            Float invt = 1.0f / t;
            return *this * invt;
        }

        bool operator==(const CoefficientSpectrum &cs) const {
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                if (c[i] != cs[i]) return false;
            }
            return true;
        }

        bool operator!=(const CoefficientSpectrum &cs) const {
            return !(*this == cs);
        }

        friend std::ostream &operator<<(std::ostream &os, const CoefficientSpectrum &cs) {
            os << "[";
            for (size_t i = 0; i < nSpectrumSamples; ++i) {
                os << cs[i];
                if (i < nSpectrumSamples - 1) os << ",";
                else os << "]";
            }
            return os;
        }

        bool IsBlack() const {
            for (size_t i = 0; i < nSpectrumSamples; ++i) {
                if (c[i] != 0.0f) return false;
            }
            return true;
        }

        CoefficientSpectrum Clamp(Float low = 0, Float high = Infinity) const {
            CoefficientSpectrum res;
            for (std::size_t i = 0; i < nSpectrumSamples; ++i) {
                res.c[i] = sr::Clamp(c[i], low, high);
            }
            return res;
        }

    protected:
        Float c[nSpectrumSamples];
    };

    //CoefficientSpectrum function declaration

    template<int n>
    inline CoefficientSpectrum<n> Sqrt(const CoefficientSpectrum<n> &cs) {
        CoefficientSpectrum<n> res;
        for (std::size_t i = 0; i < n; ++i) {
            res.c[i] = std::sqrt(cs[i]);
        }
        assert(!res.HasNans());
        return res;
    }

    template<int n>
    inline CoefficientSpectrum<n> Exp(const CoefficientSpectrum<n> &cs) {
        CoefficientSpectrum<n> res;
        for (std::size_t i = 0; i < n; ++i) {
            res.c[i] = std::exp(cs[i]);
        }
        assert(!res.HasNans());
        return res;
    }

    template<int n>
    inline CoefficientSpectrum<n> Pow(CoefficientSpectrum<n> &cs, Float e) {
        CoefficientSpectrum<n> res;
        for (std::size_t i = 0; i < n; ++i) {
            res.c[i] = std::pow(cs[i], e);
        }
        assert(!res.HasNans());
        return res;
    }

    template<int n>
    inline CoefficientSpectrum<n> Lerp(Float t, const CoefficientSpectrum<n> &cs1, const CoefficientSpectrum<n> &cs2) {
        return (1 - t) * cs1 + t * cs2;
    }


    //SampledSpectrum declaration
    class SampledSpectrum : public CoefficientSpectrum<nSpectralSamples> {
    public:
        SampledSpectrum(Float v = 0.f) : CoefficientSpectrum<nSpectralSamples>(v) {}
        SampledSpectrum(const CoefficientSpectrum<nSpectralSamples>& v): CoefficientSpectrum<nSpectralSamples>(v){}
        static SampledSpectrum FromSampled(const Float *lambda, const Float *v, int n) {
            //Sort samples if unordered, use sorted for returnd Spectrum
            if (!SpectrumSamplesSorted(lambda, v, n)) {
                std::vector<Float> tlambda(&lambda[0], &lambda[n]);
                std::vector<Float> tv(&v[0], &v[n]);
                SortSpectrumSamples(&tlambda[0], &tv[0], n);
                return FromSampled(&tlambda[0], &tv[0], n);
            }
            SampledSpectrum r;
            for (std::size_t i = 0; i < nSpectralSamples; ++i) {
                //compute the average value of given SPD over ith sample's range
                Float lambda0 = Lerp(Float(i) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
                Float lambda1 = Lerp(Float(i + 1) / Float(nSpectralSamples), sampledLambdaStart, sampledLambdaEnd);
                r.c[i] = AverageSpectrumSamples(lambda, v, n, lambda0, lambda1);
            }
            return r;
        }

        static void Init();

        void ToXYZ(Float xyz[3]) const {
            xyz[0] = xyz[1] = xyz[2] = 0.0f;
            for (std::size_t i = 0; i < nSpectralSamples; ++i) {
                xyz[0] += X.c[i] * c[i];
                xyz[1] += Y.c[i] * c[i];
                xyz[2] += Z.c[i] * c[i];
            }
            Float scale = Float(sampledLambdaEnd - sampledLambdaStart) / Float(nSpectralSamples) / CIE_Y_integral;
            xyz[0] *= scale;
            xyz[1] *= scale;
            xyz[2] *= scale;
        }

        //y coefficient is closly related to luminance, which measures the perceived brightness of a color
        Float y() const {
            Float _y = 0.f;
            for (std::size_t i = 0; i < nSpectralSamples; ++i) {
                _y += Y.c[i] * c[i];
            }
            return _y * Float(sampledLambdaEnd - sampledLambdaStart) / Float(nSpectralSamples) / CIE_Y_integral;
        }

        void ToRGB(Float rgb[3]) const {
            Float xyz[3];
            ToXYZ(xyz);
            XYZToRGB(xyz, rgb);
        }
        SampledSpectrum FromRGB(const Float rgb[3], SpectrumType type);

        RGBSpectrum ToRGBSpectrum() const;

    private:
        static SampledSpectrum X, Y, Z;
        static SampledSpectrum rgbRefl2SpectWhite, rgbRefl2SpectCyan, rgbRefl2SpectMagenta, rgbRefl2SpectYellow;
        static SampledSpectrum rgbRefl2SpectRed, rgbRefl2SpectGreen, rgbRefl2SpectBlue;

        static SampledSpectrum rbgIllum2SpectWhite, rgbIllum2SpectCyan, rgbIllum2SpectMagenta, rgbIllum2SpectYellow;
        static SampledSpectrum rgbIllum2SpectRed, rgbIllum2SpectGreen, rgbIllum2SpectBlue;
    };

    //RGBSpectrum declaration
    class RGBSpectrum : public CoefficientSpectrum<3> {
    public:
        RGBSpectrum(Float v = 0.0f) : CoefficientSpectrum<3>(v) {}

        RGBSpectrum(CoefficientSpectrum<3> &v) : CoefficientSpectrum<3>(v) {}

        static RGBSpectrum FromRGB(const Float rgb[3]) {
            RGBSpectrum s;
            s.c[0] = rgb[0];
            s.c[1] = rgb[1];
            s.c[2] = rgb[2];
            return s;
        }

        void ToRGB(Float *rgb) const {
            rgb[0] = c[0];
            rgb[1] = c[1];
            rgb[2] = c[2];
        }

        const RGBSpectrum &ToRGBSpectrum() const {
            return *this;
        }
    };

}
#endif //SIMPLERENDERER_SPECTRUM_H
