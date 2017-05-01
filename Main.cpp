#include <iostream>
#include <io.h>
#include <time.h>
#include "FileBackBone.h"

void printFile(_finddata_t &c_file) {
	char buffer[30];
	printf((c_file.attrib & _A_RDONLY) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_HIDDEN) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_SYSTEM) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_ARCH) ? " Y  " : " N  ");
	printf((c_file.attrib & _A_SUBDIR) ? " Y  " : " N  ");
	ctime_s(buffer, _countof(buffer), &c_file.time_write);
	printf(" %-12s %.24s  %9ld\n", c_file.name, buffer, c_file.size);
}

void saveFileToHash(_finddata_t &c_file, fileStructure &file) {
	char buffer1[30];
	char buffer2[30];
	char buffer3[30];
	file.setFileName(string(c_file.name));
	if ((c_file.attrib & _A_SUBDIR) == _A_SUBDIR)
	{
		file.isFileZ(false);
	}
	else {
		file.isFileZ(true);
	}
	ctime_s(buffer1, _countof(buffer1), &c_file.time_access);
	ctime_s(buffer2, _countof(buffer2), &c_file.time_create);
	ctime_s(buffer3, _countof(buffer3), &c_file.time_write);
	if (file.checkFile()) {
		file.setFileSize(c_file.size);
	}
	else {
		file.setFileSize(0);
	}
	file.setDateAccessed(buffer1);
	file.setDateCreated(buffer2);
	file.setDateModified(buffer3);
}

int main() {
	struct _finddata_t c_file;
	intptr_t hFile;
	FileLink *fileTree = new FileLink;
	fileTree->Init();
	if ((hFile = _findfirst("data/*.*", &c_file)) == -1L)
		printf("No files in current directory!\n");
	else
	{
		printf("Listing of files\n\n");
		printf("RDO HID SYS ARC SUB  FILE         DATE %25c SIZE\n", ' ');
		printf("--- --- --- --- ---  ----         ---- %25c ----\n", ' ');
		do {
			fileStructure temp;
			//printFile(c_file);
			saveFileToHash(c_file, temp);
			FileBackBone* p = fileTree->getNode(temp);
			fileTree->addTail(p);
		} while (_findnext(hFile, &c_file) == 0);
		_findclose(hFile);
	}
	
	return 0;
}