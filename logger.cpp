
#include "logger.hpp"

#include "logger_manager.hpp"

namespace log {

    /*
    log_stream methods
    */
    logger::log_stream::log_stream(logger& log,const level& lev):_buf(),_logger(&log),_level(lev){
    }

    logger::log_stream::log_stream(const log_stream& o) : _buf(),_logger(o._logger),_level(o._level) {
    }

    logger::log_stream::~log_stream() {
        if(_buf.str()!="")
            _logger->log(_buf.str(),_level);
    }


    /*
    logger methods
    */
    logger::logger() {
        _father = &logger_manager::instance().root_logger();
    }

    logger::logger(logger& father) {
        _father = &father;
    }


    void logger::log(const std::string& message,const level& des_level) throw() {
        if(des_level<effective_level())
            return;
        std::string mess = message;
        _formatters(mess,des_level);
        _handlers(mess);
    }
    void logger::fatal(const std::string& message) throw() {
        log(message,level::fatal);
    }
    void logger::error(const std::string& message) throw() {
        log(message,level::error);
    }
    void logger::warning(const std::string& message) throw() {
        log(message,level::warning);
    }
    void logger::info(const std::string& message) throw() {
        log(message,level::info);
    }
    void logger::debug(const std::string& message) throw() {
        log(message,level::debug);
    }
    void logger::trace(const std::string& message) throw() {
        log(message,level::trace);
    }

    logger::log_stream logger::log(const level& des_level) throw() {
        return log_stream(*this,des_level);
    }
    logger::log_stream logger::fatal() throw() {
        return log(level::fatal);
    }
    logger::log_stream logger::error() throw() {
        return log(level::error);
    }
    logger::log_stream logger::warning() throw() {
        return log(level::warning);
    }
    logger::log_stream logger::info() throw() {
        return log(level::info);
    }
    logger::log_stream logger::debug() throw() {
        return log(level::debug);
    }
    logger::log_stream logger::trace() throw() {
        return log(level::trace);
    }


    bool logger::has_current_level() const {
        if(_level.get()==NULL)
            return false;
        return true;
    }

    const level& logger::current_level() const throw(){
        if(_level.get()==NULL)
            throw log_exception("This logger does not define a current level.");
        return *_level;
    }

    void logger::current_level(const level& lev) {
        _level = std::auto_ptr<level>(new level(lev));
    }

    void logger::erase_current_level() throw(){
        if(_father==NULL)
            throw log_exception("You may not erase the current level of the root logger.");
        _level = std::auto_ptr<level>();
    }

    const level& logger::effective_level() const {
        if(_level.get()==NULL)
            return _father->effective_level();
        return *_level;
    }


    boost::signal<void (std::string&,level)>& logger::formatters() {
        return _formatters;
    }

    const boost::signal<void (std::string&,level)>& logger::formatters() const {
        return _formatters;
    }


    boost::signal<void (std::string)>& logger::handlers() {
        return _handlers;
    }

    const boost::signal<void (std::string)>& logger::handlers() const {
        return _handlers;
    }

}


