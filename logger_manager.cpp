

#include "logger_manager.hpp"

namespace log {

    logger_manager logger_manager::_instance;

    logger_manager& logger_manager::instance() {
        return _instance;
    }

    logger_manager::logger_manager():_root(*((logger*)NULL)) {
        _root.current_level(level());
    }

    logger& logger_manager::root_logger() {
        return _root;
    }

    const logger& logger_manager::root_logger() const {
        return _root;
    }

}
