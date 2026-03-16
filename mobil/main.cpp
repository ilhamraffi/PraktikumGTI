#include <GL/glut.h>
#include <math.h>

void roda(){
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++){
        float rad = i * 3.1416 / 180;
        glVertex2f(cos(rad)*0.2, sin(rad)*0.2);
    }
    glEnd();
}

void mobil(){

    // body mobil 
    glColor3f(0.75,0.0,0.1);
    glBegin(GL_QUADS);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(1,0.5);
        glVertex2f(-1,0.5);
    glEnd();

    // atap mobil
    glColor3f(0.8,0.0,0.1);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5,0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(0.3,0.9);
        glVertex2f(-0.3,0.9);
    glEnd();

    // jendela kiri
    glColor3f(0.2,0.3,0.4);
    glBegin(GL_QUADS);
        glVertex2f(-0.45,0.55);
        glVertex2f(-0.05,0.55);
        glVertex2f(-0.05,0.75);
        glVertex2f(-0.45,0.75);
    glEnd();

    // jendela kanan
    glBegin(GL_QUADS);
        glVertex2f(0.05,0.55);
        glVertex2f(0.45,0.55);
        glVertex2f(0.45,0.75);
        glVertex2f(0.05,0.75);
    glEnd();

    // roda kiri
    glPushMatrix();
        glTranslatef(-0.6,-0.1,0);
        roda();
    glPopMatrix();

    // roda kanan
    glPushMatrix();
        glTranslatef(0.6,-0.1,0);
        roda();
    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(0,0,0);
        mobil();
    glPopMatrix();

    glutSwapBuffers();
}

void init(){
    glClearColor(1.0,0.5,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5,5,-5,5);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Mobil");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}
