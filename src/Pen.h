//Pen.h

#ifndef _PEN_H_
#define _PEN_H_

#include <SDL2/SDL.h>

class Pen{
    private:
        SDL_Renderer* renderer_;
        int xPos_;
        int yPos_;
        bool isPenUp_;
        int r_;
        int g_;
        int b_;
        int a_;

    public:
        Pen(SDL_Renderer* renderer);
        ~Pen(void);
        SDL_Renderer* getRenderer(void);
        void setPos(int x, int y);
        int getXPos(void);
        void setXPos(int x);
        int getYPos(void);
        void setYPos(int y);
        void setColor(int r, int g, int b, int a);
        int getR(void);
        int getG(void);
        int getB(void);
        int getA(void);
        bool isPenUp(void);
        void blot(void);
        void drawLine(int x1, int y1, int x2, int y2);

}; // end class declaration

#endif