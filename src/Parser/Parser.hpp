#ifndef PARSER_XML
#define PARSER_XML

#include "API.hpp"
#include "tinyxml2.h"
#include "RunningOptions.hpp"
#include "ssdatas.hpp"

#include <functional>
#include <string>
#include <unordered_map>

using ParamSet = sds::HeterogenMap<std::string>;
using namespace tinyxml2;
using ConverterFunction= std::function<bool(const std::string&, const std::string&, ParamSet*)>;

namespace par {

    class Parser{
        private:

        ParamSet paramSet;
        XMLDocument doc;
        


        public:
        ro::RunningOptions opt;
        void readParameters();
    };

};
#endif