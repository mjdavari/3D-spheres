/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<cstring>
#include <math.h>
static int slices = 20;
static int stacks = 20;
static double scale = 1.5;
static bool label_visible = true;
//static double rotation = 10;
static double y_0 = 4,z_0 = 4, x_0 = 0;
static double alpha = 0.95;
static double theta = -2 * 3.141565/11;
static double vx=7, vy=14, vz = 2;
static double cx=0, cy=0, cz = 4;
static double R = 1;
static int N = 12;
static double l = 7 ;
static double lx,ly,lz;
double win_width = 800, win_height = 600;
bool Moving = false;

/* GLUT callback Handlers */
static void drawlabel()
{
    double h= 30;
    glDisable(GL_TEXTURE_2D); //added this
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, win_width, 0.0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3d(0,0,1);
    glRasterPos2i(5, 5);

    char s1[200];
    char s2[100];
    char s3[100];
    sprintf(s1,"eye position = (%.2lf,%.2lf,%.2lf)",vx,vy,vz );
    sprintf(s2, "center position = (%.2lf,%.2lf,%.2lf)", cx,cy,cz);
    sprintf(s3,"N = %d ,r = %.2lf , theta = %.2lf , alpha = %.2lf , axis length=%.2lf , scale=%.2lf",N, R, theta, alpha, l, scale);
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    for (int i=0; i< strlen(s3) ; ++i)
    {
        glutBitmapCharacter(font, s3[i]);
    }
    glRasterPos2i(5, 5+h);
    for (int i=0; i< strlen(s2) ; ++i)
    {
        glutBitmapCharacter(font, s2[i]);
    }
    glRasterPos2i(5, 5+2*h);
    for (int i=0; i< strlen(s1) ; ++i)
    {
        glutBitmapCharacter(font, s1[i]);
    }
    glMatrixMode(GL_PROJECTION); //swapped this with...
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW); //...this
    glPopMatrix();
//added this
    glEnable(GL_TEXTURE_2D);
}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double delta = t*0.1;

    //vx = (0 * cos(delta) - 4 *sin(delta));
    //vy = (4 * cos(delta) + 0 *sin(delta));
    //rotation = (int) (t /100) ;// 1000;
    //const double a = 0;//t*90.0;
    //rotation = t * 90;
    //gluLookAt( t, 70, 70, 0, 0, 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Reset the drawing perspective
//    glTranslatef(0.0f, 0.0f, 5.0f); //Move forward 5 units
//
//    glPushMatrix();
//    glRotated(vx,1,0,0);
//    glRotated(vy,0,1,0);
//    glRotated(vz,0,0,1);

    gluLookAt(vx, vy, vz, cx, cy, cz,
              0.0f, 0.0f,  1.0f);
    glPushMatrix();
    glScalef(scale,scale,scale);
    glColor3d(1,0,0);

    glBegin(GL_LINES);
    glVertex3d(0,0,-l);
    glVertex3d(0,0,l);
    glVertex3d(0,-l,0);
    glVertex3d(0,l,0);
    glVertex3d(-l,0,0);
    glVertex3d(l,0,0);
    glEnd();

    glRasterPos3d( 0,0, l); // location to start printing text

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'z'); // Print a character on the screen
    glRasterPos3d( 0,l, 0); // location to start printing text

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y'); // Print a character on the screen
    glRasterPos3d( l,0, 0); // location to start printing text

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x'); // Print a character on the screen
    if(label_visible)
        drawlabel();

    glColor3d(0.5,0.2,0.7);
    double x, y = y_0, z = z_0;
    //int N = 15;
    double PI = 3.14156535;

    double r = R;
    double rad = 1;
    double alphai = alpha;
    for(int i=0 ; i< N ; i++)
    {
        x = alphai *(x_0 * cos(i * theta) - y_0 *sin(i*theta));
        y = alphai *(y_0 * cos(i * theta) + x_0 *sin(i*theta));
        glPushMatrix();
        glTranslated(x,y,z);
        glutSolidSphere(r,slices,stacks);
        glPopMatrix();
        //printf("printed at (%.2lf,%.2lf,%.2lf)\n" , x,y,z);
        r *= alpha;
        z *= alpha;
        alphai *= alpha;
    }
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

static void catchKey(int key, int x, int y)
{
    double delta = 0.1;
    if(key == GLUT_KEY_LEFT)
    {
        vx = (vx * cos(delta) - vy *sin(delta));
        vy = (vy * cos(delta) + vx *sin(delta));
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        delta *= -1;
        vx = (vx * cos(delta) - vy *sin(delta));
        vy = (vy * cos(delta) + vx *sin(delta));
    }
    else if(key == GLUT_KEY_DOWN)
    {
        vz -- ;
    }
    else if(key == GLUT_KEY_UP)
    {
        vz ++ ;
    }
}
static void key(unsigned char key, int x, int y)
{
    double d = 0.5;
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    case 'x' :
        cx-=d;
        break;
    case 'y' :
        cy-=d ;
        break;
    case 'z' :
        cz-=d;
        break;
    case 'X' :
        cx+=d;
        break;
    case 'Y' :
        cy+=d ;
        break;
    case 'Z' :
        cz+=d;
        break;
    case 'r' :
        R-=0.1 ;
        break;
    case 'R' :
        R+=0.1;
        break;
    case 'a' :
        alpha -= 0.01;
        break;
    case 'A' :
        alpha += 0.01;
        break;
    case 'n' :
        N > 0 ?  N -- : N;
        break;
    case 'N' :
        N ++;
        break;
    case 't' :
        theta-=0.1;
        break;
    case 'T' :
        theta += 0.1;
        break;
    case 'l' :
        l-=0.1;
        break;
    case 'L' :
        l += 0.1;
        break;

    case 's':
        scale-=0.01;
        break;
    case 'S':
        scale+=0.01;
        break;
    case 'h':
        label_visible =!label_visible;
        break;
    }
    printf("now key entered is :%c *** %d at x=%d and y = %d\n", key, key, x, y);
    glutPostRedisplay();
}
static void mouse(int button, int state, int x, int y)
{
    if(button == 0 )
    {

        if( state == GLUT_DOWN)
        {
            Moving = true;
            lx = x;
            ly = y;
            //printf("inputs are button=%d,state=%d,x=%d,y=%d\n" , button,state,x, y);
        }
        if(state == GLUT_UP)
        {
            Moving = false;
            vx += (x-lx)/10.0;
            vy += (y - ly)/10.0;
            //printf("new vx=%.2lf and vy = %.2lf" , vx, vy);
            //printf("mouse up \n");
        }
    }
    if(button == 3)
        vz += 0.1;
    if(button == 4)
        vz -= 0.1;
}
static void mouse_move(int x, int y)
{
    if(Moving == true)
    {
        glutPostRedisplay();
    }
    printf("Mouse is moving .. \n");
}
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 9.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(win_width,win_height);
    glutInitWindowPosition(0,0);
    glViewport(5,5,600,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
//    char c = getch();
//    printf("%c**%d" , c ,c);
//    scanf(" ");
//    c = getch();
//    printf("%c**%d" , c ,c);
    glutCreateWindow("spheres");


    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_move);
    glutSpecialFunc(catchKey);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
//
    glEnable(GL_LIGHT0);
//    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

//    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glLoadIdentity(); //Reset the camera
    //The far z clipping coordinate
    glutMainLoop();

    return EXIT_SUCCESS;
}
