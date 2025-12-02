#ifndef CONFUSION36D_H    
#define CONFUSION36D_H


#include "gl_setup.h"



//void tweak_matrix( void );

void grab_camera_matrix( Matrix4 *pt_mmm );
//void grab_projection_matrix(Matrix4 *pt_mpm );

void triangulate(void);
void calc_normals(void);


void set_view_ortho(void);
void setOrthographicProjection();
void resetPerspectiveProjection();
void renderBitmapString(float, float, void *, const char *);

static void render_loop();
static void ReSizeGLScene(int, int);

void key_cb(unsigned int key);
static void parser_cb(unsigned char key, int x, int y);

void olmec_mouse_button(int button, int state, int x, int y);
void olmec_mouse_motion(int x, int y);

void start_gui(int *argc, char** argv);






#endif

