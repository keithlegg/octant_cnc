#ifndef CNC_IO_H    
#define CNC_IO_H

//#include <iostream>
//#include <math.h>

#include <vector>
using std::vector; //point_op did not make me do this!!?? WHY?

//#include "math_op.h"

#include "cnc_globals.h"


//define the way that pins get assigned in the parports 
class cnc_bitmasks
{

    public:
         cnc_bitmasks(){};
        ~cnc_bitmasks(){};

};


/**************************/

//handle the IO to the parports 
class cnc_io
{
    public:
         cnc_io(){};
        ~cnc_io(){};

    void test_port(cncglobals*);

    void aux_on(cncglobals*, unsigned int);
    void aux_off(cncglobals*, unsigned int);

    void send_pulses(cncglobals*, vector<Vector3>*);
    void read_limits(cncglobals*, Vector3*);

};



#endif

