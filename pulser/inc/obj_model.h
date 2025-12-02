#ifndef OBJMODEL_H    
#define OBJMODEL_H

#include <string>
#include <vector>

#include "Vectors.h"
#include "Matrices.h"
//#include "math_op.h"


#define MAX_NUM_VERTICES 10000
#define MAX_NUM_FACES 10000

//Cautiously moved to the heap  
const int num_vtx   = 120000;
const int num_faces = 120000;


// index/indices for a line object 
typedef struct line{
    int pt1;
    int pt2;
};

// index/indices for a triangle polygon
typedef struct triangle{
    int pt1;
    int pt2;
    int pt3;    
};

// index/indices for a quad polygon 
typedef struct quad{
    int pt1;
    int pt2;
    int pt3;    
    int pt4;
};


/*
// from : https://stackoverflow.com/questions/2750316/this-vs-this-in-c

#include <iostream>

class Foo
{
    public:
        Foo()
        {
            this->value = 0;
        }

        Foo get_copy()
        {
            return *this;
        }

        Foo& get_copy_as_reference()
        {
            return *this;
        }

        Foo* get_pointer()
        {
            return this;
        }

        void increment()
        {
            this->value++;
        }

        void print_value()
        {
            std::cout << this->value << std::endl;
        }

    private:
        int value;
};

int main()
{
    Foo foo;
    foo.increment();
    foo.print_value();

    foo.get_copy().increment();
    foo.print_value();

    foo.get_copy_as_reference().increment();
    foo.print_value();

    foo.get_pointer()->increment();
    foo.print_value();

    return 0;
}
*/

class obj_model {
    public:
        obj_model()
        {
            num_pts     = 0;
            num_vnrmls  = 0;
            num_fnrmls  = 0;
            num_uvs     = 0;
            num_lines   = 0;
            num_tris    = 0;
            num_quads   = 0; 
            num_vtxrgb  = 0;            
        };

        ~obj_model(){};

        int num_pts;
        int num_vtxrgb;
        int num_vnrmls;    
        int num_fnrmls;
        int num_uvs;
        int num_lines;
        int num_tris;
        int num_quads;    

        // --- 
        Vector3 points[MAX_NUM_VERTICES];          // vertices of model    
        Vector3 vtxrgb[MAX_NUM_VERTICES];          // vertices of model  

        Vector2 uvs[num_vtx];           // 2 floats - UV coords 
        Vector3 vnormals[num_vtx];      // 3 floats - face normal 
        Vector3 fnormals[num_faces];    // 3 floats - face normal 

        std::vector<int> lines[MAX_NUM_FACES]; // 2 sided faces 
        std::vector<int> tris[MAX_NUM_FACES];  // 3 sided 
        std::vector<int> quads[MAX_NUM_FACES]; // 4 sided 
        std::vector<int> faces[MAX_NUM_FACES]; // >4, N sided faces 
        // ---
        Vector3 bfr_pts[MAX_NUM_VERTICES];          // general point buffer   ( tmp work area )
        std::vector<int> bfr_faces[MAX_NUM_FACES];  // general polygon buffer ( tmp work area ) 

        // ---
        Matrix4 m44;

        // float& operator[] (size_t i)
        // {
        //   switch (i) {
        //     case 0: return x;
        //     case 1: return y;
        //     case 2: return z;
        //     default: throw "something";
        //   }
        // }
        // float operator[] (size_t i) const
        // { return (*const_cast<vector3f*>(this))[i];

        //Vector3 get_obj_centroid( void );
        Vector3 get_extents(void);

        void reset(void);
        void load( char *);
        void save( char *);
        void show(void);
        void calc_normals(void);
        void add_triangle(Vector3 pt1, Vector3 pt2, Vector3 pt3);
        void triangulate(void);
        void show_geom(void);

        //void get_obj_info(obj_model* loader, obj_info* obinfo);
        //void test_loader_data( obj_model* loader);


};




std::vector<std::string> tokenizer( const std::string&, char);



//DEBUG remove this and merge into the main object?
//cant recall why the hell I did it like this 
/*
class obj_info {
    public:
        obj_info(){

        };

        ~obj_info(){};

    int num_pts;
    int num_nrmls;
    int num_uvs;

    int num_tris;
    int num_faces;
    int num_quads;

    float centroid_x;
    float centroid_y;
    float centroid_z;

    float bb_min_x;
    float bb_max_x;
    
    float bb_min_y;
    float bb_max_y;

    float bb_min_z;
    float bb_max_z;    

};
*/


#endif
