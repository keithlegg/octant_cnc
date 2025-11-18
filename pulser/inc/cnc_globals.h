#ifndef CNC_GLOBALS_H    
#define CNC_GLOBALS_H

//#include <iostream>
//#include <math.h>

#include <vector>

//using std::vector; 



class cncglobals
{

    public: 
        cncglobals(){
        };

        ~cncglobals(){};
        //----------

        //DEBUG needs to be 16 bit int 
        char parport1_addr[10];
        char parport2_addr[10];
        // char parport3_addr[10];
        // char parport4_addr[10];
        // uint parport1_addr;
        // uint parport2_addr;

        //machine travel size in 3D 
        uint x_xtntx;
        uint y_xtntx;
        uint z_xtntx;

        //waveform generation parameters
        uint pp1_pulse_x_dly_us;
        uint pp1_pulse_y_dly_us;
        uint pp1_pulse_z_dly_us;

        //3d pulses per linear unit 
        uint pp1lu_x;
        uint pp1lu_y;
        uint pp1lu_z;

        //pin assignments
        uint parprt1_dir_x;
        uint parprt1_step_x;  
        
        uint parprt1_dir_y;
        uint parprt1_step_y;  
        
        uint parprt1_dir_z;
        uint parprt1_step_z;
        
        uint parprt1_dir_a;
        uint parprt1_step_a;    
        
        uint x_limit_pin;
        uint y_limit_pin;
        uint z_limit_pin;

        //----------
        void load_file( char*);
        void show( void );
        

};




#endif



