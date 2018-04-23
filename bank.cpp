#include "simulate.h"
#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

int main (int argc, char* argv[] )
{
	//declare a simulate object
	simulate bank = simulate();

	//stream input file
	ifstream in (argv[1]);

	//check if file opened successfully
	if(!in.is_open())
	{
		cout << "The input file could not be opened." << endl;
	}
	else
	{
		ofstream out;
		out.open( argv[2]);
		double a_time;
		double t_time;
		while (in >> a_time >> t_time)
		{
			//arrivals are added from input file
			bank.add_arrival(a_time, t_time);
			//update eventList after adding the arrival
			bank.update();
		}

		while (!bank.bankLine.empty() || !bank.eventList.empty())
		{
			bank.update();
		}

		out << "t = 0: Simulation begins" << endl;
		
		//loop to print the result of the final list
		list<eventnode>::iterator list_iter;
		for (list_iter = bank.finalList.begin(); 
			list_iter != bank.finalList.end(); ++list_iter)
		{
			if ( (*list_iter).arrival = true)
			{
				out << "t = " << (*list_iter).arrival_time  << ": Arrival event" << endl;
			}
			else if ((*list_iter).arrival != true)
			{
				out << "t = " << (*list_iter).depart_time  << ": Departure event" << endl;
			}
		}

		out << "Total number of customers = " << bank.total_customers << endl;

		out << "Average amount of time in the bank = " << (bank.all_time )/ (bank.total_customers) <<
			" minutes" << endl;
		out << "Maximum amount of time in the bank = " << bank.max_time_spent <<
			" minutes" << endl;
		out << "Average amount of time waiting = " << (bank.all_time_wait )/ (bank.total_customers) <<
			" minutes" << endl;
		out << "Maximum amount of time waiting = " << bank.max_time_wait <<
			" minutes" << endl;
		out << "Maximum length of line = " << bank.max_line_length <<
			" customers" << endl;
	}
	return 0;
}
