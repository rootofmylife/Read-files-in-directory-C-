#pragma once
#include <string>

using namespace std;

// DATA ===
class fileStructure
{
private:
	string fileName;
	long fileSize;
	bool isFile;
	string dateCreated;
	string dateModified;
	string dateAccessed;
public:
	fileStructure();

	void isFileZ(bool);
	long countSize();
	// get
	void setFileName(string);
	void setDateCreated(string);
	void setDateModified(string);
	void setDateAccessed(string);
	void setFileSize(long );
	// set
	string getFileName();
	string getDateCreated();
	string getDateModified();
	string getDateAccessed();
	long getSize();
	bool checkFile();
	~fileStructure();
};

// NODE ===
class FileBackBone
{
private:
	fileStructure value;
	FileBackBone *pNext;	
	//FileLink *pNextFileIfFolder; // if this is a folder, so we create a list to link files in its
public:
	FileBackBone();
	FileBackBone setFile(fileStructure );
	void setNext(FileBackBone* );
	FileBackBone* getNext();
	~FileBackBone();
};

// LIST ===
class FileLink
{
private:
	FileBackBone *pHead;
	FileBackBone *pTail;
public:
	FileLink();
	void Init();
	FileBackBone* getNode(fileStructure );
	void addTail(FileBackBone* );
	~FileLink();
};


