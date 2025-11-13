#ifndef CNC_IO_H    
#define CNC_IO_H

//#include <iostream>
//#include <math.h>

#include <vector>
using std::vector; //point_op did not make me do this!!?? WHY?

#include "math_op.h"


class cnc_io
{
    public:
         cnc_io(){};
        ~cnc_io(){};

    void test_port(void);

    void aux_on(unsigned int);
    void aux_off(unsigned int);
    void send_pulses(vector<vec3>*);
    void read_limits(vec3*);

};



#endif

