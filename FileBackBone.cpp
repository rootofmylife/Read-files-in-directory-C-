#include "FileBackBone.h"

fileStructure::fileStructure()
{
}

fileStructure::~fileStructure()
{
}

void fileStructure::isFileZ(bool check) {
	this->isFile = check;
}

long fileStructure::countSize() {
	fileSize = 0;
	return fileSize;
}

void fileStructure::setFileName(string name) {
	this->fileName = name;
}

void fileStructure::setDateCreated(string date) {
	this->dateCreated = date;
}

void fileStructure::setDateModified(string date) {
	this->dateModified = date;
}

void fileStructure::setDateAccessed(string date) {
	this->dateAccessed = date;
}

void fileStructure::setFileSize(long size) {
	fileSize = size;
}

string fileStructure::getFileName() {
	return this->fileName;
}

string fileStructure::getDateCreated() {
	return this->dateCreated;
}

string fileStructure::getDateModified() {
	return this->dateModified;
}

string fileStructure::getDateAccessed() {
	return this->dateAccessed;
}

long fileStructure::getSize() {
	return this->fileSize;
}

bool fileStructure::checkFile() {
	return this->isFile;
}

//========================

FileBackBone::FileBackBone()
{
}

FileBackBone FileBackBone::setFile(fileStructure temp) {
	this->value = temp;
	this->pNext = NULL;
}

void FileBackBone::setNext(FileBackBone* temp) {
	this->pNext = temp;
}

FileBackBone* FileBackBone::getNext() {
	return this->pNext;
}

FileBackBone::~FileBackBone()
{
}

//=======================

FileLink::FileLink()
{
	pHead = pTail = NULL;
}

void FileLink::Init() {
	this->pHead = this->pTail = NULL;
}

FileBackBone* FileLink::getNode(fileStructure temp) {
	FileBackBone *p = new FileBackBone; // fix 
	if (p == NULL) {
		return NULL;
	}
	p->setFile(temp);
	return p;
}

void FileLink::addTail(FileBackBone* p) {
	if (this->pHead == NULL) {
		this->pHead = this->pTail = p;
	}
	else {
		this->pTail->setNext(p);
		this->pTail = p;
	}
}

FileLink::~FileLink()
{
	FileBackBone * p;
	while (this->pHead != NULL) {
		p = this->pHead;
		this->pHead->setNext(this->pHead->getNext());
		delete p;
	}
}
