#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <queue> //STL queue header file
#include <list> //STL list header file
using namespace std;
//customer node in the queue that represents a line at the bank
struct customer
{
double arrival_time; //arrival time of a customer
double trans_time; //transaction time required
};
//eventnode in the list that represents future events
struct eventnode
{
double arrival_time; //arrival time of customer
double trans_time; // transaction time for customer
double depart_time; //departure time, used only for departure events
bool arrival; // false if departure, true if arrival
};

//simulate class - used to represent the bank simulation

class simulate
{
public:
//queue used to represent the line at the bank - STL queue container
queue <customer> bankLine;
//the list used to represent future events - STL list
list <eventnode> eventList;
//this list is used to store the final list of events - STL list
list <eventnode> finalList;
//a variable used to represent the current time during simulation
double curTime;
//a counter variable used to count the total number of customers
double total_customers;
//a variable used to record the max line length
double max_line_length;
//a variable used to record the total time spent by all customers
double all_time;
//variable used to record total time spent waiting by all customers
double all_time_wait;
//variable used to record the total time elapsed
double event_time;
//variable used to record total number of customers who passed
double line_amt_total;
//variable used to record maximum wait time
double max_time_wait;
//variable used to record maximum time spent in the bank
double max_time_spent;
//default constructor
simulate();
//destructor
~simulate();
//this function adds an arrival event into the eventlist
void add_arrival(double arrival_time, double trans_time);
//function which updates the line and the event_list – places
//departure events into the event list, as well as many other
//functions
void update();
//function used to calculate the time elapsed after eventlist is empty
void count_events();
};