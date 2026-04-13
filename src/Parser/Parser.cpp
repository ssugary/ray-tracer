#include "Parser.hpp"
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>


namespace par{

    template <typename T>
    bool convert(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
    assert(ps);
    std::istringstream iss{ attr_content };    
    T single_value{};                            
    std::vector<T> multiple_values;             
    bool input_string_still_has_values{ true }; 
    while (input_string_still_has_values and not iss.eof()) {
        if (std::is_same<T, bool>()) {
        iss >> std::boolalpha >> single_value;  
        } else {
        iss >> single_value; 
        }
        if (iss.fail()) {
        if (multiple_values.empty()) {  
            return false;                
        }
        input_string_still_has_values = false;
        break;
        }
        std::cout << "   ----> Value extracted is " << single_value << '\n';
        multiple_values.push_back(single_value);
    }
    if (multiple_values.size() == 1) {
        single_value = multiple_values[0];
        ps->insert(attr_name, single_value);
    } else {
        ps->insert(attr_name, multiple_values);
    }
    return true;
    }

    template <typename T, std::uint8_t N>
bool convert(const std::string& attr_name, const std::string& attr_content, ParamSet* ps) {
    std::istringstream iss{ attr_content };
    T composite_value{}; 
    for (std::uint8_t i = 0; i < N; ++i) {
        int temp_val; 
        iss >> temp_val;
        
        if (iss.fail()) {
            std::cerr << "Erro a ler o valor para o atributo " << attr_name << "\n";
            return false;
        }
        
        composite_value[i] = temp_val; 
    }
    
    ps->insert(attr_name, composite_value); 
    std::cout << "   ----> Color extracted for " << attr_name << "!\n";
    
    return true;
}

    namespace {
        std::unordered_map<std::string, std::vector<std::string>> tag_catalog{
                                                        //coppied from selan
        {
            "background",
            {
            "type",
            "filename",
            "mapping",
            "color",
            "tl",
            "tr",
            "bl",
            "br",
            },
        },
        {
            "film",
            {
            "type",
            "filename",
            "img_type",
            "x_res",
            "y_res",
            "w_res",
            "h_res",
            "crop_window",
            "gamma_corrected",
            },
        },
        {
            "world_begin",
            { "" },  // no attributes
        },
        {
            "world_end",
            { "" },  // no attributes
        },

    };
    std::unordered_map<std::string, ConverterFunction> converters{
        { "type", convert<std::string> },  // "type" must be a string.
        { "name", convert<std::string> },  // "name" must be a string.
        //
        { "color", convert<clr::Color, 3> },  // "color" is a Color with 3 fields.
        { "flip", convert<bool> },
        // Background attributes.
        { "mapping", convert<std::string> },
        { "bl", convert<clr::Color, 3> },
        { "tl", convert<clr::Color, 3> },
        { "tr", convert<clr::Color, 3> },
        { "br", convert<clr::Color, 3> },
        // Image attributes
        { "x_res", convert<int> },
        { "y_res", convert<int> },
        { "w_res", convert<int> },
        { "h_res", convert<int> },
        { "filename", convert<std::string> },
        { "img_type", convert<std::string> },
        { "gamma_corrected", convert<bool> },
    };
    }
    std::unordered_map<std::string, std::function<void(const ParamSet&)>> api_functions{
    { "background", api::APP::background },
    { "world_begin", api::APP::world_begin },
    { "world_end", api::APP::world_end },
    { "film", api::APP::film },
};


    void Parser::readParameters(){
    XMLError error = doc.LoadFile(opt.in_file.c_str());
    if(error != XML_SUCCESS){
        throw std::runtime_error("Error reading XML file.");
    }

    XMLElement* root = doc.FirstChildElement("TLSM");

    if(!root){
        throw std::runtime_error("Error finding tag <TLSM>");
    }

    XMLElement* currentElement = root->FirstChildElement();

    while (currentElement != nullptr) {
        std::string tagName = currentElement->Name();

        auto it_tag = tag_catalog.find(tagName);
        if (it_tag == tag_catalog.end()) {
            std::cerr << "[Aviso] Tag ignorada: <" << tagName << "> nao reconhecida.\n";
            currentElement = currentElement->NextSiblingElement();
            continue;
        }


        ParamSet ps; 

        const XMLAttribute* attribute = currentElement->FirstAttribute();
        
        while (attribute != nullptr) {
            std::string attrName = attribute->Name();
            std::string attrValue = attribute->Value();

            const auto& allowed_attrs = it_tag->second;
            bool isAllowed = false;
            for(const auto& allowed : allowed_attrs) {
                if (allowed == attrName || allowed == "") {
                    isAllowed = true; 
                    break;
                }
            }

            if(isAllowed) {
                auto it_conv = converters.find(attrName);
                if (it_conv != converters.end()) {
                    // Chama a função convert<> e popula o ParamSet (ps)
                    it_conv->second(attrName, attrValue, &ps);
                } else {
                    std::cerr << "[Aviso] Nenhum conversor definido para o atributo: '" << attrName << "'\n";
                }
            } else {
                std::cerr << "[Aviso] Atributo '" << attrName << "' nao e permitido na tag <" << tagName << ">\n";
            }

            attribute = attribute->Next();
        }

        auto it_api = api_functions.find(tagName);
        if (it_api != api_functions.end()) {
            it_api->second(ps);
        } else {
            std::cerr << "[Erro] Nenhuma funcao de API associada a tag <" << tagName << ">\n";
        }

        currentElement = currentElement->NextSiblingElement();
    }
}
    

};