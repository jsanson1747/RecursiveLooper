#include <cmath>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "Pen.h"


#ifdef _WIN32
    #include <Windows.h>
#elif __linux__
    #include <unistd.h>
#endif

const int FULLSCREEN_WIDTH = 1920;
const int FULLSCREEN_HEIGHT = 1080;
bool isFullscreen;

//Function Prototypes
void clearScreen(void);
bool isNumber(const std::string&);
float toRadians(int);
int drawTriangles(Pen*, int, float, float, int, int, int, int, int, int, int, bool*, SDL_Event);
int fractalTriangle(Pen*, int, float, int, int, int, int, int, bool*, SDL_Event);
int drawTriangle(Pen*, int, int, int, int, int, int, int);
int loop();

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#elif __linux__
    std::cout << "\033c";
#endif
}

bool isNumber(const std::string& s) {
    for (char const& ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

float toRadians(int degrees) {
    float pi = 3.14159;
    float radians = degrees * (pi / 180);
    return radians;
}


int drawTriangles(Pen* pen, int len, float angle, float angleIncrement, int iterations, int r, int lengthDecrement, int transparency, int toggle, int isR, int isG, int isB, bool* isRunningPtr, SDL_Event event) {
    float rads120 = toRadians(120);
    float rotationMatrix[2][2] = {
        {cosf(rads120), -1 * sinf(rads120)},
        {sinf(rads120), cosf(rads120)}
    };
    float radians = toRadians(angle);
    // Get Point 1
    float pt1x = len * cosf(radians);
    float pt1y = len * sinf(radians);
    // Get Point 2
    float pt2x = (pt1x * rotationMatrix[0][0]) + (pt1y * rotationMatrix[0][1]);
    float pt2y = (pt1x * rotationMatrix[1][0]) + (pt1y * rotationMatrix[1][1]);
     // Get Point 3
    float pt3x = (pt2x * rotationMatrix[0][0]) + (pt2y * rotationMatrix[0][1]);
    float pt3y = (pt2x * rotationMatrix[1][0]) + (pt2y * rotationMatrix[1][1]);
    drawTriangle(pen, pt1x, pt1y, pt2x, pt2y, pt3x, pt3y, transparency);

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            *isRunningPtr = false;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                *isRunningPtr = false;
            } // end if
        case SDL_MOUSEBUTTONDOWN:
            *isRunningPtr = false;
        } // end switch
    } // end while

    //Terminate if user initializes termination
    if (*isRunningPtr == false) {
        return 0;
    }
    
    if (iterations - 1 > 0) {
        if (pen->getR() == 255 || pen->getG() == 255 || pen->getB() == 255) {
            toggle = -1;
        }
        if (pen->getR() == 1 || pen->getG() == 1 || pen->getB() == 1) {
            toggle = 1;
        }
        pen->setColor(pen->getR() + (isR * toggle), pen->getG() + (isG * toggle), pen->getB() + (isB * toggle), pen->getA());
        drawTriangles(pen, len - 1 * lengthDecrement, angle + angleIncrement, angleIncrement, iterations - 1, r, lengthDecrement, transparency, toggle, isR, isG, isB, isRunningPtr, event);
    }
    return 0;
}

int fractalTriangle(Pen* pen, int r, float angleIncrement, int lengthDecrement, int transparency, int isR, int isG, int isB, bool* isRunningPtr, SDL_Event event) {
    int toggle = 1;
    drawTriangles(pen, 200, 0, angleIncrement, r, r, lengthDecrement, transparency, toggle, isR, isG, isB, isRunningPtr, event);
    return 0;
} //end fractalTriangle

int drawTriangle(Pen* pen, int x1, int y1, int x2, int y2, int x3, int y3, int transparency) {
    if (isFullscreen) {
        pen->drawLine(x1 + (FULLSCREEN_WIDTH / 2), y1 + (FULLSCREEN_HEIGHT / 2), x2 + (FULLSCREEN_WIDTH / 2), y2 + (FULLSCREEN_HEIGHT / 2));
        pen->drawLine(x2 + (FULLSCREEN_WIDTH / 2), y2 + (FULLSCREEN_HEIGHT / 2), x3 + (FULLSCREEN_WIDTH / 2), y3 + (FULLSCREEN_HEIGHT / 2));
        pen->drawLine(x3 + (FULLSCREEN_WIDTH / 2), y3 + (FULLSCREEN_HEIGHT / 2), x1 + (FULLSCREEN_WIDTH / 2), y1 + (FULLSCREEN_HEIGHT / 2));
    }
    else {
        pen->drawLine(x1 + 400, y1 + 300, x2 + 400, y2 + 300);
        pen->drawLine(x2 + 400, y2 + 300, x3 + 400, y3 + 300);
        pen->drawLine(x3 + 400, y3 + 300, x1 + 400, y1 + 300);
    }
    SDL_RenderPresent(pen->getRenderer());
    Sleep(10);

    return 0;
} //end drawTriangles

int loop() {
    clearScreen();
    std::cout << "Performing Recursion..." << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Graphics Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT, 0);
    isFullscreen = true;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    bool isRunning = true;
    SDL_Event event;
    Pen* pen = new Pen(renderer);
    pen->setColor(0, 0, 0, 255);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
    SDL_RenderClear(renderer);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_RenderSetVSync(renderer, 0);
    while (isRunning) {
        srand(time(0));
        int addRed = (rand() % 2);
        int addGreen = (rand() % 2);
        int addBlue = (rand() % 2);
        int angleRotation = (rand() % 361);
        int iterations = 500 + (rand() % 601);
        int scale = 1 + (rand() % 3);

        fractalTriangle(pen, iterations, angleRotation, scale, 255, addRed, addGreen, addBlue, &isRunning, event);
        
    } // end while

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int main(int argv, char** args) {
    clearScreen();
    bool valid;
    std::string usrInput = "";
    while (true) {
        valid = false;
        while (!valid) {
            clearScreen();
            std::cout << "Welcome to the Recursive Triangle Doodler" << std::endl;
            std::cout << "Type \"start\" to start\nType \"Continuous\" for continuous mode\nType \"quit\" to quit" << std::endl << ">>> ";
            std::cin >> usrInput;
            if (usrInput == "start" || usrInput == "Start") {
                valid = true;
            }
            if (usrInput == "continuous" || usrInput == "Continuous") {
                clearScreen();
                loop();
                valid = false;
            }
            if (usrInput == "quit" || usrInput == "Quit") {
                SDL_Quit();
                exit(0);
            }
        }

        valid = false;
        int addRed;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Colors: \nType \"yes\" or \"no\""<< std::endl;
            std::cout << "Add Red? >>> ";
            std::cin >> usrInput;
            if (usrInput == "yes" || usrInput == "Yes") {
                addRed = 1;
                valid = true;
            }
            if (usrInput == "no" || usrInput == "No") {
                addRed = 0;
                valid = true;
            }
        }
        valid = false;
        int addGreen;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Colors: \nType \"yes\" or \"no\"" << std::endl;
            std::cout << "Add Green? >>> ";
            std::cin >> usrInput;
            if (usrInput == "yes" || usrInput == "Yes") {
                addGreen = 1;
                valid = true;
            }
            if (usrInput == "no" || usrInput == "No") {
                addGreen = 0;
                valid = true;
            }
        }

        valid = false;
        int addBlue;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Colors: \nType \"yes\" or \"no\"" << std::endl;
            std::cout << "Add Blue? >>> ";
            std::cin >> usrInput;
            if (usrInput == "yes" || usrInput == "Yes") {
                addBlue = 1;
                valid = true;
            }
            if (usrInput == "no" || usrInput == "No") {
                addBlue = 0;
                valid = true;
            }
        }
        
        valid = false;
        int iterations;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Recursive Features: \nType a positive number" << std::endl;
            std::cout << "Number of iterations >>> ";
            std::cin >> usrInput;
            if (isNumber(usrInput)) {
                valid = true;
                iterations = std::stoi(usrInput);
            }
        }

        valid = false;
        int angleRotation;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Recursive Features: \nType a positive number" << std::endl;
            std::cout << "Angle of rotation >>> ";
            std::cin >> usrInput;
            if (isNumber(usrInput)) {
                valid = true;
                angleRotation = std::stoi(usrInput);
            }
        }

        valid = false;
        int scale;
        while (!valid) {
            clearScreen();
            std::cout << "Configure Recursive Features: \nType a positive number" << std::endl;
            std::cout << "scaling factor >>> ";
            std::cin >> usrInput;
            if (isNumber(usrInput)) {
                valid = true;
                scale = std::stoi(usrInput);
            }
        }

        clearScreen();
        std::cout << "Performing Recursion..." << std::endl;
        isFullscreen = false;
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window* window = SDL_CreateWindow("Graphics Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        bool isRunning = true;
        SDL_Event event;
        Pen* pen = new Pen(renderer);
        
        pen->setColor(0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
        SDL_RenderClear(renderer);
        fractalTriangle(pen, iterations, angleRotation, scale, 255, addRed, addGreen, addBlue, &isRunning, event);

        clearScreen();
        std::cout << "Close the graphics window or press escape within the graphics window to return to menu" << std::endl;
        while (isRunning) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        isRunning = false;
                    } // end if
                case SDL_MOUSEBUTTONDOWN:
                    isRunning = false;
                } // end switch
            } // end while
        } // end while

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    } //end while
    return 0;
} // end main
