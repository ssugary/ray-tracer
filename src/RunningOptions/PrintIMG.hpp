#ifndef PRINT_IMAGE
#define PRINT_IMAGE

#include "Color.hpp"
#include "lodepng.h"


#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using byte = std::uint8_t;
using size_val = std::uint16_t;

namespace pri{
    class PrintImg {
            public:
            virtual ~PrintImg() = default;
            virtual void write_image(size_val width, size_val height,const std::vector<clr::Color> color_buffer,const std::string file) = 0;
        };

        class PrintPNG : public PrintImg {
            public:
            PrintPNG(){};
            void write_image(size_val width, size_val height,const std::vector<clr::Color> color_buffer,const std::string file);
        };

        class PrintPPM : public PrintImg {
            public:
            PrintPPM(){};
            void write_image(size_val width, size_val height,const std::vector<clr::Color> color_buffer,const std::string file);
        };
    
    }

#endif