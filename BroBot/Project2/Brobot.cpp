/*
Author : Joshua Issac
////(B)ROBOT
The aim of this program is to create a Robot with 16 moveable parts.

//STRUCTURE OF THE BODY (Representation will help with Push/Pop procedure)
PARENT : (L)ower (B)ody
	CHILDREN(LB) : (R)ight (T)high, (L)eft (T)high, (U)pper (B)ody,
		Children(RT) : RT1, RT2
		Children(LT) : LT1, LT2
		CHILDREN(UB) : (R)ight (A)rm, (L)eft (A)rm, Neck
			CHILDREN(RA) : RA1, RA2
			CHILDREN(LA) : LA1, LA2
			CHILDREN(Neck) : Head
				CHILDREN(Head) : null

//CONTROLS:
	UP & DOWN arrow keys - Cycle between the various parts of the BroBot.
	A & D keys - Rotate the currently highlighted part, and corresponding children left or right, respectively.
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Brobot.h"
#include <iostream>
#include <math.h>
using namespace std;

//Initializes variables on program execution. 

//Parameters for the Window & Canvas
int win_width = 800, win_height = 800;
float canvas_width = 20.0f; float canvas_height = 20.0f;
//Variables to hold the attributes of each part


//To be used as an index for the highlighted rect
int current;
Rect R[NUM_OF_PARTS];

void Rect::drawBot() {
	
	glRotatef(R[0].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[0]);	//LB
	glPushMatrix();

	glTranslatef(-1.5f, 0.0f, 0.0f);
	glRotatef(R[1].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[1]); //RT
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(R[2].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[2]); //RT1
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(R[3].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[3]); //RT2
	glPopMatrix();
	glPopMatrix();

	//Back to LB, then LT
	glPopMatrix();
	glPushMatrix();

	glTranslatef(1.5f, 0.0f, 0.0f);
	glRotatef(R[4].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[4]); //LT
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(R[5].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[5]); //LT1
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	glRotatef(R[6].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[6]); //LT2
	glPopMatrix();
	glPopMatrix();

	////Back to LB, then UB
	glPopMatrix();

	glPushMatrix(); //Stores LB, and draws UB with respect to LB
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(R[7].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[7]); //UB
	glPushMatrix(); //Now onwards we wanna draw with respect to UB

	////Push UB, then RA
	glTranslatef(-3, 1.5f, 0);
	glRotatef(R[8].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[8]); //RA
	glPushMatrix();
	glTranslatef(-1.5f, 0, 0);
	glRotatef(R[9].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[9]); //RA1
	glPushMatrix();
	glTranslatef(-1.5f, 0, 0);
	glRotatef(R[10].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[10]); //RA2
	glPopMatrix();
	glPopMatrix(); //After this, we're back at UB
//Back to UB, then LA
	glPopMatrix();
	glPushMatrix();

	glTranslatef(3, 1.5f, 0);
	glRotatef(R[11].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[11]); //LA
	glPushMatrix();
	glTranslatef(1.5f, 0, 0);
	glRotatef(R[12].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[12]); //LA1
	glPushMatrix();
	glTranslatef(1.5f, 0, 0);
	glRotatef(R[13].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[13]); //LA2
	glPopMatrix();
	glPopMatrix();

	////Back to UB, then Neck
	glPopMatrix();

	glPushMatrix(); //To draw the Neck w.r.t UB, we push UB
	glTranslatef(0.0f, 2, 0.0f);
	glRotatef(R[14].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[14]); //Neck
	glPushMatrix(); //To draw Head w.r.t Neck
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(R[15].rotation, 0.0f, 0.0f, 1.0f);
	drawQuad(R[15]); //Head
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	
}

Rect::Rect()
{
	colors[0] = colors[1] = colors[2] = 0.0f;
	for (int i = 0; i < 4;i++) {
		V[i].x = V[i].y = 0;
	}
	rotation = 0.0f;
}

void initBot() {

	/// Initialize Rect vertices
	//LB
	R[0].V[0].x = -2; R[0].V[0].y = 0;	R[0].V[1].x = -2; R[0].V[1].y = 1;
	R[0].V[2].x = 2; R[0].V[2].y = 1;	R[0].V[3].x = 2; R[0].V[3].y = 0;
	//RT
	R[1].V[0].x = -0.5f; R[1].V[0].y = 0;	R[1].V[1].x = -0.5f; R[1].V[1].y = -2;
	R[1].V[2].x = 0.5f; R[1].V[2].y = -2;	R[1].V[3].x = 0.5f; R[1].V[3].y = 0;

	R[2].V[0].x = -0.5f; R[2].V[0].y = 0;	R[2].V[1].x = -0.5f; R[2].V[1].y = -2;
	R[2].V[2].x = 0.5f; R[2].V[2].y = -2;	R[2].V[3].x = 0.5f; R[2].V[3].y = 0;

	R[3].V[0].x = -1.5f; R[3].V[0].y = 0;	R[3].V[1].x = -1.5f; R[3].V[1].y = -1;
	R[3].V[2].x = 0.5f; R[3].V[2].y = -1;	R[3].V[3].x = 0.5f; R[3].V[3].y = 0;
	//RTend
	//LT
	R[4].V[0].x = -0.5f; R[4].V[0].y = 0;	R[4].V[1].x = -0.5f; R[4].V[1].y = -2;
	R[4].V[2].x = 0.5f; R[4].V[2].y = -2;	R[4].V[3].x = 0.5f; R[4].V[3].y = 0;

	R[5].V[0].x = -0.5f; R[5].V[0].y = 0;	R[5].V[1].x = -0.5f; R[5].V[1].y = -2;
	R[5].V[2].x = 0.5f; R[5].V[2].y = -2;	R[5].V[3].x = 0.5f; R[5].V[3].y = 0;

	R[6].V[0].x = -0.5f; R[6].V[0].y = 0;	R[6].V[1].x = -0.5f; R[6].V[1].y = -1;
	R[6].V[2].x = 1.5f; R[6].V[2].y = -1;	R[6].V[3].x = 1.5f; R[6].V[3].y = 0;
	//LTend
	//UB
	R[7].V[0].x = -3; R[7].V[0].y = 0;	R[7].V[1].x = -3; R[7].V[1].y = 2;
	R[7].V[2].x = 3; R[7].V[2].y = 2;	R[7].V[3].x = 3; R[7].V[3].y = 0;
	//RA
	R[8].V[0].x = 0; R[8].V[0].y = 0.5f;	R[8].V[1].x = -1.5f; R[8].V[1].y = 0.5f;
	R[8].V[2].x = -1.5f; R[8].V[2].y = -0.5f;	R[8].V[3].x = 0; R[8].V[3].y = -0.5f;

	R[9].V[0].x = 0; R[9].V[0].y = 0.5f;	R[9].V[1].x = -1.5f; R[9].V[1].y = 0.5f;
	R[9].V[2].x = -1.5f; R[9].V[2].y = -0.5f;	R[9].V[3].x = 0; R[9].V[3].y = -0.5f;

	R[10].V[0].x = -0.5f; R[10].V[0].y = 0.75f;	R[10].V[1].x = 0; R[10].V[1].y = 0.75f;
	R[10].V[2].x = 0; R[10].V[2].y = -0.75f;	R[10].V[3].x = -0.5f; R[10].V[3].y = -0.75f;
	//RAend
	//LA
	R[11].V[0].x = 0; R[11].V[0].y = 0.5f;	R[11].V[1].x = 1.5f; R[11].V[1].y = 0.5f;
	R[11].V[2].x = 1.5f; R[11].V[2].y = -0.5f;	R[11].V[3].x = 0; R[11].V[3].y = -0.5f;

	R[12].V[0].x = 0; R[12].V[0].y = 0.5f;	R[12].V[1].x = 1.5f; R[12].V[1].y = 0.5f;
	R[12].V[2].x = 1.5f; R[12].V[2].y = -0.5f;	R[12].V[3].x = 0; R[12].V[3].y = -0.5f;

	R[13].V[0].x = 0.5f; R[13].V[0].y = 0.75f;	R[13].V[1].x = 0; R[13].V[1].y = 0.75f;
	R[13].V[2].x = 0; R[13].V[2].y = -0.75f;	R[13].V[3].x = 0.5f; R[13].V[3].y = -0.75f;
	//RAend
	//Neck
	R[14].V[0].x = -0.25f; R[14].V[0].y = 0;	R[14].V[1].x = -0.25f; R[14].V[1].y = 0.5f;
	R[14].V[2].x = 0.25f; R[14].V[2].y = 0.5f;	R[14].V[3].x = 0.25f; R[14].V[3].y = 0;
	//Head
	R[15].V[0].x = -1; R[15].V[0].y = 0;	R[15].V[1].x = -1; R[15].V[1].y = 2;
	R[15].V[2].x = 1; R[15].V[2].y = 2;	R[15].V[3].x = 1; R[15].V[3].y = 0;
}

void init() {


	//Initialize Brobot Parts
	initBot();
	//Set current part that is in focus and color it red
	R[current].colors[0] = 1.0f;	
}


void drawQuad(Rect R) {
	//, const float* c) {

	glColor3fv(R.colors);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
		glVertex2f(R.V[i].x, R.V[i].y);
	glEnd();
}

//CALLBACK: Reshape Function
void reshape(int w, int h)
{
	win_width = w;
	win_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
	glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

	glutPostRedisplay();
}

//CALLBACK: Display Function
void display(void) {

	R[current].colors[0] = 1.0f;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	R[current].drawBot();

	/// . . . . . 

	glutSwapBuffers();
}

/*
////ASCII Required
	A : 65, 97  (lowercase)
	D : 68, 100 (lowercase)
*/

//CALLBACK: Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 27:exit(0); //27 - ESC
		    break;

	case 65: 
	case 97:	R[current].rotation -= 2.75; break;

	case 68:
	case 100:	R[current].rotation += 2.75; break;

	default: break;		

	}
	
	glutPostRedisplay();
}

//CALLBACK: Special Function
void specialInput(int key, int x, int y) {

	switch (key) {

		//Cycle between parent and children rects
	case GLUT_KEY_UP:
		R[current].colors[0] = 0.0f;		
		current = (current+1)%15; break;

	case GLUT_KEY_DOWN: 
		R[current].colors[0] = 0.0f;		
		if (current > 0)
			current--;
		else if (current == 0) 
			current = 15;
		break;
		//Cycle between children rects on the same level	

	default: break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	////Initialization
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("BROBOT - Your Friendly Brotherly Robot");

	////Callbacks

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//For A & D
	glutKeyboardFunc(keyboard);
	//glutKeyboardUpFunc(keyboardUp);
	//For Arrow Keys
	glutSpecialFunc(specialInput);
	//glutSpecialUpFunc(specialInputUp);
	//Run Main Loop
	glutMainLoop();

	return 0;

}