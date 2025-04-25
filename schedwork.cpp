#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper(
    AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int> assigned,
    size_t day,
	size_t col
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    
    sched.assign(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID)); //initialize sched with invalid id
    vector<int> assigned(avail[0].size(), 0); //stores the number of shifts for each worker
    AvailabilityMatrix temp = avail;

    return schedHelper(temp, dailyNeed, maxShifts, sched, assigned, 0, 0);
}

bool schedHelper(
    AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int> assigned,
    size_t day,
	size_t col
)
{
    //return true when all days have been scheduled
	if(day == avail.size())
		return true;

    //loops throught each worker
	for(Worker_T i = 0; i < avail[0].size(); ++i){
		if(avail[day][i] == true && assigned[i] < maxShifts){ //runs if worker is available and does not exceed a certain number of shifts
			sched[day][col] = i; //assigns worker
			assigned[i]++; // adds 1 to the # of shifts that the worker now has
            bool temp;
			if(col + 1 == dailyNeed) 
				temp = schedHelper(avail, dailyNeed, maxShifts, sched, assigned, day + 1, 0); //move on to next day of daily need is met
			else
				temp = schedHelper(avail, dailyNeed, maxShifts, sched, assigned, day, col + 1); //move on to next column (another worker) if daily need is not met
            
            if(temp)
                return true;
            //backtrack
            assigned[i]--;
            sched[day][col] = INVALID_ID;
            
		}
	}
	return false;
}

