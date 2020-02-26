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

//Parameters for the Window & Canvas
int win_width = 800, win_height = 800;
float canvas_width = 20.0f; float canvas_height = 20.0f;

//Variables to hold the attributes of each part
float colors[3 * NUM_OF_PARTS];
float rotations[NUM_OF_PARTS];

bool keyStates[256];

//Initializes variables on program execution. 
void init(){

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

void display(void) {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/// . . . . . 

	glutSwapBuffers();
}

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

int main(int argc, char* argv[])
{
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("BROBOT - Your Friendly Brotherly Robot");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMainLoop();
	return 0;

}