// LoftwarePrintMod.cpp
// Written by Peter Melko
// 1 December 2011
/*-----------------------------------------------------------------------------
   The program will take input from WMS a file that contains the 
   Loftware instructions to print a pick order. The program will
   parse out multiple orders to create separate print jobs.
   
   The output files are names after the input file with a letter appended
   after the filename. Currently the program supports up to 27 (A-Z) parsed
   files.
   
   The parser finds the line "LP_PAGE_NO,x of y" and if x == y, then the
   parser advances 5 more lines and closes the output file in the directory:
   \\xxxx\loftware$\WDDrop where is it then handled by Loftware.
   
   Once the input file reaches end of file, the file is closed and deleted.
-----------------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <istream>
#include <string>
#include <cstdio>

using namespace std;

string getFile(string in);
//Pre:  The input directory is known.
//Post: Returns the filename to be checked.

string makeFile(string out, string file, int count);
//Pre:  The output directory is known.
//Post: Returns the output file appended to the directory.

void main()
{
	string fname, ofname, findfile, filename, line, cut;
	string inDir, outDir;
	int count = 65, i = 0;
	ifstream infile;
	ofstream outfile;
	
	outDir = "\\\\xxxx\\loftware$\\WDDrop\\"; // Location where Loftware picks up files.
	//outDir = "C:\\Loftware-test\\"; //Debug location
	//fname = "201112021134340000_LPS001.PAS" //Debug case
	inDir = "C:\\Loftware-test\\TestDirScan\\";
	filename = getFile(inDir);
	fname = inDir + filename;
	
	infile.open(fname);		// open infile
	if(infile.fail())
	{
		cout<<"Could not open the file."<<endl;
		getchar();
		exit(1);
	}
	
	getline(infile,line);
	if(line == "*FORMAT,CompSalesPickLst.lwl")	// Is it a pick ticket?
	{
		cout<<"This is a Pick List"<<endl;
		ofname = makeFile(outDir, filename, count);
		outfile.open(ofname);
		outfile<<line<<endl;
		
		while(!infile.eof())  
		{
			getline(infile, line);  
			outfile<<line<<endl;
			cut = line.substr(0,11); // Generate cut to check for end of page
			if(cut.compare("LP_PAGE_NO") == 0) // Found end of page marker
			{
				if(line.at(11) == line.at(16))
				{
					for(int j=0; j<4;j++)  // When end of pick ticket, read next 5 lines.
					{
						getline(infile,line);
						outfile<<line<<endl;
					}
					outfile.close();
					count++;
					ofname = makefile(outDir, filename, count); // Creates next filename and opens it
					outfile.open(ofname);
				}
			}
		}
		outfile.close();
		infile.close();
		remove(fname.c_str());	// Deletes the input file
	}
	else
	{
		infile.close();
		count++;
		cout<<endl<<"Not a Pick List!"<<endl;
		ofname = outDir + filename;
		outfile.close();
		remove(fname.c_str());
	}
	
	cout<<"END"<<endl;
	i++;
	return;
}
//-----------------------------------------------
string getFile(string in)
//Pre:  The input directory is known.
//Post: Returns the filename to be checked.
{
	string file, findfile;
	HANDLE h;
	WIN32_FIND_DATA info;
	
	do{
		findfile = in + "*.pas";
		cout<<"findfile= "<<findfile<<endl;
		h = FindFirstFile(findfile.c_str(),&info); // built-in function
		file = info.cFileName;
		cout<<"file= "<<file<<endl;
	}while(file == in);

	return file;
}
//-----------------------------------------------
string makeFile(string out, string file, int count)
//Pre:  The output directory is known.
//Post: Returns the output file appended to the directory.
{
	string output, ct;
	int length = 0;
	char a;

	output = out + file;
	cout<<"output= "<<endl;
	length = output.length();
	a = static_cast<char> (count);
	ct = a;
	output.insert(length - 4, ct);
	
	return output;
}
