/*************************************************************
FILE DESCIPTION:
This program reads data file 'students.scv', 
sorts its sontent, and writes sorted data into 
output file 'students-graded.csv'.

compile:   c++ -std=c++11 grade-scores.cpp -o grade-scores.exe
run:       ./grade-scores.exe students.csv
**************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <algorithm>
#include <strings.h>
#include <stdexcept>
using namespace std;

/* This function reads from students.csv, 
and stores the data as 2D array of strings */
vector <vector <string>> read_from_file(ifstream &infile, string name){
    vector <vector <string>> x;     // x = data[][] - elements of 2D array of strings.
    if (!infile)
    throw runtime_error("Could not open file to read. Check correct spelling - students.csv");
    
    while (infile)                  
    {
        string s;
        if (!getline( infile, s )) break;

        istringstream ss( s );
        vector <string> record;

        while (ss)
        {
            string s;
        if (!getline( ss, s, ',' )) break;
            record.push_back( s );
        }

        x.push_back( record );
    }
    return x;                       // x = data[][] - data to pass.
}

/* This function takes stored data and sorts it by Grade column, 
and then by Name column if necessary */
vector <vector <string>> sort_grades(vector <vector <string>> y){
    string Name, Surname, Grade;                    // Columns in data file
    for(int i=0;i<y.size()-1;i++)
    {
        for(int j=0; j<y.size()-i-1; j++)
        {
            if (y[j+1][2].compare(y[j][2]) > 0)     // sort by descending Grade
            {
                Grade = y[j][2];
                y[j][2] = y[j+1][2];
                y[j+1][2] = Grade;
                Surname = y[j][1];
                y[j][1] = y[j+1][1];
                y[j+1][1] = Surname;
                Name = y[j][0];
                y[j][0] = y[j+1][0];
                y[j+1][0] = Name;
            }
            else if(y[j+1][2].compare(y[j][2]) == 0)
            {
                if(y[j+1][0].compare(y[j][0]) < 0)  // sort by ascending Name
                {
                    Grade = y[j][2];
                    y[j][2] = y[j+1][2];
                    y[j+1][2] = Grade;
                    Surname = y[j][1];
                    y[j][1] = y[j+1][1];
                    y[j+1][1] = Surname;
                    Name = y[j][0];
                    y[j][0] = y[j+1][0];
                    y[j+1][0] = Name;
                }
            }
        }
    }
    return y;                       // y = Sorted 2D array of strings to pass
}

/* This procedure takes sorted 2D data and writes 
it appropriately into output file students-graded.csv */
void writo_to_file(ofstream &outfile, vector <vector <string>> z){
    for(int i=0; i<z.size(); i++)
        outfile << z[i][1] <<", "<<z[i][0]<<", "<<z[i][2]<<endl;  // z = defferent elements of sorted 2D array for writing
}


int main(int argc, char *argv[])
{
  vector <vector <string> > data, sdata;
  string fileName = argv[1];
  ifstream infile( fileName );
  string outfile_path = "./students-graded.csv";    // can be relative or absolute path
  ofstream outfile(outfile_path);
  if (!argv[1]){
        printf("Type name of the input data file after executable. Hint - students.csv");
        exit(0);
    }

data = read_from_file(infile, fileName);
infile.close();

/****** QUICK OUTPUT FOR SNAPSHOT *****************************/
cout<<endl;

for(int i=0; i<data.size(); i++)
        cout << data[i][0] <<", "<<data[i][1]<<", "<<data[i][2]<<endl;

cout<<"\nOriginal data above\n"<<endl;
/**************************************************************/

sdata = sort_grades(data);

/****** QUICK OUTPUT FOR SNAPSHOT *****************************/
cout<<"\nSorted data below\n"<<endl;
for(int i=0; i<sdata.size(); i++)
        cout << sdata[i][1] <<", "<<sdata[i][0]<<", "<<sdata[i][2]<<endl;
/**************************************************************/

try{
    writo_to_file(outfile, sdata);
    outfile.close();
}
catch(std::ofstream::failure &writeErr) {
    std::cerr << "\nProblem occured when writing to a file\n"
         << writeErr.what()
         << std::endl;
    return -1;
}


return 0;
}
