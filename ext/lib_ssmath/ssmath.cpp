#include "ssmath.hpp"

namespace glm {

    mat3::mat3(){mat = {1, 0, 0, 0, 1, 0, 0, 0, 1};};
    mat3::mat3(float e00, float e01, float e02, 
               float e10, float e11, float e12,
               float e20, float e21, float e22){
            mat[0] = e00; mat[1] = e01; mat[2] = e02;
            mat[3] = e10; mat[4] = e11; mat[5] = e12;
            mat[6] = e20; mat[7] = e21; mat[8] = e22;
        }
    mat3::mat3(const mat3 &m2){
        mat = m2.mat;
    }
    mat3::mat3(std::initializer_list<float> list){
        std::copy(list.begin(), list.end(), mat.begin());
    };

    inline const mat3& mat3::operator+() const {return *this;};
    inline mat3 mat3::operator-() const {return mat3(-mat[0], -mat[1], -mat[2],
                                                    -mat[3], -mat[4], -mat[5],
                                                    -mat[6], -mat[7], -mat[8]);};

    inline float& mat3::operator()(size_t row, size_t col){return mat[row * 3 + col];}
    inline float  mat3::operator()(size_t row, size_t col) const {return mat[row * 3 + col];}


    inline mat3 mat3::operator+(const mat3 &m2) const {return mat3(mat[0] + m2.mat[0], mat[1] + m2.mat[1], mat[2] + m2.mat[2],
                                                            mat[3] + m2.mat[3], mat[4] + m2.mat[4], mat[5] + m2.mat[5],
                                                            mat[6] + m2.mat[6], mat[7] + m2.mat[7], mat[8] + m2.mat[8]);};
    inline mat3 mat3::operator-(const mat3 &m2) const {return mat3(mat[0] - m2.mat[0], mat[1] - m2.mat[1], mat[2] - m2.mat[2],
                                                            mat[3] - m2.mat[3], mat[4] - m2.mat[4], mat[5] - m2.mat[5],
                                                            mat[6] - m2.mat[6], mat[7] - m2.mat[7], mat[8] - m2.mat[8]);};
    inline mat3 mat3::operator*(const float t ) const {return mat3(mat[0] * t, mat[1] * t, mat[2] * t,
                                                            mat[3] * t, mat[4] * t, mat[5] * t,
                                                            mat[6] * t, mat[7] * t, mat[8] * t);};
    inline mat3 mat3::operator/(const float t ) const {return mat3(mat[0] / t, mat[1] / t, mat[2] / t,
                                                            mat[3] / t, mat[4] / t, mat[5] / t,
                                                            mat[6] / t, mat[7] / t, mat[8] / t);};

    inline mat3& mat3::operator=(const mat3 &m2){
        for(int i{0}; i < 9; i++){
            mat[i] = m2.mat[i];
        }
        return *this;
    };
    inline mat3& mat3::operator+=(const mat3 &m2){
        for(int i{0}; i < 9; i++){
            mat[i] += m2.mat[i];
        }
        return *this;
    };
    inline mat3& mat3::operator-=(const mat3 &m2){
        for(int i{0}; i < 9; i++){
            mat[i] -= m2.mat[i];
        }
        return *this;
    };
    inline mat3& mat3::operator*=(const float t){
        for(int i{0}; i < 9; i++){
            mat[i] += t;
        }
        return *this;
    };

    // inline vec3<float> mat3::operator*(vec3<float> v3){
    //     return vec3<float>(
    //                      toVecVec3()[0].dot(v3),
    //                      toVecVec3()[1].dot(v3),
    //                      toVecVec3()[2].dot(v3)
    //     );
    // }

    inline mat3& translate(mat3 &m1){
        std::swap(m1.mat[1], m1.mat[3]);
        std::swap(m1.mat[2], m1.mat[6]);
        std::swap(m1.mat[5], m1.mat[7]);
        return m1;
    }

    inline float det(const mat3 &m) {
        return m.mat[0] * (m.mat[4] * m.mat[8] - m.mat[5] * m.mat[7]) -
               m.mat[1] * (m.mat[3] * m.mat[8] - m.mat[5] * m.mat[6]) +
               m.mat[2] * (m.mat[3] * m.mat[7] - m.mat[4] * m.mat[6]);
    }

    // inline vec3<vec3<float>> mat3::toVecVec3(){
    //     return vec3<vec3<float>>(vec3<float>(mat[0], mat[1], mat[2]),
    //                              vec3<float>(mat[3], mat[4], mat[5]),
    //                              vec3<float>(mat[6], mat[7], mat[8]));
    // }

    mat4::mat4(){mat = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};};
    mat4::mat4(float e00, float e01, float e02, float e03,
               float e10, float e11, float e12, float e13,
               float e20, float e21, float e22, float e23,
               float e30, float e31, float e32, float e33){

                mat[0] = e00; mat[1] = e01; mat[2] = e02;mat[3] = e03; 
                mat[4] = e10; mat[5] = e11;mat[6] = e12; mat[7] = e13;
                mat[8] = e20;mat[9] = e21; mat[10] = e22; mat[11] = e23;
                mat[12] = e30; mat[13] = e31; mat[14] = e32;mat[15] = e33;
        }
    mat4::mat4(const mat4 &m2){
        mat = m2.mat;
    }
    mat4::mat4(std::initializer_list<float> list){
        std::copy(list.begin(), list.end(), mat.begin());
    };

    inline const mat4& mat4::operator+() const{return *this;};
    inline mat4 mat4::operator-() const{return mat4(-mat[0], -mat[1], -mat[2],
                                                    -mat[3], -mat[4], -mat[5],
                                                    -mat[6], -mat[7], -mat[8], -mat[9], -mat[10], -mat[11], -mat[12], -mat[13], -mat[14], -mat[15]);};
    inline float& mat4::operator()(size_t row, size_t col){return mat[4 * row + col];};
    inline float mat4::operator()(size_t row, size_t col) const{return mat[4 * row + col];};

    inline mat4 mat4::operator+(const mat4 &m2) const {return mat4(mat[0] + m2.mat[0], mat[1] + m2.mat[1], mat[2] + m2.mat[2],
                                                            mat[3] + m2.mat[3], mat[4] + m2.mat[4], mat[5] + m2.mat[5],
                                                            mat[6] + m2.mat[6], mat[7] + m2.mat[7], mat[8] + m2.mat[8],
                                                            mat[9] + m2.mat[9], mat[10] + m2.mat[10], mat[11] + m2.mat[11], mat[12] + m2.mat[12],
                                                            mat[13]+ m2.mat[13], mat[14] + m2.mat[14], mat[15] + m2.mat[15]);};
    inline mat4 mat4::operator-(const mat4 &m2) const {return mat4(mat[0] - m2.mat[0], mat[1] - m2.mat[1], mat[2] - m2.mat[2],
                                                            mat[3] - m2.mat[3], mat[4] - m2.mat[4], mat[5] - m2.mat[5],
                                                            mat[6] - m2.mat[6], mat[7] - m2.mat[7], mat[8] - m2.mat[8],
                                                            mat[9] - m2.mat[9], mat[10] - m2.mat[10], mat[11] - m2.mat[11], mat[12] - m2.mat[12],
                                                            mat[13]- m2.mat[13], mat[14] - m2.mat[14], mat[15] - m2.mat[15]);};
    inline mat4 mat4::operator*(const float t ) const {return mat4(mat[0] * t, mat[1] * t, mat[2] * t,
                                                            mat[3] * t, mat[4] * t, mat[5] * t,
                                                            mat[6] * t, mat[7] * t, mat[8] * t, mat[9] * t, mat[10] * t,
                                                            mat[11] * t, mat[12] * t, mat[13] * t, mat[14] * t, mat[15] * t);};
    inline mat4 mat4::operator/(const float t ) const{return mat4(mat[0] / t, mat[1] / t, mat[2] / t,
                                                            mat[3] / t, mat[4] / t, mat[5] / t,
                                                            mat[6] / t, mat[7] / t, mat[8] / t, mat[9] / t, mat[10] / t,
                                                            mat[11] / t, mat[12] / t, mat[13] / t, mat[14] / t, mat[15] / t);};


    inline mat4& mat4::operator=(const mat4 &m2){
        for(int i{0}; i < 16; i++){
            mat[i] = m2.mat[i];
        }
        return *this;
    };
    inline mat4& mat4::operator+=(const mat4 &m2){
        for(int i{0}; i < 16; i++){
            mat[i] += m2.mat[i];
        }
        return *this;
    };
    inline mat4& mat4::operator-=(const mat4 &m2){
        for(int i{0}; i < 16; i++){
            mat[i] -= m2.mat[i];
        }
        return *this;
    };
    inline mat4& mat4::operator*=(const float t){
        for(int i{0}; i < 16; i++){
            mat[i] *= t;
        }
        return *this;
    };;
    inline mat4& mat4::operator/=(const float t){
        for(int i{0}; i < 16; i++){
            mat[i] /= t;
        }
        return *this;
    };;
    
};

