
#include "sdlw_stream.hpp"

using namespace std;

namespace sdlw {

	int yaseek(struct SDL_RWops *context, int offset, int whence) {
	    std::streambuf* s = (std::streambuf*)context->hidden.unknown.data1;
	    std::ios::seekdir mode;
		switch(whence) {
			case SEEK_SET:
				mode = std::ios::beg;
				break;
			case SEEK_CUR:
				mode = std::ios::cur;
				break;
			case SEEK_END:
				mode = std::ios::end;
				break;
		}
		return s->pubseekoff(offset,mode);
		/*std::istream* s = (std::istream*)context->hidden.unknown.data1;
		int mode;
		switch(whence) {
			case SEEK_SET:
				mode = std::ios::beg;
				break;
			case SEEK_CUR:
				mode = std::ios::cur;
				break;
			case SEEK_END:
				mode = std::ios::end;
				break;
		}*/
		// problème avec gcc
		//s->seekg(offset,mode);
		//return s->tellg();
		//return s->rdbuf()->pubseekoff(offset,mode,ios::in|ios::binary);
	}
	int yaread(struct SDL_RWops *context, void *ptr, int size, int maxnum) {
	    std::streambuf* s = (std::streambuf*)context->hidden.unknown.data1;
	    return s->sgetn((char*)ptr,size*maxnum)/size;
		/*std::istream* s = (std::istream*)context->hidden.unknown.data1;
		return s->rdbuf()->sgetn((char*)ptr,size*maxnum)/size;*/
	}
	int yawrite(struct SDL_RWops *context, const void *ptr, int size, int num) {
	    // pas sur
	    std::streambuf* s = (std::streambuf*)context->hidden.unknown.data1;
		return s->sputn((const char*)ptr,size*num);
	}
	int yaclose(struct SDL_RWops *context) {
	    SDL_FreeRW(context);
	    return 0;
    }

	SDL_RWops* build_rwops_stream(std::streambuf* s) {
		SDL_RWops* wop = SDL_AllocRW();
		wop->hidden.unknown.data1=s;
		wop->seek=&yaseek;
		wop->read=&yaread;
		wop->write=&yawrite;
		wop->close=&yaclose;
		return wop;
	}
}



