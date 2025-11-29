
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>  

#include "parse_cmds.h"
#include "gl_setup.h"

#include "confusion_36d.h"


   

/***************************************/
/***************************************/

//---
//std::string s(1, key);
//std::cout << s << std::endl;
//--- 
//std::string s{key};
//std::cout << s << std::endl;
//---      
//std::string s;
//s.push_back(key);
//std::cout << s << "\n";

void parse_cmd_text(std::string *buffer)
{
    std::cout << " hello parser \n" << *buffer <<"\n";

}


    //std::cout << " cursor "<< cursor <<"\n"; 

    // std::istringstream iss(*buffer);
    // if (getline(iss, parsed, ' '))
    // {
    //     // do some processing.
    //     std::cout << "EEE " << parsed << "\n";
    // };

    // std::stringstream ss(*buffer);
    // int number_int;
    // double number_double;
    // // Extracting words separated by spaces
    // ss >> word; // word will be "apple"
    // ss >> word; // word will be "banana"

  
    /*
    if(*pt_key==*"a"||i==97)
    {
        std::cout << "a PRESSED\n";        
    }*/

/*


    std::stringstream ss(buffer);
    std::string word;
    int number_int;
    double number_double;

    // Extracting words separated by spaces
    ss >> word; // word will be "apple"
    ss >> word; // word will be "banana"

    // Extracting numbers
    ss >> number_int;    // number_int will be 123
    ss >> number_double; // number_double will be 4.5

    std::cout << "Word 1: " << word << std::endl;
    std::cout << "Integer: " << number_int << std::endl;
    std::cout << "Double: " << number_double << std::endl;
*/


/*
std::string input_txt(void){

    std::string sentence;
    std::cout << "Enter a sentence please: "; std::cout.flush();

    std::getline(std::cin,sentence);
    std::istringstream iss(sentence);

    std::vector<std::string> words;
    std::string word;
    while(iss >> word) {
        words.push_back(word);
    } 

    for(std::vector<std::string>::const_iterator it = words.begin();
        it != words.end();
        ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl; return 0;
    
    return sentence;
}
*/


/***************************************/
/***************************************/

int cursor = 0;

void parse_cmds(std::string *buffer, unsigned char *pt_key )
{
    int i = static_cast<int>(*pt_key);
    //std::cout << " int val " << i << std::endl;

    //-----
    if(i!=8)
    {
        cursor = buffer->size();
    }

    //-----
    //backspace key
    if(i==8)
    {
        if (buffer->size()>0)
        {
            cursor--;
            buffer->erase(cursor, buffer->size());
        }


    }

    //-----
    //enter key
    if(i==13)
    {
        //todo - keep a log of commands as txt file ??
        
        //std::cout << "command to parse \n" << *buffer << "\n";

        parse_cmd_text(buffer);

        buffer->clear();
        //std::cout << "ENTER PRESSED\n";        
    }    

    //-----
    //esc key
    if(i==27)
    {
        key_cb(i);      
    }  

    //-----
    //output results
    buffer->push_back(*pt_key);

    //std::cout << *buffer << "\n";
    //std::cout << *pt_key << "\n";



};




