#ifndef RUNNING_OPTIONS
#define RUNNING_OPTIONS

#include "Film.hpp"
#include "ssdatas.hpp"


namespace ro {

     struct RunningOptions {
        std::array<float, 4> crop_window{0, 1, 0, 1};
        std::string out_file{""}, in_file{""};
        bool quick_render{false};
        bool crop_window_provided{false};
        bool has_out_file{false};

        void run_options(int argc, char* argv[]);
        void validade_cropwindow(std::array<float, 4> arr);

    };
};
#endif