/*****************************************************************************/
/* 
    timer.cpp

    

    modified - 2025 Keith Legg - keithlegg23@gmail.com

    AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
    Copyright (C) 2005 Song Ho Ahn

    MIT License


    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.


*/
         

/*****************************************************************************/



#include <chrono>
#include <iostream>


#include "timer.h"

double trav_speed ; //linear unit per sec 


/***************************************/
//void timer::reset_sim(void)


/***************************************/
//step/reset gets called once every "tick" between 0-1 
void timer::step_sim(void)
{
    sim_time_us = 0;
}

/***************************************/
void timer::start()
{
    stopped = 0; // reset stop flag
    running = true;
    gettimeofday(&startCount, NULL);

}


/***************************************/
//void timer::pause()

/***************************************/
void timer::stop()
{
    stopped = 1; // set timer stopped flag
    running = false;

    gettimeofday(&endCount, NULL);

}


/***************************************/
double timer::getElapsedTimeInMicroSec()
{

    if(!stopped)
        gettimeofday(&endCount, NULL);

    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
    endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;

    //keith added this for a resetable "time" var 
    sim_time_us = sim_time_us+10000;
 

    return endTimeInMicroSec - startTimeInMicroSec;
}

/***************************************/ 
double timer::get_elapsed_simtime_ms()
{
    this->getElapsedTimeInMicroSec();
    return this->sim_time_us * 0.001;
}

/***************************************/
double timer::get_elapsed_simtime_sec()
{
    this->getElapsedTimeInMicroSec();
    return this->sim_time_us * 0.000001;
}


/***************************************/
double timer::getElapsedTimeInMilliSec()
{
    return this->getElapsedTimeInMicroSec() * 0.001;
}

/***************************************/
double timer::getElapsedTimeInSec()
{
    return this->getElapsedTimeInMicroSec() * 0.000001;
}

/***************************************/
double timer::get_elapsed_simtime()
{
    return this->get_elapsed_simtime_sec();
}

/***************************************/
double timer::getElapsedTime()
{
    return this->getElapsedTimeInSec();
}







