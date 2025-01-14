#ifndef _MAP_EXCEPTIONS_HPP
#define _MAP_EXCEPTIONS_HPP

#include <stdexcept> 

namespace ani{
    class map_out_of_range : public std::out_of_range{
        public:
            map_out_of_range() : out_of_range("Map key not found in map") { }
    };
}

#endif // _MAP_EXCEPTIONS_HPP