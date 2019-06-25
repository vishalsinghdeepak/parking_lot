//
// Created by Vishal Singh on 20/06/19.
//

#ifndef GOJAK_CONSOLE_MODE_H
#define GOJAK_CONSOLE_MODE_H

#include <iostream>
#include "Global_declaration.h"
#include "Command_function.h"
#include "Formatting.h"
void Console_Mode()
{
    while (!cin.eof())
    {
        global_command_name=input_string();
        Identify_Command_Type();
	if(global_command_type!=invalid_commmad) {
        if(global_command_type==Exit)
            break;

        if(global_parking_size==0 && global_command_type!=create_parking_lot)
        {
            cout<<"No Parking created. Please create the parking first"<<endl;
            continue;
        }
	}


        //Reading required inputs for the command types
        switch(global_command_type)
        {
            case create_parking_lot:
            {
                cin>>global_parking_size;
                break;
            }
            case park:
            {
                global_vehicle_obj.registration_number=input_string();
                global_vehicle_obj.color=input_string();
                break;
            }
            case leave:
            {
                cin>>global_slot_num;
                break;
            }
            case registration_numbers_for_cars_with_colour:
            {
                global_color=input_string();
                break;
            }
            case slot_numbers_for_cars_with_colour:
            {
                global_color=input_string();
                break;
            }
            case slot_number_for_registration_number:
            {
                global_registration_num=input_string();
                break;
            }
            default:
                break;
        }

        Process_Read_Command();

    }
}

#endif //GOJAK_CONSOLE_MODE_H
