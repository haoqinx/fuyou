#include  "Httpdata.h"
namespace fuyou
{
pthread_once_t FileType::once_control = PTHREAD_ONCE_INIT;
std::unordered_map<std::string, std::string> FileType::_typeMap;
FileType::FileType(){

}
FileType::~FileType(){
    LOG << "delete filetype";
}

void FileType::init(){
    _typeMap[".html"] = "text/html";
    _typeMap[".avi"] = "video/x-msvideo";
    _typeMap[".bmp"] = "image/bmp";
    _typeMap[".c"] = "text/plain";
    _typeMap[".doc"] = "application/msword";
    _typeMap[".gif"] = "image/gif";
    _typeMap[".gz"] = "application/x-gzip";
    _typeMap[".htm"] = "text/html";
    _typeMap[".ico"] = "image/x-icon";
    _typeMap[".jpg"] = "image/jpeg";
    _typeMap[".png"] = "image/png";
    _typeMap[".txt"] = "text/plain";
    _typeMap[".mp3"] = "audio/mp3";
    _typeMap["default"] = "text/html";
}

std::string FileType::getType(const std::string& suffix){
    pthread_once(&once_control, FileType::init);
    if (_typeMap.find(suffix) == _typeMap.end()){
        LOG << "Not found" << suffix << " , get " << _typeMap["default"] << " instead.";
        return _typeMap["default"];
    }
    else{
        return _typeMap[suffix];
    }
}



// Httpdata::Httpdata(HTTPopt opt, HTTPverion version, std::string filepath)
//                     :_opt(opt),
//                     _version(version),
//                     _filepath(filepath),
//                     _isKeepAlive(true){
    
// }

// Httpdata::~Httpdata(){
//     LOG << "Delete Httpdata";
// }


}