#include  "Httpdata.h"
namespace fuyou
{
FileType::FileType(){

}
FileType::~FileType(){
    LOG << "delete filetype";
}



Httpdata::Httpdata(HTTPopt opt, HTTPverion version, std::string filepath)
                    :_opt(opt),
                    _version(version),
                    _filepath(filepath),
                    _ftype("text"),
                    _isKeepAlive(true){
    
}

Httpdata::~Httpdata(){
    LOG << "Delete Httpdata";
}
}