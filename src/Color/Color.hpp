#ifndef COLOR 
#define COLOR

#include <cstdint>
#include <sstream>
#include "ssmath.hpp"

using byte = std::uint8_t;

namespace clr {

    class Color {
        public:
            byte r, g, b;
            Color();
            Color(byte r, byte g, byte b);
            
            Color operator*(float t);
            Color operator+(const Color& c);
            byte& operator[](const size_t index);
            byte operator[](const size_t index) const;
            };

    
}

#endif