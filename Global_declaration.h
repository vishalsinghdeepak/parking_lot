//
// Created by Vishal Singh on 20/06/19.
//

#ifndef GOJAK_GLOBAL_DECLARATION_H
#define GOJAK_GLOBAL_DECLARATION_H

#include <string>
#include <limits.h>
#include <map>
#include <queue>
typedef long long int ll;
using namespace::std;
struct Vehicle
{
    string registration_number;
    string color;
};
struct Parking_Slot
{
    ll slot_number;
    Vehicle vehicle_details;
};


enum Command_Types
{
    create_parking_lot=0,
    park=1,
    leave=2,
    status=3,
    registration_numbers_for_cars_with_colour=4,
    slot_numbers_for_cars_with_colour=5,
    slot_number_for_registration_number=6,
    Exit=7,
    invalid_commmad=INT_MAX

} global_command_type;



ll global_parking_size=0,global_slot_num;
ll slot_width=22, reg_num_width=20, color_width=10;
priority_queue <int, vector<int>, greater<int> > global_available_slots;
string global_command_name, global_color, global_registration_num;
Vehicle global_vehicle_obj;

map< ll, bool > slot_occupied;
map< ll, Vehicle > slot_to_vehicle_map;
map< string, vector< Parking_Slot > > color_to_parking_map;
map< string, ll> registration_num_to_slot_map;


#endif //GOJAK_GLOBAL_DECLARATION_H
