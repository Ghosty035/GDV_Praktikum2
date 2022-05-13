// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream>
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"
Wuerfel *n_Wuerfel = new Wuerfel();
void Init()
{
    // Hier finden jene Aktionen statt, die zum Programmstart einmalig
    // durchgeführt werden müssen
  /*  glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);*/
}

void RenderScene() //Zeichenfunktion
{
    // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
    glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
    glBegin(GL_POLYGON);
    glPushMatrix();
    n_Wuerfel->zeichneWuerfel(30.0f);
    glPopMatrix();

  /*  glColor4f(1.0, 0.0, 0.0, 1.0);
    //glVertex3f(-0.5, -0.5, -0.5);
    glColor4f(0.0, 0.0, 1.0, 1.0); //blau

    //Draw T

    glVertex3f(0.5, -1.0, -0.5); //Dreieck 1 __ Viereck 0 __ Mitte __ ganz_unten __ T
    glVertex3f(0.5, 0.0, -0.5);
    glVertex3f(-0.5, 0.0, -0.5);

    glVertex3f(0.5, -1.0, -0.5); //Dreieck 2 __ Viereck 0 __ Mitte __ ganz_unten __ T
    glVertex3f(-0.5, 0.0, -0.5);
    glVertex3f(-0.5, -1.0, 0.5);

    glVertex3f(0.5, -0.5, -0.5); //Dreieck 1 __ Viereck 1 __ Mitte __ unten __ T
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(0.5, -0.5, -0.5); //Dreieck 2 __ Viereck 1 __ Mitte __ unten __ T
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(0.5, 0.0, -0.5); //Dreieck 1 __ Viereck 2 __ Mitte __ oben __ T
    glVertex3f(0.5, 1.0, -0.5);
    glVertex3f(-0.5, 1.0, -0.5);

    glVertex3f(0.5, 0.0, -0.5); //Dreieck 2 __ Viereck 2 __ Mitte __ oben __ T
    glVertex3f(-0.5, 0.0, 0.5);
    glVertex3f(-0.5, 1.0, -0.5);

    glVertex3f(1.0, 0.0, -0.5); //Dreieck 1 __ Viereck 3 __ Rechts __ oben __ T
    glVertex3f(1.0, 1.0, -0.5);
    glVertex3f(0.0, 1.0, -0.5);

    glVertex3f(1.0, 0.0, -0.5); //Dreieck 2 __ Viereck 3 __ Rechts __ oben __ T
    glVertex3f(0.0, 1.0, -0.5);
    glVertex3f(0.0, 0.0, 0.5);

    glVertex3f(0.0, 0.0, -0.5); //Dreieck 1 __ Viereck 3 __ Links __ oben __ T
    glVertex3f(0.0, 1.0, -0.5);
    glVertex3f(-1.0, 1.0, -0.5);

    glVertex3f(0.0, 0.0, -0.5); //Dreieck 2 __ Viereck 3 __ Links __ oben __ T
    glVertex3f(-1.0, 1.0, -0.5);
    glVertex3f(-1.0, 0.0, 0.5); */
    glEnd();
    glutSwapBuffers();
}

void Reshape(int width, int height)
{
    // Hier finden die Reaktionen auf eine Veränderung der Größe des
    // Graphikfensters statt
}

void Animate(int value)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.65f, 0.0f, 1.0f);;
    // Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene
    // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle
    // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins
    // inkrementiert und dem Callback wieder uebergeben.
    std::cout << "value=" << value << std::endl;
    // RenderScene aufrufen
    glutPostRedisplay();
    // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
    int wait_msec = 10;
    glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                // GLUT initialisieren
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);         // Fenster-Konfiguration
    glutCreateWindow("Tim; Simon");// Fenster-Erzeugung
    glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
    glutReshapeFunc(Reshape);
    // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0
    glutTimerFunc(10, Animate, 0);
    Init();
    glutMainLoop();
    return 0;
}
