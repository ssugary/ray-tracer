#include "Color.hpp"



namespace clr{


    Color::Color() : r(0), g(0), b(0) {};
    Color::Color(byte r, byte g, byte b) : r(r), g(g), b(b) {};
        
    Color Color::operator*(float t){return Color(
        static_cast<byte>(r * t),
        static_cast<byte>(g * t), 
        static_cast<byte>(b * t));}
    Color Color::operator+(const Color& c){return Color(r + c.r, g + c.g, b + c.b);}
    
    byte& Color::operator[](const size_t index){
        if(index == 0)return r;
        if(index == 1)return g;
        return b;
    };
    byte Color::operator[](const size_t index) const {
        if(index == 0)return r;
        if(index == 1)return g;
        return b;
    }
}
