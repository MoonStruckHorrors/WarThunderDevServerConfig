/*
Program that edits config.blk in the War Thunder to use the dev server.

~Nikhil Vyas
~http://thenikhilvyas.com/
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
	fstream cfile, cnewfile;
	string path;
	string mod_block = "yunetwork{\n isExpertMode:b=yes\n curCircuit:t=\"dev\"\n}";
	cout << "Enter the installation directory/path." << endl;
	getline(cin, path);
	
	if(path[path.length() - 1] != '\\') {
		path.append("\\");
	}
	
	cfile.open(path + "config.blk", ios::in);
	
	if(!cfile) { //File not found.
		cout << "Not a valid installation directory/Couldn't find config.blk" << endl;
		cfile.close();
		return 1; //Sad Goodbye!
	}
	
	cout << endl << "Found config.blk.." << endl;
	
	cnewfile.open(path + "config_new.blk", ios::out);
	
	bool in_yu_block = false;
	
	while(cfile) {
		string temp;
		getline(cfile, temp);
		
		if(temp.find("yunetwork") != -1) {
			in_yu_block=true;
			cnewfile << mod_block << endl;
		}
		
		if(!in_yu_block) {
			cnewfile << temp << endl;
		}
		
		if(in_yu_block && temp.find("}") != -1) {
			in_yu_block = false;
		}
	}
	
	cout << endl << "Edited config.blk.." << endl;
	
	cfile.close();
	cnewfile.close();
	
	int result = 0;
	
	remove((path+"config_backup.blk").c_str());
	
	result = rename((path+"config.blk").c_str(), (path+"config_backup.blk").c_str());
	if(result == 0) {
		rename((path+"config_new.blk").c_str(), (path+"config.blk").c_str());
	} else {
		cout << "Something went wrong. No modifications have been perfromed" << endl;
		return 1;
	}
	
	cout << endl << "Operation performed successfully, Please launch the game from launcher.exe to download the update." << endl << endl <<
	"INFO: For switching back to production server(normal server), delete config.blk & rename config_backup.blk to config.blk" << endl;
	
	return 0;
}