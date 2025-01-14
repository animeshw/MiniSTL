#ifndef _STRING_EXCEPTIONS_HPP
#define _STRING_EXCEPTIONS_HPP

#include <stdexcept>

namespace ani{
    class string_empty : public std::runtime_error{
        public:
            string_empty() : std::runtime_error("String is empty") { }
    };

    class string_out_of_range : public std::out_of_range{
        public:
            string_out_of_range() : out_of_range("String index out of range") { }
    };
}

#endif // _STRING_EXCEPTIONS_HPP