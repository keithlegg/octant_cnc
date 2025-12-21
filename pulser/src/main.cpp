
#include <iostream>
#include <cstring>
#include <functional>
#include <unistd.h>

#include "point_op.h"         
#include "cnc_globals.h"
#include "cnc_plot.h" 
#include "gl_setup.h" 
#include "octant.h" 



// window properties
int window_id;      // ID if GLUT window 
int scr_size_x      = 512;
int scr_size_y      = 512;
bool scr_full_toglr = true;
char* obj_filepath;  

GLuint texture[3]; // storage for textures






 
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
    // parse_args(cg, argc, argv); 
    // if(sizeof(argv[1]) == sizeof(char *))
    //    std::cout << "empty " << argc << "\n";

    /*------------------*/
    // test of limit switch reading 
    //cnc_plot plot;
    //vec3 foo;
    //plot.read_limits(&foo);
    
    /*------------------*/
    //self contained openGL example to mess with 
    //spinningCubeDemo(&argc, argv);


    return 0;
}

