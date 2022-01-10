#ifndef __HTTPDATA_H
#define __HTTPDATA_H
#include <unordered_map>
#include <string>
#include <pthread.h>
#include <atomic>
#include "../base/Logger.h"

namespace fuyou{

class Tcpconn;

enum HTTPopt {
    GET = 0, 
    HEAD,
    POST, 
    DELETE, 
    UPDATE
};
enum HTTPverion {
    HTTP10 = 0, 
    HTTP11 = 1
};
enum HTTPcharset {
    GB2312 = 0, 
    UTF8, 
    ISO8859
};
enum HTTPencoding {
    GZIP = 0, 
    COMPRESS
};
enum AnalysisState {
    ANALYSIS_SUCCESS = 1,
    ANALYSIS_ERROR
};
enum ProcessState { 
    PRO_PARSE_URI = 1,
    PRO_PARSE_HEADERS,
    PRO_RECV_BODY,
    PRO_ANALYSIS,
    PRO_FINISH
};
enum URIState{
    PARSE_URI_AGAIN = 1,
    PARSE_URI_ERROR,
    PARSE_URI_SUCCESS
};
enum HeaderState{
    PARSE_HEADER_AGAIN = 1,
    PARSE_HEADER_ERROR,
    PARSE_HEADER_SUCCESS
};
enum ParseState {
  H_START = 0,
  H_KEY,
  H_COLON,
  H_SPACES_AFTER_COLON,
  H_VALUE,
  H_CR,
  H_LF,
  H_END_CR,
  H_END_LF
};
enum ConnectionState{
    STATE_CONNECTED = 1,
    STATE_DISCONNECTING,
    STATE_DISCONNECTED
}; 

class FileType{
public:
    FileType();
    ~FileType();
    static std::string getType(const std::string& f);
    static void init();
private:
    static std::unordered_map<std::string, std::string> _typeMap;
    static pthread_once_t once_control;
};


// class Httpdata{
// public:
//     Httpdata(HTTPopt opt, HTTPverion version, std::string filepath);
//     ~Httpdata();
//     void setFilepath();
//     void setOpt();
//     void setVersion();

// private:
//     HTTPopt _opt;
//     std::string _filepath;
//     HTTPverion _version;
    
//     std::string _userAgent;
//     FileType _filetype;
//     atomic<bool> _isKeepAlive;
//     HTTPcharset _charset;
//     HTTPencoding _encoding;
//     friend class Tcpconn;
// };


}
#endif