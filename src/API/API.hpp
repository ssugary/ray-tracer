#ifndef APP_HPP
#define APP_HPP
#include "ssdatas.hpp"
#include "Background.hpp"
#include "Film.hpp"
#include "RunningOptions.hpp"

#include <memory>
#include <string>
#include <unordered_map>

using ParamSet = sds::HeterogenMap<std::string>;

namespace api{

    struct RenderOptions {

        std::unordered_map<std::string, ParamSet> actors;
        std::unique_ptr<bkg::Background> background;
        std::unique_ptr<flm::Film> film;
    };

    class APP {
        public: 

        static void init_engine(const ro::RunningOptions& opt);
        static void background(const ParamSet& paramSet);
        static void world_begin(const ParamSet& paramSet);
        static void world_end(const ParamSet& paramSet);
        static void film(const ParamSet& paramSet);
        static void render();

        static ro::RunningOptions m_current_running_options;
    };
}

#endif