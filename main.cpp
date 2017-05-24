#include <iostream>
#include <dirent.h>
#include <string>
#include <math.h>

using namespace std;

#define TABLE_FILE 128

struct filesystem {
    string name;
    string type; // F -> Folder; f -> file
    unsigned long size;
    string dateCreated;
    string dateModified;
    int subF;
    filesystem *pSub;
};
typedef struct filesystem FILESYS;

class FileNode {
private:
    string key;
    FILESYS data;
    FileNode* pNext;
public:
    FileNode(string key, FILESYS data) {
        this->key = key;
        this->data.name = data.name;
        this->data.type = data.type;
        this->data.size = data.size;
        this->data.dateCreated = data.dateCreated;
        this->data.dateModified = data.dateModified;
        this->data.subF = data.subF;
        this->data.pSub = data.pSub;
        this->pNext = NULL;
    }
    string getkey() {
        return key;
    }

    FILESYS getFILE() {
        return data;
    }

    FileNode* getNext() {
        return pNext;
    }

    void setNext(FileNode *p) {
        this->pNext = p;
    }
};

class FileHash {
private:
    FileNode **table;
public:
    FileHash () {
        table = new FileNode*[TABLE_FILE];
        for(int i = 0 ;i < TABLE_FILE; i++) {
            table[i] = NULL;
        }
    }

    int createHash(string key) {
        int sum = 0;
        int len = key.length();
        for(unsigned int i = 0; i < key.length(); i++) {
            long long temp = (int)key[i] * pow(128 * 1.0, len * 1.0);
            sum += temp % TABLE_FILE;
            len--;
        }
        return sum;
    }

    void InsertFile(string key, FILESYS data) {
        int hash = createHash(key);

        if(table[hash] == NULL) {
            table[hash] = new FileNode(key, data);
        }
        else {
            FileNode* temp = table[hash];
            while(temp->getNext() != NULL) {
                temp = temp->getNext();
            }
            temp->setNext(new FileNode(key, data));
        }
    }

    void SearchFile(string key) {
        int hash = createHash(key);

        if(table[hash] == NULL) {
            cout << "Not found...";
            return;
        }
        else {
            FileNode* temp = table[hash];
            while(temp->getkey() != key && temp != NULL) {
                temp = temp->getNext();
            }
            if(temp == NULL) {
                cout << "Not found...";
                return;
            }
            FILESYS t = temp->getFILE();
            cout << t.name << endl << t.size << t.type << endl << t.dateCreated << endl << t.dateModified << endl;
            return;
        }
    }

    void DeleteFile(string key) {
        int hash = createHash(key);

        if(table[hash] == NULL) {
            cout << "NOT FOUND...";
            return;
        }
        else {
            FileNode* pre = NULL;
            FileNode* temp = table[hash];

            while(temp->getNext() != NULL && temp->getkey() != key) {
                pre = temp;
                temp = temp->getNext();
            }

            if(temp->getkey() == key) {
                if(pre == NULL) {
                    FileNode* next = temp->getNext();
                    delete temp;
                    table[hash] = next;
                }
                else {
                    FileNode* next = temp->getNext();
                    delete temp;
                    pre->setNext(next);
                }
            }
        }
    }

    void RemoveFile(string key) {
    }

    ~FileHash() {
        for(int i = 0; i < TABLE_FILE; i++) {
            FileNode *temp = table[i];
            while(temp != NULL) {
                FileNode* p = temp;
                temp = temp->getNext();
                delete p;
            }
        }
        delete[] table;
    }
};

int main()
{
    //https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir("data")) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            //FILESYS temp;
            string str = ent->d_name;
            //cout << ent->d_name << "\t" << ent->d_reclen << endl;
            cout << str << endl;
        }
        closedir(dir);
    }
    else {
        cout << "Could not open dir...";
        return 0;
    }
    return 0;
}
