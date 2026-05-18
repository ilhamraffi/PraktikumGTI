#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, palm = 0;
static int thumb1 = 0, thumb2 = 0;
static int index1 = 0, index2 = 0;
static int middle1 = 0, middle2 = 0;
static int ring1 = 0, ring2 = 0;
static int little1 = 0, little2 = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger(float yPos, float len, int ang1, int ang2) {
    glPushMatrix();
        glTranslatef(0.0, yPos, 0.0);   
        glRotatef((GLfloat)ang1, 0.0, 0.0, 1.0); 
        glTranslatef(len/2, 0.0, 0.0);
        
        glPushMatrix();
            glScalef(len, 0.1, 0.8);
            glutWireCube(1.0);           
        glPopMatrix();

        glTranslatef(len/2, 0.0, 0.0);   
        glRotatef((GLfloat)ang2, 0.0, 0.0, 1.0); 
        glTranslatef(len/3, 0.0, 0.0);
        
        glPushMatrix();
            glScalef(len/1.5, 0.1, 0.8);
            glutWireCube(1.0);           // Gambar ruas ujung
        glPopMatrix();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); 
  
    glTranslatef(-2.0, 0.0, 0.0); 
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0); 
    glPopMatrix();
    
    // --- LENGAN BAWAH ---
    glTranslatef(1.0, 0.0, 0.0); 
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0); 
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0); 
    glRotatef((GLfloat)palm, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glPushMatrix();
        glScalef(0.8, 0.6, 1.0); 
        glutWireCube(1.0); 
    glPopMatrix();

    glTranslatef(0.4, 0.0, 0.0); 

    drawFinger(0.2, 0.4, index1, index2);     
    drawFinger(0.05, 0.45, middle1, middle2); 
    drawFinger(-0.1, 0.4, ring1, ring2);    
    drawFinger(-0.25, 0.3, little1, little2); 

    glPushMatrix();
        glTranslatef(-0.3, 0.25, 0.0);
        glRotatef((GLfloat)thumb1, 0.0, 0.0, 1.0);
        glTranslatef(0.2, 0.0, 0.0);
        glPushMatrix(); glScalef(0.4, 0.12, 1.0); glutWireCube(1.0); glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0); 
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'p': palm = (palm + 5) % 360; break;
        case 'P': palm = (palm - 5) % 360; break;
        
        case 'f': index1 = (index1 + 5) % 90; middle1 = (middle1 + 5) % 90; 
                  ring1 = (ring1 + 5) % 90; little1 = (little1 + 5) % 90; break;
        case 'F': index1 = (index1 - 5) % 90; middle1 = (middle1 - 5) % 90; 
                  ring1 = (ring1 - 5) % 90; little1 = (little1 - 5) % 90; break;
        case 'g': index2 = (index2 + 5) % 90; middle2 = (middle2 + 5) % 90; 
                  ring2 = (ring2 + 5) % 90; little2 = (little2 + 5) % 90; break;
        case 'G': index2 = (index2 - 5) % 90; middle2 = (middle2 - 5) % 90; 
                  ring2 = (ring2 - 5) % 90; little2 = (little2 - 5) % 90; break;
                  
        case '1': shoulder = 0;
				  elbow = 0;
				  palm = 0;
				  index1 = 0;
				  index2 = 0;
				  middle1 = 60; middle2 = 60; ring1 = 60;   ring2 = 60; little1 = 60; little2 = 60; thumb1 = 30;
				  break;
		case '2': index1 = middle1 = ring1 = little1 = 80;
    			  index2 = middle2 = ring2 = little2 = 80;
                  thumb1 = 40;
    			  break;

        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600); 
    glutCreateWindow("Ilham Muhammad Raffi");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
