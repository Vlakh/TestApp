#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace System::IO;
using namespace std;

// function for creating files with some information
void create () {
	int qfiles, i;
	ostringstream path, text;
	cout <<"Number of files: " <<endl;
	cin >> qfiles;
	for ( i = 1; i <= qfiles; ++i ){
		path <<"files\\" <<i<<".vvv"; // path to text files of format "*.vvv"
		text <<rand()<<"=ID"<<" encoded message, space and other things..."<<endl; // text with random ID and other things
		ofstream fout(path.str());  // open file
		fout << text.str(); //input info
		fout.close(); 
		path.str("");
		text.str("");
	}
}

// function for sorting lines by ID into new file 
void Sort(int* n, string* s, int count) {
	for(int i=0; i<count; ++i)  // sort data using bubble method
		for(int j=i+1; j<count; ++j)
		  if(n[j]<n[i]) {
			  swap(n[i],n[j]); 
			  swap(s[i],s[j]); // swap items in array
		  };
    cout << "Our new file with sorted lines :)" << endl;   
    string path;
	path = "files\\complete.vvv"; // create a new file
	ofstream fout(path);
	for(int i=0; i<count; ++i){
		fout << s[i] << endl; // record into the file
		cout << s[i] << endl; // show in the window
	}
    fout.close();
} 

void Files() {

   string path, num;
   array<String^>^ file = System::IO::Directory::GetFiles( "files\\" ); // array with files which are in our folder
   string *str =new string [file->Length]; // array with strings
   int *n = new int [file->Length]; // array withs numbers
   for (int i=0; i<file->Length; i++) {
	   path = (char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(file[i])).ToPointer(); // path to files (convert from System::String^ to std::string)
	   ifstream fout(path); // open our files
	   getline(fout,str[i]); // get line from file
	   fout.close();
	   num = str[i]; // "num" is a temporary variable for getting number from string
	   for (int j=0; j<num.length(); j++) {
		   if (num[j] == '=' ) 
			   num[j] = '\0'; // erase string to number
	   }
       n[i] = atoi(num.c_str()); // record to array with numbers
   }
   Sort(n, str, file->Length); // sorting
   delete [] str; // delete arrays
   delete [] n;
   
}


int _tmain(int argc, _TCHAR* argv[])
{
	create(); // create files
	Files(); // work with them
	system("pause");
	return 0;
}

