#ifndef _UNORDERED_MAP_EXCEPTIONS_HPP
#define _UNORDERED_MAP_EXCEPTIONS_HPP

#include <stdexcept> 

namespace ani{
    class unordered_map_out_of_range : public std::out_of_range{
        public:
            unordered_map_out_of_range() : out_of_range("Unordered map key not found in map") { }
    };
}

#endif // _UNORDERED_MAP_EXCEPTIONS_HPP