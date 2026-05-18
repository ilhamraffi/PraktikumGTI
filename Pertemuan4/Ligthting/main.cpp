#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Variabel kamera
float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 15.0f; 
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;

// Variabel Lighting
const GLfloat light_ambient[]  = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

//------------------------------------------------------------------
// Fungsi Reshape
//------------------------------------------------------------------
void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------
// Navigasi Kamera
//------------------------------------------------------------------
void updateCamera() {
    if (deltaMove) {
        x += deltaMove * lx * 0.2f;
        z += deltaMove * lz * 0.2f;
    }
    if (deltaAngle) {
        angle += deltaAngle;
        lx = sin(angle);
        lz = -cos(angle);
    }
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------
// Objek: Grid Lantai
//------------------------------------------------------------------
void drawGrid() {
    float i;
    glDisable(GL_LIGHTING); // Grid tidak butuh efek lampu
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (i = -50; i <= 50; i += 1.5) {
        glVertex3f(i, 0, -50); glVertex3f(i, 0, 50); // Garis Vertikal
        glVertex3f(-50, 0, i); glVertex3f(50, 0, i); // Garis Horizontal
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

//------------------------------------------------------------------
// Objek: Kotak dengan Koordinat Tekstur
//------------------------------------------------------------------
void KotakKayu() {
    // Kita buat loop atau manual per sisi untuk mapping tekstur 0.0 ke 1.0
    glPushMatrix();
    glBegin(GL_QUADS);
        // Depan
        glNormal3f(0,0,1);
        glTexCoord2f(0,0); glVertex3f(-3,-3, 3);
        glTexCoord2f(1,0); glVertex3f( 3,-3, 3);
        glTexCoord2f(1,1); glVertex3f( 3, 3, 3);
        glTexCoord2f(0,1); glVertex3f(-3, 3, 3);
        // Belakang
        glNormal3f(0,0,-1);
        glTexCoord2f(0,0); glVertex3f(-3,-3,-3);
        glTexCoord2f(1,0); glVertex3f( 3,-3,-3);
        glTexCoord2f(1,1); glVertex3f( 3, 3,-3);
        glTexCoord2f(0,1); glVertex3f(-3, 3,-3);
        // Atas
        glNormal3f(0,1,0);
        glTexCoord2f(0,0); glVertex3f(-3, 3,-3);
        glTexCoord2f(1,0); glVertex3f( 3, 3,-3);
        glTexCoord2f(1,1); glVertex3f( 3, 3, 3);
        glTexCoord2f(0,1); glVertex3f(-3, 3, 3);
        // Bawah
        glNormal3f(0,-1,0);
        glTexCoord2f(0,0); glVertex3f(-3,-3,-3);
        glTexCoord2f(1,0); glVertex3f( 3,-3,-3);
        glTexCoord2f(1,1); glVertex3f( 3,-3, 3);
        glTexCoord2f(0,1); glVertex3f(-3,-3, 3);
    glEnd();
    glPopMatrix();
}

void display() {
    updateCamera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawGrid();
    
    // Memberi warna dasar jika tekstur belum di-load
    glColor3f(1.0, 1.0, 1.0); 
    KotakKayu();
    
    glutSwapBuffers();
}

//------------------------------------------------------------------
// Kontrol Keyboard
//------------------------------------------------------------------
void pressKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT  : deltaAngle = -0.03f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.03f; break;
        case GLUT_KEY_UP    : deltaMove = 1; break;
        case GLUT_KEY_DOWN  : deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT  : if (deltaAngle < 0) deltaAngle = 0; break;
        case GLUT_KEY_RIGHT : if (deltaAngle > 0) deltaAngle = 0; break;
        case GLUT_KEY_UP    : if (deltaMove > 0)  deltaMove = 0; break;
        case GLUT_KEY_DOWN  : if (deltaMove < 0)  deltaMove = 0; break;
    }
}

//------------------------------------------------------------------
// Inisialisasi
//------------------------------------------------------------------
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D); // AKTIFKAN TEKSTUR
    glEnable(GL_COLOR_MATERIAL);
    
    
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Box - Camera & Texture");
    
    init();
    
    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    
    glutMainLoop();
    return 0;
}
