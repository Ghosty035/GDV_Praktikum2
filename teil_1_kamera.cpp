// GD-Praktikum:   teil_1_kamera.cpp  (Teil 2: Szenegraph und Animationen)
// Hergenroether / Groch / Froemmer    Last Update: 26.04.2021

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL

#include "Wuerfel.h"
Wuerfel *n_Wuerfel = new Wuerfel();
Wuerfel *n_Wuerfel2 = new Wuerfel();
void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen	
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
}

void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glBegin(GL_POLYGON);
   // Kameraposition, Blickwinkel und Up-Vector
   gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.); // extrinsische Kameraparameter
   glPushMatrix();
   n_Wuerfel->Wuerfel1(2.0f, 0.2f, 0.3f, 0.05f, 0, 0, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.06f, 0.05f, 0.05f, 0, 0.4f, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.1f, 0.05f, -0.25f, 0.2f, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.1f, 0.05f, -0.25, -0.2, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.1f, 0.05f, 0.25f, 0.2f, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.1f, 0.05f, 0.25, -0.2, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.15f, 0.05f, -0.1, -0.5, 0);
   n_Wuerfel->Wuerfel1(2.0f, 0.03f, 0.15f, 0.05f, 0.1, -0.5, 0);
  // n_Wuerfel2->Wuerfel1(0.0f, 0.0f, 0.0f);
   glPopMatrix();
   glEnd();
   glutSwapBuffers();
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Veränderung der Größe des 
   // Graphikfensters statt

	// Matrix fuer Transformation: Frustum -> viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
    //glScalef(0.1f, 0.1f, 0.1f);
    //n_Wuerfel->scaleCube(0.1f, 0.1f, 0.1f); // transform
    //glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Kamera definieren (intrinsische Kameraparameter)
	//glOrtho(-1., 1., -1., 1., 0., 10.); // orthogonale Kamera
	gluPerspective(90., 1, 0.1, 10.0); // perspektivische Kamera
	// Matrix fuer Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate (int value)    
{
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

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Name_1; Name_2" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene);         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
