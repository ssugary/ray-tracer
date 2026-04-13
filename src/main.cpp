#include "API.hpp"
#include "Parser.hpp"
#include <exception>

using namespace std;
using namespace flm;
using namespace bkg;
using namespace clr;
using namespace pri;
using namespace ro;

using size_val = std::uint16_t;

int main(int argc, char* argv[]){

    par::Parser parser;
    
    try{

        parser.opt.run_options(argc, argv);
        api::APP::init_engine(parser.opt);
        parser.readParameters();
        api::APP::render();

    }catch(const std::exception& e){std::cerr << e.what() << "\n";return 1;}
    



    return 0;
}