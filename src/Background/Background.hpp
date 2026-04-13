
#include "Color.hpp"
#include <vector>

namespace bkg {

    class Background {  
        private:
        std::array<clr::Color, 4> corners{clr::Color(0, 0, 0), clr::Color(0, 0, 0),
                                          clr::Color(0, 0, 0), clr::Color(0, 0, 0)};
        enum Corners : std::uint8_t {
            bl = 0,
            tl,
            tr,
            br
        };

        clr::Color lerp(clr::Color A, clr::Color B, float t);
        public:

        Background(const std::vector<clr::Color>& colors);
        clr::Color sampleUV(float u, float v);

    };
}