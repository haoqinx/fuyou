#include  "Httpdata.h"
namespace fuyou
{
FileType::FileType(){

}
FileType::~FileType(){
    LOG << "delete filetype";
}

FileType::init(){
    mime[".html"] = "text/html";
    mime[".avi"] = "video/x-msvideo";
    mime[".bmp"] = "image/bmp";
    mime[".c"] = "text/plain";
    mime[".doc"] = "application/msword";
    mime[".gif"] = "image/gif";
    mime[".gz"] = "application/x-gzip";
    mime[".htm"] = "text/html";
    mime[".ico"] = "image/x-icon";
    mime[".jpg"] = "image/jpeg";
    mime[".png"] = "image/png";
    mime[".txt"] = "text/plain";
    mime[".mp3"] = "audio/mp3";
    mime["default"] = "text/html";
}

std::string FileType::getType(const std::string& f){
    pthread_once(&once_control, MimeType::init);
    if (mime.find(suffix) == mime.end()){
        LOG << "Not found" << f << " , get " << mime["default"] << " instead."；
        return mime["default"];
    }
    else{
        return mime[suffix];
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