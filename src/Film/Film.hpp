#ifndef FILM
#define FILM

#include "Color.hpp"
#include "PrintIMG.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using byte = std::uint8_t;
using size_val = std::uint16_t;

namespace flm {

    class Film {
        public:
            std::unique_ptr<pri::PrintImg> printImg;
        
            size_val width, height;
            std::string file, img_type;
            std::vector<clr::Color> color_buffer;

            Film();
            Film(size_val w, size_val h, std::string s);
            void setImgType();
            void draw_pixel(size_val x, size_val y, clr::Color& color);
            void write_image() const;


    };

};

#endif