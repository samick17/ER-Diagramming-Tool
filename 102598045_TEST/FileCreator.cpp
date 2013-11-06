#include "FileCreator.h"
#include <direct.h>
#include "DirectoryUtil.h"
#include "Document.h"

//return path
string FileCreator::createDefaultFile(){
    //set file directory
    string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
    _mkdir(directory.c_str());
    //save file to directory
    string filePath = directory+"/test_file1.erd";
    Document doc(filePath);    
    string fileData[] = {
        "E, Engineer","A, Emp_ID","R, Has","A, Name","E, PC","A, PC_ID","A, Purchase_Date","C","C","C","C","C, 1","C, 1","A, Department","C",
        "",
        "7 0,1","8 0,3","9 4,5","10 4,6","11 0,2","12 2,4","14 0,13",
        "",
        "0 1,3","4 5"
    };
    for(int lineIndex = 0;lineIndex<sizeof(fileData)/sizeof(*fileData);lineIndex++)
        doc.wirteLine(fileData[lineIndex]);
    doc.saveFile();
    return filePath;
}

void FileCreator::deleteDefaultFile(){
    string directory = DirectoryUtil::getCurrentWorkingDirectory()+"/testdata";
    string filePath = directory+"/test_file1.erd";    
    remove(filePath.c_str());
    _rmdir(directory.c_str());
}