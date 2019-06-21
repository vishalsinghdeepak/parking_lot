//
// Created by Vishal Singh on 20/06/19.
//

//The below function are the main driver functions of the program
#ifndef GOJAK_COMMAND_FUNCTION_H
#define GOJAK_COMMAND_FUNCTION_H


#include <iostream>
#include <iomanip>
#include "Global_declaration.h"
using namespace::std;


//function to park the vehicle
ll Park_Vehicle(Vehicle vehicle_obj)
{
    ll slot_number;
    if(global_available_slots.empty())
        slot_number=-1;
    else
    {
        slot_number=global_available_slots.top();
        global_available_slots.pop();



        //creating parking slot obj
        Parking_Slot parking_slot_obj;
        parking_slot_obj.slot_number=slot_number;
        parking_slot_obj.vehicle_details=vehicle_obj;

        //filling the parking data
        slot_occupied[slot_number]=true;
        slot_to_vehicle_map[slot_number]=vehicle_obj;
        registration_num_to_slot_map[vehicle_obj.registration_number]=slot_number;
        color_to_parking_map[vehicle_obj.color].push_back(parking_slot_obj);

    }
    return slot_number;
}

//function to exit the vehicle
ll Clear_Slot(ll slot_num)
{

    if(!(slot_num >=1 && slot_num<=global_parking_size))
        return -1;
    if(slot_occupied[slot_num]==false)
        return 0;



    Vehicle vehicle_obj=slot_to_vehicle_map[slot_num];

    string color=vehicle_obj.color;
    string reg_num=vehicle_obj.registration_number;

    slot_occupied[slot_num]=false;
    slot_to_vehicle_map.erase(slot_num);
    registration_num_to_slot_map[reg_num]=0;

    vector< Parking_Slot > spots_with_same_color = color_to_parking_map[color];

    ll position=-1;
    for(ll i=0;i<spots_with_same_color.size();i++)
    {
        Parking_Slot parking_obj=spots_with_same_color[i];

        if(parking_obj.slot_number == slot_num)
        {
            position=i;
            break;
        }

    }

    if(position!=-1)
    {
        spots_with_same_color.erase(spots_with_same_color.begin() + position );
        color_to_parking_map[color]=spots_with_same_color;
    }
    global_available_slots.push(slot_num);

    return slot_num;
}

void Print_Status()
{
    const char separator    = ' ';
    cout << left << setw(slot_width) << setfill(separator) << "Slot No. ";
    cout << left << setw(reg_num_width) << setfill(separator) << "Registration No";
    cout << left << setw(color_width) << setfill(separator) << "Color";
    cout<<endl;

    for(ll slot=1;slot<=global_parking_size;slot++)
    {
        if(slot_occupied[slot])
        {
            Vehicle vehicle_obj=slot_to_vehicle_map[slot];
            string reg_num=vehicle_obj.registration_number;
            string color=vehicle_obj.color;
            cout << left << setw(slot_width) << setfill(separator) << slot;
            cout << left << setw(reg_num_width) << setfill(separator) << reg_num;
            cout << left << setw(color_width) << setfill(separator) <<color;
            cout<<endl;
        }
    }

}

void Print_Reg_With_Same_Col(string col)
{
    vector< Parking_Slot > parking_slots=color_to_parking_map[col];

    if(parking_slots.size()==0)
        cout<<"No vehicles parked with the given color"<<endl;
    else
    {
        cout<<parking_slots[0].vehicle_details.registration_number;
        for(ll i=1;i<parking_slots.size();i++)
        {
            cout<<", ";
            cout<<parking_slots[i].vehicle_details.registration_number;
        }
        cout<<endl;
    }
}
void Print_Slot_With_Same_Col(string col)
{
    vector< Parking_Slot > parking_slots=color_to_parking_map[col];

    if(parking_slots.size()==0)
        cout<<"No vehicles parked with the given color"<<endl;
    else
    {
        cout<<parking_slots[0].slot_number;
        for(ll i=1;i<parking_slots.size();i++)
        {
            cout<<", ";
            cout<<parking_slots[i].slot_number;
        }
        cout<<endl;
    }
}


void Print_Slot_With_Reg_Num(string reg_num)
{
    ll slot_num=registration_num_to_slot_map[reg_num];
    if(slot_num==0)
        cout<<"Not found"<<endl;
    else
        cout<<slot_num<<endl;

}


void Identify_Command_Type()
{
    if(global_command_name.compare("create_parking_lot")==0)
        global_command_type=create_parking_lot;
    else if(global_command_name.compare("park")==0)
        global_command_type=park;
    else if(global_command_name.compare("leave")==0)
        global_command_type=leave;
    else if(global_command_name.compare("status")==0)
        global_command_type=status;
    else if(global_command_name.compare("registration_numbers_for_cars_with_colour")==0)
        global_command_type=registration_numbers_for_cars_with_colour;
    else if(global_command_name.compare("slot_numbers_for_cars_with_colour")==0)
        global_command_type=slot_numbers_for_cars_with_colour;
    else if(global_command_name.compare("slot_number_for_registration_number")==0)
        global_command_type=slot_number_for_registration_number;
    else if(global_command_name.compare("exit")==0)
        global_command_type=Exit;
    else
        global_command_type=invalid_commmad;

}

// pocessing the command entered by the user
void Process_Read_Command()
{
    switch (global_command_type)
    {
        case create_parking_lot:
        {
            if(global_parking_size>0)
            {
                //clearing the priority queue
                global_available_slots=priority_queue <int, vector<int>, greater<int> >();

                //adding slots
                for(ll i=1;i<=global_parking_size;i++)
                {
                    global_available_slots.push(i);
                    slot_occupied[i]=false;

                }

                cout<<"Created a parking lot with "<<global_parking_size<<" slots"<<endl;
            }
            else
            {
                cout<<"Invalid parking size"<<endl;
            }
            break;
        }
        case park:
        {
            reg_num_width=max(reg_num_width,(ll)global_vehicle_obj.registration_number.length()+1);
            color_width=max(color_width, (ll)global_vehicle_obj.color.length()+1);

            ll slot_num_parked=Park_Vehicle(global_vehicle_obj);
            if(slot_num_parked==-1)
                cout<<"Sorry, parking lot is full"<<endl;
            else
                cout<<"Allocated slot number: "<<slot_num_parked<<endl;
            break;
        }
        case leave:
        {
            ll slot_num_cleared=Clear_Slot(global_slot_num);
            if(slot_num_cleared==-1)
                cout<<"Invalid slot number"<<endl;
            else if(slot_num_cleared==0)
                cout<<"Slot number is already free"<<endl;
            else
                cout<<"Slot number "<<slot_num_cleared<<" is free"<<endl;

            break;
        }
        case status:
        {
            Print_Status();
            break;
        }
        case registration_numbers_for_cars_with_colour:
        {
            Print_Reg_With_Same_Col(global_color);
            break;
        }
        case slot_numbers_for_cars_with_colour:
        {
            Print_Slot_With_Same_Col(global_color);
            break;
        }
        case slot_number_for_registration_number:
        {
            Print_Slot_With_Reg_Num(global_registration_num);
            break;
        }
        default:
        {
            cout<<"Invalid command"<<endl;
            break;
        }

    }

}

#endif //GOJAK_COMMAND_FUNCTION_H
