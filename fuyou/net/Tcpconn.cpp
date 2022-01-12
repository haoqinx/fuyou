#include "Tcpconn.h"
#include <memory>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace fuyou
{
const __uint32_t DEFAULT_EVENT = EPOLLIN |  EPOLLPRI | EPOLLRDHUP;
const int DEFAULT_EXPIRED_TIME = 2000;  
const int KEEP_CONN_TIME = 5 * 60 * 1000;
// The path to the static resource folder
const std::string BASE_DIR = "/home/hqin/fuyou/static/";

Tcpconn::Tcpconn(EventLoop* loop, int connfd):
                _loop(loop),
                _connfd(connfd),
                _channel(new Channel(loop, connfd)),
                _version(HTTP11),
                _nowReadPos(0),
                _headerState(H_START),
                _opt(GET),
                _connectionState(STATE_CONNECTED),
                _pstate(PRO_PARSE_URI){
    _channel -> setEvents(EPOLLIN | EPOLLPRI | EPOLLRDHUP);
    _channel -> setReadHandler(bind(&Tcpconn::handleRead, this));
    _channel -> setWriteHandler(bind(&Tcpconn::handleWrite, this));
    _channel -> setConnHandler(bind(&Tcpconn::handleConn, this));
}

Tcpconn::~Tcpconn(){
    LOG << "TCP closed";
    close(_connfd);
}

void Tcpconn::handleRead(){
    LOG << "handle read...";
    __uint32_t &events = _channel -> getEvents();
    LOG << "current events : " << events;
    bool isClose = false;
    bool isEnd = false;
    do{
        bool zero = false;
        int readBytes = readn(_connfd, _inbuffer, zero);
        // test info
        LOG << "New Msg :" << _inbuffer; 
        if( STATE_DISCONNECTING == _connectionState){
            _inbuffer.clear();
            break;
        }
        if(readBytes < 0){
            perror("read error");
            handleError(_connfd, 400, "Bad req");
        }
        else if(zero){
            LOG << "read zero data....";
            _connectionState = STATE_DISCONNECTING;
            handleClose();
        }   
        
        if( _pstate == PRO_PARSE_URI){
            URIState ustate = this -> parseURI();
            if(ustate == PARSE_URI_AGAIN){
                break;
            }
            else if(ustate == PARSE_URI_ERROR){
                perror("URI parse error");
                //LOG << _connfd << " URI parse error";
                _inbuffer.clear();
                _error = true;
                this -> handleError(_connfd, 400, "Bad Request");
                break;
            }
            else{
                _pstate = PRO_PARSE_HEADERS;
            }
        }
        if(_pstate == PRO_PARSE_HEADERS){
            HeaderState hstate = this -> parseHeaders();
            if(PARSE_HEADER_AGAIN == hstate){
                //do nothing
            }
            else if(PARSE_HEADER_ERROR == hstate){
                perror("parse header error");
                //LOG << _connfd << " parse header error";
                handleError(_connfd, 400, "Bad Request");
                break;
            }
            if(_opt == POST){
                _pstate = PRO_RECV_BODY;
            }
            else{
                _pstate = PRO_ANALYSIS;
            }
        }
        if(_pstate == PRO_RECV_BODY){
            int content_len = -1;
            if(_headers.find("Content-length") != _headers.end()){
                content_len = stoi(_headers["Content-length"]);
            }
            else{
                _error = true;
                handleError(_connfd, 400, "Bad Request, lack of options Content-length");
                break;
            }
            if(static_cast<int>(_inbuffer.size()) < content_len){
                break;
            }
            _pstate = PRO_ANALYSIS;
        }
        if( _pstate == PRO_ANALYSIS){
            AnalysisState astate = this -> parseRequsets();
            if(ANALYSIS_SUCCESS == astate){
                _pstate = PRO_FINISH;
            }
            else{
                _error = true;
            }
        }

    }while(false);
    if(! _error){
        if (_outbuffer.size() > 0) {
            handleWrite();
            // events_ |= EPOLLOUT;
        }
        // error_ may change
        if (!_error && _pstate == PRO_FINISH) {
            this->reset();
            if (_inbuffer.size() > 0) {
                if (_connectionState != STATE_DISCONNECTING) handleRead();
            }
    }
}

void Tcpconn::handleWrite(){
    LOG << "handle Write...";
    if(!_error){
        __uint32_t &_events = _channel -> getEvents();
        int writeBytes = 0;
        if((writeBytes = writen(_connfd, _outbuffer)) < 0){
            perror("writen error");
            _events = 0;
            _error = true;
        }
        else if(_outbuffer.size() > 0){
            _events |= EPOLLOUT;
            _events |= EPOLLIN | EPOLLPRI | EPOLLRDHUP;
            _channel -> setEvents(_events);
            _poller -> epollMod(_channel, 0);
            LOG << "last " << writeBytes << " data";
        }
        LOG << "_outbuffer size: " << _outbuffer.size();
        LOG << "Have write " << writeBytes << "Bytes.";
        
    }
}

void Tcpconn::newEvent(){
    _channel -> setEvents(DEFAULT_EVENT);
    _loop -> addPoller(_channel, DEFAULT_EXPIRED_TIME);
}

void Tcpconn::handleConn(){
    LOG << "handling connection, conn state: " << _connectionState;
    // LOG << "is KeepAlive ? " << _isKeepAlive;
    seperateTimer();
    __uint32_t& _events = _channel -> getEvents();
    LOG << "Events: " << _events; 
    if(_events & EPOLLOUT){
        LOG << "Handleconn event detects: EPOLLOUT";
    }
    else if(_events & EPOLLIN){
        LOG << "Handleconn event detects: EPOLLIN";
    }
    // if(! _error && _connectionState == STATE_CONNECTED){
    //     int timeout = DEFAULT_EXPIRED_TIME;
    //     if(_isKeepAlive) timeout = KEEP_CONN_TIME;
    //     _events |= EPOLLIN |  EPOLLPRI | EPOLLRDHUP;
    //     _loop -> updatePoller(_channel, timeout);
    // }
    // else if(! _error && _connectionState == STATE_DISCONNECTING){
    //     LOG << "disconnecting..."
    // }
    // else{
    //     _loop -> runInLoop(bind(&Tcpconn::handleClose, shared_from_this()));
    // }
    // _events |= (EPOLLIN | EPOLLET);
    // int timeout = KEEP_CONN_TIME;
    // _loop -> updatePoller(_channel, timeout);
}
void Tcpconn::handleError(int fd, int err_num, std::string msg){
    //LOG << "Doing Handle Error";
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
    _connectionState = STATE_DISCONNECTED;
    std::shared_ptr<Tcpconn> guard(shared_from_this());
    _loop -> removeFromPoller(_channel);
}



AnalysisState Tcpconn::parseRequsets(){
    LOG << "Parsing requests ...";
    if(_opt == POST){

    }
    else if(_opt == GET || _opt == HEAD){
        string header;
        header += "HTTP/1.1 200 OK\r\n";
        if(_headers.find("Connection") != _headers.end() && 
            (_headers["Connection"] == "Keep-Alive"  || _headers["Connection"] == "keep-alive")){
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
            _outbuffer += "HTTP/1.1 200 OK\r\n";
            _outbuffer += "Content-type: text/plain\r\n";
            _outbuffer += "Content-Length: " + std::to_string(strlen("Success")) + "\r\n";
            _outbuffer += "\r\nSuccess";
            return ANALYSIS_SUCCESS;
        }
        //文件是否存在
        std::string filepath = BASE_DIR + _filename;
        struct stat sbuf;
        if(stat(filepath.c_str(), &sbuf) < 0){
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
        int src_fd = open(filepath.c_str(), O_RDONLY, 0);
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
    LOG << "Parsing URI ...";
    string& str = _inbuffer;
    string cop = str;
    size_t pos = str.find('\r', _nowReadPos);
    if(pos < 0 || pos >= str.size()){
        return PARSE_URI_AGAIN;
    }
    string req_line = str.substr(0, pos);
    if(str.size() > pos + 1){
        str = str.substr(pos + 1);
    }
    else{
        str.clear();
    }
    int posGet = req_line.find("GET");
    int posPost = req_line.find("POST");
    int posHead = req_line.find("HEAD");

    if(posGet >= 0){
        pos = posGet;
        _opt = GET;
    }
    else if(posPost >= 0){
        pos = posPost;
        _opt = POST;
    }
    else if(posHead >= 0){
        pos = posHead;
        _opt = HEAD;
    }
    else {
        return PARSE_URI_ERROR;
    }
    // filename
    // LOG << "req_line is " << req_line;
    pos = req_line.find("/", pos);
    // LOG << "pos is " << pos;
    if(pos < 0){
        _filename = "index.html";
        _version = HTTP11;
        return PARSE_URI_SUCCESS;
    }
    else{
        size_t _pos = req_line.find(' ', pos);
        // LOG << "pos2 is " << _pos;
        if(_pos - pos > 1){
            _filename = req_line.substr(pos + 1, _pos - pos - 1);
            // LOG << "filename1 is " << _filename;
            size_t __pos = _filename.find('?');
            if(__pos >= 0){
                _filename = _filename.substr(0, __pos);
            }
        }
        else{
            _filename = "index.html";
        }
        pos = _pos;
    }
    //version
    pos = req_line.find("/", pos);
    if(pos < 0 || req_line.size() - pos <= 3){
        return PARSE_URI_ERROR;
    }
    else{
        string version = req_line.substr(pos + 1, 3);
        if(version == "1.0"){
            _version = HTTP10;
        }
        else if(version == "1.1"){
            _version = HTTP11;
        }
        else{
            return PARSE_URI_ERROR;
        }
    }
    
    return PARSE_URI_SUCCESS;
}

HeaderState Tcpconn::parseHeaders(){
    LOG << "Parsing header ...";
    string& str = _inbuffer;
    int key_start = -1, key_end = -1, value_start = -1, value_end = -1;
    int cur_line_pos = 0;
    bool finished = false;
    size_t index = 0;
    for(; index < str.size(); ++ index){
        switch (_headerState){
            case H_START:{
                if(str[index] == '\n' || str[index] == '\r') break;
                _headerState = H_KEY;
                key_start = index;
                cur_line_pos = index;
                break;
            }
            case H_KEY:{
                if(str[index] == ':'){
                    key_end = index;
                    if(key_end - key_start <= 0){
                        return PARSE_HEADER_ERROR;
                    }
                    _headerState = H_COLON;
                }
                else if(str[index] == '\n' || str[index] == '\r'){
                    return PARSE_HEADER_ERROR;
                }
                break;
            }
            case H_COLON:{
                if(str[index] == ' '){
                    _headerState = H_SPACES_AFTER_COLON;
                }
                else{
                    return PARSE_HEADER_ERROR;
                }
                break;
            }
            case H_SPACES_AFTER_COLON:{
                _headerState = H_VALUE;
                value_start = index;
                break;
            }
            case H_VALUE:{
                if(str[index] == '\r'){
                    _headerState = H_CR;
                    value_end = index;
                    if(value_end - value_start <= 0) {
                        return PARSE_HEADER_ERROR;
                    }
                }
                else if(index - value_start > 255){
                    return PARSE_HEADER_ERROR;
                }
                break;
            }
            case H_CR:{
                if(str[index] == '\n'){
                    _headerState = H_LF;
                    std::string key(str.begin() + key_start, str.begin() + key_end);
                    std::string value(str.begin() + value_start, str.begin() + value_end);
                    _headers[key] = value;
                    cur_line_pos = index;
                }
                else{
                    return PARSE_HEADER_ERROR;
                }
                break;
            }
            case H_LF:{
                if(str[index] == '\r'){
                    _headerState = H_END_CR;
                }
                else{
                    key_start = index;
                    _headerState = H_KEY;
                }
                break;
            }
            case H_END_CR:{
                if(str[index] == '\n'){
                    _headerState = H_END_LF;
                }
                else{
                    return PARSE_HEADER_ERROR;
                }
                break;
            }
            case H_END_LF:{
                finished = true;
                key_start = index;
                cur_line_pos = index;
                break;
            }
        }
    }
    if(_headerState == H_END_LF){
        str = str.substr(index);
        return PARSE_HEADER_SUCCESS;
    }
    str = str.substr(cur_line_pos);
    return PARSE_HEADER_AGAIN;
}

void Tcpconn::reset(){
    _filename.clear();
    _filepath.clear();
    _nowReadPos = 0;
    _pstate = PRO_PARSE_URI;
    _headerState = H_START;
    _headers.clear();
    seperateTimer();
    // if(_timer.lock()){
    //     std::shared_ptr<TimerNode> my_timer(_timer.lock());
    //     my_timer -> clearReq();
    //     _timer.reset();
    // }
}
} // namespace fuyou
