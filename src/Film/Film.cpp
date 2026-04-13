#include "Film.hpp"
#include "Color.hpp"
#include "lodepng.h"
#include <fstream>

namespace flm{

    Film::Film() : width(0), height(0){};
    Film::Film(size_val w, size_val h, std::string s) : width(w), height(h), file(s){
        color_buffer.resize(height * width);
    };

    void Film::setImgType(){
        if(img_type == "PNG" || img_type == "png"){
                printImg = std::unique_ptr<pri::PrintImg>(new pri::PrintPNG());
                if(file.find(".png") == std::string::npos)file += ".png";
            }

        if(img_type == "PPM" || img_type == "ppm"){
            printImg = std::unique_ptr<pri::PrintImg>(new pri::PrintPPM());
            if(file.find(".ppm") == std::string::npos)file += ".ppm";
        }
    }
    
    void Film::draw_pixel(size_val x, size_val y, clr::Color& color){
        color_buffer[y * width + x] = color;
    }


    void Film::write_image() const {

        printImg->write_image(width,  height, color_buffer,  file);

    }
}