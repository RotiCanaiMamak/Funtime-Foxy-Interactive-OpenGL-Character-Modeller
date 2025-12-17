#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include <string>
#include <cmath>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



CONST float PI = 3.14159;

//sphere
GLUquadricObj* sphere = gluNewQuadric();
GLUquadricObj* shadow = gluNewQuadric();
//cone
GLUquadricObj* cone = gluNewQuadric();
GLUquadricObj* cylinder = gluNewQuadric();
GLUquadricObj* disk = gluNewQuadric();

int renderNum = 2;

//For Arm
// Rotation
float RotationX = 0.0f;
float RotationY = 0.0f;
float RotationZ = 0.0f;
float rotationSpeed = 1.0f;

//Rotation of Arm
float upperArmRotation = 0.0f;
float lowerArmRotation = 0.0f;
float upperArmRotation2 = 0.0f;
bool faceOpen = false;
float faceOpenAngle = 0.0f;
float faceOpenSpeed = 0.9f;
bool showJaw = true;

//view perspective
float rotatex = 0, rotatey = 0, rotatez = 0;
float rotateinc = 5;
float translatex = 0, translatey = 0, translatez = -6;
float translateinc = 0.1;
bool changeView = true;

// Mouse rotation
bool isMouseDown = false;
int lastMouseX = 0, lastMouseY = 0;
float mouseRotateX = 0, mouseRotateY = 0;

//texture
GLuint metalTex = 0;
GLuint whiteTex = 0;
GLuint teethTex = 0;
GLuint plasticTex = 0;
GLuint eyeTex = 0;

BITMAP BMP;
HBITMAP hBMP = NULL;

//metal Tex
float metalR = 0.7, metalG = 0.7, metalB = 0.7;
//teeth Tex
float teethR = 0.8, teethG = 0.8, teethB = 0.8;

//eye
float isBlinked = 0;

//rotation testing
float testAngle = 0;
float testAngle2 = 0;
bool removeShell = false;

//qf
float rotateobjx, rotateobjy, rotateobjz, rotatearmx, rotatearmy, rotatearmz, rotatelowerarmx, rotatelowerarmy, rotatelowerarmz, rotatewristx, rotatewristy, rotatewristz, rotatethumbx, rotatethumby, rotatethumbz, rotateffx, rotateffy, rotateffz, rotatemfx, rotatemfy, rotatemfz, rotaterfx, rotaterfy, rotaterfz, rotatelfx, rotatelfy, rotatelfz, rotatefsttoe, rotatescdtoe, rotatethdtoe, rotatefourtoe, rotatethigh, rotatecalf, rotatefoot;
int keyset = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		isMouseDown = true;
		lastMouseX = LOWORD(lParam);
		lastMouseY = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		isMouseDown = false;
		break;

	case WM_MOUSEMOVE:
		if (isMouseDown) {
			int currentX = LOWORD(lParam);
			int currentY = HIWORD(lParam);

			mouseRotateY += (currentX - lastMouseX) * 0.5f;
			mouseRotateX += (currentY - lastMouseY) * 0.5f;

			lastMouseX = currentX;
			lastMouseY = currentY;
		}
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

		case'0':
			isBlinked--;
			if (isBlinked < 0) {
				isBlinked = 0;
			}
			testAngle--;
			if (testAngle < 0) {
				testAngle = 0;
			}
			testAngle2--;
			if (testAngle < 0) {
				testAngle = 0;
			}
			break;

		case'P':
			isBlinked++;
			if (isBlinked > 8) {
				isBlinked = 8;
			}
			testAngle++;
			if (testAngle > 10) {
				testAngle = 10;
			}
			testAngle2++;
			if (testAngle2 > 20) {
				testAngle2 = 20;
			}
			break;

			//ch
		//case 'H':    // Lower arm up
		//	lowerArmRotation += rotationSpeed;
		//	if (lowerArmRotation > 90.0f) lowerArmRotation = 90.0f;
		//	break;

		//case 'N':  // Lower arm down
		//	lowerArmRotation -= rotationSpeed;
		//	if (lowerArmRotation < -90.0f) lowerArmRotation = -90.0f;
		//	break;

		//case 'M': // Rotate whole arm right
		//	upperArmRotation += rotationSpeed;
		//	break;

		//case 'B':  // Rotate whole arm left
		//	upperArmRotation -= rotationSpeed;
		//	break;

		//case 'J':  // Rotate whole arm to left
		//	upperArmRotation2 -= rotationSpeed;
		//	break;

		//case 'G':  // Rotate whole arm to right
		//	upperArmRotation2 += rotationSpeed;
		//	break;
			//

		case 'U':
			switch (renderNum) {
			case 1:
				rotatearmx++;
				break;
			case 2:
				rotatelowerarmx++;
				break;
			case 3:
				rotatewristx++;
				break;
			case 4:
				rotatethumbx++;
				break;
			case 5:
				rotateffx++;
				break;
			case 6:
				rotatemfx++;
				break;
			case 7:
				rotaterfx++;
				break;
			case 8:
				rotatelfx++;
				break;
			}
			break;
		case 'O':
			switch (renderNum) {
			case 1:
				rotatearmx--;
				break;
			case 2:
				rotatelowerarmx--;

				break;
			case 3:
				rotatewristx--;
				break;
			case 4:
				rotatethumbx--;
				break;
			case 5:
				rotateffx--;
				break;
			case 6:
				rotatemfx--;
				break;
			case 7:
				rotaterfx--;
				break;
			case 8:
				rotatelfx--;
				break;
			}
			break;
		case 'K':
			switch (renderNum) {
			case 1:
				rotatearmy++;
				break;
			case 2:
				rotatelowerarmy++;
				break;
			case 3:
				rotatewristy++;
				break;
			case 4:
				rotatethumby++;
				break;
			case 5:
				rotateffy++;
				break;
			case 6:
				rotatemfy++;
				break;
			case 7:
				rotaterfy++;
				break;
			case 8:
				rotatelfy++;
				break;
			}
			break;
		case 'L':
			switch (renderNum) {
			case 1:
				rotatearmy--;
				break;
			case 2:
				rotatelowerarmy--;
				break;
			case 3:
				rotatewristy--;
				break;
			case 4:
				rotatethumby--;
				break;
			case 5:
				rotateffy--;
				break;
			case 6:
				rotatemfy--;
				break;
			case 7:
				rotaterfy--;
				break;
			case 8:
				rotatelfy--;
				break;
			}
			break;
		case 'M':
			switch (renderNum) {
			case 1:
				rotatearmz++;
				break;
			case 2:
				rotatelowerarmz++;
				break;
			case 3:
				rotatewristz++;
				break;
			case 4:
				rotatethumbz++;
				break;
			case 5:
				rotateffz++;
				break;
			case 6:
				rotatemfz++;
				break;
			case 7:
				rotaterfz++;
				break;
			case 8:
				rotatelfz++;
				break;
			}
			break;
		case 'N':
			switch (renderNum) {
			case 1:
				rotatearmz--;
				break;
			case 2:
				rotatelowerarmz--;
				break;
			case 3:
				rotatewristz--;
				break;
			case 4:
				rotatethumbz--;
				break;
			case 5:
				rotateffz--;
				break;
			case 6:
				rotatemfz--;
				break;
			case 7:
				rotaterfz--;
				break;
			case 8:
				rotatelfz--;
				break;
			}
			break;

		case 'I':
			faceOpen = !faceOpen; 
			showJaw = !showJaw;
			break;

		case 'Y':
			changeView = !changeView;
			break;

		case 'Z':
			removeShell = !removeShell;
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
//ch's function for me
void drawOval3D(float r, float g, float b, float x, float y, float z, float radiusX, float radiusY, float radiusZ);

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
	gluCylinder(cone, baseRad, topRad, height, 50, 50);
	glPopMatrix();
}

void drawDonut(float r, float g, float b, float majorRadius, float minorRadius, float arcAngle, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	//majorRadius: distance from center of torus to center of tube
	//minorRadius: radius of the tube
	//segments: number of segments around the major circle
	//arcAngle: angle in degrees (360 = full donut, 180 = half, 90 = quarter)
	float segmentsToDraw = 10;

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(r, g, b);
	GLfloat col[] = { r, g, b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	//convert arcAngle to radians and calculate how many segments to draw
	float arcRadians = (arcAngle / 180.0f) * PI; //convert angle to radian (total angle to draw)
	float angleStep = arcRadians / segmentsToDraw; //angle to turn for the next segment

	int tubeSegments = 20; //number of segments around the tube cross section (higher means rounder)

	for (int i = 0; i < segmentsToDraw; i++) { //draw 1 segment between angle1 and angle2
		float angle1 = i * angleStep;
		float angle2 = (i + 1) * angleStep;

		//texture coordinate for major circle (0 to 1 along the donut)
		float u1, u2;

		if (flipTex) {
			u1 = 1.0f - (float)i / segmentsToDraw;
			u2 = 1.0f - (float)(i + 1) / segmentsToDraw;
		}
		else {
			u1 = (float)i / segmentsToDraw;
			u2 = (float)(i + 1) / segmentsToDraw;
		}

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
			glNormal3f(flipX * nx1, flipY * ny1, flipZ * nz1);
			glTexCoord2f(u1, v);
			glVertex3f(x1, y1, z1);

			//second ring
			float x2 = (majorRadius + minorRadius * cos(tubeAngle)) * cos(angle2);
			float y2 = minorRadius * sin(tubeAngle);
			float z2 = (majorRadius + minorRadius * cos(tubeAngle)) * sin(angle2);

			//normal for second point
			float nx2 = cos(tubeAngle) * cos(angle2);
			float ny2 = sin(tubeAngle);
			float nz2 = cos(tubeAngle) * sin(angle2);
			glNormal3f(flipX * nx2, flipY * ny2, flipZ * nz2);
			glTexCoord2f(u2, v);
			glVertex3f(x2, y2, z2);
		}
		glEnd();
	}
}

void drawDonutLow(float r, float g, float b, float majorRadius, float minorRadius, float arcAngle, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	//majorRadius: distance from center of torus to center of tube
	//minorRadius: radius of the tube
	//segments: number of segments around the major circle
	//arcAngle: angle in degrees (360 = full donut, 180 = half, 90 = quarter)
	float segmentsToDraw = 3;

	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(r, g, b);
	GLfloat col[] = { r, g, b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	//convert arcAngle to radians and calculate how many segments to draw
	float arcRadians = (arcAngle / 180.0f) * PI; //convert angle to radian (total angle to draw)
	float angleStep = arcRadians / segmentsToDraw; //angle to turn for the next segment

	int tubeSegments = 20; //number of segments around the tube cross section (higher means rounder)

	for (int i = 0; i < segmentsToDraw; i++) { //draw 1 segment between angle1 and angle2
		float angle1 = i * angleStep;
		float angle2 = (i + 1) * angleStep;

		//texture coordinate for major circle (0 to 1 along the donut)
		float u1, u2;

		if (flipTex) {
			u1 = 1.0f - (float)i / segmentsToDraw;
			u2 = 1.0f - (float)(i + 1) / segmentsToDraw;
		}
		else {
			u1 = (float)i / segmentsToDraw;
			u2 = (float)(i + 1) / segmentsToDraw;
		}

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
			glNormal3f(flipX * nx1, flipY * ny1, flipZ * nz1);
			glTexCoord2f(u1, v);
			glVertex3f(x1, y1, z1);

			//second ring
			float x2 = (majorRadius + minorRadius * cos(tubeAngle)) * cos(angle2);
			float y2 = minorRadius * sin(tubeAngle);
			float z2 = (majorRadius + minorRadius * cos(tubeAngle)) * sin(angle2);

			//normal for second point
			float nx2 = cos(tubeAngle) * cos(angle2);
			float ny2 = sin(tubeAngle);
			float nz2 = cos(tubeAngle) * sin(angle2);
			glNormal3f(flipX * nx2, flipY * ny2, flipZ * nz2);
			glTexCoord2f(u2, v);
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

	int tubeSegments = 10; //number of points to create smooth circle

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

void drawMetalStrips(float r, float g, float b, float majorRadius, float minorRadius, float arcAngle, GLuint texture, bool flipTex = false) {
	drawDonut(r, g, b, majorRadius, minorRadius, arcAngle, metalTex, flipTex);
	drawDonutOutline(0, 0, 0, majorRadius, minorRadius, 40, arcAngle, 1);
}

void drawQuadMetalStrips(int x, int y, int z) {
	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(0, 0, 1, 0);
	glRotated(-18 * x, 1, 0, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 90, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(35, 0, 1, 0);
	glRotated(-36 * x, 1, 0, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 120, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(60, 0, 1, 0);
	glRotated(-52 * x, 1, 0, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 120, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(60, 0, 1, 0);
	glRotated(-75 * x, 1, 0, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 110, metalTex);
	glPopMatrix();

	glPushMatrix();
	glScaled(0.8, 0.9, 0.8);
	glRotated(95 * y, 0, 0, 1);
	glRotated(70, 0, 1, 0);
	glRotated(-90 * x, 1, 0, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 70, metalTex);
	glPopMatrix();

}

void drawSphereMetalStrips() {
	//center (vertical)
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 360, metalTex);
	glPopMatrix();

	//center (horizontal)
	glPushMatrix();
	glScaled(1, 1, 0.9);
	drawMetalStrips(metalR, metalG, metalB, 0.5, 0.1, 360, metalTex);
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

void drawEyeMetalStrips(float x, float y, float z, float tranX, float tranY, float tranZ, float direction, bool flipTex = false, bool isDown = false) {
	glPushMatrix();
	glTranslated(0.27 * x, 0.05 * y, 0);
	glRotated(-15 * x + tranX, 0, 1, 0);
	glRotated(10 * x * z + tranZ, 0, 0, 1);//left right
	glTranslated(0, 0.01 * y, 0.045 * z); //translate back pivot point
	glRotated(-90 * y + tranY, 1, 0, 0); //up down
	glTranslated(0, -0.01 * y, -0.045 * z); //translate pivot point

	float end = 9;
	if (isDown) {
		end = 6;
	}

	for (int i = -3; i < end; i++) {
		glPushMatrix();
		glScaled(0.9, 1, 1);
		glRotated(direction * 7.5 * (i + isBlinked), 1, 0, 0);
		drawMetalStrips(metalR, metalG, metalB, 0.3, 0.015, 160, metalTex, flipTex);
		glPopMatrix();
	}

	glPopMatrix();
}

void drawEye() {
	//left eye
	//outline
	glPushMatrix();
	glTranslated(-0.55, -0.1, 0.4);

	//up
	drawEyeMetalStrips(1, 1, 1, 0, 0, 0, 1);
	//down
	drawEyeMetalStrips(1, -1, 1, 0, 0, -27, -1, false, true);
	//back metal strips
	glPushMatrix();
	glTranslated(0.3, 0.05, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, 0, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, -0.05, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	//outer circle
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(metalR, metalG, metalB, 0.07, 0.01, 360, metalTex);
	glPopMatrix();
	//inner circle
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(metalR, metalG, metalB, 0.05, 0.01, 360, metalTex);
	glPopMatrix();
	//center ball
	glPushMatrix();
	glScaled(0.5, 1, 1);
	drawSphere(metalR, metalG, metalB, 1, 0, 0, 0, 0.05, metalTex);
	glPopMatrix();

	glPopMatrix();
	//eye
	glPushMatrix();
	glTranslated(-0.3, -0.1, 0.5);
	drawSphere(1, 1, 1, 1, 0, 0, 0, 0.25, eyeTex);
	glPopMatrix();

	//right eye
	//outline
	glPushMatrix();
	glScaled(-1, 1, 1);
	glTranslated(-0.55, -0.1, 0.4);

	//up
	drawEyeMetalStrips(1, 1, 1, 0, 0, 0, 1, true);
	//down
	drawEyeMetalStrips(1, -1, 1, 0, 0, -27, -1, false, true);
	//back metal strips
	glPushMatrix();
	glTranslated(0.3, 0.05, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, 0, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.3, -0.05, 0.1);
	glRotated(-195, 0, 1, 0);
	drawMetalStrips(metalR, metalG, metalB, 0.3, 0.025, 60, metalTex);
	glPopMatrix();
	//outer circle
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(metalR, metalG, metalB, 0.07, 0.01, 360, metalTex);
	glPopMatrix();
	//inner circle
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	drawMetalStrips(metalR, metalG, metalB, 0.05, 0.01, 360, metalTex);
	glPopMatrix();
	//center ball
	glPushMatrix();
	glScaled(0.5, 1, 1);
	drawSphere(metalR, metalG, metalB, 1, 0, 0, 0, 0.05, metalTex);
	glPopMatrix();

	glPopMatrix();
	//eye
	glPushMatrix();
	glTranslated(0.3, -0.1, 0.5);
	drawSphere(1, 1, 1, 1, 0, 0, 0, 0.25, eyeTex);
	glPopMatrix();
}

void drawTeeth() {
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	drawCylinder(teethR, teethG, teethB, 0, 0, 0, 0.05, 0.02, 0.13, teethTex);
	glPopMatrix();
}

void drawInnerTeeth() {
	glPushMatrix();
	glTranslated(0, -0.665, 0);

	//left
	glPushMatrix();
	glTranslated(-0.135	, 0, 1.53);
	drawTeeth();
	glPopMatrix();

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(-0.175, 0, 1.39 + (i * -0.14));
		drawTeeth();
		glPopMatrix();
	}

	//center
	glPushMatrix();
	glTranslated(0, 0, 1.6);
	drawTeeth();
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslated(0.135, 0, 1.53);
	drawTeeth();
	glPopMatrix();

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(0.175, 0, 1.39 + (i * -0.14));
		drawTeeth();
		glPopMatrix();
	}


	glPopMatrix();
}

void drawInnerJaw() {
	//left metal
	glPushMatrix();
	glScaled(1.2, 0.7, 1);
	glTranslated(-0.15, -0.9, 0.2);
	drawCylinder(metalR, metalG, metalB, 0, 0, 0, 0.05, 0.05, 0.88, metalTex);
	glPopMatrix();
	//right metal
	glPushMatrix();
	glScaled(1.2, 0.7, 1);
	glTranslated(0.15, -0.9, 0.2);
	drawCylinder(metalR, metalG, metalB, 0, 0, 0, 0.05, 0.05, 0.88, metalTex);
	glPopMatrix();
	//curve between left and right metal
	glPushMatrix();
	glScaled(1.2, 0.7, 1);
	glTranslated(0, -0.9, 1.08);
	glRotated(0, 0, 1, 0);
	drawDonut(metalR, metalG, metalB, 0.15, 0.05, 180, metalTex);
	glPopMatrix();
}

void drawNose() {
	//center nose
	glPushMatrix();
	glScaled(1, 0.7, 1);
	glTranslated(0, -0.6, 0.2);

	glPushMatrix();
	drawCylinder(metalR, metalG, metalB, 0, 0, 0, 0.05, 0.05, 1, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1);
	glScaled(1, 1, 0.7);
	drawBox(metalR, metalG, metalB, 0, 0, 0, 0.15, 0.15, 0.15, metalTex);
	glPopMatrix();

	glPopMatrix();

	//center half ring
	glPushMatrix();
	glScaled(1, 1, 1.5);

	glPushMatrix();
	glScaled(1, 1.2, 1.2);
	glTranslated(0, -0.5, 0.27);
	glRotated(-90, 1, 0, 0);
	drawDonut(metalR, metalG, metalB, 0.2, 0.025, 180, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.6, 0.46);
	glRotated(-90, 1, 0, 0);
	drawDonut(metalR, metalG, metalB, 0.2, 0.025, 180, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.6, 0.6);
	glRotated(-90, 1, 0, 0);
	drawDonut(metalR, metalG, metalB, 0.2, 0.025, 180, metalTex);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.6, 0.74);
	glRotated(-90, 1, 0, 0);
	drawDonut(metalR, metalG, metalB, 0.2, 0.025, 180, metalTex);
	glPopMatrix();

	glPopMatrix();

	//upper draw
	drawInnerJaw();
	//metal between center nose and curve
	glPushMatrix();
	glScaled(1.2, 0.7, 0.7);
	glTranslated(0, -0.8, 1.5);
	glRotated(-70, 1, 0, 0);
	glRotated(-90, 0, 0, 1);
	drawDonut(metalR, metalG, metalB, 0.3, 0.05, 60, metalTex);
	glPopMatrix();
}

void drawCurve(float r, float g, float b, float length, GLuint texture, bool leftTrue = true, bool rightTrue = true, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	for (int i = -39; i < 40; i++) {
		glPushMatrix();
		glTranslated(0.01 * i, length * 0.32, length * 0.32);
		glRotatef(90, 0, 0, 1);
		drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
		glPopMatrix();
	}


	if (leftTrue) {
		for (int i = 0; i > -6; i--) {
			glPushMatrix();
			glTranslated(-0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
	if (rightTrue) {
		for (int i = 0; i < 6; i++) {
			glPushMatrix();
			glTranslated(0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
}

void drawCurve2(float r, float g, float b, float length, GLuint texture, bool leftTrue = true, bool rightTrue = true, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	for (int i = -6; i < 40; i++) {
		glPushMatrix();
		glTranslated(0.01 * i, length * 0.32, length * 0.32);
		glRotatef(90, 0, 0, 1);
		drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
		glPopMatrix();
	}


	if (leftTrue) {
		for (int i = 0; i > -6; i--) {
			glPushMatrix();
			glTranslated(-0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
	if (rightTrue) {
		for (int i = 0; i < 6; i++) {
			glPushMatrix();
			glTranslated(0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
}

void drawEntireHead() {
	//head
	drawSphereMetalStrips();

	glPushMatrix();
	glTranslated(0, -0.7, -0.3);
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

	glPushMatrix();
	glTranslated(0, -0.75, 0);
	glRotated(testAngle, 1, 0, 0);
	glTranslated(0, 0.75, 0);

	//nose section
	glPushMatrix();
	glScaled(1, 1, 1.3);
	drawNose();
	glPopMatrix();

	//inner teeth (upper jaw)
	glPushMatrix();
	glTranslated(0, 0.01, 0);
	drawInnerTeeth();
	glPopMatrix();

	glPopMatrix();

	//bottom jaw
	glPushMatrix();
	glScaled(1, 1, 1);
	glTranslated(0, -0.6, 0.2);
	glTranslated(0, -0.5, 0); //translate back
	glRotated(-testAngle, 1, 0, 0);
	glTranslated(0, 0.5, 0); //translate to pivot
	drawInnerJaw();
	glPushMatrix();
	glTranslated(0, -1.27, 0);
	glScaled(1, -1, 0.769);
	drawInnerTeeth();
	glPopMatrix();
	glPopMatrix();

}

void drawCurvedBox(float r, float g, float b, float width, float height, float depth, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	float scale = 0.8f;
	//inset offsets
	float xOffset = (width - width * scale) / 2;
	float yOffset = (height - height * scale) / 2;
	float zOffset = (depth - depth * scale) / 2;

	//top & front
	drawCurve(r, g, b, width, texture, true, false, flipTex, flipX, flipY, flipZ);

	//left & front
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	drawCurve(r, g, b, width, texture, false, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//left & top
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	drawCurve(r, g, b, width, texture, true, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//top & back
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawCurve(r, g, b, width, texture, true, false, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//left & front
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	drawCurve(r, g, b, width, texture, false, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//front
	glNormal3f(0, 0, 1);
	glPushMatrix();
	glTranslated(xOffset, -yOffset, depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale, height * scale, texture);
	glPopMatrix();

	//back
	glNormal3f(0, 0, -1);
	glPushMatrix();
	glTranslated(xOffset, -yOffset, -depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale, height * scale, texture);
	glPopMatrix();

	//left
	glNormal3f(-1, 0, 0);
	glPushMatrix();
	glTranslated(-width / 2, -yOffset, -zOffset);
	glRotated(90, 0, 1, 0);
	drawRectangle3D(r, g, b, -depth / 2, height / 2, 0, depth * scale, height * scale, texture);
	glPopMatrix();

	//top
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslated(xOffset, height / 2, -zOffset);
	glRotated(90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width * scale, depth * scale, texture);
	glPopMatrix();

}

void drawCurvedBox2(float r, float g, float b, float width, float height, float depth, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	float scale = 0.8f;
	//inset offsets
	float xOffset = (width - width * scale) / 2;
	float yOffset = (height - height * scale) / 2;
	float zOffset = (depth - depth * scale) / 2;

	//top & front
	drawCurve2(r, g, b, width, texture, false, false, flipTex, flipX, flipY, flipZ);

	//top & back
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawCurve2(r, g, b, width, texture, false, false, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//front
	glNormal3f(0, 0, 1);
	glPushMatrix();
	glTranslated(xOffset + 0.33, -yOffset, depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale - 0.4, height * scale - 0.6, texture);
	glPopMatrix();

	//back
	glNormal3f(0, 0, -1);
	glPushMatrix();
	glTranslated(xOffset + 0.33, -yOffset, -depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale - 0.4, height * scale, texture);
	glPopMatrix();

	//top
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslated(xOffset + 0.33, height / 2, -zOffset);
	glRotated(90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width * scale - 0.4, depth * scale, texture);
	glPopMatrix();

}

void drawHeadShell(bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	//top left
	glPushMatrix();
	glTranslated(0, -0.5, -0.5);
	glRotated(-testAngle2, 1, 1, 0);
	glTranslated(0, 0.5, 0.5);

	//main shell
	glPushMatrix();
	glTranslated(-0.4, 0.4, 0);
	glScaled(1, 0.7, 1.6);
	drawCurvedBox(1, 1, 1, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();
	//second shell
	glPushMatrix();
	glTranslated(-0.4, -0.1, 0);
	glScaled(1, 0.7, 1.6);
	glRotated(90, 0, 0, 1);
	drawCurvedBox2(1, 1, 1, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();
	//eye corner triangle (right)
	glPushMatrix();
	glTranslated(0, 0.12, 0.8);
	drawTriangle3D(1, 1, 1, 0, 0, 0, 0, -0.15, 0, -0.2, 0, 0, plasticTex);
	glPopMatrix();
	//eye corner triangle (left)
	glPushMatrix();
	glTranslated(-0.6, 0.12, 0.8);
	glRotated(-180, 0, 1, 0);
	drawTriangle3D(1, 1, 1, 0, 0, 0, 0, -0.15, 0, -0.2, 0, 0, plasticTex);
	glPopMatrix();
	//eyelid
	glPushMatrix();
	glTranslated(-0.3,-0.15, 0.8);
	glRotated(-90, 1, 0, 0);
	glScaled(1, 0.5, 1);
	drawDonut(1, 0.7, 0.85, 0.3, 0.025, 180, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();
	//eyebrown
	glPushMatrix();
	glTranslatef(-0.3, -0.2, 0.8);
	glRotatef(60, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glScaled(1, 0.5, 1);
	drawDonut(0.545, 0, 0, 0.5, 0.05, 60, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//ear
	glPushMatrix();
	glTranslatef(-0.8, 1, -0.05);
	glRotatef(-60, 0, 1, 0);
	glRotatef(45, 0, 0, 1);
	glScaled(2, 3, 2);
	drawOval3D(1.0, 0.7, 0.85, 0, 0, 0, 0.07, 0.22, 0.15);
	glPopMatrix();

	glPopMatrix();
}

void drawCurve3(float r, float g, float b, float length, GLuint texture, bool leftTrue = true, bool rightTrue = true, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	for (int i = -39; i < 15; i++) {
		glPushMatrix();
		glTranslated(0.01 * i, length * 0.32, length * 0.32);
		glRotatef(90, 0, 0, 1);
		drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
		glPopMatrix();
	}


	if (leftTrue) {
		for (int i = 0; i > -6; i--) {
			glPushMatrix();
			glTranslated(-0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
	if (rightTrue) {
		for (int i = 0; i < 6; i++) {
			glPushMatrix();
			glTranslated(0.4, length * 0.32, length * 0.32);
			glTranslated(0, 0, -(length / 2));
			glRotatef(1 * i, 0, 1, 0); //left right
			glTranslated(0, 0, (length / 2));
			glRotatef(90, 0, 0, 1);
			drawDonutLow(r, g, b, 0.2 * length, 0.01, 100, texture, flipTex, flipX, flipY, flipZ);
			glPopMatrix();
		}
	}
}

void drawCurvedBox3(float r, float g, float b, float width, float height, float depth, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	float scale = 0.8f;
	//inset offsets
	float xOffset = (width - width * scale) / 2;
	float yOffset = (height - height * scale) / 2;
	float zOffset = (depth - depth * scale) / 2;

	//top & front
	drawCurve3(r, g, b, width, texture, true, false, flipTex, flipX, flipY, flipZ);

	//left & front
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	drawCurve(r, g, b, width, texture, false, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//left & top
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	drawCurve(r, g, b, width, texture, true, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//top & back
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawCurve(r, g, b, width, texture, true, false, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//left & front
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	drawCurve(r, g, b, width, texture, false, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//front
	glNormal3f(0, 0, 1);
	glPushMatrix();
	glTranslated(xOffset, -yOffset, depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale-0.25, height * scale, texture);
	glPopMatrix();

	//back
	glNormal3f(0, 0, -1);
	glPushMatrix();
	glTranslated(xOffset, -yOffset, -depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale, height * scale, texture);
	glPopMatrix();

	//left
	glNormal3f(-1, 0, 0);
	glPushMatrix();
	glTranslated(-width / 2, -yOffset, -zOffset);
	glRotated(90, 0, 1, 0);
	drawRectangle3D(r, g, b, -depth / 2, height / 2, 0, depth * scale, height * scale, texture);
	glPopMatrix();

	//top
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslated(xOffset, height / 2, -zOffset);
	glRotated(90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width * scale, depth * scale, texture);
	glPopMatrix();

}

void drawHeadShell2(bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	glPushMatrix();
	glTranslated(0, 0, -0.05);
	glTranslated(0, -0.2, -0.5);
	glRotated(-testAngle2, 1, 1, 0);
	glTranslated(0, 0.5, 0.5);

	//main shell
	glPushMatrix();
	glTranslated(-0.4, 0.6, 0);
	glScaled(1, 1, 1.7);
	drawCurvedBox3(1, 1, 1, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();
	//second shell
	glPushMatrix();
	glTranslated(-0.4, -0.1, 0);
	glScaled(1, 1, 1.7);
	glRotated(90, 0, 0, 1);
	drawCurvedBox2(1, 1, 1, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();
	//eye corner triangle (center)
	glPushMatrix();
	glTranslated(0, 0.12, 0.845);
	drawTriangle3D(1, 1, 1, -0.25, 0.12, 0, -0.25, -0.14, 0, -0.6, -0.14, 0, plasticTex);
	glPopMatrix();
	//eye corner triangle (left)
	glPushMatrix();
	glTranslated(-0.6, 0.12, 0.845);
	glRotated(-180, 0, 1, 0);
	drawTriangle3D(1, 1, 1, 0, 0.08, 0, 0, -0.25, 0, -0.35, 0.08, 0, plasticTex);
	glPopMatrix();
	//eyelid
	glPushMatrix();
	glTranslated(-0.3, -0.35, 0.85);
	glRotated(30, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glScaled(1, 0.5, 1);
	drawDonut(1, 0.7, 0.85, 0.35, 0.025, 120, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//blush
	glPushMatrix();
	drawSphere(0.545, 0, 0, 1, -0.45, 0.25, 0.8, 0.2, plasticTex);
	glPopMatrix();

	//cheek
	glPushMatrix();
	glTranslated(-0.9, 0.7, 0);
	glScaled(0.5, 0.9, 1.8);
	drawSphere(1, 1, 1, 1, 0, 0, 0, 0.5, plasticTex);
	glPopMatrix();

	glPopMatrix();

}

void drawCurvedBox4(float r, float g, float b, float width, float height, float depth, GLuint texture, bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	glColor3f(r, g, b);
	GLfloat col[] = { r,g,b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	float scale = 0.8f;
	//inset offsets
	float xOffset = (width - width * scale) / 2;
	float yOffset = (height - height * scale) / 2;
	float zOffset = (depth - depth * scale) / 2;

	//top & front
	drawCurve(r, g, b, width, texture, true, false, flipTex, flipX, flipY, flipZ);

	//left & front
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	drawCurve(r, g, b, width, texture, false, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//left & top
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	drawCurve(r, g, b, width, texture, true, true, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//front
	glNormal3f(0, 0, 1);
	glPushMatrix();
	glTranslated(xOffset, -yOffset, depth / 2);
	drawRectangle3D(r, g, b, -width / 2, height / 2, 0, width * scale, height * scale, texture);
	glPopMatrix();

	//left
	glNormal3f(-1, 0, 0);
	glPushMatrix();
	glTranslated(-width / 2, -yOffset, -zOffset);
	glRotated(90, 0, 1, 0);
	drawRectangle3D(r, g, b, -depth / 2, height / 2, 0, depth * scale, height * scale, texture);
	glPopMatrix();

	//top
	glNormal3f(0, 1, 0);
	glPushMatrix();
	glTranslated(xOffset, height / 2, -zOffset);
	glRotated(90, 1, 0, 0);
	drawRectangle3D(r, g, b, -width / 2, depth / 2, 0, width * scale, depth * scale, texture);
	glPopMatrix();

}

void drawOuterNose(bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	//top left
	glPushMatrix();
	glTranslated(-1, 1, 0);
	glRotated(testAngle2, 1, 0, 0);
	glRotated(-testAngle2, 0, 1, 0);
	glTranslated(1, -1, 0);

	//main shell
	glPushMatrix();
	glTranslated(-0.15, -0.55, 1.2);
	glScaled(0.4, 0.5, 1.2);
	drawCurvedBox4(1.0, 0.7, 0.85, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//teeth
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(-0.3, -0.7, 0.8 + (i * 0.2));
		drawTeeth();
		glPopMatrix();
	}

	glPopMatrix();
}

void drawOuterNose2(bool flipTex = false, float flipX = 1, float flipY = 1, float flipZ = 1) {
	//top left
	glPushMatrix();
	glTranslated(0, 0, 0.5);
	glRotated(-testAngle2, 1, 0, 0);
	glRotated(-testAngle2, 0, 1, 0);
	glTranslated(0, 0, -0.5);

	//main shell
	glPushMatrix();
	glTranslated(-0.15, -0.55, 1.2);
	glScaled(0.4, 0.5, 1.2);
	drawCurvedBox4(1, 1, 1, 1, 1, 1, plasticTex, flipTex, flipX, flipY, flipZ);
	glPopMatrix();

	//teeth
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(-0.3, -0.7, 0.8 + (i * 0.2));
		drawTeeth();
		glPopMatrix();
	}

	glPopMatrix();
}


void drawOuterShell() {
	//upper left
	drawHeadShell();

	//upper right
	glPushMatrix();
	glScaled(-1, 1, 1);
	glTranslated(0, 0, 0);
	drawHeadShell(true, -1);
	glPopMatrix();

	//lower left
	glPushMatrix();
	glScaled(1, -1, 1);
	drawHeadShell2(true, false, true);
	glPopMatrix();

	//lower right
	glPushMatrix();
	glScaled(-1, -1, 1);
	drawHeadShell2(true, true, true);
	glPopMatrix();

	//nose (upper left)
	glPushMatrix();
	drawOuterNose();
	glPopMatrix();

	//nose (upper right)
	glPushMatrix();
	glScaled(-1, 1, 1);
	drawOuterNose(true, -1, 1, 1);
	glPopMatrix();

	//nose (bottom left)
	glPushMatrix();
	glScaled(1, -0.8, 1);
	glTranslated(0, 2, -0.3);
	drawOuterNose2(true, 1, -1, 1);
	glPopMatrix();

	//nose (bottom right)
	glPushMatrix();
	glScaled(-1, -0.8, 1);
	glTranslated(0, 2, -0.3);
	drawOuterNose2(true, -1, -1, 1);
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
		gluLookAt(2, 1, 2, 0, 0, 0, 0, 1, 0);

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

//qf
void drawcubeface(float(&arr)[4][3], float colorarr[3], float x, float y, float z) {
	glBegin(GL_QUADS);

	glColor3f(colorarr[0], colorarr[1], colorarr[2]);
	glTexCoord2f(0, 0);
	glVertex3f(arr[0][0] * x, arr[0][1] * y, arr[0][2] * z);
	glTexCoord2f(1, 0);
	glVertex3f(arr[1][0] * x, arr[1][1] * y, arr[1][2] * z);
	glTexCoord2f(1, 1);
	glVertex3f(arr[2][0] * x, arr[2][1] * y, arr[2][2] * z);
	glTexCoord2f(0, 1);
	glVertex3f(arr[3][0] * x, arr[3][1] * y, arr[3][2] * z);
	glEnd();

}

void drawcube(float x, float y, float z) {
	float cuboidpoint[4][3] = {
		{1 ,1,1},
		{1 ,0,1},
		{1 ,0,0},
		{1 ,1,0}
	};
	float color[3] = { 1,1,0 };
	drawcubeface(cuboidpoint, color, x, y, z);

	float cuboidpoint1[4][3] = {
		{1 ,1,0},
		{1 ,0,0},
		{0 ,0,0},
		{0 ,1,0}
	};
	float color1[3] = { 0,1,1 };

	drawcubeface(cuboidpoint1, color1, x, y, z);

	float cuboidpoint2[4][3] = {
		{1 ,1,1},
		{0 ,1,1},
		{0 ,1,0},
		{1 ,1,0}
	};
	float color2[3] = { 0,1,0 };

	drawcubeface(cuboidpoint2, color2, x, y, z);

	float cuboidpoint3[4][3] = {
		{0 ,0,1},
		{0 ,0,0},
		{1 ,0,0},
		{1 ,0,1}
	};
	float color3[3] = { 1,0,1 };

	drawcubeface(cuboidpoint3, color3, x, y, z);

	float cuboidpoint4[4][3] = {
		{0 ,1,1},
		{0 ,1,0},
		{0 ,0,0},
		{0 ,0,1}
	};
	float color4[3] = { 1,0,0 };

	drawcubeface(cuboidpoint4, color4, x, y, z);

	float cuboidpoint5[4][3] = {
		{1 ,1,1},
		{1 ,0,1},
		{0 ,0,1},
		{0 ,1,1}
	};
	float color5[3] = { 1,1,1 };

	drawcubeface(cuboidpoint5, color5, x, y, z);

}

void drawfinger(bool left) {
	glColor3f(1, 0.5, 0);
	gluCylinder(cone, 0.03, 0.02, 0.05, 50, 50);

	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	gluSphere(sphere, 0.02, 100, 100);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.05);

	if (left) {
		glRotatef(-45, 0, 1, 0);
	}
	else {
		glRotatef(45, 0, 1, 0);
	}

	gluCylinder(cone, 0.02, 0.02, 0.05, 50, 50);

	glPushMatrix();
	glTranslatef(0, 0, 0.05);

	gluSphere(sphere, 0.02, 100, 100);

	//nails
	glPushMatrix();
	glTranslatef(0.01, -0.02, 0.01);
	drawcube(0.01, 0.03, 0.02);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawhand(bool left) {
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	//glRotatef(rotateobjx, 1, 0, 0);
	//glRotatef(rotateobjy, 0, 1, 0);
	//glRotatef(rotateobjz, 0, 0, 1);

	//shoulder joint
	glPushMatrix();
	glColor3f(0, 0, 0);

	gluSphere(sphere, 0.28, 100, 100);

	//upper arm
	glPushMatrix();
	glRotatef(rotatearmx, 1, 0, 0);
	glRotatef(rotatearmy, 0, 1, 0);
	glRotatef(rotatearmz, 0, 0, 1);

	glRotatef(90, 1, 0, 0);

	glColor3f(1, 0, 1);
	gluCylinder(cone, 0.3, 0.2, 1, 100, 100);

	//elbow joint
	glPushMatrix();
	glTranslatef(0, 0, 1.1);
	glColor3f(0, 0, 0);
	gluSphere(sphere, 0.19, 100, 100);

	//lower arm
	glPushMatrix();
	glTranslatef(0, 0, 0.1);
	glRotatef(rotatelowerarmx, 1, 0, 1);
	glRotatef(rotatelowerarmy, 0, 1, 0);
	glRotatef(rotatelowerarmz, 0, 0, 1);

	glColor3f(1, 0, 1);
	gluCylinder(cone, 0.2, 0.11, 1, 100, 100);

	//wrist
	glPushMatrix();
	glTranslatef(0, 0, 1.1);
	glRotatef(rotatewristx, 1, 0, 0);
	glRotatef(rotatewristy, 0, 1, 0);
	glRotatef(rotatewristz, 0, 0, 1);

	glColor3f(0, 0, 0);
	gluSphere(sphere, 0.1, 100, 100);

	//palm
	glPushMatrix();
	glTranslatef(-0.05, -0.1, 0.1);

	glColor3f(0.5, 0.5, 0.5);
	drawcube(0.1, 0.2, 0.15);

	//thumb
	glPushMatrix();
	glTranslatef(0.05, 0, 0.08);
	glRotatef(rotatethumbx, 1, 0, 0);
	glRotatef(rotatethumby, 0, 1, 0);
	glRotatef(rotatethumbz, 0, 0, 1);
	glRotatef(45, 1, 0, 0);

	drawfinger(left);

	glPopMatrix();

	//forefinger
	glPushMatrix();
	glTranslatef(0.05, 0.02, 0.15);
	glRotatef(rotateffx, 1, 0, 0);
	glRotatef(rotateffy, 0, 1, 0);
	glRotatef(rotateffz, 0, 0, 1);

	drawfinger(left);

	glPopMatrix();

	//middlefinger
	glPushMatrix();
	glTranslatef(0.05, 0.07, 0.15);
	glRotatef(rotatemfx, 1, 0, 0);
	glRotatef(rotatemfy, 0, 1, 0);
	glRotatef(rotatemfz, 0, 0, 1);
	drawfinger(left);

	glPopMatrix();

	//ringfinger
	glPushMatrix();
	glTranslatef(0.05, 0.12, 0.15);
	glRotatef(rotaterfx, 1, 0, 0);
	glRotatef(rotaterfy, 0, 1, 0);
	glRotatef(rotaterfz, 0, 0, 1);
	drawfinger(left);

	glPopMatrix();

	//smallfinger
	glPushMatrix();
	glTranslatef(0.05, 0.18, 0.15);
	glRotatef(rotatelfx, 1, 0, 0);
	glRotatef(rotatelfy, 0, 1, 0);
	glRotatef(rotatelfz, 0, 0, 1);
	drawfinger(left);

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}


void drawrighttriangle(float x, float y, float z) {
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(0 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 0);
	glVertex3f(1 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 1);
	glVertex3f(1 * x, 0 * y, 1 * z);
	glTexCoord2f(0, 1);
	glVertex3f(0 * x, 0 * y, 1 * z);
	
	glEnd();

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(0 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 0);
	glVertex3f(1 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 1);
	glVertex3f(1 * x, 1 * y, 1 * z);
	glTexCoord2f(0, 1);
	glVertex3f(0 * x, 1 * y, 1 * z);

	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(1,0,0);
	glTexCoord2f(0, 0);
	glVertex3f(0 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 0);
	glVertex3f(0 * x, 0 * y, 1 * z);
	glTexCoord2f(1, 1);
	glVertex3f(0 * x, 1 * y, 1 * z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1 * x, 0 * y, 0 * z);
	glTexCoord2f(1, 0);
	glVertex3f(1 * x, 0 * y, 1 * z);
	glTexCoord2f(1, 1);
	glVertex3f(1 * x, 1 * y, 1 * z);
	glEnd();

}

void drawtoe() {
	glPushMatrix();
	glTranslatef(0.1, 0.1, -0.2);
	glRotatef(180, 0, 0, 1);
	//drawcube(0.15, 0.02, 0.2);
	
	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glRotatef(-20, 1, 0, 0);

	//drawcube(0.15, 0.05, 0.2);
	drawrighttriangle(0.1,0.05,0.2);


	//glPopMatrix();
	glPopMatrix();

}

void drawdecoration(float x,float y,float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glColor3f(0, 0, 0.5);

	gluSphere(sphere, 0.07, 100, 100);

	glPopMatrix();
}

void drawleg(bool left) {
	glPushMatrix();
	
	glColor3f(0, 0, 0);
	gluSphere(sphere, 0.28, 100, 100);
	
	//thigh
	glPushMatrix();
	glRotatef(rotatethigh, 1, 0, 0);

	glRotatef(90, 1, 0, 0);

	glColor3f(1, 0, 1);
	gluCylinder(cone, 0.3, 0.2, 0.5, 100, 100);

	//knee
	glPushMatrix();
	glTranslatef(0, 0, 0.5);

	glColor3f(0, 0, 0);
	gluSphere(sphere, 0.2, 100, 100);

	//calf
	glPushMatrix();
	glTranslatef(0, 0, 0.15);
	glRotatef(rotatecalf, 1, 0, 0);

	glColor3f(1, 0, 1);
	gluCylinder(cone, 0.2, 0.25, 0.5, 100, 100);

	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	gluCylinder(cone, 0.25, 0.2, 0.5, 100, 100);
	
	//decoration
	float leftlegx;
	if (left) {
		leftlegx = -0.1;
	}
	else {
		leftlegx = 0.1;
	}

	drawdecoration(leftlegx, 0.2, 0);
	drawdecoration(leftlegx, 0.2, 0.2);
	drawdecoration(leftlegx,0.2,-0.2);

	//ankle
	glPushMatrix();
	glTranslatef(0, 0, 0.5);

	glColor3f(0, 0, 0);
	gluSphere(sphere, 0.2, 100, 100);

	//foot
	glPushMatrix();
	glTranslatef(-0.2, 0.4, 0.15);
	glRotatef(rotatefoot, 1, 0, 0);
	glRotatef(90, 1, 0, 0);
	
	drawcube(0.46, 0.1, 0.55);
	
	//fst toe
	glPushMatrix();
	glRotatef(rotatefsttoe, 0, 1, 0);

	drawtoe();
	glPopMatrix();

	//scd toe
	glPushMatrix();
	glTranslatef(0.12, 0, 0);
	glRotatef(rotatescdtoe, 0, 1, 0);

	drawtoe();

	glPopMatrix();

	//third toe
	glPushMatrix();
	glTranslatef(0.24, 0, 0);
	glRotatef(rotatethdtoe, 0, 1, 0);

	drawtoe();

	glPopMatrix();

	//fourthtoe
	glPushMatrix();
	glTranslatef(0.36, 0, 0);
	glRotatef(rotatefourtoe, 0, 1, 0);

	drawtoe();

	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

//ch
//ch
//test
float degreeToRadian(int degree) {
	return degree * (PI / 180.0f);
}

// Draw face de
void drawFilledCube(float r, float g, float b, float x, float y, float z, float width, float height, float depth) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);

	// Front face
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(0, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, 0, depth);
	glVertex3f(0, 0, depth);
	glEnd();

	// Back face
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(0, height, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, height, 0);
	glEnd();

	// Top face
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(0, height, 0);
	glVertex3f(width, height, 0);
	glVertex3f(width, height, depth);
	glVertex3f(0, height, depth);
	glEnd();

	// Bottom face
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, depth);
	glVertex3f(width, 0, depth);
	glVertex3f(width, 0, 0);
	glEnd();

	// Right face
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(width, height, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 0, depth);
	glVertex3f(width, height, depth);
	glEnd();

	// Left face
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, height, 0);
	glVertex3f(0, height, depth);
	glVertex3f(0, 0, depth);
	glVertex3f(0, 0, 0);
	glEnd();

	glPopMatrix();
}

//Ear
void drawPyramid(float r, float g, float b, float x, float y, float z, float base, float height) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);

	float halfBase = base / 2.0f;

	// Bottom face
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-halfBase, 0, -halfBase);
	glVertex3f(halfBase, 0, -halfBase);
	glVertex3f(halfBase, 0, halfBase);
	glVertex3f(-halfBase, 0, halfBase);
	glEnd();

	// Front face
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.6f, 0.8f);
	glVertex3f(0, height, 0);
	glVertex3f(-halfBase, 0, halfBase);
	glVertex3f(halfBase, 0, halfBase);
	glEnd();

	// Back face
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0.6f, -0.8f);
	glVertex3f(0, height, 0);
	glVertex3f(halfBase, 0, -halfBase);
	glVertex3f(-halfBase, 0, -halfBase);
	glEnd();

	// Right face
	glBegin(GL_TRIANGLES);
	glNormal3f(0.8f, 0.6f, 0);
	glVertex3f(0, height, 0);
	glVertex3f(halfBase, 0, halfBase);
	glVertex3f(halfBase, 0, -halfBase);
	glEnd();

	// Left face
	glBegin(GL_TRIANGLES);
	glNormal3f(-0.8f, 0.6f, 0);
	glVertex3f(0, height, 0);
	glVertex3f(-halfBase, 0, -halfBase);
	glVertex3f(-halfBase, 0, halfBase);
	glEnd();

	glPopMatrix();
}

//Sphere(Eyeball?)
void drawSphere2(float r, float g, float b, float x, float y, float z, float radius) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);
	gluSphere(sphere, radius, 30, 30);
	glPopMatrix();
}

//Cylinder
void drawCylinder2(float r, float g, float b, float x, float y, float z, float radius, float height) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cone, radius, radius, height, 30, 30);
	glPopMatrix();
}

// Draw 3D Oval
void drawOval3D(float r, float g, float b, float x, float y, float z, float radiusX, float radiusY, float radiusZ) {
	glColor3f(r, g, b);

	// Add material properties for lighting
	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(radiusX, radiusY, radiusZ); // Scale the sphere to make it oval
	gluSphere(sphere, 1.0f, 30, 30);
	glPopMatrix();
}

//Snout
void drawSnout(float r, float g, float b,
	float x, float y, float z,
	float width, float height, float depth)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, depth);

	drawSphere2(r, g, b, 0, 0, 0, 1.0f);

	glPopMatrix();
}

//Hemishpere
void drawHemisphere(float r, float g, float b, float x, float y, float z, float radius, bool frontHalf) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);

	// Draw hemisphere using quad strips
	int stacks = 15;
	int slices = 30;

	for (int i = 0; i < stacks; i++) {
		float lat0 = M_PI * (-0.5 + (float)(i) / stacks);
		float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);

		if (frontHalf && lat0 > 0) continue;
		if (!frontHalf && lat1 < 0) continue;

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j < slices; j++) {
			float lng = 2 * M_PI * (float)(j) / slices;

			float x0 = cos(lat0) * cos(lng);
			float y0 = sin(lat0);
			float z0 = cos(lat0) * sin(lng);

			float x1 = cos(lat1) * cos(lng);
			float y1 = sin(lat1);
			float z1 = cos(lat1) * sin(lng);

			// Apply hemisphere filtering
			if (frontHalf) {
				if (z0 < 0) z0 = 0;
				if (z1 < 0) z1 = 0;
			}
			else {
				if (z0 > 0) z0 = 0;
				if (z1 > 0) z1 = 0;
			}

			glNormal3f(x0, y0, z0);
			glVertex3f(radius * x0, radius * y0, radius * z0);

			glNormal3f(x1, y1, z1);
			glVertex3f(radius * x1, radius * y1, radius * z1);
		}
		glEnd();
	}

	glPopMatrix();
}

// Function to draw one quarter of front hemisphere
void drawFaceQuarter(float r, float g, float b, float x, float y, float z, float radius, int quarter) {
	glColor3f(r, g, b);

	GLfloat col[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glPushMatrix();
	glTranslatef(x, y, z);

	int stacks = 15;
	int slices = 30;

	// Define angle ranges for each quarter
	float startLng, endLng, startLat, endLat;

	switch (quarter) {
	case 1: // Top-right
		startLng = 0; endLng = M_PI / 2;
		startLat = 0; endLat = M_PI / 2;
		break;
	case 2: // Top-left  
		startLng = M_PI / 2; endLng = M_PI;
		startLat = 0; endLat = M_PI / 2;
		break;
	case 3: // Bottom-left
		startLng = M_PI; endLng = 3 * M_PI / 2;
		startLat = 0; endLat = M_PI / 2;
		break;
	case 4: // Bottom-right
		startLng = 3 * M_PI / 2; endLng = 2 * M_PI;
		startLat = 0; endLat = M_PI / 2;
		break;
	}

	// Draw the quarter sphere
	for (int i = 0; i < stacks / 2; i++) { // Only front half
		float lat0 = startLat + (endLat - startLat) * (float)(i) / (stacks / 2);
		float lat1 = startLat + (endLat - startLat) * (float)(i + 1) / (stacks / 2);

		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= slices / 4; j++) { // Quarter of slices
			float lng0 = startLng + (endLng - startLng) * (float)(j) / (slices / 4);
			float lng1 = lng0;

			float x0 = cos(lat0) * cos(lng0);
			float y0 = sin(lat0);
			float z0 = cos(lat0) * sin(lng0);

			float x1 = cos(lat1) * cos(lng1);
			float y1 = sin(lat1);
			float z1 = cos(lat1) * sin(lng1);

			// Only draw front hemisphere
			if (z0 >= 0 && z1 >= 0) {
				glNormal3f(x0, y0, z0);
				glVertex3f(radius * x0, radius * y0, radius * z0);

				glNormal3f(x1, y1, z1);
				glVertex3f(radius * x1, radius * y1, radius * z1);
			}
		}
		glEnd();
	}

	glPopMatrix();
}

void rotateUpperLeftFace(float angle)
{
	glPushMatrix();

	// Move back from hinge
	glTranslatef(0.05f, -0.175f, 0.0f);

	// Rotate OUTWARD (around Y axis)
	glRotatef(25, 0.0f, 1.0f, 0.0f);

	// Move back from hinge
	glTranslatef(-0.05f, 0.08f, 0.0f);

	// Rotate outward (opposite direction of UL)
	glRotatef(-angle, 0.0f, 1.0f, 0.0f);

	glScalef(1.0f, 1.1f, 1.0f);

	// Draw ONLY upper-left quarter
	drawFaceQuarter(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f,
		0.4f,
		2  
	);

	glPopMatrix();
}

void rotateUpperRightFace(float angle)
{
	glPushMatrix();

	//glScaled(-1, 1, 1);

	// Move back from hinge
	glTranslatef(-0.025f, -0.085f, -0.025f);

	// Rotate OUTWARD (around Y axis)
	glRotatef(25, 0.0f, -1.0f, 0.0f);

	glTranslatef(0.05f, 0.08f, 0.0f);

	// Rotate outward (opposite direction of UL)
	glRotatef(+angle, 0.0f, 1.0f, 0.0f);

	// Undo hinge offset
	glTranslatef(-0.05f, -0.08f, 0.0f);

	glScalef(1.0f, 1.1f, 1.0f);

	// Draw ONLY upper-right quarter
	drawFaceQuarter(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f,
		0.4f,
		1   // quarter 1 = upper-right
	);

	glPopMatrix();
}

void rotateLowerLeftFace(float angle)
{
	glPushMatrix();

	glTranslatef(-0.08f, 0.97f, 0.0f);

	glRotatef(180, 1, 0, 0);

	// Move back from hinge
	glTranslatef(0.05f, -0.08f, 0.0f);

	// Rotate OUTWARD (around Y axis)
	glRotatef(195, 0.0f, 1.0f, 0.0f);

	// Move back from hinge
	glTranslatef(-0.05f, 0.08f, 0.0f);

	// Rotate outward (opposite direction of UL)
	glRotatef(+angle, 0.0f, 1.0f, 0.0f);

	// Draw ONLY upper-left quarter
	drawFaceQuarter(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f,
		0.4f,
		2   // quarter 2 = upper-left
	);

	glPopMatrix();
}

void rotateLowerRightFace(float angle)
{
	glPushMatrix();

	glTranslatef(0.085f, 0.97f, 0.047f);

	glRotatef(180, 1, 0, 0);

	glTranslatef(-0.05f, -0.08f, 0.0f); 

	glRotatef(245, 0.0f, 1.0f, 0.0f);

	// Move back from hinge
	glTranslatef(0.05f, 0.08f, 0.0f);  

	glRotatef(-angle, 0.0f, 1.0f, 0.0f); 

	drawFaceQuarter(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f,
		0.4f,
		2   
	);
	glPopMatrix();
}

void rotateFaceQuarter(
	float angle,
	float axisX, float axisY,
	int quarter
);


void drawLowerBackFace()
{
	glPushMatrix();

	// Move to head position

	glTranslatef(0.0f, 0.47f, 0.0f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	// Flatten to look like a face plate


	// Draw only FRONT hemisphere
	drawHemisphere(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.4f,
		true
	);

	glPopMatrix();
}

//Draw Foxy Head
void drawFuntimeFoxyHead() {
	glPushMatrix();

	// Back hemisphere (static - always visible)
	drawHemisphere(1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.4f, false);

	drawLowerBackFace();

	// Front face quarters (can rotate when faceOpen is true)
	if (!faceOpen) {
		// Closed state - draw complete front hemisphere
		drawHemisphere(1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.4f, true);
		glTranslatef(0, 0.5, 0.5);
		glRotatef(270,1,0,0);
		drawHemisphere(1.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.4f, true);
	}
	else {
		float rotationAngle = faceOpenAngle;

		rotateUpperLeftFace(faceOpenAngle);
		rotateUpperRightFace(faceOpenAngle);
		rotateLowerLeftFace(faceOpenAngle);
		rotateLowerRightFace(faceOpenAngle);
	}
	glPopMatrix();


	// Left cheek
	glPushMatrix();
	glScalef(1, 1, 1.6f);
	glTranslatef(-0.35f, 0.35f, 0.0f);
	glRotatef(135, 1, 0, 0);
	drawOval3D(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f, 0.18f, 0.08f);
	glPopMatrix();

	//Right Cheek
	glPushMatrix();
	glScalef(1, 1, 1.6f);
	glTranslatef(0.35f, 0.35f, 0.0f);
	glRotatef(135, 1, 0, 0);
	drawOval3D(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.15f, 0.18f, 0.08f);
	glPopMatrix();

	// Right ear
	glPushMatrix();
	glTranslatef(0.22f, 0.95f, -0.05f);
	glRotatef(90, 0, 1, 0);
	drawOval3D(1.0f, 0.7f, 0.85f,
		0.0f, 0.0f, 0.0f,
		0.07f, 0.22f, 0.15f);
	glPopMatrix();

	// Left ear
	glPushMatrix();
	glTranslatef(-0.22f, 0.95f, -0.05f);
	glRotatef(90, 0, 1, 0);
	drawOval3D(1.0f, 0.7f, 0.85f,
		0.0f, 0.0f, 0.0f,
		0.07f, 0.22f, 0.15f);
	glPopMatrix();

	// Left pink cheek (FLAT)
	glPushMatrix();
	glTranslatef(-0.25f, 0.365f, 0.3f);

	glRotatef(-45, -0.7,1,0);
	glScalef(1.0f, 1.0f, 0.25f);

	drawSphere2(
		1.0f, 0.4f, 0.6f,
		0.0f, 0.0f, 0.0f,
		0.08f
	);

	glPopMatrix();


	// Right pink cheek (FLAT)
	glPushMatrix();
	glTranslatef(0.25f, 0.365f, 0.3f);

	glRotatef(45, 0.7, 1, 0);
	glScalef(1.0f, 1.0f, 0.25f);

	drawSphere2(
		1.0f, 0.4f, 0.6f,
		0.0f, 0.0f, 0.0f,
		0.08f
	);

	glPopMatrix();

	if (showJaw) {
		//Upper jaw
		glPushMatrix();
		drawSnout(
			1.0f, 0.4f, 0.6f,   // colour
			0.0f, 0.36f, 0.45f, // position
			0.22f, 0.1f, 0.3f // size
		);
		glPopMatrix();

		//Lower jaw
		glPushMatrix();
		glRotatef(90 * 0.6f, 1.0f, 0.0f, 0.0f);
		drawSnout(
			1.0f, 0.4f, 0.6f,   // colour
			0.0f, 0.34f, 0.21f, // position
			0.22f, 0.07f, 0.28f // size
		);
		glPopMatrix();
	}
}

//Draw Foxy Body
void drawFuntimeFoxyBody() {
	// Main body torso (white)
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	// Rotate cylinder to stand upright
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	float baseradius = 0.28f;
	float topradius = 0.2f;
	float height = 0.55f;

	gluCylinder(cone, topradius, baseradius, height, 40, 10);
	glTranslatef(0.0, 0.0f, 0.55f);
	gluCylinder(cone, 0.28, 0.01, 0.1, 40, 10);
	glPopMatrix();

	// Main body torso (pink)
	//Down
	glPushMatrix();
	glColor3f(1.0f, 0.4f, 0.6f);
	GLfloat pinkCol[] = { 1.0f, 0.4f, 0.6f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pinkCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pinkCol);
	glScaled(1.12f, 0.5f, 1.65f);
	// Rotate cylinder to stand upright 
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	float baseradius2 = 0.16f;
	float topradius2 = 0.13f;
	float height2 = 0.55f;
	gluCylinder(cone, topradius2, baseradius2, height2, 40, 10);
	gluCylinder(cone, baseradius2 - 0.25f, topradius2, height2, 40, 10);
	glPopMatrix();

	//Up
	glPushMatrix();
	glColor3f(1.0f, 0.4f, 0.6f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pinkCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pinkCol);
	glScaled(1.12f, 0.5f, 1.65f);
	// Rotate cylinder to stand upright 
	glTranslatef(0, 1.1f, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	gluCylinder(cone, topradius2, baseradius2, height2, 40, 10);
	gluCylinder(cone, baseradius2 + 0.02f, topradius2 + 0.03f, height2, 40, 10);
	glPopMatrix();

	// Skirt (White)
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);

	glTranslatef(0, -0.15f, 0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	// Torso shape
	gluCylinder(cone, baseradius - 0.02f, topradius, 0.15, 40, 10);
	glTranslatef(0.0, 0.0f, -0.05f);
	gluCylinder(cone, 0.01, 0.26, 0.05, 40, 10);
	glPopMatrix();

	//Skirt (Pink)
	glPushMatrix();
	glColor3f(1.0f, 0.4f, 0.6f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pinkCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pinkCol);
	glScaled(1.12f, 0.27f, 1.65f);
	// Rotate cylinder to stand upright 
	glTranslatef(0, 0.0f, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	gluCylinder(cone, topradius2, baseradius2 +0.01f, height2, 40, 10);
	glPopMatrix();

	// Bowtie
	//Center
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	GLfloat redCol[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redCol);
	glTranslatef(0.0f, 0.52f, 0.32f);
	// Rotate cylinder to stand upright 
	drawSphere2(1.0f, 0.0f, 0.0f, 0, 0, 0, 0.045f);
	glPopMatrix();

	//Left part
	glPushMatrix();
	glTranslatef(-0.09f, 0.52f, 0.32f);
	glScalef(1.3f, 0.75f, 0.35f);
	glRotatef(10, 0, 1, 0);
	drawSphere2(1.0f, 0.0f, 0.0f, 0, 0, 0, 0.07f);
	glPopMatrix();

	//Right part
	glPushMatrix();
	glTranslatef(0.09f, 0.52f, 0.32f);
	glScalef(1.3f, 0.75f, 0.35f);
	glRotatef(10, 0, 1, 0);
	drawSphere2(1.0f, 0.0f, 0.0f, 0, 0, 0, 0.07f);
	glPopMatrix();

	//Speaker
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	GLfloat whiteCol[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, whiteCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, whiteCol);
	glTranslatef(0.0f, 0.375f, 0.25f);
	// Outer cylinder
	gluCylinder(cone, 0.09f, 0.09f, 0.05f, 40, 10);
	// Inner hole
	glTranslatef(0.0f, 0.0f, 0.001f);
	gluCylinder(cone, 0.07f, 0.07f, 0.05f, 40, 10);
	glPopMatrix();

	//Fill of the speaker colour
	glPushMatrix();
	glTranslatef(0.0f, 0.375f, 0.3f);
	gluDisk(cone, 0.07f, 0.09f, 40, 1);
	glPopMatrix();

	// Speaker grille
	glPushMatrix();

	// Grey net
	glColor3f(0.2f, 0.2f, 0.2f);
	GLfloat lightdarkCol[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightdarkCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightdarkCol);

	glTranslatef(0.0f, 0.375f, 0.285f);
	glScalef(1.1f, 1.1f, 1.1f);
	float innerR = 0.0f;
	float outerR = 0.065f;
	gluDisk(cone, innerR, outerR, 40, 1);

	glLineWidth(1.5f);
	glBegin(GL_LINES);
	for (int i = 0; i < 24; i++) {
		float angle = 2.0f * M_PI * i / 24.0f;
		float x = outerR * cos(angle);
		float y = outerR * sin(angle);

		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
	glPopMatrix();
	
	//Net effect
	glPushMatrix();
	glColor3f(0.2f, 0.2f, 0.2f);
	GLfloat darkCol[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, darkCol);

	glTranslatef(0.0f, 0.375f, 0.298f);
	for (float r = 0.01f; r <= 0.065f; r += 0.01f) {
		gluDisk(cone, r - 0.001f, r, 40, 1);
	}
	glPopMatrix();

	// Black line
	glPushMatrix();

	// Black color
	glColor3f(0.0f, 0.0f, 0.0f);
	GLfloat blackCol[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blackCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blackCol);

	glTranslatef(0.0f, -0.2f, 0.187f);
	glRotatef(9.5 ,1, 0.0f, 0.0f);
	glLineWidth(3.0f);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.20f, 0.0f);   
	glVertex3f(0.0f, 0.55f, 0.0f);   
	glEnd();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.01f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.67f, 0.0f);
	glVertex3f(0.0f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();

	//Grey Line
	//1
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		GLfloat lightblackCol[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);
		glTranslatef(0, -0.15, 0.246f);
		glRotatef(-45, 1, 1.2, 1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.20f, 0.0f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glEnd();
	glPopMatrix();

	//2
	glPushMatrix();
		glScalef(-1.0f, 1.0f, 1.0f); 
		glColor3f(0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);
		glTranslatef(0, -0.15f, 0.246f);
		glRotatef(-45, 1, 1.2f, 1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.20f, 0.0f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glEnd();
	glPopMatrix();

	//3
	glPushMatrix();
		glColor3f(0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);
		glScaled(1,1,-1);
		glTranslatef(0, -0.15, 0.246f);
		glRotatef(-45, 1, 1.2, 1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.20f, 0.0f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glEnd();
	glPopMatrix();

	//4
	glPushMatrix();
		glScalef(-1.0f, 1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);
		glScaled(1, 1, -1);
		glTranslatef(0, -0.15, 0.246f);
		glRotatef(-45, 1, 1.2, 1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.20f, 0.0f);
		glVertex3f(0.0f, 0.4f, 0.0f);
		glEnd();
	glPopMatrix();

	// Joint 1 and 3
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);

	float r = 0.246f;
	int segments = 32;
	glTranslatef(0.016, 0.12, 0.03f);
	glRotatef(45, 0, 1, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= segments; i++) {
		float t = (1.0f * M_PI / 2.0f) * i / segments;
		float z = r * cos(t) -0.05;
		float x = r * sin(t);
		glVertex3f(x, 0.05f, z);
	}
	glEnd();
	glPopMatrix();

	// Joint 2 and 4
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightblackCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightblackCol);

	glScalef(-1.0f, 1.0f, 1.0f);
	glTranslatef(0.016f, 0.12f, 0.03f);

	glRotatef(45, 0, 1, 0);

	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= segments; i++) {
		float t = (1.0f * M_PI / 2.0f) * i / segments;
		float z = r * cos(t) - 0.05f;
		float x = r * sin(t);
		glVertex3f(x, 0.05f, z);
	}
	glEnd();
	glPopMatrix();
}

//Draw Foxy Tail
void drawFuntimeFoxyTail()
{
	GLfloat tailCol[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tailCol);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tailCol);

	//Cone 1
	glPushMatrix();
	glScalef(1.5f,1.5f,1.5f);
	glTranslatef(0.0f, 0.0f, -0.115f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(cone,0.07f, 0.02f, 0.12f,30, 10);
	glPopMatrix();

	//Cone 2
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.0f, 0.0f, -0.27f);
	glRotatef(3, 0, 1, 0);
	gluCylinder(cone,0.07f, 0.02f, 0.05f, 30, 10);
	glPopMatrix();

	//Cone 3
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.005f, 0.0f, -0.31f);
	glRotatef(9, 0, 1, 0);
	gluCylinder(cone, 0.12f, 0.0675f, 0.05f, 30, 10);
	glPopMatrix();

	//Cone 4
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.005f, 0.0f, -0.35f);
	glRotatef(9, 0, 1, 0);
	gluCylinder(cone, 0.16f, 0.1075f, 0.05f, 30, 10);
	glPopMatrix();

	//Cone 5
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.008f, 0.0f, -0.39f);
	glRotatef(9, 0, 1, 0);
	gluCylinder(cone, 0.22f, 0.1475f, 0.05f, 30, 10);
	glPopMatrix();


	//Cone 6 (Up start)
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.01f, -0.43f);
	glRotatef(2, 1, 0, 0);  
	glRotatef(9, 0, 1, 0);   
	gluCylinder(cone, 0.18f, 0.21f, 0.05f, 30, 10);
	glPopMatrix();


	//Cone 7 
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.02f, -0.41f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.05f);
	glRotatef(6, 1, 0, 0);
	gluCylinder(cone, 0.15f, 0.196f, 0.045f, 30, 10);
	glPopMatrix();

	//Cone 8
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.03f, -0.39f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.095f);
	glRotatef(12, 1, 0, 0);
	gluCylinder(cone, 0.11f, 0.165f, 0.04f, 30, 10);
	glPopMatrix();

	//Cone 9 
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.04f, -0.37f); 
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.135f);  
	glRotatef(18, 1, 0, 0);    
	gluCylinder(cone, 0.075f, 0.12f, 0.035f, 30, 10);
	glPopMatrix();

	//Cone 10
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.05f, -0.35f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.17f);    
	glRotatef(24, 1, 0, 0);            
	gluCylinder(cone, 0.05f, 0.08f, 0.03f, 30, 10);
	glPopMatrix();

	//Cone 11
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.065f, -0.32f);   
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.195f); 
	glRotatef(32, 1, 0, 0);   
	gluCylinder(cone, 0.03f, 0.06f, 0.02f, 30, 10);
	glPopMatrix();

	//Cone 12
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.075f, -0.30f);  
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.0f, -0.22f);      
	glRotatef(40, 1, 0, 0);             
	gluCylinder(cone, 0.015f, 0.03f, 0.018f, 30, 10);
	glPopMatrix();

	//Cone 13 (Tip)
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.085f, -0.28f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.013f, -0.24f);
	glRotatef(45, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	//Random on tails
	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.01f, 0.085f, -0.28f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.013f, -0.24f);
	glRotatef(45, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.01f, 0.075f, -0.30f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.013f, -0.24f);
	glRotatef(45, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.01f, 0.075f, -0.30f);
	glRotatef(2, 1, 0, 0);
	glRotatef(9, 0, 1, 0);
	glTranslatef(0.0f, 0.013f, -0.24f);
	glRotatef(45, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.02f, 0.09f, -0.27f);
	glRotatef(3, 1, 0, 0);
	glRotatef(12, 0, 1, 0);
	glTranslatef(0.0f, 0.015f, -0.23f);
	glRotatef(50, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();


	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.02f, 0.065f, -0.32f);
	glRotatef(1.5f, 1, 0, 0);
	glRotatef(6, 0, 1, 0);
	glTranslatef(0.0f, 0.012f, -0.22f);
	glRotatef(38, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();




	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.07f, 0.06f, -0.33f);
	glRotatef(2.5f, 1, 0, 0);
	glRotatef(18, 0, 1, 0);
	glTranslatef(0.0f, 0.016f, -0.215f);
	glRotatef(48, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.086f, 0.08f, -0.29f);
	glRotatef(2.5f, 1, 0, 0);
	glRotatef(11, 0, 1, 0);
	glTranslatef(0.0f, 0.014f, -0.235f);
	glRotatef(42, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.07f, 0.05f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(0.09f, 0.065f, -0.32f);
	glRotatef(1.8f, 1, 0, 0);
	glRotatef(7, 0, 1, 0);
	glTranslatef(0.0f, 0.012f, -0.22f);
	glRotatef(35, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.06f, 0.1f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.08f, 0.09f, -0.27f);
	glRotatef(3.5f, 1, 0, 0);
	glRotatef(16, 0, 1, 0);
	glTranslatef(0.0f, 0.016f, -0.23f);
	glRotatef(55, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.075f, 0.15f, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.5f, 1.5f, 1.5f);
	glTranslatef(-0.05f, 0.07f, -0.31f);
	glRotatef(2, 1, 0, 0);
	glRotatef(-6, 0, 1, 0);
	glTranslatef(0.0f, 0.013f, -0.24f);
	glRotatef(47, 1, 0, 0);
	gluCylinder(cone, 0.00f, 0.043f, 0.18f, 30, 10);
	glPopMatrix();


	glPopMatrix();
}

void rotateFaceQuarter(float angle,float axisX, float axisY,int quarter) {
	glPushMatrix();

	// Move to head center
	glTranslatef(0.0f, 0.5f, 0.0f);

	float hx = 0.0f, hy = 0.0f;

	if (quarter == 1) { hx = 0.1f; hy = 0.1f; }
	if (quarter == 2) { hx = -0.1f; hy = 0.1f; }
	if (quarter == 3) { hx = -0.1f; hy = -0.1f; }
	if (quarter == 4) { hx = 0.1f; hy = -0.1f; }

	glTranslatef(hx, hy, 0.0f);

	// Rotate outward
	glRotatef(angle, axisX, axisY, 1.0f);

	// Undo hinge offset
	glTranslatef(-hx, -hy, 0.0f);

	// Move back
	glTranslatef(0.0f, -0.5f, 0.0f);

	// Draw the quarter
	drawFaceQuarter(
		1.0f, 1.0f, 1.0f,
		0.0f, 0.5f, 0.0f,
		0.4f,
		quarter
	);

	glPopMatrix();
}

void display()
{
	//glClearColor(0.529, 0.808, 0.922, 1);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	//glShadeModel(GL_SMOOTH); //shader

	// ======= FOR POINTS =======
	//glPointSize(50);
	//glBegin(GL_POINTS);
	// ==========================

	// ====== FOR LINES =========
	//glLineWidth(5);
	//glBegin(GL_LINE_LOOP);
	// ==========================

	glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);


	// Camera position
	glTranslatef(translatex, translatey, -3.5f + translatez);

	// Apply mouse rotation
	glRotatef(mouseRotateX, 1, 0, 0);
	glRotatef(mouseRotateY, 0, 1, 0);

	// Apply keyboard rotation
	glRotatef(rotatex, 1, 0, 0);
	glRotatef(rotatey, 0, 1, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightPos[] = { 2.0f, 3.0f, 2.0f, 1.0f };
	GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	switch (renderNum) {
		//ZC
	case 1:
		//manageRotations();

		glPushMatrix();
		drawEntireHead();
		drawOuterShell();
		glPopMatrix();
		break;


	case 2: {
		//manageRotations();
		//left hand
		glPushMatrix();
		glTranslatef(-1, 1.5, 0);
		drawhand(true);

		glPopMatrix();

		//right hand
		glPushMatrix();
		glTranslatef(1, 1.5, 0);
		drawhand(false);

		glPopMatrix();

		//left leg
		glPushMatrix();
		glTranslatef(-0.4, -0.6, 0);
		drawleg(true);

		glPopMatrix();

		//right leg
		glPushMatrix();
		glTranslatef(0.4, -0.6, 0);
		drawleg(false);

		glPopMatrix();

		//Head
		glPushMatrix();

		glScalef(0.7f, 0.7f, 0.7f);
		glTranslatef(0.0f, 4.0f, 0.0f);
		drawEntireHead();
		if (!removeShell) {
			drawOuterShell();
		}

		glPopMatrix();

		glPushMatrix();

		//Body and Tail
		glScaled(3, 3, 3);
		drawFuntimeFoxyBody();

		drawFuntimeFoxyTail();

		glPopMatrix();

		break;
	}
		  //CH
	case 3: {
		//glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//gluPerspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//// Camera position
		//glTranslatef(translatex, translatey, -3.5f + translatez);

		//// Apply mouse rotation
		//glRotatef(mouseRotateX, 1, 0, 0);
		//glRotatef(mouseRotateY, 0, 1, 0);

		//// Apply keyboard rotation
		//glRotatef(rotatex, 1, 0, 0);
		//glRotatef(rotatey, 0, 1, 0);

		//// Enable lighting
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);

		//GLfloat lightPos[] = { 2.0f, 3.0f, 2.0f, 1.0f };
		//GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		//GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };

		//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

		//drawFuntimeFoxyBody();

		//drawFuntimeFoxyTail();

		drawFuntimeFoxyHead();
		drawEntireHead();


		//glTranslatef(0,0.6,0);
		//glScaled(0.3, 0.3, 0.3);
		//drawEntireHead();
	}
		  break;
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
	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);

	gluQuadricTexture(disk, GL_TRUE);
	gluQuadricNormals(disk, GLU_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	LoadBMPTexture("metal.bmp", metalTex);
	LoadBMPTexture("white.bmp", whiteTex);
	LoadBMPTexture("teeth.bmp", teethTex);
	LoadBMPTexture("plastic.bmp", plasticTex);
	LoadBMPTexture("eye.bmp", eyeTex);

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

		// ===== FACE OPEN ANIMATION UPDATE =====
		if (faceOpen) {
			if (faceOpenAngle < 90.0f) {
				faceOpenAngle += faceOpenSpeed;
				if (faceOpenAngle > 90.0f)
					faceOpenAngle = 90.0f;
			}
		}
		else {
			if (faceOpenAngle > 0.0f) {
				faceOpenAngle -= faceOpenSpeed;
				if (faceOpenAngle < 0.0f)
					faceOpenAngle = 0.0f;
			}
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------