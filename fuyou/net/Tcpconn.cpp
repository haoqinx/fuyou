#include "Tcpconn.h"
#include "Epoll.h"
#include "Httpdata.h"
#include <memory>
#include <unistd.h>
#include <sys/mman.h>

namespace fuyou
{
const __uint32_t DEFAULT_EVENT = EPOLLIN | EPOLLPRI | EPOLLRDHUP;
const int DEFAULT_EXPIRED_TIME = 2000;  
const int KEEP_CONN_TIME = 5 * 60 * 1000;

Tcpconn::Tcpconn(EventLoop* loop, int connfd):
                _loop(loop),
                _connfd(connfd),
                _channel(new Channel(loop, connfd)){
    _channel -> setReadHandler(bind(&Tcpconn::handleRead, this));
    _channel -> setWriteHandler(bind(&Tcpconn::handleWrite, this));
    _channel -> setConnHandler(bind(&Tcpconn::handleConn, this));
}

Tcpconn::~Tcpconn(){
    LOG << "TCP closed";
    close(_connfd);
}

void Tcpconn::handleRead(){
    __uint32_t &events = _channel -> getEvents();
    bool isClose = false;
    bool isEnd = false;
    do{
        bool zero = false;
        int readBytes = readn(_connfd, _inbuffer, zero);
       
        if(readBytes > 0){
            LOG << "New Msg :" << _inbuffer; 

            handleWrite();
        }
        else if(readBytes < 0){
            perror("read error");
            handleError(_connfd, 400, "Bad req");
        }
        else if(zero){
            handleClose();
        }   

    }while(false);
}

void Tcpconn::handleWrite(){
    if(!_error){
        __uint32_t &_events = _channel -> getEvents();
        LOG << "handle Write: " << _events;
        int writeBytes = 0;
        if((writeBytes = writen(_connfd, _outbuffer)) < 0){
            perror("writen error");
            _events = 0;
            _error = true;
        }
        else if(_outbuffer.size() > 0){
            _events |= EPOLLOUT;
            LOG << "write " << writeBytes << " data";
            _channel -> setEvents(_events);
            _poller -> epollMod(_channel, 0);
        }
    }
}

void Tcpconn::newEvent(){
    _channel -> setEvents(DEFAULT_EVENT);
    _loop -> addPoller(_channel, DEFAULT_EXPIRED_TIME);
}

void Tcpconn::handleConn(){
    LOG << "handling connection";
    __uint32_t& _events = _channel -> getEvents();
    if(_events & EPOLLOUT){
        LOG << "Handleconn event detects: EPOLLOUT";
    }
    else if(_events & EPOLLIN){
        LOG << "Handleconn event detects: EPOLLIN";
    }
    // _events |= (EPOLLIN | EPOLLET);
    // int timeout = KEEP_CONN_TIME;
    // _loop -> updatePoller(_channel, timeout);
}
void Tcpconn::handleError(int fd, int err_num, std::string msg){
    LOG << "Doing Handle Error";
    msg = " " + msg;
    char send_buf[4096];
    string body_buff, header_buff;
    body_buff += "<html><title>出现了一些意想不到的事...</title>";
    body_buff += "<body bgcolor = \"ffffff\">";
    body_buff += std::to_string(err_num) + msg;
    body_buff += "<hr><em> fuyou</em>\n</body></html>";

    header_buff += "HTTP/1.1 " + to_string(err_num) + msg + "\r\n";
    header_buff += "Content-Type: text/html\r\n";
    header_buff += "Connection: Close\r\n";
    header_buff += "Content-Length: " + to_string(body_buff.size()) + "\r\n";
    header_buff += "Server: LinYa's Web Server\r\n";
    header_buff += "\r\n";

    sprintf(send_buf, "%s", header_buff.c_str());
    writen(fd, send_buf, strlen(send_buf));
    sprintf(send_buf, "%s", body_buff.c_str());
    writen(fd, send_buf, strlen(send_buf));
}

void Tcpconn::handleClose(){
    LOG << "begin to close";
    std::shared_ptr<Tcpconn> guard(shared_from_this());
    _loop -> removeFromPoller(_channel);
}



AnalysisState Tcpconn::parseRequsets(){
    if(_opt == POST){

    }
    else if(_opt == GET || _opt == HEAD){
        string header;
        header += "HTTP/1.1 200 OK\r\n";
        if(_headers.find("Connection") != _headers.end() && 
            (_headers["Connection"] == "Keep-Alive" ) || _headers["Connection"] == "keep-alive")){
            _isKeepAlive = true;
            header += std::string("Connection: Keep-Alive\r\n") + "Keep-Alive: timeout=" + 
                        to_string(KEEP_CONN_TIME) + "\r\n";
        }
        int dot_pos = _filename.find(".");
        string filetype;
        if(dot_pos < 0){
            filetype = FileType::getType("default");
        }
        else{
            filetype = FileType::getType(_filename.substr(dot_pos));
        }
        // test case
        if(_filename == "hello"){
            _outbuffer = "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\nSuccess";
            return ANALYSIS_SUCCESS;
        }
        //文件是否存在
        struct stat sbuf;
        if(stat(name.c_str(), &sbuf) < 0){
            header.clear();
            handleError(_connfd, 404, "Not found");
            return ANALYSIS_ERROR;
        }
        header += "Content-Type: " + filetype + "\r\n";
        header += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        header += "Server: fuyou Server\r\n";
        header += "\r\n";
        _outbuffer += header;

        if(_opt == HEAD) return ANALYSIS_SUCCESS;
        //尝试打开文件
        int src_fd = open(_filename.c_str(), O_RDONLY, 0);
        if(src_fd < 0){
            _outbuffer.clear();
            handleError(_connfd, 404, "Not Found!");
            return ANALYSIS_ERROR;
        }
        //将文件映射到共享存储区
        void* mmapfile = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
        close(src_fd);
        if(mmapfile == (void*) -1){
            munmap(mmapfile, sbuf.st_size);
            _outbuffer.clear();
            handleError(_connfd, 404, "Not Found!");
            return ANALYSIS_ERROR;
        }
        char*src_addr = static_cast<char*>(mmapfile);
        _outbuffer += string(src_addr, src_addr + sbuf.st_size);
        munmap(mmapfile, sbuf.st_size);
        return ANALYSIS_SUCCESS;
    }
    return ANALYSIS_SUCCESS;
}

URIState Tcpconn::parseURI(){
    string& str = _inbuffer;
    string cop = str;
    size_t pos = str.find('\r', )
}
} // namespace fuyou
