#ifndef _LIST_EXCEPTIONS_HPP
#define _LIST_EXCEPTIONS_HPP

#include <stdexcept> 

namespace ani{
    class list_empty : public std::runtime_error{
        public:
            list_empty() : std::runtime_error("List is empty") { }
    };
}

#endif // _LIST_EXCEPTIONS_HPP