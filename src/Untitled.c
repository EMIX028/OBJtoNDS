#include <nds.h>
#include "Untitled.h"

void drawCube(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE));
	glColor3b(255,255,255);
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(0.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(0.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(-2.000000));
	glEnd();
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(-2.000000));
	glEnd();
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(0.000000));
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(0.000000));
	glEnd();
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(0.000000));
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(0.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(0.000000));
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(0.000000));
	glEnd();
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(2.000000), floattov16(0.000000), floattov16(0.000000));
	glVertex3v16(floattov16(0.000000), floattov16(0.000000), floattov16(0.000000));
	glEnd();
	glBegin(GL_QUADS);
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(-2.000000));
	glVertex3v16(floattov16(0.000000), floattov16(2.000000), floattov16(0.000000));
	glVertex3v16(floattov16(2.000000), floattov16(2.000000), floattov16(0.000000));
	glEnd();
}

void drawPlane(bool cullback){
	glPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE));
	glColor3b(255,255,255);
}