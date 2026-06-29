#include "Untitled.h"

void drawCube(bool cullback, unsigned int alpha, float x, float y, float z){
  if(cullback){
    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_BACK);
  }
  else{
    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_NONE);
  }
}
void drawPlane(bool cullback, unsigned int alpha, float x, float y, float z){
  if(cullback){
    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_BACK);
  }
  else{
    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_NONE);
  }
}
