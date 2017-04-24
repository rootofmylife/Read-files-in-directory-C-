#include <iostream>
#include <io.h>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

// List files				<- DONE
// Search by name			<- PROCESSING
//			 size
//			 date
// Create
// Copy
// Move
// Delete
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
					std::cerr << exc.what();
				}
				cout << t << endl;
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
				else if (first == "whr") {// find
					cout << t;
				}
				else if (first == "dup") { // copy
					cout << t;
				}
				else if (first == "crt") { // create
					cout << t;
				}
				else if (first == "shf") { // move
					cout << t;
				}
				else if (first == "rne") { // rename
					cout << t;
				}
				else if (first == "dlt") { // delete
					cout << t;
				}
				else if (first == "cps") { // compress
					cout << t;
				}
				else if (first == "ext") { // extract
					cout << t;
				}
				else { // Check if type wrong command
					cout << "Somthing is going wrong with your command, Please try again.";
				}
				cout << endl;
			}
		}


	}
	return 0;
}