#include <stdlib.h> // standard definitions  

#include <stdio.h> // C I/O (for sprintf)  

#include <math.h> // standard definitions  

#include <GL/glut.h> // GLUT  

double rotAngle = 10; // rotation angle (BEWARE: Global)  

double rotAngle1 = 10; // rotation angle (BEWARE: Global)  

//------------------------------------------------------------------ 

// init  

// Sets up some default OpenGL values.  

//------------------------------------------------------------------ 

void init()  

{  

glClearColor(0, 0, 0, 0); // background color  

glClearDepth(1.0); // background depth value  

  glMatrixMode(GL_PROJECTION);  

  glLoadIdentity();  

  gluPerspective(60, 1, 1, 1000); // setup a perspective projection  

  glMatrixMode(GL_MODELVIEW);  

  glLoadIdentity();  

  gluLookAt( // set up the camera  

        0.0, 0.0, 5.0, // eye position  

        0.0, 0.0, 0.0, // lookat position  

        0.0, 1.0, 0.0); // up direction  

}  

//------------------------------------------------------------------ 

// display callback function  

// This is called each time application needs to redraw itself.  

// Most of the opengl work is done through this function.  

//------------------------------------------------------------------ 

void display()  
{  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glPushMatrix(); 
    glRotated(rotAngle, 0, 1, 0);   
    glRotated(rotAngle1, 1, 0, 0);  
    glEnable(GL_COLOR_MATERIAL); 

    // GANTI DI SINI: (Red, Green, Blue) dari rentang 0.0 sampai 1.0
    glColor3f(0.0, 1.0, 1.0); // Warna Cyan / Biru Muda Terang

    glutSolidTeapot(1); 
  glPopAttrib(); // Tambahan opsional: amankan state warna
  glPopMatrix();  
  glFlush();  
  glutSwapBuffers();  
}

//------------------------------------------------------------------  

// keyboard callback function  

// This is called whenever a keyboard key is hit.  

//------------------------------------------------------------------ 

void keyboard(unsigned char k, int x, int y)  

{  

  switch (k)  

  {  

   case 'a':  

     rotAngle += 5; // increase rotation by 5 degrees  

     break;  

   case 'y':  

     rotAngle1 += 5; // increase rotation by 5 degrees  

     break;  

   case 'b':  

     rotAngle1 -= 5; // increase rotation by 5 degrees  

     break;  

   case 'l':  

    rotAngle -= 5; // decrease rotation by 5 degrees  

    break;  

  case 'q':  

    exit(0); // exit  

  }  

  glutPostRedisplay(); // redraw the image now  

}  

//-----------------------------------------------------------------  

// main program  

// Where everything begins.  

//------------------------------------------------------------------ 

int main()  

{  

  glutInitDisplayMode( // initialize GLUT  

     GLUT_DOUBLE | // use double buffering  

     GLUT_DEPTH | // request memory for z-buffer  

     GLUT_RGB ); // set RGB color mode  

  glutCreateWindow("GLUT Example"); // create the window  

  glutDisplayFunc(display); // call display() to redraw window  

  glutKeyboardFunc(keyboard); // call keyboard() when key is hit  

  init(); // our own initializations  

  glutMainLoop(); // let GLUT take care of everything  

  return 0;  

}
