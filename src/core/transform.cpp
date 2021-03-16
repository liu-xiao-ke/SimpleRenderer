//
// Created by 18310 on 2021/3/14.
//
#include "transform.h"

namespace sr{
    Matrix4x4::Matrix4x4(Float _m[4][4]) {
        std::memcpy(m, _m, 4 * 4 * sizeof(Float));
    }

    Matrix4x4::Matrix4x4(Float t00, Float t01, Float t02, Float t03, Float t10, Float t11, Float t12, Float t13,
                         Float t20, Float t21, Float t22, Float t23, Float t30, Float t31, Float t32, Float t33) {
        m[0][0] = t00;
        m[0][1] = t01;
        m[0][2] = t02;
        m[0][3] = t03;
        m[1][0] = t10;
        m[1][1] = t11;
        m[1][2] = t12;
        m[1][3] = t13;
        m[2][0] = t20;
        m[2][1] = t21;
        m[2][2] = t22;
        m[2][3] = t23;
        m[3][0] = t30;
        m[3][1] = t31;
        m[3][2] = t32;
        m[3][3] = t33;
    }

    Matrix4x4 Matrix4x4::Mul(const Matrix4x4 &m1, const Matrix4x4 &m2) {
        Matrix4x4 res;
        for (std::size_t i = 0; i < 4; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                for (std::size_t k = 0; k < 4; ++k) {
                    res.m[i][j] += m1.m[i][k] * m2.m[k][j];
                }
            }
        }
        return res;
    }

    bool Matrix4x4::operator==(const Matrix4x4 &m2) const {
        for(std::size_t i = 0; i < 4; ++i){
            for(std::size_t j = 0; j < 4; ++j){
                if(m[i][j] != m2.m[i][j]) return false;
            }
        }
        return true;
    }

    bool Matrix4x4::operator!=(const Matrix4x4 &m2) const {
        for(std::size_t i = 0; i < 4; ++i){
            for(std::size_t j = 0; j < 4; ++j){
                if(m[i][j] != m2.m[i][j]) return true;
            }
        }
        return false;
    }

    std::ostream & operator<<(std::ostream& out, const Matrix4x4& m){
        out << "[ " << m.m[0][0] << " " << m.m[0][1] << " " << m.m[0][2] << " " << m.m[0][3] << " ]\n" <<
               "[ " << m.m[1][0] << " " << m.m[1][1] << " " << m.m[1][2] << " " << m.m[1][3] << " ]\n" <<
               "[ " << m.m[2][0] << " " << m.m[2][1] << " " << m.m[2][2] << " " << m.m[2][3] << " ]\n" <<
               "[ " << m.m[3][0] << " " << m.m[3][1] << " " << m.m[3][2] << " " << m.m[3][3] << " ]\n";
        return out;
    }

    Matrix4x4 Transpose(const Matrix4x4 &m) {
        return Matrix4x4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0],
                         m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1],
                         m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
                         m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]);
    }

    Matrix4x4 Inverse(const Matrix4x4 &m) {
        int indxc[4], indxr[4];
        int ipiv[4] = {0, 0, 0, 0};
        Float minv[4][4];
        std::memcpy(minv, m.m, 4 * 4 * sizeof(Float));
        for(int i = 0; i < 4; ++i){
            int row = 0, col = 0;
            Float biggest = 0.f;
            for(int j = 0; j < 4; ++j){
                if(ipiv[j] != 1){
                    for(int k = 0; k < 4; ++k){
                        if (ipiv[k] == 0){
                            if(minv[j][k] >= biggest){
                                biggest = minv[j][k];
                                row = j;
                                col = k;
                            }
                        }
                        else if (ipiv[k] > 1){
                            //singular matrix error
                        }
                    }
                }
            }
            ipiv[col]++;
            indxr[i] = row;
            indxc[i] = col;
            if(row != col){
                for(int k = 0; k < 4; ++k) std::swap(minv[row][k], minv[col][k]);
            }
            if (minv[col][col] == 0.f){
                //singular matrix error
            }
            Float piv_ratio = 1.0f / minv[col][col];
            minv[col][col] = 1;
            for(int k = 0; k < 4; ++k){
                minv[col][k] *= piv_ratio;
            }
            for(int j = 0; j < 4; ++j){
                if(j == col) continue;
                Float save = minv[j][col];
                minv[j][col] = 0;
                for(int k = 0; k < 4; ++k){
                    minv[j][k] -= minv[col][k] * save;
                }
            }
        }
        for(int j = 3; j >= 0; --j){
            if (indxr[j] == indxc[j]) continue;
            for(int k = 0; k < 4; ++k){
                std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
            }
        }
        return Matrix4x4(minv);
    }

    Transform::Transform(const Float _m[4][4]) {
        std::memcpy(m.m, _m, 4 * 4 * sizeof(Float));
    }

    Transform Transpose(const Transform &t) {

    }

    Transform Inverse(const Transform &t) {

    }
}
