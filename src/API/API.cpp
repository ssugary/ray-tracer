#include "API.hpp"

using namespace ro;
using namespace flm;
using namespace bkg;
using namespace clr;

namespace api {

    static RenderOptions renderState; 
    ro::RunningOptions APP::m_current_running_options;
    void APP::film(const ParamSet& paramSet) {
        int x_res = 800;
        int y_res = 600;
        std::string img_type = "ppm";
        std::string filename = "output.ppm";

        if (paramSet.count("x_res")) {
            x_res = paramSet["x_res"].cast<int>();
        }
        if (paramSet.count("y_res")) {
            y_res = paramSet["y_res"].cast<int>();
        }
        if (paramSet.count("filename")) {
            filename = paramSet["filename"].cast<std::string>();
        }
        if (paramSet.count("img_type")){
            img_type = paramSet["img_type"].cast<std::string>();
        }

        if(m_current_running_options.quick_render){
            x_res /= 4;
            y_res /= 4;
        }
        if(m_current_running_options.has_out_file){
            filename = m_current_running_options.out_file;
        }

        renderState.film = std::unique_ptr<Film>(new Film(x_res, y_res, filename));
        renderState.film->img_type = img_type;
        
        std::cout << "[API] Film configurado: " << x_res << "x" << y_res << " -> " << filename << "\n";
    }

    void APP::background(const ParamSet& paramSet) {
        Color tl(0,0,0), tr(0,0,0), bl(0,0,0), br(0,0,0);

        if (paramSet.count("tl")) tl = paramSet["tl"].cast<Color>();
        if (paramSet.count("tr")) tr = paramSet["tr"].cast<Color>();
        if (paramSet.count("bl")) bl = paramSet["bl"].cast<Color>();
        if (paramSet.count("br")) br = paramSet["br"].cast<Color>();

        if (paramSet.count("color")) {
            Color solida = paramSet["color"].cast<Color>();
            tl = tr = bl = br = solida;
        }

        renderState.background = std::unique_ptr<Background>(new Background({bl, tl, tr, br}));
        
        std::cout << "[API] Background configurado.\n";
    }

    void APP::world_begin(const ParamSet& paramSet) {
        std::cout << "[API] A ler objetos do mundo...\n";
    }

    void APP::world_end(const ParamSet& paramSet) {
        std::cout << "[API] Leitura do mundo terminada.\n";
    }

    void APP::render() {
        if (!renderState.film || !renderState.background) {
            std::cerr << "ERRO: O ficheiro XML nao possui as tags <film> ou <background> completas.\n";
            return;
        }

        std::cout << "A iniciar o renderizador...\n";

        // Obter os objetos recém-criados
        Film& film = *(renderState.film);
        Background& background = *(renderState.background);
        

        film.setImgType(); 
        size_val width = film.width;  
        size_val height = film.height; 

        size_val x_start = 0, x_end = width;
        size_val y_start = 0, y_end = height;

        

        if(m_current_running_options.crop_window_provided){
            x_start = m_current_running_options.crop_window[0] * width;
            x_end = m_current_running_options.crop_window[1] * width;
            y_start = m_current_running_options.crop_window[2] * height;
            y_end = m_current_running_options.crop_window[3] * height;
        }

        for (size_val y{y_start}; y < y_end; y++) {
            for (size_val x{x_start}; x < x_end; x++) {
                auto color = background.sampleUV(float(x) / float(width - 1), float(y) / float(height - 1));
                film.draw_pixel(x, y, color);
            }
        }

        film.write_image();
    }

    void APP::init_engine(const ro::RunningOptions &opt){
        m_current_running_options = opt;
        
    }


}