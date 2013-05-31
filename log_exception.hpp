
#ifndef LOG_EXCEPTION_HPP_INCLUDED
#define LOG_EXCEPTION_HPP_INCLUDED

#include <stdexcept>

namespace log {

    class log_exception : std::logic_error {
        public:
        log_exception():std::logic_error("undefined exception") {};
        log_exception(const std::string& mes):std::logic_error(mes) {};
    };

}


#endif


