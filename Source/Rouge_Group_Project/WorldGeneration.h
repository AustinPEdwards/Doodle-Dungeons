#pragma once
#include <iostream>
#include <time.h>
#include <stack>

using namespace std;
const int COL = 13;
const int ROW = 13;
const int START_X = COL / 2;
const int START_Y = ROW / 2;

void printMaze(char(&maze)[ROW][COL]);
void createBase(char(&maze)[ROW][COL]);
void createStart(char(&maze)[ROW][COL], int& startX, int& startY);
int chooseRand(bool choices[], int numChoices);
void lookBack(char(&maze)[ROW][COL], char around[], int posX, int posY);
void lookAround(char(&maze)[ROW][COL], char around[], int posX, int posY);
int possibleDirections(char around[], bool choices[]);
void move(int& X, int& Y, int direction);
void generateMaze(char(&maze)[ROW][COL], char(&mapDirection)[ROW][COL], stack <int> posX, stack <int> posY, int& endPosX, int& endPosY, int& maxStack);
void cleanupMaze(char(&maze)[ROW][COL], int endPosX, int endPosY);
char assignDoorValue(char around[]);
void lookForDoors(char(&maze)[ROW][COL], int xPos, int yPos);