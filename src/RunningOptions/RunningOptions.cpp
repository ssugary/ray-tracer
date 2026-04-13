#include "RunningOptions.hpp"
#include "ssdatas.hpp"
#include <algorithm>
#include <cctype>
#include <functional>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unordered_map>

using namespace pri;


namespace ro {
    enum CMArg {
            help=0,
            cropwindow,
            quick,
            outfile,
            filename
        };
    namespace {
            std::unordered_map<std::string, CMArg> m {
                {"--help", help}, {"-h", help},
                {"--cropwindow", cropwindow}, {"-crop", cropwindow},
                {"--quick", quick}, {"-q", quick},
                {"--outfile",outfile}, {"-o", outfile}
            };
            
      };

      void usage(std::string msg = "") {
        if (!msg.empty()) {
            std::cout <<">>> Error: " << msg << "\n\n";
        }

        std::cout
            << "Usage: gcrt [<options>] <input_scene_file>\n"
            << "  Rendering simulation options:\n"
            << "    --help                     Print this help text.\n"
            << "    --verbose or -v            Run in verbose mode.\n"
            << "    --cropwindow x0 x1 y0 y1   Specify an image crop window; values must be between 0 and "
            "1.\n"
            << "    --quick                    Reduces quality parameters to render image quickly.\n"
            << "    --outfile <filename>       Write the rendered image to <filename>.\n\n";
        exit(msg.empty() ? 1 : 0);

        }

    bool file_exists(const std::string& path) {
        struct stat buffer;   
        return (::stat(path.c_str(), &buffer) == 0); 
    }

    std::string toLowerCase(std::string s){
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    void RunningOptions::run_options(int argc, char* argv[]){

        if(argc == 1){
            usage();
        }
    
        std::ostringstream oss;
        bool has_scene_file = false;

        for(int i{1}; i < argc; i++){
            std::string option{toLowerCase(argv[i])};
            if(m.count(option)){
                switch(m[option]){
                    case help:
                        usage();
                    break;

                    case cropwindow:{
                        if(i + 4 >= argc){
                            usage("expected at least 4 values after --cropwindow argument.");
                        }
                        std::array<float, 4> temp{std::stof(argv[++i]), std::stof(argv[++i]), std::stof(argv[++i]), std::stof(argv[++i])};
                        validade_cropwindow(temp);
                    break;}
                    case quick:
                        quick_render = true;
                    break; 

                    case outfile:
                        if(i + 1 >= argc)usage("missing filename after --outfile argument.");
                        out_file = argv[++i];
                        has_out_file = true;
                    break;
                    default:
                    break;
                }
            }
            else{
                if(!file_exists(argv[i]))usage("scene file provided does not exist.");
                in_file = option;
                has_scene_file = true;
            }
        }
        if(!has_scene_file){
            usage("missing scene file, cannot proceed.");
        }
    }

    void RunningOptions::validade_cropwindow(std::array<float, 4> arr){
        try {
    unsigned short idx{ 0 };
    for (const auto& value : arr) {
      crop_window[idx++] = value;
    }
  } catch (const std::invalid_argument& e) {
    usage("could not convert --cropwindow's arguments into real number.");
  } catch (const std::out_of_range& e) {
    usage("at least one of the --cropwindow values are out of range.");
  }
  float& x0{ crop_window[0] };
  float& x1{ crop_window[1] };
  float& y0{ crop_window[2] };
  float& y1{ crop_window[3] };
  // Check whether the values are in the expected range (in [0,1])...
  if (x0 < 0.F or x0 > 1.F or x1 < 0.F or x1 > 1.F or y0 < 0.F or y0 > 1.F or y1 < 0.F
      or y1 > 1.F) {
    usage("at least one of the --cropwindow values are out of range.");
  }
  // ... and if they obey x0<x1 and y0<y1.
  if (x0 > x1 or y0 > y1) {
    usage("the --cropwindow values doest not comply with x0<x1 and y0<y1.");
  }
  // Finally, turn on flag to indicate we got a crop window via CLI.
    crop_window_provided = true;

    }
};
        

