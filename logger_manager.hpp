
#ifndef LOGGER_MANAGER_HPP_INCLUDED
#define LOGGER_MANAGER_HPP_INCLUDED


namespace log {
    class logger_manager;
}


#include "logger.hpp"

#include <boost/noncopyable.hpp>

namespace log {
    class logger_manager : boost::noncopyable {
        private:

        static logger_manager _instance;

        logger _root;

        logger_manager();

        public:

        static logger_manager& instance();

        logger& root_logger();

        const logger& root_logger() const;
    };
}

#endif
