#ifndef SSUGARY_GLM
#define SSUGARY_GLM

#include <array>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <istream>


namespace glm {
    template<typename T>
    class vec3 {    //ideia pega de Ray Tracing in One Weekend by Peter Shirley.
        public:
    vec3(){};
    vec3(T e0, T e1, T e2){e[0] = e0; e[1] = e1; e[2] = e2;};
    inline T x() const {return e[0];};
    inline T y() const {return e[1];};
    inline T z() const {return e[2];};
    inline T r() const {return e[0];};
    inline T g() const {return e[1];};
    inline T b() const {return e[2];};

    inline const vec3<T>& operator+() const {return *this;};
    inline vec3<T> operator-() const {return vec3(-e[0], -e[1], -e[2]);};
    inline T operator[](size_t index) const {return e[index];};
    inline T& operator[](size_t index){return e[index];};

    inline vec3<T> operator+(const vec3<T> &v2){return vec3<T>(v2.e[0] + e[0], v2.e[1] + e[1], v2.e[2] + e[2]);};
    inline vec3<T> operator-(const vec3<T> &v2){return vec3<T>(e[0] - v2.e[0], e[1] - v2.e[1], e[2] - v2.e[2]);};
    inline vec3<T> operator*(const vec3<T> &v2){return vec3<T>(e[0] * v2.e[0], e[1] * v2.e[1], e[2] * v2.e[2]);};
    inline vec3<T> operator/(const vec3<T> &v2){return vec3<T>(e[0] / v2.e[0], e[1] / v2.e[1], e[2] / v2.e[2]);};
    inline vec3<T> operator*(const float t){return vec3<T>(e[0] * t, e[1] * t, e[2] * t);};
    inline vec3<T> operator/(const float t){return vec3<T>(t/e[0], t/e[1], t/e[2]);};

    float dot(vec3<T> v2){
        return e[0] * v2.e[0] + e[1] * v2.e[1] + e[2] * v2.e[2];
    }
    
    inline vec3<T>& operator=(const vec3<T> &v2){
        e[0] = v2.e[0];
        e[1] = v2.e[1];
        e[2] = v2.e[2];
        return *this;
    }
    inline vec3<T>& operator+=(const vec3<T> &v2){
        e[0] += v2.e[0];
        e[1] += v2.e[1];
        e[2] += v2.e[2];
        return *this;
    };
    inline vec3<T>& operator-=(const vec3<T> &v2){
        e[0] -= v2.e[0];
        e[1] -= v2.e[1];
        e[2] -= v2.e[2];
        return *this;
    };
    inline vec3<T>& operator*=(const vec3<T> &v2){
        e[0] *= v2.e[0];
        e[1] *= v2.e[1];
        e[2] *= v2.e[2];
        return *this;
    };
    inline vec3<T>& operator/=(const vec3<T> &v2){
        e[0] /= v2.e[0];
        e[1] /= v2.e[1];
        e[2] /= v2.e[2];
        return *this;
    };
    inline vec3<T>& operator*=(const float t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    };
    inline vec3<T>& operator/=(const float t){
        e[0] /= t;
        e[1] /= t;
        e[2] /= t;
        return *this;
    };
    inline float length() const {return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);};
    inline float sqr_lenght() const {return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];};
    inline void mk_unit_vec(){
        float k = 1.0 / this->length();
        e[0] *= k; e[1] *= k; e[2] *= k;
    }

    inline vec3<T> unit_vec(vec3<T> v){return v / v.length();};
    
            float e[3];
    };
    template<typename T>
    inline std::istream& operator>>(std::istream &is, vec3<T> &v){
        is >> v.e[0] >> v.e[1] >> v.e[2];
        return is;
    }
    template<typename T>
    inline std::ostream& operator<<(std::ostream &os, vec3<T> &v){
        os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        return os;
    }
    template<typename T>
    inline vec3<T> cross(vec3<T> &v1, vec3<T> &v2){
        return vec3<T>(
            v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            -(v1.e[0]*v2.e[2] - v1.e[2] * v2.e[0]),
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0] 
        );
    }


    class mat3 {
        public:
            std::array<float, 9> mat;
            mat3();
            mat3(float e00, float e01, float e02, 
                 float e10, float e11, float e12,
                 float e20, float e21, float e22);
            mat3(const mat3 &m2);
            mat3(std::initializer_list<float> list);

            // inline vec3<vec3<float>> toVecVec3();

            inline const mat3& operator+() const;
            inline mat3 operator-() const;
            inline float& operator()(size_t row, size_t col);
            inline float operator()(size_t row, size_t col) const;
        
            inline mat3 operator+(const mat3 &m2) const;
            inline mat3 operator-(const mat3 &m2) const;
            inline mat3 operator*(const float t) const;
            inline mat3 operator/(const float t) const;

            inline mat3& operator=(const mat3 &m2);
            inline mat3& operator+=(const mat3 &m2);
            inline mat3& operator-=(const mat3 &m2);
            inline mat3& operator*=(const float t);
            inline mat3& operator/=(const float t);

            inline vec3<float> operator*(const vec3<float> v3);
            
    };

    class mat4 {
        public:
            std::array<float, 16> mat;
            mat4();
            mat4(float e00, float e01, float e02, float e03,
                 float e10, float e11, float e12, float e13,
                 float e20, float e21, float e22, float e23,
                 float e30, float e31, float e32, float e33);
            mat4(const mat4 &m2);
            mat4(std::initializer_list<float> list);

            inline const mat4& operator+() const;
            inline mat4 operator-() const;
            inline float& operator()(size_t row, size_t col);
            inline float operator()(size_t row, size_t col) const;
        
            inline mat4 operator+(const mat4 &m2) const;
            inline mat4 operator-(const mat4 &m2) const;
            inline mat4 operator*(const float t) const;
            inline mat4 operator/(const float t) const;

            inline mat4& operator=(const mat4 &m2);
            inline mat4& operator+=(const mat4 &m2);
            inline mat4& operator-=(const mat4 &m2);
            inline mat4& operator*=(const float t);
            inline mat4& operator/=(const float t);
            
    };

};

#endif