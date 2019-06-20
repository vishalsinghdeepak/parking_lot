//
// Created by Vishal Singh on 20/06/19.
//
//The below functions have been used to bolster the File mode
#ifndef GOJAK_FILE_MODE_H
#define GOJAK_FILE_MODE_H

#include "Global_declaration.h"
#include "Command_function.h"
#include "Formatting.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace::std;


bool Is_File_Good(const std::string& filename)
{
    std::ifstream source;
    source.open(filename);
    if (source.is_open() && source.good()) {
        return true;
    }
    else
    {
        return false;
    }
}


bool Process_File_Read_Request(vector< string > params)
{

    global_command_name=format_string(params[0]);

    Identify_Command_Type();

    if(global_command_type==Exit)
        return false;
    if(global_parking_size==0 && global_command_type!=create_parking_lot)
    {
        cout<<"No Parking created. Please create the parking first"<<endl;
        return true;
    }

    bool invalid_params=false;
    //Reading required inputs for the command types
    switch(global_command_type)
    {
        case create_parking_lot:
        {
            global_parking_size=convert_to_number(format_string(params[1]));
            if(global_parking_size==-1)
                invalid_params=true;
            break;
        }
        case park:
        {
            global_vehicle_obj.registration_number=format_string(params[1]);
            global_vehicle_obj.color=format_string(params[2]);
            break;
        }
        case leave:
        {
            global_slot_num=convert_to_number(format_string(params[1]));
            if(global_slot_num==-1)
                invalid_params=true;
            break;
        }
        case registration_numbers_for_cars_with_colour:
        {
            global_color=format_string(params[1]);
            break;
        }
        case slot_numbers_for_cars_with_colour:
        {
            global_color=format_string(params[1]);
            break;
        }
        case slot_number_for_registration_number:
        {
            global_registration_num=format_string(params[1]);
            break;
        }
        default:
            break;
    }

    if(!invalid_params)
        Process_Read_Command();
    return true;

}




void File_Mode(string filename)
{
    if(!Is_File_Good(filename))
    {
        cout << "Failed to open file "<<filename;
        return;
    }

    //Reading File
    std::ifstream source;
    source.open(filename);
    std::string line;

    while (std::getline(source, line))
    {
        //cout<<line<<endl;
        vector< string > params;
        stringstream ss(line);

        // Traverse through all words
        do {
            // Read a word
            string word;
            ss >> word;

            // Add the read word
            params.push_back(word);
            // While there is more to read
        } while (ss);


        if(!Process_File_Read_Request(params))
            return;

    }

}

#endif //GOJAK_FILE_MODE_H
