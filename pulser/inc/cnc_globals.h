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

        void load_file( char*);
        void show( void );
        

};



#endif

