#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include <time.h>

typedef struct{
    float x1;
    float y1;
    float z1;
}Ponto;

float alpha = 0;
float beta = 0;
float delta = 1;

unsigned char key;
int g, e;

Ponto bola;

void DesenhaTextoStroke(char *);

void init(void);

void desenhabola(void);

void desenhatraves(void);

void desenhacampo(void);

void animacao(int);

void display(void);

void keyboard(unsigned char , int , int );

void listeningSpKey(GLint , GLint , GLint );

void desenhaTextoGol(void);

void desenhaTextoErro(void);

void start(void);

void delay(int );


int main(int argc, char **argv)
 {
     glLoadIdentity();
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(800, 800);
     glutCreateWindow("Penalti");
     gluOrtho2D(-4, 4, -4, 4);
     init();

     glutKeyboardFunc(keyboard);
     glutSpecialFunc(listeningSpKey);
     glutDisplayFunc(display);
     glutMainLoop();
 }

 void keyboard(unsigned char key, int x, int y)
{
    if(key == 27)
            exit(0);

     switch(key){

        case'q':
        delta = delta * 1.1f;
        break;

      case 'w':
        delta = delta * 0.9f;
        break;

     case ' ':
        glutTimerFunc(10, animacao, 0);
        break;

     case 'r':
        printf("\n%i gols e %i erros\n", g, e);
        g = 0;
        e = 0;
        bola.x1 = 0.0f;
        bola.y1 = -0.5f;
        bola.z1 = 4.0f;
        break;
    }

     glutPostRedisplay();
 }



void  listeningSpKey (GLint tecla, GLint x, GLint y)
 {
	switch(tecla) {
		case GLUT_KEY_UP:
		        alpha = alpha - 1;
				break;
		case GLUT_KEY_DOWN:
		        alpha = alpha + 1;
				break;
		case GLUT_KEY_LEFT:
		        beta = beta + 1;
				break;
		case GLUT_KEY_RIGHT:
		        beta = beta - 1;
				break;
	}
	glutPostRedisplay();
}

void display(){

     glClearColor(0.0, 0.0, 0.0, 0.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glRotatef(beta, 0, 1, 0);
     glRotatef(alpha, 1, 0, 0);
     glScalef(delta, delta, delta);

     desenhabola();
     desenhatraves();
     desenhacampo();
     desenhaTextoGol();
     desenhaTextoErro();
     glFlush();
     glutSwapBuffers();
 }

 void animacao(int value)
{
    time_t t;
    srand((unsigned) time(&t));
    int r, s;
    r = rand();
    if(r%2 == 0){
        bola.x1 += -0.025;
        bola.y1 += +0.025;
        bola.z1 += -0.1;
    }
    else{
        bola.x1 += -0.025;
        bola.y1 += +0.075;
        bola.z1 += -0.1;
    }

    glutPostRedisplay();


    if(((bola.z1 <= 1.0f)) && ((bola.x1 >= -2.0f) && (bola.x1 <= 2.0f)) && ((bola.y1 <= 1.5f) && (bola.y1 >= -1.5f))){


            g = g+1;
            bola.x1 = 0.0f;
            bola.y1 = -0.5f;
            bola.z1 = 4.0f;
            return;
    }
    else if(bola.z1 <= 1.0f)
    {
        e = e+1;
        bola.x1 = 0.0f;
        bola.y1 = -0.5f;
        bola.z1 = 4.0f;
        return;
    }



    glutTimerFunc(10, animacao, 0);
}

void desenhacampo(void)
{
    glPushMatrix();
        glTranslatef(0, -1.5, 0);
        glScalef(4, 0.5f, 10);
        glColor3f(0, 0, 1);
        glutSolidCube(1.0f);
    glPopMatrix();
}

void desenhatraves(void)
{
    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3f(2, 2 ,0);
        glVertex3f(-2.0f, -1.5f, 1.0f);
        glVertex3f(-2.0f, 1.5f, 1.0f);

        glVertex3f(2.0f, -1.5f, 1.0f);
        glVertex3f(2.0f, 1.5f, 1.0f);

        glVertex3f(-2.0f, 1.5f, 1.0f);
        glVertex3f(2.0f, 1.5f, 1.0f);

        glVertex3f(-2.0f, -1.5f, 1.0f);
        glVertex3f(2.0f, -1.5f, 1.0f);
    glEnd();
}

void desenhabola(void)
 {
     glColor3f(2, 2 ,2);
     glPushMatrix();
     glTranslatef(bola.x1, bola.y1, bola.z1);
     glutWireSphere(0.5f, 40, 20);
     glPopMatrix();
 }

 void DesenhaTextoStroke(char *aux)
 {
	char *p;
	p = aux;
	while(*p)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*p++);
}

void init()
{
     glClearColor(0, 0, 0, 0);
     glEnable(GL_DEPTH_TEST);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-6, 6, -6, 6, -6, 6);

     bola.x1 = 0.0f;
     bola.y1 = -0.5f;
     bola.z1 = 4.0f;
 }

void desenhaTextoErro(){

    char errosStr[3];

    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    glColor3f(1,0,0);
    glTranslatef(-600,700,0);
    glScalef(1, 1, 0); // diminui o tamanho do fonte
    glLineWidth(2); // define a espessura da linha
    DesenhaTextoStroke("Erros:\n");
    sprintf(errosStr, "%d", e);
    DesenhaTextoStroke(errosStr);
    glFlush();
}

 void desenhaTextoGol(){

    char golsStr[3];

    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    glColor3f(0,1,0);
    glTranslatef(-600,900,0);
    glScalef(1, 1, 0);
    glLineWidth(2);
    DesenhaTextoStroke("Gols:\n");
    sprintf(golsStr, "%d", g);
    DesenhaTextoStroke(golsStr);
    glFlush();
}
