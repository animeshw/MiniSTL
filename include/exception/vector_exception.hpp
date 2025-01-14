#ifndef _VECTOR_EXCEPTIONS_HPP
#define _VECTOR_EXCEPTIONS_HPP

#include <stdexcept>

namespace ani{
    class vector_empty : public std::runtime_error{
        public:
            vector_empty() : std::runtime_error("Vector is empty") { }
    };

    class vector_out_of_range : public std::out_of_range{
        public:
            vector_out_of_range() : out_of_range("Vector index out of range") { }
    };
}

#endif // _VECTOR_EXCEPTIONS_HPP