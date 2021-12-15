#include "FileUtil.h"
namespace fuyou
{
void FileUtil::append(const char* line, const size_t len){
    size_t n = this -> write(line, len);
    size_t left = len - n;
    while(left > 0){
        size_t x = this -> write(line + n, left);
        if(x == 0){
            int err = ferror(fp_);
            if(err){
                fprintf(stderr, "FileUtil::append() error \n");
            }
            
            break;
        }
        n += x;
        left = len - n;
    }
}

size_t FileUtil::write(const char* line, const size_t len){
    return fwrite_unlocked(line, 1, len, fp_);
}
} // namespace fuyou

