#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
// #include "produceConsume.h"
#define SIZE 5

int cq[SIZE];
int front=0;
int rear=0;
int cnt=0;

int outCount(){
  return cnt;
}

void send(int data){
	adding(data);
}

void adding(unsigned int data){
	if(cnt!=SIZE){
		cq[rear]=data;
		rear = (rear +1) % SIZE;
		++cnt;
	}
}

void recv1(char** data){
	int tmp;
	tmp = remov();
	if(tmp != -1)
		sprintf(&data[0],"consumed %d",tmp);
	else
		sprintf(&data[0],"consumed nothing");
}

int remov(void){
	int val;
	if(cnt!=0){
		val=cq[front];
		front = (front+1) % SIZE;
		cnt--;
		return val;
	}else
		return -1;

}

/*
DESCRIPTION: Saturate the throttle command to limit the acceleration.
PARAMETERS: throttleIn - throttle input
            saturate - true if saturated, false otherwise
RETURNS: throttle output (ThrottleCmd)
*/
float saturateThrottle(float throttleIn, int* saturate)
{
	static const float THROTTLESATMAX = 45.0;
	if (throttleIn > THROTTLESATMAX) {
		*saturate = 1;
		return THROTTLESATMAX;
	}
	else if (throttleIn < 0) {
		*saturate = 1;
		return 0;
	}
	else {
		*saturate = 0;
		return throttleIn;
	}
}

/*
DESCRIPTION: Saturate the throttle command to limit the acceleration.
PARAMETERS: isGoingOn - true if the cruise control has just gone into the ON state 
                        from another state; false otherwise
            saturate - true if saturated, false otherwise
RETURNS: throttle output (ThrottleCmd)
*/
float regulateThrottle(int isGoingOn, float cruiseSpeed, float vehicleSpeed)
{
	static const float KP = 8.113;
	static const float KI = 0.5;
	static bool saturate = 1;
	static float iterm = 0;
	
	if (isGoingOn) {
		iterm = 0;	// reset the integral action
		saturate = 1;	
	}
	float error = cruiseSpeed - vehicleSpeed;
	float proportionalAction = error * KP;
	if (saturate)
		error = 0;	// integral action is hold when command is saturated
	iterm = iterm + error;
	float integralAction = KI * iterm;
	return saturateThrottle(proportionalAction + integralAction, &saturate);
}

int number(int num){
	return num;
}

float floatCal(float f){
return f;
}

int isAccel(float Accel, float PedalsMin){
	if(Accel >= PedalsMin){
		return 1;
	} else return 0;
}

int isBrake(float Brake, float PedalsMin){
	if(Brake >= PedalsMin){
		return 1;
	} else return 0;
}

float incSpeed(float Brake, float PedalsMin){
	if(Brake >= PedalsMin){
		return 1;
	} else return 0;
}

float decSpeed(float Brake, float PedalsMin){
	if(Brake >= PedalsMin){
		return 1;
	} else return 0;
}