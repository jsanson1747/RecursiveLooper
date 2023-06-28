//Pen.cpp
#include "Pen.h"

Pen::Pen(SDL_Renderer* renderer)
    :renderer_(renderer), r_(255), g_(255), b_(255), a_(255), xPos_(0), yPos_(0), isPenUp_(true){}
 //end default constructor

Pen::~Pen(void){

} // end destructor

SDL_Renderer* Pen::getRenderer(void) {
    return renderer_;
} //end setRenderer

void Pen::setPos(int x, int y) {
    setXPos(x);
    setYPos(y);
} //end getPos

int Pen::getXPos(void) {
    return xPos_;
} // end getXPos

void Pen::setXPos(int x){
    xPos_ = x;
} // end setXPos

int Pen::getYPos(void){
    return yPos_;
} // end getYPos

void Pen::setYPos(int y){
    yPos_ = y;
} // end setYPos

void Pen::setColor(int r, int g, int b, int a){
    r_ = r;
    g_ = g;
    b_ = b;
    a_ = a;
} // end setColor

int Pen::getR(void){
    return r_;
} // end getR

int Pen::getG(void) {
    return g_;
} //end getG

int Pen::getB(void) {
    return b_;
} //end getB

int Pen::getA(void) {
    return a_;
} //ebd getA

bool Pen::isPenUp(){
    return isPenUp_;
} // end isPenUp

void Pen::blot() {
    SDL_SetRenderDrawColor(getRenderer(), getR(), getG(), getB(), getA());
    SDL_RenderDrawPoint(getRenderer(), getXPos(), getYPos());
}

void Pen::drawLine(int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(getRenderer(), getR(), getG(), getB(), getA());
    SDL_RenderDrawLine(getRenderer(), x1, y1, x2, y2);
}
