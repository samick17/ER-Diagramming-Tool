#include "DirectoryUtil.h"
#include <direct.h>

//@return : current working directory
string DirectoryUtil::getCurrentWorkingDirectory(){
    char* currentWorkingDirectoryCharArray = _getcwd(NULL, 0);
    string currentWorkingDirectory(currentWorkingDirectoryCharArray);
    free(currentWorkingDirectoryCharArray);
    return currentWorkingDirectory;
}