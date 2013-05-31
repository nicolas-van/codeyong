
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

#ifndef HANDLERS_HPP_INCLUDED
#define HANDLERS_HPP_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

namespace log {

    using namespace std;

    template<class A>
    struct base_stream_handler {
        protected:
        bool _use_endl;
        void output_to_stream(std::string out,A& stream) const {
            stream<<out;
            if(_use_endl)
                stream<<endl;
            stream.flush();
        }
        virtual void implementation(std::string out) const=0;
        public:
        base_stream_handler(bool use_endl=false):_use_endl(use_endl){}
        void operator()(std::string out) const {
            implementation(out);
        }
        virtual ~base_stream_handler() {}
    };

    template<class A>
    struct base_stream_handler_threaded {
        protected:
        boost::shared_ptr<boost::mutex> _mutex;
        bool _use_endl;
        void output_to_stream(std::string out,A& stream) const {
            stream<<out;
            if(_use_endl)
                stream<<endl;
            stream.flush();
        }
        virtual void implementation(std::string out) const=0;
        public:
        base_stream_handler_threaded(bool use_endl=false):_use_endl(use_endl){
            _mutex=boost::shared_ptr<boost::mutex>(new boost::mutex());
        }
        void operator()(std::string out) const {
            boost::mutex::scoped_lock my_lock(*_mutex);
            implementation(out);
        }
        virtual ~base_stream_handler_threaded() {}
    };

    template<class A>
    struct generic_stream_handler : public base_stream_handler<ofstream> {
        private:
        A* _stream;
        void implementation(std::string out) const {
            this->output_to_stream(out,*_stream);
        }
        public:
        generic_stream_handler(A& stream)
            :base_stream_handler<ofstream>(true),_stream(&stream) {};
    };

    template<class A>
    struct generic_stream_handler_threaded : public base_stream_handler_threaded<ofstream> {
        private:
        A* _stream;
        void implementation(std::string out) const {
            this->output_to_stream(out,*_stream);
        }
        public:
        generic_stream_handler_threaded(A& stream)
            :base_stream_handler_threaded<ofstream>(true),_stream(&stream) {};
    };

    struct file_handler : public base_stream_handler<ofstream> {
        private:
        std::string filename;
        void implementation(std::string out) const {
            ofstream file(filename.c_str(),std::ios::app);
            this->output_to_stream(out,file);
            file.close();
        }
        public:
        file_handler(std::string file)
            :base_stream_handler<ofstream>(true),filename(file) {};
    };

    struct file_handler_threaded : public base_stream_handler_threaded<ofstream> {
        private:
        std::string filename;
        void implementation(std::string out) const {
            ofstream file(filename.c_str(),std::ios::app);
            this->output_to_stream(out,file);
            file.close();
        }
        public:
        file_handler_threaded(std::string file)
            :base_stream_handler_threaded<ofstream>(true),filename(file) {};
    };

    struct console_handler : public base_stream_handler<ostream> {
        private:
        void implementation(std::string out) const {
            this->output_to_stream(out,cout);
        }
        public:
        console_handler() : base_stream_handler<ostream>(true) {};
    };

    struct console_handler_threaded : public base_stream_handler_threaded<ostream> {
        private:
        void implementation(std::string out) const {
            this->output_to_stream(out,cout);
        }
        public:
        console_handler_threaded() : base_stream_handler_threaded<ostream>(true) {};
    };

}


#endif // HANDLERS_HPP_INCLUDED
