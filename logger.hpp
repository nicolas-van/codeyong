
/*
	Yong Master: a small game that looks like othello.
	Copyright (C) 2006 Nicolas Vanhoren

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

	Nicolas Vanhoren
	nicolasvnh-0@yahoo.fr
*/

#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

namespace log {
    class logger;
}

#include "level.hpp"
#include "handlers.hpp"
#include "log_exception.hpp"

#include <boost/signal.hpp>
#include <string>
#include <assert.h>
#include <sstream>
#include <memory>

namespace log {

    class logger : boost::noncopyable {
        public:

        /**
            This structure ca only be constructed by a logger object.
            It encapsulate an ostringstream object you can access by using
            stream() method. When this object is destroyed, the content of
            the ostringstream object is logged.
        */
        class log_stream {
            private:
            friend class logger;
            std::ostringstream _buf;
            logger* _logger;
            level _level;

            log_stream(logger& log,const level& lev);
            log_stream(const log_stream& o);

            //undefined
            log_stream();
            log_stream& operator = (const log_stream& o);

            public:

            operator std::ostream& () {
                return _buf;
            };

            template<typename A>
            std::ostream& operator << (A& a) {
                return ((std::ostream&)*this) << a;
            }

            template<typename A>
            std::ostream& operator << (const A& a) {
                return ((std::ostream&)*this) << a;
            }

            std::ostream& operator<<(ostream& (*a)(ostream&)) {
                return ((std::ostream&)*this) << a;
            }
            std::ostream& operator<<(ios& (*a)(ios&)) {
                return ((std::ostream&)*this) << a;
            }
            std::ostream& operator<<(ios_base& (*a)(ios_base&)) {
                return ((std::ostream&)*this) << a;
            }

            ~log_stream();
        };

        private:
        logger* _father;
        std::auto_ptr<level> _level;
        boost::signal<void (std::string&,level)> _formatters;
        boost::signal<void (std::string)> _handlers;


        public:

        logger();

        logger(logger& father);


        /**
            Log a message, indicating its level.
        */
        void log(const std::string& message,const level& des_level) throw();
        void fatal(const std::string& message) throw();
        void error(const std::string& message) throw();
        void warning(const std::string& message) throw();
        void info(const std::string& message) throw();
        void debug(const std::string& message) throw();
        void trace(const std::string& message) throw();
        /**
            Return a log_stream object that can be used to log
            messages with a better "C++ streaming" style.
            You can specify the level of the message.
        */
        log_stream log(const level& des_level) throw();
        log_stream fatal() throw();
        log_stream error() throw();
        log_stream warning() throw();
        log_stream info() throw();
        log_stream debug() throw();
        log_stream trace() throw();

        bool has_current_level() const;

        const level& current_level() const throw();

        void current_level(const level&);

        void erase_current_level() throw();

        const level& effective_level() const;

        /**
            The formatters are used to format the message before it is logged.
        */
        boost::signal<void (std::string&,level)>& formatters();
        /**
            The formatters are used to format the message before it is logged.
        */
        const boost::signal<void (std::string&,level)>& formatters() const;

        /**
            The handlers are used to define the way of saving the messages.
        */
        boost::signal<void (std::string)>& handlers();
        /**
            The handlers are used to define the way of saving the messages.
        */
        const boost::signal<void (std::string)>& handlers() const;
    };

}

#endif // LOGGER_HPP_INCLUDED
