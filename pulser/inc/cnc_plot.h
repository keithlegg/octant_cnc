#ifndef CNC_PLOT_H    
#define CNC_PLOT_H

//#include <iostream>
//#include <math.h>

#include <vector>
using std::vector;  

//#include "math_op.h"
#include "Vectors.h"


class cnc_plot
{
    public:
        cnc_plot(){};
        ~cnc_plot(){};

    void gen_pules(std::vector<int>*, int, int);

    void gen_3d_pules(std::vector<Vector3>*, int, int);

    void calc_3d_pulses(std::vector<Vector3>*,
                        Vector3, 
                        Vector3,
                        int);


    //void load_config_file(char*);

};



#endif

