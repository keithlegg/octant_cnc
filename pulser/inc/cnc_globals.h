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

        char parport1_addr[10];
        char parport2_addr[10];
        // char parport3_addr[10];
        // char parport4_addr[10];

        //----------
        void load_file( char*);
        void show( void );
        

};



#endif

