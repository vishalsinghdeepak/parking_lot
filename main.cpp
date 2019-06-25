#include <iostream>
#include "File_mode.h"
#include "Console_mode.h"
using namespace std;
typedef long long int ll;

int main(int argc, char** argv) {
    if(argc>1)
    {
        string filename(argv[1]);
        //cout<<"Reading from file "<<filename<<endl;
        File_Mode(filename);
    }
    else
    {
        //cout<<"Console mode ON"<<endl;

        Console_Mode();
    }
    return 0;
}
