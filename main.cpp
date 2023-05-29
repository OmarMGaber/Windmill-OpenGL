/**
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 *
 *
 * Author: Omar Muhammad Gaber Ahmed (20221446137)
 * Lab Work assignment
 * Computer Graphics Course
 * Department of Mathematics and Computer Science, Faculty of Science, Alexandria University
 *
 *
 *
 **/
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <cmath>
#endif

#include <stdlib.h>

#define start glPushMatrix();
#define end glPopMatrix();

static int slices = 16;
static int stacks = 16;

float cameraAngle = 0.0f;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawCylinder(float radius, float height, int slices, int stacks)
{
     glColor3f(1.0, 1.0, 1.0);
    float stackHeight = height / stacks;
    float stackRadius = radius / stacks;

    for (int i = 0; i < stacks; i++)
    {
        float y1 = i * stackHeight;
        float y2 = (i + 1) * stackHeight;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++)
        {
            float angle = 2.0 * M_PI * j / slices;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            glNormal3f(x / radius, 0.0, z / radius);
            glVertex3f(x, y1, z);
            glVertex3f(x, y2, z);
        }
        glEnd();
    }
}

static double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
static double a = 1;
static double c = 1;

static void grass(){
    /** Omar Muhammad Gaber **/
    for (double i = 0, j = -3.9; i < 10; i++){
        for (double k = -17; k < 6; k+=0.3){
        start
            glTranslated(k, -2, j);
            glColor3f(0, 0.7, 0);
            glutSolidCube(1);
        end
        }
        j--;
    }
}
static void water(){
    for (double i = 0, j = -1.9; i < 10; i++){
        for (double k = 5; k < 10; k+=0.3){
        start
            glTranslated(k, -3.9, j);
            glColor3f(0, 0, 1);
            glutSolidCube(5);
        end
        }
        j--;
    }
}

static void drawSquare(float x, float y, float size){
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     if (a <= 1){
    }else{
        a+=0.05;
    }

    //Windmill
    start
    glTranslated(0, -4, -3.9);
    glRotated(0, 0, 1, 0);

    drawCylinder(0.45,5.2,100,100);

    end


    start

    glTranslatef(0.0, 1.0, -3.4);
    glRotatef(a, 0.0, 0.0, 1.0);

    glColor3f(1.0, 0.2, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.2, 0.0);
    glVertex3f(0.8, 0.8, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-0.2, 1.0, 0.0);
    glVertex3f(-0.8, 0.8, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0, -0.2, 0.0);
    glVertex3f(-0.8, -0.8, 0.0);

    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.2, -1.0, 0.0);
    glVertex3f(0.8, -0.8, 0.0);
    glEnd();

    end

    //Grass
    grass();

    //House
   start
        glTranslated(-1.7, -0.7, -5.95);
        glColor3f(1, 0.5, 0.5);
        glutSolidCube(1.5);
    end

    start
        glTranslated(-2.4, -0.7, -5.95);
        glColor3f(1, 0.5, 0.5);
        glutSolidCube(1.5);
    end

    //Door
    start
        glTranslated(-1, -0.7, -5.);
        glColor3f(1.0, 0.5, 0.0);
        drawSquare(-1.2, -0.7, 0.4);
        drawSquare(-1.2, -0.5, 0.4);
    end

    //Windows
    start
        glTranslated(-1, -0.7, -5);
        glColor3f(0.5, 0.7, 1.0);
        drawSquare(-1.8, 0.1, 0.4);
        drawSquare(-0.6, 0.1, 0.4);
    end

    //Sky
    start
        glTranslated(0, 0, -14);
        glColor3f(0.678, 0.47, 0.999);
        drawSquare(-14, -2, 100);
    end

    water();

    glutSwapBuffers();

}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            a+=3.5;
            break;

        case '-':
            a-=3.5;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Windmill Farm");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
