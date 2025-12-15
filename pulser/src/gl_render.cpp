

#include "gl_setup.h"



extern GLfloat clr_linez[]   ;
extern GLfloat emis_full[]   ;
extern GLfloat emis_half[]   ;
extern GLfloat emis_text[]   ;
extern GLfloat emis_points[] ;
extern GLfloat emis_off[]    ;
extern GLfloat emis_teal[]   ;
extern GLfloat emis_red[]    ;
extern GLfloat emis_green[]  ;
extern GLfloat emis_blue[]   ;
extern GLfloat emis_lines[]  ;
extern GLfloat clr_yellow[]  ;
extern GLfloat clr_green[]   ;
extern GLfloat clr_blue[]    ;


extern GLuint texture[3];


int line_clr_r; //read from setup.olm 
int line_clr_g; 
int line_clr_b; 
int num_pts_drw;


/***************************************/

void render_vbo(obj_model* pt_model_buffer)
{
    // persistant point buffer   
    // Not tested well! - I think it needs OpenGL4 amd up

    //http://ogldev.atspace.co.uk/www/tutorial02/tutorial02.html 
    //https://stackoverflow.com/questions/28849321/how-to-draw-polygon-with-3d-points-in-modern-opengl
    
    glMaterialfv(GL_FRONT, GL_EMISSION, emis_points);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, emis_off);

    glPointSize(2);

    //-------------------------
    num_pts_drw = pt_model_buffer->num_pts;

    GLfloat vertices[num_pts_drw*4];
    GLfloat* pt_vert = vertices;
    dump_points_GLfloat( pt_vert, pt_model_buffer, num_pts_drw );
    
    // add in custom points loaded from scene.olm  
    //dump_points_GLfloat( pt_vert, pt_scene_drawpoints, num_drawpoints );



    //-------------------------


    GLuint VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);


    // "Enable a port" to the shader pipeline
    glEnableVertexAttribArray(0);
    
    //DEBUG COMMENTED OUT
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // pass information about how vertex array is composed
    glVertexAttribPointer(0, // same as in glEnableVertexAttribArray(0)
                          4, // # of coordinates that build a vertex
                          GL_FLOAT, // data type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*)0);// vbo offset


    glDrawArrays(GL_POINTS, 0, num_pts_drw);
    //glDrawArrays(GL_LINES, 0, num_pts_drw);
    glDisableVertexAttribArray(0);
    
    glMaterialfv(GL_FRONT, GL_EMISSION, emis_off);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, emis_full);
}



/***************************************/



void render_lines(obj_model* pt_model_buffer)
{
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, emis_off);
    
    // glEnable(GL_COLOR_MATERIAL);  
    // glColor3f(.5, 0, .5);
        
    for (int p_i=0;p_i<pt_model_buffer->num_lines;p_i++)
    {   
        glBegin(GL_LINES);
            // fetch the line indices from vertex list 
            int lin1 = pt_model_buffer->lines[p_i][0];
            int lin2 = pt_model_buffer->lines[p_i][1];
            
            Vector3 pt1 = pt_model_buffer->points[lin1-1];
            Vector3 pt2 = pt_model_buffer->points[lin2-1];

            //use the same vertex indices to lookup RGB 
            Vector3 c1 = pt_model_buffer->vtxrgb[lin1-1];
            Vector3 c2 = pt_model_buffer->vtxrgb[lin2-1];

            if(c1.x==0){c1.x=line_clr_r;c2.x=line_clr_r;}
            if(c1.y==0){c1.y=line_clr_g;c2.y=line_clr_g;}
            if(c1.z==0){c1.z=line_clr_b;c2.z=line_clr_b;}

            //std::cout << "line color is set to " << c1.x <<" "<< c1.y<< " " << c1.z << "\n";
            glMaterialfv(GL_FRONT, GL_EMISSION, clr_linez);
            glColor3f(c1.x, c1.y, c1.z);   
            glVertex3f(pt1.x, pt1.y, pt1.z);

            glColor3f(c2.x, c2.y, c2.z);  
            glVertex3f(pt2.x, pt2.y, pt2.z);

        glEnd();
    }

    glMaterialfv(GL_FRONT, GL_EMISSION, emis_off);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, emis_full);  
}




/***************************************/



