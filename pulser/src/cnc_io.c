

#include <stdio.h>
#include <unistd.h> //sleep()
#include <sys/io.h> //outb() ioperm()
#include <stdlib.h>
#include <math.h>
#include <iomanip>

#include <iostream>
#include <algorithm>
#include <vector>

#include "math_op.h"
#include "point_op.h"

#include "cnc_plot.h"
#include "cnc_io.h"



// µs (microsecond) duration between pulses 
// gecko docs say minimun pulse with is 2.5µs per pulse - seems way too fast for me 
int pulse_del = 1000;
#define LPT1 0xc010
//#define LPT1 0x0378


#define HEX(x) setw(2) << setfill('0') << hex << (int)( x )



/******************************************/
void cnc_io::aux_on(unsigned int pin)
{
    if(ioperm(LPT1,1,1))
    { 
        fprintf(stderr, "# Couldn't open parallel port \n"), exit(1);
    
    }

    unsigned char data_read;
    data_read = inb(LPT1);
    data_read = data_read |= (1 << pin);
    outb(data_read, LPT1);            


}



/******************************************/
void cnc_io::aux_off(unsigned int pin)
{
    if(ioperm(LPT1,1,1))
    { 
        fprintf(stderr, "# Couldn't open parallel port \n"), exit(1);
    
    }

    unsigned char data_read;
    data_read = inb(LPT1);
    data_read = data_read &= ~(1 << pin);
    outb(data_read, LPT1);    

}



/******************************************/

void cnc_io::test_port(void)
{
    if(ioperm(LPT1,1,1))
    { 
        fprintf(stderr, "# Couldn't open parallel port \n"), exit(1);
    
    }

    unsigned char send_byte = 0x00;
    int a=0;int b=0;

    outb(0x00,LPT1); 
    //for(b=0;b<4;b++)
    //{
        send_byte = 0x01;
        for(a<0;a<8;a++)
        {
            outb(send_byte,LPT1);
            usleep(500000); 
                       
            outb(0x00,LPT1); 
            usleep(500000); 
            send_byte = send_byte << 1;
            cout <<"bit "<< a <<" value: "<< HEX(send_byte) <<"\n";

        }
    //}

}




/******************************************/
/*
       Read the parallel port inputs to make sure we didnt crash the machine 

       Data State: 

       All pins pulled down  == 0x80 - 10000000
       ACK       - pin 10 - 0xc0     - 11000000
       BUSY      - pin 11 - 0x0      - 00000000 (active high)
       PAPER OUT - pin 12 - 0xa0     - 10100000
       SELECT    - pin 13 - 0x08     - 00001000
       LINE FEED - pin 14 - 0x88     - 10001000 (active high)
       ERROR     - pin 15 - 0x90     - 10010000

                            
*/

void cnc_io::read_limits(vec3* pt_limit_switch_data)
{

    if(ioperm(LPT1+1,1,1))
    { 
        fprintf(stderr, "# Couldn't open parallel port \n"), exit(1);
    
    }

    unsigned char pin_10_mask = 0b11000000;
    unsigned char pin_12_mask = 0b10100000;
    unsigned char pin_13_mask = 0b00010000;

    unsigned char data_read;
    data_read = inb(LPT1+1); 
    
    //printf("Data read from parallel port: 0x%x\n", data_read);

    //X
    if ((data_read & pin_10_mask)==pin_10_mask)
    {
        cout << "X limit triggered (p10) \n";  
        pt_limit_switch_data->x =1;
    };

    //Z
    if ((data_read & pin_12_mask)==pin_12_mask)
    {
        cout << "Z limit triggered (p12) \n";  
        pt_limit_switch_data->z =1;
    };

    //Y 
    if ((data_read & pin_13_mask)==pin_13_mask)
    {
        cout << "Y limit triggered (p13) \n";  
        pt_limit_switch_data->y =1;        
    };


}

/******************************************/
/*
    take the output of calc_3d_pulses() and send the signals to the parallel port 
    
    The first elemtent of the array denotes direction pulses
    

    DB25 PINOUT (using the CNC4PC/LinuxCNC board as my "default")

    db25 pin #2 - X pulse  -  address 0x01  -  bitshift (1<<0) 
    db25 pin #3 - X dir    -  address 0x02  -  bitshift (1<<1)
    db25 pin #4 - Y pulse  -  address 0x04  -  bitshift (1<<2)
    db25 pin #5 - Y dir    -  address 0x08  -  bitshift (1<<3)
    db25 pin #6 - Z pulse  -  address 0x10  -  bitshift (1<<4)
    db25 pin #7 - Z dir    -  address 0x20  -  bitshift (1<<5)


    #optional pulses
    db25 pin #8 - INV Y pulse   -  address 0x40  -  bitshift (1<<6)



*/

void cnc_io::send_pulses(vector<vec3>* pt_pulsetrain)
{
    unsigned char send_byte = 0x00;
    int send_it = 1; 

    cout << "# we have pulses! count: " << pt_pulsetrain->size() << "\n";

    if(send_it==1)
    {
        if(ioperm(LPT1,1,1))
        { 
            fprintf(stderr, "# Couldn't open parallel port \n"), exit(1);
        }
        cout << "# transmitting pulses to LPT port \n";
    }

    //**************************//
    vec3 dirpulses = pt_pulsetrain->at(0);
    
    vec3 limit_switches;


    if(send_it==0)
    {
        cout <<"# debug - direction "<< dirpulses.x<<" " << dirpulses.y<<" " << dirpulses.z <<"\n";
    }

    if(send_it==1)
    {   
        //x direction high 
        if (dirpulses.x>1){
            //outb(0x02, LPT1);
            send_byte = send_byte |= (1 << 1);
            outb(send_byte, LPT1);            
        }else{
             //outb(0x00, LPT1);  
            send_byte = send_byte &= ~(1 << 1);
            outb(send_byte, LPT1);               
        }

        /*****/

        //y direction high 
        if (dirpulses.y>1){
            send_byte = send_byte |= (1 << 3);
            outb(send_byte, LPT1);  
            
            //!! THIS IS EXTRA FOR A GANTRY MACHINE INVERTED Z AXIS
            //send_byte = send_byte &= ~(1 << 5);   
            //outb(send_byte, LPT1); 

        }else{
            //y direction low         
            send_byte = send_byte &= ~(1 << 3);
            outb(send_byte, LPT1);   

            //!! THIS IS EXTRA FOR A GANTRY MACHINE INVERTED Z AXIS
            //send_byte = send_byte |= (1 << 5);
            //outb(send_byte, LPT1);                          

        }


        /*****/
        //THIS IS A STANDARD 3D SETUP USING Z AXIS

        //z direction high 
        if (dirpulses.z>1){
            send_byte = send_byte |= (1 << 5);
            outb(send_byte, LPT1);               
        }else{
            send_byte = send_byte &= ~(1 << 5);   
            outb(send_byte, LPT1);                   
        }
        
        
        




    }


    //**************************//
    int x=0;

    //the first element is reserved for direction data 
    //we intentionally skip it starting at index 1 
    for(x=1;x<pt_pulsetrain->size();x++)
    {

        if(send_it==0)
        {
            cout<< pt_pulsetrain->at(x).x<<" " << pt_pulsetrain->at(x).y<<" " << pt_pulsetrain->at(x).z <<"\n";
        }

        if(send_it==1)
        {
            
            // watch the limit switches - if triggered, switch off motors NOW!
            (*this).read_limits(&limit_switches);
            
            if(limit_switches.x==1 || limit_switches.y==1 || limit_switches.z==1){
                cout << "machine has crashed. Condolences. pulsing aborted. ";
            }
            else
            {
                //X channel 
                if(pt_pulsetrain->at(x).x==1){
                    send_byte = send_byte |= (1 << 0);
                    outb(send_byte, LPT1); 
                }else{
                    send_byte = send_byte &= ~ (1 << 0);
                    outb(send_byte, LPT1);  
                }
                    
                //Y channel
                if(pt_pulsetrain->at(x).y==1){
                    send_byte = send_byte |= (1 << 2);
                    outb(send_byte, LPT1);    

                    //!! THIS IS ALSO RUNNING Z AXIS (INVERTED DIR) FOR A GANTRY 
                    //send_byte = send_byte |= (1 << 4);
                    //outb(send_byte, LPT1);    

                }else{
                    send_byte = send_byte &= ~(1 << 2);
                    outb(send_byte, LPT1);           

                    //!! THIS IS ALSO RUNNING Z AXIS (INVERTED DIR) FOR A GANTRY 
                    //send_byte = send_byte &= ~(1 << 4);
                    //outb(send_byte, LPT1);                    
                }

                  
                //standard Z channel
                if(pt_pulsetrain->at(x).z==1){
                    send_byte = send_byte |= (1 << 4);
                    outb(send_byte, LPT1);   
                }else{
                    send_byte = send_byte &= ~(1 << 4);
                    outb(send_byte, LPT1);                 
                }
            

            }




            usleep(pulse_del); 
        }

    }

    if(send_it==1)
    {
        cout << "finished transmitting pulses.\n";
    }


}



