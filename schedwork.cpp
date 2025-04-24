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
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  vector<size_t> assignedShifts,
  DailySchedule& schedule,
  int currDay, // the current day
  int currSlot //number of slots in a day
);


// Add your implementation of schedule() and other helper functions here


//d =max maxShifts
//k = possible workers [numWorkers]
//d = needed workers
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
){
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


    int numDays = avail.size();
    int numWorkers = avail[0].size();
    sched.resize(numDays, vector<Worker_T> (dailyNeed, INVALID_ID));

    vector<size_t> assignedShifts(numWorkers,0);

    return schedHelper(avail, dailyNeed, maxShifts, assignedShifts, sched,0,0);

}


bool schedHelper(
  const AvailabilityMatrix& avail,
  const size_t dailyNeed,
  const size_t maxShifts,
  vector<size_t> assignedShifts,
  DailySchedule& schedule,
  int currDay, // the current day
  int currSlot //number of slots in a day
  ){

    int numDays = avail.size();
    int numWorkers= avail[0].size();

    if(currDay==numDays){
      return true;
      
    }

    if(currSlot == dailyNeed){ //filled all slots for the day, move to next
      return schedHelper(avail, dailyNeed, maxShifts, assignedShifts, schedule, currDay+1, 0);
    }

    //try to assign each worker to the current slot, need to check if they are also available
    for(Worker_T i =0; i<numWorkers;i++){
      if(assignedShifts[i]<maxShifts&&avail[currDay][i]){
        bool scheduled = false;
        for(int j = 0; j<currSlot;j++){
          if(schedule[currDay][j]==i){
            scheduled = true;
            break;
          }
        }


        //worker aviable/not scheduled, assign to the shift
        if(scheduled == false){
          assignedShifts[i]++;
          schedule[currDay][currSlot] = i;


          if(schedHelper(avail, dailyNeed, maxShifts, assignedShifts, schedule, currDay, currSlot+1)){
            return true;
          }



          schedule[currDay][currSlot] = INVALID_ID;
          assignedShifts[i]-=1;



        }


      }
    }

    //cannot assign
    return false;

}
