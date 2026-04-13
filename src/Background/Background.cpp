#include "Background.hpp"
#include "Color.hpp"

namespace bkg {

    Background::Background(const std::vector<clr::Color>& arr){
        if(arr.size() == 1){
            corners[bl] = arr[0];
            corners[tl] = arr[0];
            corners[tr] = arr[0];
            corners[br] = arr[0];
        }
        else if(arr.size() == 4){
            corners[bl] = arr[0];
            corners[tl] = arr[1];
            corners[tr] = arr[2];
            corners[br] = arr[3];
        }
    }

    clr::Color Background::lerp(clr::Color A, clr::Color B, float t){
        return A * (1 - t) + B * t;
    }

    clr::Color Background::sampleUV(float u, float v){

        clr::Color Xt = corners[tl] * (1 - u) + corners[tr] * u;
        clr::Color Xb = corners[bl] * (1 - u) + corners[br] * u;
        
        return Xt * (1 - v) + Xb * v;
    }

};