#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>

#define MarsRows 840    //y
#define MarsCols 1035   //x

#define Black 0
#define White 255

#define Red 10
#define LightRed 15

#define Gold 20
#define LightGold 25

#define Green 30
#define LightGreen 35

#define Blue 40
#define LightBlue 45

#define Orchid 50
#define LightOrchid 55

typedef struct
{
	int Row;
	int Col;
}Point;

//A struct that helps me in "move" the point

typedef struct
{
	Point Current;
	Point* Neighbors;
}WalkingPoint;

typedef struct
{
	double Distance;
	int Key;
}Candidate;
