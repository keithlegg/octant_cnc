#ifndef CNC_PLOT_H    
#define CNC_PLOT_H

#include <vector>
using std::vector;  


#include "Vectors.h"


class cnc_plot
{
    public:
        cnc_plot(){};
        ~cnc_plot(){};



    void calc_precache(vector<Vector3>* pt_disppathcache, 
                                  Vector3 fr_pt, 
                                  Vector3 to_pt,
                                  int numdivs);


    void gen_pules(std::vector<int>*, int, int);
    
    void calc_3d_pulses(std::vector<Vector3>*,
                        Vector3, 
                        Vector3,
                        int);


    //void gen_3d_pules(std::vector<Vector3>*, int, int);
 

};



#endif

