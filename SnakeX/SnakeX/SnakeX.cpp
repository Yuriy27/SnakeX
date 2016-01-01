// SnakeX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "glut.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int speed = 50;
int score = 0;

int w = 30;
int h = 20;
int size = 30;

int scrW = w * size;
int scrH = h * size;

int slen = 2;
const int flen = 1;
const int maxSlen = 70;

bool flag = true;

enum Direction
{
	Up,
	Down,
	Left,
	Right,
} dir;

struct Snake
{
public:
	int x;
	int y;
	void Paint()
	{
		glColor3f(0, 0, 1);
		glRectf(x*size, y*size, (x + 1)*size, (y + 1)*size);
	}
} snake[maxSlen];

struct Fruit
{
public:
	int x;
	int y;
	void Create()
	{
		x = rand() % w;
		y = rand() % h;
		for (int i = 0; i < slen; i++)
			if (snake[i].x == x && snake[i].y == y)
				Create();
	}
	void Paint()
	{
		glColor3f(1, 0, 0);
		glRectf(x*size, y*size, (x + 1)*size, (y + 1)*size);
	}
} fruits[flen];

void Draw()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < slen; i++)
	    snake[i].Paint();
	for (int i = 0; i < flen; i++)
		fruits[i].Paint();

	glFlush();
}

void Update()
{
	for (int i = slen; i>0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (dir == Up)
		snake[0].y += 1;
	if (dir == Left)
		snake[0].x -= 1;
	if (dir == Right)
		snake[0].x += 1;
	if (dir == Down)
		snake[0].y -= 1;

	for (int i = 0; i < flen; i++)
	{
		if (fruits[i].x == snake[0].x && fruits[i].y == snake[0].y)
		{
			fruits[i].Create();
			slen++;
			score++;
		}
	}

	if (snake[0].x < 0)
		snake[0].x = w;
	else
	    if (snake[0].x >= w)
	     	snake[0].x = 0;
	    else
			if (snake[0].y < 0)
		        snake[0].y = h;
			else   
				if (snake[0].y >= h)
		            snake[0].y = 0;

	for (int i = 1; i < slen; i++)
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			glutDestroyWindow(1);
			clog << score << endl;
			cin.get();
			exit(0);
		}

	if (slen == maxSlen)
		slen = 2;
}

void timer(int b)
{
	flag = true;
	Update();
	Draw();
	
	glutTimerFunc(speed, timer, 0);
}

void KeyPress(unsigned char key, int a, int b)
{
	if (flag == true)
	{
		switch (key)
		{
		case 27:
			exit(0); 
			break;
		case 'w':
			if (dir != Down)
			{
				dir = Up;
			} break;
		case 'd':
			if (dir != Left)
			{
				dir = Right;
			} break;
		case 'a':
			if (dir != Right)
			{
				dir = Left;
			} break;
		case 's':
			if (dir != Up)
			{
				dir = Down;
			} break;
		case 'q':
			if (dir != Up)
			{
				if (slen > 2)
				    slen--;
			} break;
		case 'e':
			if (dir != Up)
			{
				if (slen < maxSlen)
					slen++;
			} break;
		}
	}
	flag = false;
}

void Init()
{
	srand(time(0));
	for (int i = 0; i < maxSlen; i++)
	{
		snake[i].x = 2;
		snake[i].y = 2;
	}
	for (int i = 0; i < flen; i++)
		fruits[i].Create();
}

int main(int argc, char** argv)
{
	Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(scrW, scrH);
	glutCreateWindow("Game");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, scrW, 0, scrH);

	glutDisplayFunc(Draw);
	glutKeyboardFunc(KeyPress);
	glutTimerFunc(speed, timer, 0);

	glutMainLoop();
	

	return 0;
}

