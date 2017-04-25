#include <iostream>
#include <io.h>
#include <string>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

// List files				<- DONE
// Search by name			<- DONE
//			 size
//			 date
// Create					<- DONE
// Copy						<- DONE
// Move						<- DONE
// Delete					<- DONE
// Compress
// Extract

//http://www.dummies.com/programming/cpp/how-to-get-the-contents-of-a-directory-in-c/
//http://www.digitalmars.com/rtl/io.html

void DumpEntry(_finddata_t &data)
{
	//string createtime(ctime(&data.time_create));
	//cout << createtime;
	cout << "Size : " << data.size << "\t";
	if ((data.attrib & _A_SUBDIR) == _A_SUBDIR)
	{
		cout << "[" << data.name << "]" << endl;
	}
	else
	{
		cout << data.name << endl;
	}
	cout << "Time access: " << ctime(&data.time_access) << "Time create: " << ctime(&data.time_create) << "Time write: " << ctime(&data.time_write);
}

void SearchName(_finddata_t &data, string temp)
{
	//string createtime(ctime(&data.time_create));
	//cout << createtime;
	cout << "Size : " << data.size << "\t";
	if (((data.attrib & _A_SUBDIR) != _A_SUBDIR) && (temp == data.name))
	{
		cout << data.name << endl;
	}
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

int main(int argc, char *argv[]) {
	int check = 1;
	if (argc == 2) {
		string temp(argv[1]);
		if (temp != "start") {
			check = 0;
			cout << "Command is invalid. Please try again with 'swDir start'";
		}
	}

	if (check == 1) {
		cout << "Welcome to my Letr-Bach. This version is 1.0.0.\n";
		cout << "Type 'help' to list instructions about this product.\n";
		cout << "Press enter to continue...";
		getchar();
		system("cls");
		while (true) {
			string cmd, t;
			cout << "LB<.>";
			getline(cin, cmd);

			string first = cmd.substr(0, 3);
			int n = cmd.length() - first.length() - 1;

			bool check = false;
			if (cmd.length() <= 3) {
				if (cmd == "out") {
					cout << "Thank you for using my product, any feedback please send to email: 1512122@student.hcmus.edu.vn";
					system("pause");
					system("cls");

					return 0;
				}
				else {
					cout << "Something is going wrong with your command. Please try again.";
					check = true;
				}
			}

			// HELP
			if (cmd == "help") {

			}
			//

			if (check == false) {

				try {
					t = cmd.substr(4, n);
				}
				catch (const std::exception &exc) {
					cerr << exc.what();
				}
				if (first == "sph") { // show path
					// check path or .exe
					cout << cmd;
				}
				else if (first == "sdr") { // show files in path
					_finddata_t data;
					int ff = _findfirst(t.c_str(), &data);
					if (ff != -1)
					{
						int res = 0;
						while (res != -1)
						{
							DumpEntry(data);
							res = _findnext(ff, &data);
						}
						_findclose(ff);
					}
				}
				else if (first == "whr") {// find in all disks or in one directory
					// Name
					_finddata_t data;							
					int ff = _findfirst(t.c_str(), &data);		
					if (ff != -1)
					{
						int res = 0;
						while (res != -1)
						{
							SearchName(data, t);
							res = _findnext(ff, &data);
						}
						_findclose(ff);
					}					
					// Time

					// Size

				}
				else if (first == "dup") { // copy
					size_t index = t.find(' ');
					string src_temp = t.substr(0, index);
					string des_temp = t.substr(index + 1, t.length()- src_temp.length() - 1);

					//convert

					wstring des = s2ws(des_temp);
					LPCWSTR des_result = des.c_str();

					// Fix err when user dont input the name of destination file
					wstring src = s2ws(src_temp);
					LPCWSTR src_result = src.c_str();
					// done
					CopyFile(src_result, des_result, TRUE);					
				}
				else if (first == "crt") { // create 
					size_t index = t.find(' ');
					string check_file = t.substr(0, index);
					string url = t.substr(index + 1, t.length() - check_file.length() - 1);
					wstring src = s2ws(url);
					LPCWSTR src_result = src.c_str();

					if (check_file == "-fd") {
						
						CreateDirectory(src_result, NULL);
					}
					else {
						
						HANDLE h = CreateFile(src_result,// name of the file
							GENERIC_WRITE,				// open for writing
							0,							// sharing mode, none in this case
							0,							// use default security descriptor
							CREATE_ALWAYS,				// overwrite if exists
							FILE_ATTRIBUTE_NORMAL,
							0);
						if (h)
						{
							cout << "CreateFile() succeeded\n";
							CloseHandle(h);
						}
						else
						{
							cerr << "CreateFile() failed:" << GetLastError() << "\n";
						}
					}
				}
				else if (first == "shf") { // move
					size_t index = t.find(' ');
					string src_temp = t.substr(0, index);
					string des_temp = t.substr(index + 1, t.length() - src_temp.length() - 1);

					//convert

					wstring des = s2ws(des_temp);
					LPCWSTR des_result = des.c_str();

					// Fix err when user dont input the name of destination file
					wstring src = s2ws(src_temp);
					LPCWSTR src_result = src.c_str();

					// fix add name of file in the end of src_result
					MoveFile(src_result, des_result);
				}
				else if (first == "rne") { // rename
					size_t index = t.find(' ');
					string src_temp = t.substr(0, index);
					string des_temp = t.substr(index + 1, t.length() - src_temp.length() - 1);

					rename(src_temp.c_str(), des_temp.c_str());
				}
				else if (first == "dlt") { // delete
					wstring des = s2ws(t);
					LPCWSTR des_result = des.c_str();
					DeleteFile(des_result);
				}
				else if (first == "cps") { // compress
					cout << t;
				}
				else if (first == "ext") { // extract
					cout << t;
				}
				else { // Check if type wrong command
					cout << "Something is going wrong with your command, Please try again.";
				}
				cout << endl;
			}
		}		
	}
	return 0;
}