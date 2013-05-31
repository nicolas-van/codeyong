
#ifndef LOGGING_EVENT_HPP_INCLUDED
#define LOGGING_EVENT_HPP_INCLUDED

#include "level.hpp"
#include "logger.hpp"

#include <string>

namespace log {

    namespace internal {

        struct logging_event {

            std::string message;
            log::level used_level;
            const log::logger* calling_logger;

            logging_event(const std::string& message,const log::level& used_level
                ,const log::logger& calling_logger) {
                this->message = message;
                this->used_level = used_level;
                this->calling_logger = &calling_logger;
            }

        };

    }

}

#endif
