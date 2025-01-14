#ifndef _DCDS_EXCEPTION_HPP
#define _DCDS_EXCEPTION_HPP

#include <stdexcept>

namespace ani{
    class dcds_representative_exists : public std::runtime_error{
        public:
            dcds_representative_exists() : runtime_error("Representative element already present in DCDS") {}
    };

    class dcds_representative_not_found : public std::runtime_error{
        public:
            dcds_representative_not_found() : runtime_error("Representative element nto found in DCDS") {}
    };
};

#endif // _DCDS_EXCEPTION_HPP