#include "DirectoryUtil.h"
#include <direct.h>

string DirectoryUtil::getCurrentWorkingDirectory(){
	char* a_cwd = _getcwd(NULL, 0);
    string s_cwd(a_cwd);
    free(a_cwd);
    return s_cwd;
}