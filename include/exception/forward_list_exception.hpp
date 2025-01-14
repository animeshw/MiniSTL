#ifndef FORWARD_LIST_EXCEPTIONS_HPP
#define FORWARD_LIST_EXCEPTIONS_HPP

#include <stdexcept> 

namespace ani{
    class fl_empty : public std::runtime_error{
        public:
            fl_empty() : std::runtime_error("Forward list is empty") { }
    };

    class fl_invalid_iterator : public std::runtime_error{
        public:
            fl_invalid_iterator() : std::runtime_error("Forward list iterator pointing to after end of list") { }
    };
}

#endif // FORWARD_LIST_EXCEPTIONS_HPP