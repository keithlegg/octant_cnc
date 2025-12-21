
#include <iostream>
#include <cstring>
#include <functional>
#include <unistd.h>

#include "point_op.h"         
#include "cnc_globals.h"
#include "cnc_plot.h" 
#include "gl_setup.h" 
#include "octant.h" 


/************************/
// window properties and various globals 
// probably should relocate these 

char* obj_filepath;  


/************************/


 
int main(int argc, char **argv) 
{  
    /*------------------*/  
    if( argc == 2 ) {
        obj_filepath = argv[1] ;

        if( access( obj_filepath, F_OK ) != -1 ) {
            start_gui(&argc, argv); 
        } else {
            printf("# file %s does not exist.\n", obj_filepath);
            exit(0);
        }
    }


    /*------------------*/
    // test of limit switch reading 
    //cnc_plot plot;
    //vec3 foo;
    //plot.read_limits(&foo);

    return 0;
}

