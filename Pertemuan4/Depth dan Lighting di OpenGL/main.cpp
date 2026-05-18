// Template Objek 3D OpenGL GLUT
// Kamera bisa maju, mundur, kiri, kanan
// Sudah ada lighting dan depth test

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Variabel kamera
float angle = 0.0f;
float deltaAngle = 0.0f;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float deltaMove = 0.0f;

int w = 640;
int h = 480;
float ratio;

// ==============================
// LIGHTING
// ==============================

const GLfloat light_ambient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {0.0f, 20.0f, 10.0f, 1.0f};

const GLfloat mat_ambient[]    = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[]    = {0.8f, 0.5f, 0.3f, 1.0f};
const GLfloat mat_specular[]   = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

// ==============================
// RESHAPE
// ==============================

void Reshape(int w1, int h1)
{
    if (h1 == 0)
        h1 = 1;

    w = w1;
    h = h1;

    ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
}

// ==============================
// KAMERA
// ==============================

void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

void moveMeFlat(int i)
{
    x += i * lx * 0.2f;
    z += i * lz * 0.2f;

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );
}

// ==============================
// GRID
// ==============================

void Grid()
{
    float i;

    glDisable(GL_LIGHTING);

    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (i = -50; i <= 50; i += 1.5f)
    {
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);

        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
    }

    glEnd();

    glEnable(GL_LIGHTING);
}

// ==============================
// KOTAK 3D
// ==============================

void KotakKayu()
{
    glColor3f(0.7f, 0.4f, 0.2f);

    glBegin(GL_QUADS);

    // DEPAN
    glNormal3f(0.0f, 0.0f, 1.0f);

    glVertex3f(-3.0f, -3.0f,  3.0f);
    glVertex3f( 3.0f, -3.0f,  3.0f);
    glVertex3f( 3.0f,  3.0f,  3.0f);
    glVertex3f(-3.0f,  3.0f,  3.0f);

    // BELAKANG
    glNormal3f(0.0f, 0.0f, -1.0f);

    glVertex3f(-3.0f, -3.0f, -3.0f);
    glVertex3f(-3.0f,  3.0f, -3.0f);
    glVertex3f( 3.0f,  3.0f, -3.0f);
    glVertex3f( 3.0f, -3.0f, -3.0f);

    // KANAN
    glNormal3f(1.0f, 0.0f, 0.0f);

    glVertex3f(3.0f, -3.0f, -3.0f);
    glVertex3f(3.0f,  3.0f, -3.0f);
    glVertex3f(3.0f,  3.0f,  3.0f);
    glVertex3f(3.0f, -3.0f,  3.0f);

    // KIRI
    glNormal3f(-1.0f, 0.0f, 0.0f);

    glVertex3f(-3.0f, -3.0f, -3.0f);
    glVertex3f(-3.0f, -3.0f,  3.0f);
    glVertex3f(-3.0f,  3.0f,  3.0f);
    glVertex3f(-3.0f,  3.0f, -3.0f);

    // ATAS
    glNormal3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-3.0f, 3.0f, -3.0f);
    glVertex3f(-3.0f, 3.0f,  3.0f);
    glVertex3f( 3.0f, 3.0f,  3.0f);
    glVertex3f( 3.0f, 3.0f, -3.0f);

    // BAWAH
    glNormal3f(0.0f, -1.0f, 0.0f);

    glVertex3f(-3.0f, -3.0f, -3.0f);
    glVertex3f( 3.0f, -3.0f, -3.0f);
    glVertex3f( 3.0f, -3.0f,  3.0f);
    glVertex3f(-3.0f, -3.0f,  3.0f);

    glEnd();
}

// ==============================
// DISPLAY
// ==============================

void display()
{
    if (deltaMove)
        moveMeFlat(deltaMove);

    if (deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
        x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f
    );

    Grid();

    KotakKayu();

    glutSwapBuffers();
}

// ==============================
// KEYBOARD
// ==============================

void pressKey(int key, int xx, int yy)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.01f;
            break;

        case GLUT_KEY_RIGHT:
            deltaAngle = 0.01f;
            break;

        case GLUT_KEY_UP:
            deltaMove = 1;
            break;

        case GLUT_KEY_DOWN:
            deltaMove = -1;
            break;
    }
}

void releaseKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0f;
            break;

        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
            break;
    }
}

// ==============================
// LIGHTING SETUP
// ==============================

void lighting()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// ==============================
// INIT
// ==============================

void init()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// ==============================
// MAIN
// ==============================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);

    glutCreateWindow("3D OpenGL Lighting");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(Reshape);

    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutIgnoreKeyRepeat(1);

    lighting();
    init();

    glutMainLoop();

    return 0;
}
