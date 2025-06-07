//The type 'string' is defined as 'char*' in Esterel, hence passing a string by referenc  is 'char**'
//Aviod naming a function 'recv'
// void send(int data);
// void recv1(char** data);
// void adding(unsigned int data);
// int remov();
// int outCount();

#include <stdbool.h>

// #define PedalsMin 3.00
// #define SpeedMin 30.00
// #define SpeedMax 150.00
// #define SpeedInc 10.00
// #define Zero 0.00



float saturateThrottle(float throttleIn, int* saturate);


float regulateThrottle(int isGoingOn, float cruiseSpeed, float vehicleSpeed); // for some reason I need to comment this out
