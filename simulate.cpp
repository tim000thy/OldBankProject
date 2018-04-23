#include "simulate.h"

using namespace std;

//adds arrival event to event list
void simulate:: add_arrival(double arrival_time, double trans_time)
{
	while (eventList.size() > 1)
	{
		update();
	}

	//create new eventList node
	eventnode *x = new eventnode;
	(*x).arrival_time = arrival_time;
	(*x).trans_time = trans_time;
	(*x).arrival = true;
	total_customers++;

	if (eventList.empty())
	{
		eventList.push_front(*x);
	}
	else if ( !eventList.empty())
	{
		eventnode *temp = &eventList.front();

		if ((*x).arrival_time < (*temp).depart_time)
		{
			eventList.push_front(*x);
		}

		else if ((*x).arrival_time > (*temp).depart_time)
		{
			eventList.push_back(*x);
		}

		else if ((*x).arrival_time == (*temp).depart_time)
		{
			update();
			eventList.push_front(*x);
		}
	}
}

void simulate::update()
{
	//current event is the first event in eventlist
	eventnode *curEvent = &eventList.front();

	if ((*curEvent).arrival)
	{
		//set current time to arrival time and adds customer to line
		curTime = (*curEvent).arrival_time;
		customer *newCustomer = new customer;
		(*newCustomer).arrival_time = (*curEvent).arrival_time;
		(*newCustomer).trans_time = (*curEvent).trans_time;
		bankLine.push(*newCustomer);
		line_amt_total++;


		if (bankLine.size() > max_line_length)
		{
			max_line_length = bankLine.size();
		}

		//remove curEvent from event list
		eventList.pop_front();
		finalList.push_back(*curEvent);

		//if there is only 1 person in line, a departure is added
		// in the correct position
		if (bankLine.size() == 1)
		{
			customer curCustomer = bankLine.front();
			eventnode *d = new eventnode;
			(*d).arrival_time = curCustomer.arrival_time;
			(*d).trans_time = curCustomer.trans_time;
			(*d).depart_time = curTime + curCustomer.trans_time;
			(*d).arrival = false;
			double time_spent = ( (*d).depart_time - (*d).arrival_time);
			double time_wait = time_spent - (*d).trans_time;
			all_time_wait = all_time_wait + time_wait;
			all_time = all_time + time_spent;

			if ( time_spent > max_time_spent)
			{
				max_time_spent = time_spent;
			}

			if ( time_wait > max_time_wait)
			{
				max_time_wait = time_wait;
			}


			eventnode *temp = &eventList.front();
			if ((*d).arrival_time < (*temp).depart_time)
			{
				eventList.push_front(*d);
			}

			else if ((*d).arrival_time > (*temp).depart_time)
			{
				eventList.push_back(*d);
			}
		}
	}

	if (!(*curEvent).arrival)
	{
		//set current time to departure time
		//pop customer from bankline and evenList
		//pushes current event onto final list
		curTime = (*curEvent).depart_time;
		bankLine.pop();
		eventList.pop_front();
		finalList.push_back(*curEvent);


		if (bankLine.size() > 0)
		{
			//adds a departure event at the correct position
			customer curCustomer = bankLine.front();
			eventnode *d = new eventnode;
			(*d).arrival_time = curCustomer.arrival_time;
			(*d).trans_time = curCustomer.trans_time;
			(*d).depart_time = curTime + curCustomer.trans_time;
			(*d).arrival = false;

			double time_spent = ( (*d).depart_time - (*d).arrival_time);
			double time_wait = time_spent - (*d).trans_time;
			all_time_wait = all_time_wait + time_wait;
			all_time = all_time + time_spent;

			if ( time_spent > max_time_spent)
			{
				max_time_spent = time_spent;
			}

			if ( time_wait > max_time_wait)
			{
				max_time_wait = time_wait;
			}


			eventnode *temp = &eventList.front();
			if ((*d).arrival_time < (*temp).depart_time)
			{
				eventList.push_front(*d);
			}

			else if ((*d).arrival_time > (*temp).depart_time)
			{
				eventList.push_back(*d);
			}
		}
	}
}

simulate:: simulate()
{
	bankLine;
	eventList;
	finalList;
	curTime = 0;
	total_customers = 0;
	max_line_length = 0;
	all_time = 0;
}

simulate:: ~simulate()
{
	eventList.clear();
	finalList.clear();
	while (!bankLine.empty())
	{
		bankLine.pop();
	}

	curTime, total_customers = NULL;

}


