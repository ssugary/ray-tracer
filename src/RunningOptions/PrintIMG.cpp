#include "PrintIMG.hpp"

namespace pri{
    void PrintPNG::write_image(size_val width, size_val height,
                                const std::vector<clr::Color> color_buffer, const std::string file){
            std::vector<byte> img; 
            img.reserve(width * height * 4);

            for(auto& color : color_buffer){
                img.push_back(color.r);
                img.push_back(color.g);
                img.push_back(color.b);
                img.push_back(255);
            }

            unsigned error = lodepng::encode(file, img, width, height);

            if(error){std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << "\n";}
            else     {std::cout << "image generated in: " << file << "\n";}

        }

        void PrintPPM::write_image(size_val width, size_val height,
                                   const std::vector<clr::Color> color_buffer, const std::string file){

            std::ofstream os(file);

            os << "P3\n" << width << " " << height << "\n255\n";

            for(auto& color : color_buffer){
                os << (int) color.r << " " << (int) color.g << " " << (int) color.b << "\n";
            }

            os.close();
        }
    }