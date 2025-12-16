#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

CONST float PI = 3.14159;

//sphere
GLUquadricObj* sphere = gluNewQuadric();
GLUquadricObj* shadow = gluNewQuadric();
//cone
GLUquadricObj* cone = gluNewQuadric();

int renderNum = 1;

//view perspective
float rotatex = 0, rotatey = 0, rotatez = 0;
float rotateinc = 5;
float translatex = 0, translatey = 0, translatez = 0;
float translateinc = 0.1;
bool changeView = false;

GLuint metalTex = 0;

BITMAP BMP;
HBITMAP hBMP = NULL;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {

		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case '1':
			renderNum = 1;
			break;

		case '2':
			renderNum = 2;
			break;

		case '3':
			renderNum = 3;
			break;

		case '4':
			renderNum = 4;
			break;

		case '5':
			renderNum = 5;
			break;

		case '6':
			renderNum = 6;
			break;

		case VK_UP:
			rotatex -= rotateinc;
			break;

		case VK_LEFT:
			rotatey -= rotateinc;
			break;

		case VK_DOWN:
			rotatex += rotateinc;
			break;

		case VK_RIGHT:
			rotatey += rotateinc;
			break;

		case VK_SPACE:

			break;

		case 'W':
			translatey -= translateinc;
			break;

		case 'S':
			translatey += translateinc;
			break;

		case 'D':
			translatex -= translateinc;
			break;

		case 'A':
			translatex += translateinc;
			break;

		case 'Q':
			translatez += translateinc;
			break;

		case 'E':
			translatez -= translateinc;
			break;

		case 'U':

			break;

		case 'I':

			break;

		case 'K':

			break;

		case 'Y':
			changeView = !changeView;
			break;

		}
		break;

	case WM_KEYUP:
		switch (wParam) {
		case 'W':

			break;
		case 'S':

			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

// =================================== ZC (START) ========================================
bool LoadBMPTexture(const char* filename, GLuint& textureID) {
	HBITMAP hBMP;
	BITMAP BMP;

	// Load the bitmap from file
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (hBMP == NULL) {
		std::string errorMsg = "Failed to load ";
		errorMsg += filename;
		MessageBox(NULL, errorMsg.c_str(), "Error", MB_OK);
		return false;
	}

	GetObject(hBMP, sizeof(BMP), &BMP);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	return true;
}

void calculateNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float* nx, float* ny, float* nz) {
	//calculate two vectors from the three points
	float ux = x2 - x1;
	float uy = y2 - y1;
	float uz = z2 - z1;

	float vx = x3 - x1;
	float vy = y3 - y1;
	float vz = z3 - z1;

	//calculate cross product
	*nx = (uy * vz) - (uz * vy);
	*ny = (uz * vx) - (ux * vz);
	*nz = (ux * vy) - (uy * vx);

	//normalize the normal vector
	float length = sqrt((*nx) * (*nx) + (*ny) * (*ny) + (*nz) * (*nz));
	if (length > 0) {
		*nx /= length;
		*ny /= length;
		*nz /= length;
	}
}

void drawRectangle3D(float r, float g, float b, float x, float y, float z, float width, float height, GLuint texture) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	glBindTexture(GL_TEXTURE_2D, texture);

	//calculate normal for the rectangle (using first 3 vertices)
	float x1 = x, y1 = y, z1 = z;
	float x2 = x, y2 = y - height, z2 = z;
	float x3 = x + width, y3 = y - height, z3 = z;
	float nx, ny, nz;
	calculateNormal(x1, y1, z1, x2, y2, z2, x3, y3, z3, &nx, &ny, &nz);

	glBegin(GL_QUADS);
	glNormal3f(nx, ny, nz);
	glTexCoord2f(0, 1);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y - height, z);
	glTexCoord2f(1, 0);
	glVertex3f(x + width, y - height, z);
	glTexCoord2f(1, 1);
	glVertex3f(x + width, y, z);
	glEnd();
}

void drawBox(float r, float g, float b, float x, float y, float z, float width, float height, float depth, GLuint texture) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	//front
	glNormal3f(0, 0, 1);
	glPushMatrix();
	glTranslated(0, 0, depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width, height, texture);
	glPopMatrix();

	//back
	glNormal3f(0, 0, -1);
	glPushMatrix();
	glTranslated(0, 0, -depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width, height, texture);
	glPopMatrix();

	//left
	glNormal3f(-1, 0, 0);
	glPushMatrix();
	glTranslated(-width / 2, 0, 0);
	glRotated(90, 0, 1, 0);
	drawRectangle3D(r, g, b, -depth / 2, height / 2, 0, depth, height, texture);
	glPopMatrix();

	//right
	glNormal3f(1, 0, 0);
	glPushMatrix();
	glTranslated(width / 2, 0, 0);
	glRotated(-90, 0, 1, 0);
	drawRectangle3D(r, g, b, -depth / 2, height / 2, 0, depth, height, texture);
	glPopMatrix();

	//top
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslated(0, height / 2, 0);
	glRotated(90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width, depth, texture);
	glPopMatrix();

	//bottom
	glNormal3f(0, -1, 0);
	glPushMatrix();
	glTranslated(0, -height / 2, 0);
	glRotated(-90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width, depth, texture);
	glPopMatrix();
}

void drawTriangle3D(float r, float g, float b, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, GLuint texture) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	glBindTexture(GL_TEXTURE_2D, texture);

	float nx, ny, nz;
	calculateNormal(x1, y1, z1, x2, y2, z2, x3, y3, z3, &nx, &ny, &nz);

	glBegin(GL_TRIANGLES);
	glNormal3f(nx, ny, nz);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glEnd();
}

void drawLine3D(float r, float g, float b, float x1, float y1, float z1, float x2, float y2, float z2, float thick) {
	glLineWidth(thick);
	glColor3f(r, g, b);

	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void shadowSphere(float r, float g, float b, float planeDistance, float sphereX, float sphereRadius, GLfloat* lightPosition) {
	glDisable(GL_LIGHTING);

	GLfloat shadowMat[16] = {
		lightPosition[1], 0, 0, 0,
		-lightPosition[0], 0, -lightPosition[2], -1,
		0, 0, lightPosition[1], 0,
		0, 0, 0, lightPosition[1]
	};

	glPushMatrix();
	glColor3f(r, g, b);
	glTranslatef(0, -planeDistance + 0.001, 0);
	glMultMatrixf(shadowMat);
	glTranslatef(sphereX, 0, 0);
	gluSphere(shadow, sphereRadius, 100, 100);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void drawSphere(float r, float g, float b, float alpha, float x, float y, float z, float rad, GLuint texture) {
	glColor4f(r, g, b, alpha);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
	glTranslated(x, y, z);
	gluSphere(sphere, rad, 100, 100);
	glPopMatrix();
}

void drawCylinder(float r, float g, float b, float x, float y, float z, float baseRad, float topRad, float height, GLuint texture) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
	glTranslated(x, y, z);
	gluCylinder(cone, baseRad, topRad, height, 100, 100);
	glPopMatrix();
}

void drawDonut(float r, float g, float b, float majorRadius, float minorRadius, float arcAngle, GLuint texture) {
	//majorRadius: distance from center of torus to center of tube
	//minorRadius: radius of the tube
	//segments: number of segments around the major circle
	//arcAngle: angle in degrees (360 = full donut, 180 = half, 90 = quarter)

	glColor3f(r, g, b);
	GLfloat col[] = { r, g, b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	//convert arcAngle to radians and calculate how many segments to draw
	float arcRadians = (arcAngle / 180.0f) * PI; //convert angle to radian (total angle to draw)
	float angleStep = arcRadians / 40; //angle to turn for the next segment

	int tubeSegments = 20; //number of segments around the tube cross section (higher means rounder)

	for (int i = 0; i < 40; i++) { //draw 1 segment between angle1 and angle2
		float angle1 = i * angleStep;
		float angle2 = (i + 1) * angleStep;

		//texture coordinate for major circle (0 to 1 along the donut)
		float u1 = (float)i / 40;
		float u2 = (float)(i + 1) / 40;

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= tubeSegments; j++) { //draw tube cross section to make it rounder
			//formula source: https://www.nosco.ch/mathematics/en/torus.php
			/*
			function f = torus(r, R, numGridPoints)
				gridPoints = linspace(0, 2*pi, numGridPoints);
				[u, v] = meshgrid(gridPoints, gridPoints);
				x = (R + r * cos(v)) * cos(u);
				y = (R + r * cos(v)) * sin(u);
				z = r * sin(v);
				surf(x, y, z);
			end
			*/
			float tubeAngle = (j * 2 * PI) / tubeSegments; //calculate which face we are currently drawing

			//texture coordinate for tube cross section (0 to 1 around the tube)
			float v = (float)j / tubeSegments;

			//first ring
			float x1 = (majorRadius + minorRadius * cos(tubeAngle)) * cos(angle1);
			float y1 = minorRadius * sin(tubeAngle);
			float z1 = (majorRadius + minorRadius * cos(tubeAngle)) * sin(angle1);

			//normal for first point
			float nx1 = cos(tubeAngle) * cos(angle1);
			float ny1 = sin(tubeAngle);
			float nz1 = cos(tubeAngle) * sin(angle1);
			glNormal3f(nx1, ny1, nz1);
			glVertex3f(x1, y1, z1);

			//second ring
			float x2 = (majorRadius + minorRadius * cos(tubeAngle)) * cos(angle2);
			float y2 = minorRadius * sin(tubeAngle);
			float z2 = (majorRadius + minorRadius * cos(tubeAngle)) * sin(angle2);

			//normal for second point
			float nx2 = cos(tubeAngle) * cos(angle2);
			float ny2 = sin(tubeAngle);
			float nz2 = cos(tubeAngle) * sin(angle2);
			glNormal3f(nx2, ny2, nz2);
			glVertex3f(x2, y2, z2);
		}
		glEnd();
	}
}

void drawDonutOutline(float r, float g, float b, float majorRadius, float minorRadius, int numCircles, float arcAngle, float lineThickness) {
	//majorRadius: distance from center of torus to center of tube
	//minorRadius: radius of the tube
	//numCircles: number of vertical circles to draw around the donut
	//arcAngle: angle in degrees (360 = full donut, 180 = half, 90 = quarter)

	glColor3f(r, g, b);
	GLfloat col[] = { r, g, b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	glLineWidth(lineThickness);

	float arcRadians = (arcAngle / 180.0f) * PI; //convert arcAngle to radians
	float realNumCircles = (arcAngle / 360) * numCircles; //calculate how many lines to draw based on the arcangle
	float angleStep = arcRadians / (realNumCircles - 1); //divide by numCircles-1 to include both start and end

	int tubeSegments = 50; //number of points to create smooth circle

	//draw vertical circles at evenly spaced positions
	for (int i = 0; i < realNumCircles; i++) {
		float majorAngle = i * angleStep;

		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < tubeSegments; j++) {
			float tubeAngle = (j * 2 * PI) / tubeSegments;

			//calculate position on the vertical circle
			float xPos = (majorRadius + minorRadius * cos(tubeAngle)) * cos(majorAngle);
			float yPos = minorRadius * sin(tubeAngle);
			float zPos = (majorRadius + minorRadius * cos(tubeAngle)) * sin(majorAngle);

			glVertex3f(xPos, yPos, zPos);
		}
		glEnd();
	}
}

void drawMetalStrips(float r, float g, float b, float majorRadius, float minorRadius, float arcAngle, GLuint texture) {
	drawDonut(r, g, b, majorRadius, minorRadius, arcAngle, metalTex);
	drawDonutOutline(0, 0, 0, majorRadius, minorRadius, 40, arcAngle, 1);
}

void drawQuadMetalStrips(int x, int y, int z) {
	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(0, 0, 1, 0);
	glRotated(-18 * x, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 90, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(35, 0, 1, 0);
	glRotated(-36 * x, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 120, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(60, 0, 1, 0);
	glRotated(-52 * x, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 120, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(60, 0, 1, 0);
	glRotated(-75 * x, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 110, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(70, 0, 1, 0);
	glRotated(-90 * x, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 70, metalTex);
	glPopMatrix();

}

void drawSphereMetalStrips() {
	//center (vertical)
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 360, metalTex);
	glPopMatrix();

	//center (horizontal)
	glPushMatrix();
	glScaled(1, 1, 0.9);
	drawMetalStrips(0.7, 0.7, 0.7, 0.5, 0.1, 360, metalTex);
	glPopMatrix();

	//top left
	drawQuadMetalStrips(1, 1, 1);

	//top right
	drawQuadMetalStrips(-1, 1, 1);

	//bot left
	drawQuadMetalStrips(-1, -1, 1);

	//bot right
	drawQuadMetalStrips(1, -1, 1);
}

void drawEye() {
	//left eye
	//eyebrowns
	glPushMatrix();
	glTranslated(-0.3, -0.1, 0.4);
	glScaled(1, 1, 2);
	glRotated(-90, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.3, 0.05, 180, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.3, -0.1, 0.4);
	glScaled(1, 1, 2);
	glRotated(90, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.3, 0.05, 180, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.3, -0.1, 0.4);
	drawSphere(1, 1, 1, 1, 0, 0, 0, 0.25, metalTex);
	glPopMatrix();

	//right eye
	//eyebrowns
	glPushMatrix();
	glTranslated(0.3, -0.1, 0.4);
	glScaled(1, 1, 2);
	glRotated(-90, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.3, 0.05, 180, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, -0.1, 0.4);
	glScaled(1, 1, 2);
	glRotated(90, 1, 0, 0);
	drawMetalStrips(0.7, 0.7, 0.7, 0.3, 0.05, 180, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.3, -0.1, 0.4);
	drawSphere(1, 1, 1, 1, 0, 0, 0, 0.25, metalTex);
	glPopMatrix();
}

void manageRotations() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (rotatex >= 360) {
		rotatex -= 360;
	}
	if (rotatex < 0) {
		rotatex += 360;
	}
	if (rotatey >= 360) {
		rotatey -= 360;
	}
	if (rotatey < 0) {
		rotatey += 360;
	}

	if (changeView) {
		glFrustum(-0.16, 0.16, -0.09, 0.09, 0.1, 5);
	}
	if (!changeView) {
		glOrtho(-1.6 * 2, 1.6 * 2, -0.9 * 2, 0.9 * 2, -2, 2);
	}
	glTranslated(translatex, translatey, translatez);
	glRotated(rotatex, 1, 0, 0);
	glRotated(rotatey, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
}
// =================================== ZC (END) ========================================

void display()
{
	glClearColor(0.529, 0.808, 0.922, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glShadeModel(GL_SMOOTH); //shader

	// ======= FOR POINTS =======
	//glPointSize(50);
	//glBegin(GL_POINTS);
	// ==========================

	// ====== FOR LINES =========
	//glLineWidth(5);
	//glBegin(GL_LINE_LOOP);
	// ==========================

	switch (renderNum) {
		//ZC
	case 1:
		manageRotations();

		//head
		drawSphereMetalStrips();

		glPushMatrix();
		glTranslated(0, -0.8, -0.3);
		drawSphereMetalStrips();
		glPopMatrix();

		glPushMatrix();
		glScaled(1, 1.1, 1);
		glTranslated(-0.3, -0.5, -0.2);
		drawSphereMetalStrips();
		glPopMatrix();

		glPushMatrix();
		glScaled(1, 1.1, 1);
		glTranslated(0.3, -0.5, -0.2);
		drawSphereMetalStrips();
		glPopMatrix();

		//eye section
		drawEye();

		break;

	case 2: {

	}




	}



	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1600, 900,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-2, 2, -2, 2, -2, 2);
	glEnable(GL_DEPTH_TEST);
	//glFrustum(-0.16, 0.16, -0.09, 0.09, 0.1, 5);
	//gluPerspective(90.0f / (16 / 9), 16.0f / 9, 0.1, 5);

	//texture things
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricTexture(shadow, GL_TRUE);
	gluQuadricNormals(shadow, GLU_SMOOTH);

	gluQuadricTexture(cone, GL_TRUE);
	gluQuadricNormals(cone, GLU_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	LoadBMPTexture("metal.bmp", metalTex);

	glEnable(GL_TEXTURE_2D);



	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------