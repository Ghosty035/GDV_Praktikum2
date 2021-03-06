// GD-Praktikum:   teil_1_kamera.cpp  (Teil 2: Szenegraph und Animationen)
// Hergenroether / Groch / Froemmer    Last Update: 26.04.2021

#include <iostream> 
#include <GL/freeglut.h>         //l?dt alles f?r OpenGL

#include "Wuerfel.h"
GLfloat RotationAngle = 0;
GLfloat armRotationAngle = 0;
GLfloat legRotationAngle = 0;
bool isAnimatingArms = false;
bool isAnimatingLegs = false;


void rotateArms();

void Init()
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgef?hrt werden m?ssen	
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
}

void RenderScene() //Zeichenfunktion
{
   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Kameraposition, Blickwinkel und Up-Vector
   gluLookAt(1., 1., 1., 0., 0., 0., 0., 1., 0.); // extrinsische Kameraparameter

   Wuerfel1(2.0f, 0.2f, 0.3f, 0.05f, 0, 0, 0); // Bauch
   Wuerfel2(2.0f, 0.06f, 0.05f, 0.05f, 0, 0.4f, 0, RotationAngle);//Kopf

   rotateArms();
   glTranslatef(0, 0.02, -0.09);
   glRotatef(23, 1, 0, 0);

   glRotatef(-33, 1, 0, 0);
   glTranslatef(0, 0.02, -0.09);
   Wuerfel2(2.0f, 0.03f, 0.15f, 0.05f, -0.1, -0.5, 0, legRotationAngle); //Linkes Bein
   glRotatef(33, 1, 0, 0);
   glTranslatef(0, -0.02, +0.09);


   glRotatef(33, 1, 0, 0);
   glTranslatef(0, -0.02, +0.09);
   Wuerfel2(2.0f, 0.03f, 0.15f, 0.05f, 0.1, -0.5, 0, -legRotationAngle); //Rechtes Bein


   glutSwapBuffers();
}

void rotateArms() {
        glRotatef(-23, 1, 0, 0);
        glTranslatef(0, -0.02, 0.09);
        glRotatef(RotationAngle, 1, 0, 0);
        Wuerfel2(2.0f, 0.03f, 0.1f, 0.05f, -0.25f, 0.2f, 0, armRotationAngle); //Linker Oberarm

        glRotatef(-23, 1, 0, 0);
        glTranslatef(0, 0, 0.01);
        Wuerfel1(2.0f, 0.03f, 0.15f, 0.05f, -0.25, -0.1, 0); //Linker Unterarm

        glTranslatef(0, 0, -0.01);
        glRotatef(23, 1, 0, 0);
        Wuerfel2(2.0f, 0.03f, 0.1f, 0.05f, 0.25f, 0.2f, 0, armRotationAngle); //Rechter Oberarm
        glRotatef(-23, 1, 0, 0);

        glTranslatef(0, 0, 0.01);
        Wuerfel1(2.0f, 0.03f, 0.15f, 0.05f, 0.25, -0.1, 0); //Rechter Unterarm
        glRotatef(23, 1, 0, 0);
        glTranslatef(0, 0, -0.01);

        glRotatef(-RotationAngle, 1, 0, 0); //stop legs rotating
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Ver?nderung der Gr??e des 
   // Graphikfensters statt
	// Matrix fuer Transformation: Frustum -> viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
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
   // Hier werden Berechnungen durchgef?hrt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess l?uft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   std::cout << "value=" << value << std::endl;

    if(isAnimatingArms){
        RotationAngle+=0.5f;
        armRotationAngle+= 0.2f;
        if(RotationAngle == 10 || armRotationAngle == 7) isAnimatingArms = false;
    }else{
        RotationAngle -= 0.5f;
        armRotationAngle-=0.2f;
        if(RotationAngle == -10 || armRotationAngle == -7) isAnimatingArms = true;
    }

    if(isAnimatingLegs) {
        legRotationAngle++;
        if(RotationAngle == 10) isAnimatingLegs = false;
    } else {
        legRotationAngle--;
        if(RotationAngle == -10) isAnimatingLegs = true;
    }

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
