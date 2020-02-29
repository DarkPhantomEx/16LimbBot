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
	UP & DOWN arrow keys - Cycle between the parent and it's children
	LEFT & RIGHT arrow keys - Cycle between the child nodes at the same level
	A & D keys - Rotate part, and corresponding children left or right, respectively.
*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define NUM_OF_PARTS 16

struct vert {
	float x, y;
};

class Rect {
public:
	vert V[4];
	float colors[3];
}R[NUM_OF_PARTS];

//Parameters for the Window & Canvas
int win_width = 800, win_height = 800;
float canvas_width = 20.0f; float canvas_height = 20.0f;

//Variables to hold the attributes of each part
float colors[3 * NUM_OF_PARTS];
float rotations[NUM_OF_PARTS];

bool keyStates[256];

//To be used as an index for the highlighted rect
int current;

//Initializes variables on program execution. 
void init(){

	/// Initialize Rect vertices
	//LB
	R[0].V[0].x = -2; R[0].V[0].y = 0;	R[0].V[1].x = -2; R[0].V[1].y = 1;
	R[0].V[2].x =  2; R[0].V[2].y = 1;	R[0].V[3].x =  2; R[0].V[3].y = 0;
	//RT
	R[1].V[0].x = -0.5f; R[1].V[0].y =  0;	R[1].V[1].x = -0.5f; R[1].V[1].y = -2;
	R[1].V[2].x =  0.5f; R[1].V[2].y = -2;	R[1].V[3].x =  0.5f; R[1].V[3].y =  0;
	
	R[2].V[0].x = -0.5f; R[2].V[0].y =  0;	R[2].V[1].x = -0.5f; R[2].V[1].y = -2;
	R[2].V[2].x =  0.5f; R[2].V[2].y = -2;	R[2].V[3].x =  0.5f; R[2].V[3].y =  0;
	
	R[3].V[0].x = -1.5f; R[3].V[0].y = 0;	R[3].V[1].x = -1.5f; R[3].V[1].y = -1;
	R[3].V[2].x =  0.5f; R[3].V[2].y = -1;	R[3].V[3].x =  0.5f; R[3].V[3].y = 0;
	//RTend
	//LT
	R[4].V[0].x = -0.5f; R[4].V[0].y =  0;	R[4].V[1].x = -0.5f; R[4].V[1].y = -2;
	R[4].V[2].x =  0.5f; R[4].V[2].y = -2;	R[4].V[3].x =  0.5f; R[4].V[3].y =  0;
	
	R[5].V[0].x = -0.5f; R[5].V[0].y =  0;	R[5].V[1].x = -0.5f; R[5].V[1].y = -2;
	R[5].V[2].x =  0.5f; R[5].V[2].y = -2;	R[5].V[3].x =  0.5f; R[5].V[3].y =  0;
	
	R[6].V[0].x = -0.5f; R[6].V[0].y = 0;	R[6].V[1].x = -0.5f; R[6].V[1].y = -1;
	R[6].V[2].x =  1.5f; R[6].V[2].y = -1;	R[6].V[3].x =  1.5f; R[6].V[3].y = 0;
	//LTend
	//UB
	R[7].V[0].x = -3; R[7].V[0].y = 0;	R[7].V[1].x = -3; R[7].V[1].y = 2;
	R[7].V[2].x =  3; R[7].V[2].y = 2;	R[7].V[3].x =  3; R[7].V[3].y = 0;
	//RA
	R[8].V[0].x =    0; R[8].V[0].y =  0.5f;	R[8].V[1].x = -1.5f; R[8].V[1].y =  0.5f;
	R[8].V[2].x = -1.5f; R[8].V[2].y = -0.5f;	R[8].V[3].x =    0; R[8].V[3].y = -0.5f;

	R[9].V[0].x =    0; R[9].V[0].y =  0.5f;	R[9].V[1].x = -1.5f; R[9].V[1].y =  0.5f;
	R[9].V[2].x = -1.5f; R[9].V[2].y = -0.5f;	R[9].V[3].x =    0; R[9].V[3].y = -0.5f;
	
	R[10].V[0].x = -0.5f; R[10].V[0].y =  0.75f;	R[10].V[1].x =     0; R[10].V[1].y =  0.75f;
	R[10].V[2].x =     0; R[10].V[2].y = -0.75f;	R[10].V[3].x = -0.5f; R[10].V[3].y = -0.75f;
	//RAend
	//LA
	R[11].V[0].x =    0; R[11].V[0].y =  0.5f;	R[11].V[1].x = 1.5f; R[11].V[1].y =  0.5f;
	R[11].V[2].x = 1.5f; R[11].V[2].y = -0.5f;	R[11].V[3].x =    0; R[11].V[3].y = -0.5f;

	R[12].V[0].x =    0; R[12].V[0].y =  0.5f;	R[12].V[1].x = 1.5f; R[12].V[1].y =  0.5f;
	R[12].V[2].x = 1.5f; R[12].V[2].y = -0.5f;	R[12].V[3].x =    0; R[12].V[3].y = -0.5f;
	
	R[13].V[0].x = 0.5f; R[13].V[0].y =  0.75f;	R[13].V[1].x =     0; R[13].V[1].y =  0.75f;
	R[13].V[2].x =     0; R[13].V[2].y = -0.75f;	R[13].V[3].x = 0.5f; R[13].V[3].y = -0.75f;
	//RAend
	//Neck
	R[14].V[0].x = -0.25f; R[14].V[0].y = 0;	R[14].V[1].x = -0.25f; R[14].V[1].y = 0.5f;
	R[14].V[2].x = 0.25f; R[14].V[2].y = 0.5f;	R[14].V[3].x = 0.25f; R[14].V[3].y = 0;
	//Head
	R[15].V[0].x = -1; R[15].V[0].y = 0;	R[15].V[1].x = -1; R[15].V[1].y = 2;
	R[15].V[2].x = 1; R[15].V[2].y = 2;	R[15].V[3].x = 1; R[15].V[3].y = 0;

	
	int current = 0; 
	R[current].colors[0] = 1.0f;
	for(int i = 0; i < 256; i++)
		keyStates[i] = false;

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

void drawQuad(Rect R){
	//, const float* c) {

	glColor3fv(R.colors);
	glLineWidth(.1f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++)
		glVertex2f(R.V[i].x, R.V[i].y);
	glEnd();
}
void display(void) {
////STRUCTURE OF THE BODY (Representation will help with Push/Pop procedure)
//PARENT: (L)ower(B)ody
//	CHILDREN(LB) : (R)ight(T)high, (L)eft(T)high, (U)pper(B)ody,
//	Children(RT) : RT1, RT2
//	Children(LT) : LT1, LT2
//	CHILDREN(UB) : (R)ight(A)rm, (L)eft(A)rm, Neck
//	CHILDREN(RA) : RA1, RA2
//	CHILDREN(LA) : LA1, LA2
//	CHILDREN(Neck) : Head
//	CHILDREN(Head) : null

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawQuad(R[0]);	//LB
	glPushMatrix();
	
	glTranslatef(-1.5f, 0.0f, 0.0f);

	drawQuad(R[1]); //RT
		glPushMatrix();
		glTranslatef(0.0f, -2.0f, 0.0f);
	drawQuad(R[2]); //RT1
			glPushMatrix();
			glTranslatef(0.0f, -2.0f, 0.0f);
	drawQuad(R[3]); //RT2
			glPopMatrix();
		glPopMatrix();
	
	//Back to LB, then LT
	glPopMatrix();
	glPushMatrix();
	
	glTranslatef(1.5f, 0.0f, 0.0f);
	drawQuad(R[4]); //LT
		glPushMatrix();
		glTranslatef(0.0f, -2.0f, 0.0f);
	drawQuad(R[5]); //LT1
			glPushMatrix();
			glTranslatef(0.0f, -2.0f, 0.0f);
	drawQuad(R[6]); //LT2
			glPopMatrix();
		glPopMatrix();

	////Back to LB, then UB
	glPopMatrix();

	glPushMatrix(); //Stores LB, and draws UB with respect to LB
	glTranslatef(0.0f, 1.0f, 0.0f);
	drawQuad(R[7]); //UB
	glPushMatrix(); //Now onwards we wanna draw with respect to UB

	////Push UB, then RA
	glTranslatef(-3, 1.5f, 0);
	drawQuad(R[8]); //RA
		glPushMatrix();
		glTranslatef(-1.5f,0, 0);
		drawQuad(R[9]); //RA1
			glPushMatrix();
			glTranslatef(-1.5f, 0, 0);
	drawQuad(R[10]); //RA2
			glPopMatrix();
		glPopMatrix(); //After this, we're back at UB
	//Back to UB, then LA
	glPopMatrix();
	glPushMatrix();

	glTranslatef(3, 1.5f, 0);
	drawQuad(R[11]); //LA
		glPushMatrix();
		glTranslatef(1.5f, 0, 0);
	drawQuad(R[12]); //LA1
			glPushMatrix();
			glTranslatef(1.5f, 0, 0);
	drawQuad(R[13]); //LA2
			glPopMatrix();
		glPopMatrix();
	
	////Back to UB, then Neck
	glPopMatrix();

	glPushMatrix(); //To draw the Neck w.r.t UB, we push UB
	glTranslatef(0.0f, 2, 0.0f);
	drawQuad(R[14])	; //Neck
		glPushMatrix(); //To draw Head w.r.t Neck
		glTranslatef(0.0f, 0.5f, 0.0f);
	drawQuad(R[15]); //Head

	/// . . . . . 

	glutSwapBuffers();
}

/*
////ASCII Required
	A : 65, 97  (lowercase)
	D : 68, 100 (lowercase)
*/

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // 27: ASCII for 'ESC'
		exit(0);

	unsigned char asciiOffset = 49; // 49 : ASCII for '1'
	/*for (unsigned char i = '1'; i < '7'; i++) {
		if (key == i) {
			keyStates[i] = true;
			colors[(i - asciiOffset) * 3 + 0] = 1.0f;
			colors[(i - asciiOffset) * 3 + 1] = 0.0f;
			colors[(i - asciiOffset) * 3 + 2] = 0.0f;
		}
	}*/
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	unsigned char asciiOffset = 49; // 49 : ASCII for '1'
	/*for (unsigned char i = '1'; i < '7'; i++) {
		if (key == i) {
			keyStates[i] = false;
			colors[(i - asciiOffset) * 3 + 0] = 0.0f;
			colors[(i - asciiOffset) * 3 + 1] = 0.0f;
			colors[(i - asciiOffset) * 3 + 2] = 0.0f;
		}
	}*/
	glutPostRedisplay();
}

void specialInput(int key, int x, int y){
	
	switch (key) {
		
//Cycle between parent and children rects
	case GLUT_KEY_UP: break;

	case GLUT_KEY_DOWN: break;
//Cycle between children rects on the same level	
	case GLUT_KEY_LEFT: break;

	case GLUT_KEY_RIGHT: break;

	default: break;
	}

}

void specialInputUp(int key, int x, int y){

	switch (key) {

//Cycle between parent and children rects
	case GLUT_KEY_UP: break;
	
	case GLUT_KEY_DOWN: break;
//Cycle between children rects on the same level	
	case GLUT_KEY_LEFT: break;
	
	case GLUT_KEY_RIGHT: break;

	default: break;
	}

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
	glutKeyboardUpFunc(keyboardUp);
	//For Arrow Keys
	glutSpecialFunc(specialInput);
	glutSpecialUpFunc(specialInputUp);
	//Run Main Loop
	glutMainLoop();

	return 0;

}