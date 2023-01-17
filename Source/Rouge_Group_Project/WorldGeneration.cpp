#include "WorldGeneration.h"

using namespace std;

void printMaze(char(&maze)[ROW][COL])
{
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			cout << maze[y][x] << " ";
		}
		cout << endl;
	}
	return;
}
void createBase(char(&maze)[ROW][COL])
{
	int count = 0;
	for (int y = 0; y < ROW; y++)
		for (int x = 0; x < COL; x++)
		{
			if (y == 0 || x == 0 || y == ROW - 1 || x == COL - 1)
			{
				maze[y][x] = 'X';
			}
			else
				(maze[y][x] = ' ');
		}
	return;
}
void createStart(char(&maze)[ROW][COL], int& startX, int& startY)
{
	startX = COL / 2;
	startY = ROW / 2;
	maze[startY][startX] = 'S';
}
int chooseRand(bool choices[], int numChoices)
{
	int temp = rand() % numChoices;
	int index = 0;
	for (index = 0; index < 4; index++)
	{
		if (choices[index])
		{
			if (temp == 0)
			{
				return index;
			}
			else (temp--);
		}
	}
	return index;
}
void lookBack(char(&maze)[ROW][COL], char around[], int posX, int posY)
{
	around[0] = maze[posY - 1][posX];	//up
	around[1] = maze[posY][posX + 1]; //right
	around[2] = maze[posY + 1][posX]; //down
	around[3] = maze[posY][posX - 1]; //left
}
void lookAround(char(&maze)[ROW][COL], char around[], int posX, int posY)
{
	around[0] = maze[posY - 1][posX];
	if (around[0] == 's')
	{
		around[0] = 'X';
		maze[posY - 1][posX] = 'X';
	}
	if (around[0] == ' ')
	{
		around[0] = 's';
		maze[posY - 1][posX] = 's';
	}

	around[1] = maze[posY][posX + 1];
	if (around[1] == 's')
	{
		around[1] = 'X';
		maze[posY][posX + 1] = 'X';
	}
	if (around[1] == ' ')
	{
		around[1] = 's';
		maze[posY][posX + 1] = 's';
	}

	around[2] = maze[posY + 1][posX];
	if (around[2] == 's')
	{
		around[2] = 'X';
		maze[posY + 1][posX] = 'X';
	}
	if (around[2] == ' ')
	{
		around[2] = 's';
		maze[posY + 1][posX] = 's';
	}

	around[3] = maze[posY][posX - 1];
	if (around[3] == 's')
	{
		around[3] = 'X';
		maze[posY][posX - 1] = 'X';
	}
	if (around[3] == ' ')
	{
		around[3] = 's';
		maze[posY][posX - 1] = 's';
	}

}
int possibleDirections(char around[], bool choices[])
{
	int count = 0;
	for (int index = 0; index < 4; index++)
	{
		if (around[index] == 's')
		{
			choices[index] = true;
			count++;
		}
		else(choices[index] = false);
	}
	return count;
}
void move(int& X, int& Y, int direction)
{
	if (direction == 0)		 // move up
		Y = Y - 1;
	else if (direction == 1) // move right
		X = X + 1;
	else if (direction == 2) // move down
		Y = Y + 1;
	else if (direction == 3) // move left
		X = X - 1;
}
void generateMaze(char(&maze)[ROW][COL], char(&mapDirection)[ROW][COL], stack <int> posX, stack <int> posY, int& endPosX, int& endPosY, int& maxStack)
{
	if (posX.size() > maxStack)
	{
		maxStack = posX.size();
		endPosX = posX.top();
		endPosY = posY.top();
	}
	char around[4];
	bool choices[4];
	int numDirections, randDirection;
	lookAround(maze, around, posX.top(), posY.top());
	maze[posY.top()][posX.top()] = '.';
	numDirections = possibleDirections(around, choices);
	if (posX.size() > (COL / 2 + 1))
	{
		maze[posY.top()][posX.top()] = 'T';
		posX.pop();
		posY.pop();
		posX.pop();
		posY.pop();

		lookBack(maze, around, posX.top(), posY.top());
		numDirections = possibleDirections(around, choices);
	}
	if (numDirections == 0)
	{
		while (numDirections == 0)
		{
			if (posX.top() == START_X && posY.top() == START_Y)
			{
				return;
			}
			posX.pop();
			posY.pop();
			lookBack(maze, around, posX.top(), posY.top());
			numDirections = possibleDirections(around, choices);
		}
	}

	randDirection = chooseRand(choices, numDirections);
	int tempX = posX.top();
	int tempY = posY.top();
	move(tempX, tempY, randDirection);
	if (randDirection == 0)	 // move up
		mapDirection[tempY][tempX] = 'U';
	else if (randDirection == 1)// move right
		mapDirection[tempY][tempX] = 'R';
	else if (randDirection == 2)// move down
		mapDirection[tempY][tempX] = 'D';
	else if (randDirection == 3) // move left
		mapDirection[tempY][tempX] = 'L';
	posX.push(tempX);
	posY.push(tempY);
	generateMaze(maze, mapDirection, posX, posY, endPosX, endPosY, maxStack);
}
void cleanupMaze(char(&maze)[ROW][COL], int endPosX, int endPosY)
{
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			if (maze[y][x] == 's')
				maze[y][x] = ' ';
			else if (maze[y][x] == ' ')
				maze[y][x] = ' ';
			else if (maze[y][x] == '.')
				maze[y][x] = 'X';
			else if (maze[y][x] == 'X')
				maze[y][x] = ' ';
		}
	}

	maze[START_Y][START_X] = 'S';
	maze[endPosY][endPosX] = 'G';

	//	for (int y = 0; y < ROW; y++)
	//	{
	//		for (int x = 0; x < COL; x++)
	//		{
	//			if (maze[y][x] == ' ')
	//				maze[y][x] = 254;
	//			else if (maze[y][x] == 'X')
	//				maze[y][x] = ' ';
	//		}
	//	}
}
char assignDoorValue(char around[])
{
	bool map[4];
	for (int i = 0; i < 4; i++)
	{
		if (around[i] == ' ')
			map[i] = false;
		else (map[i] = true);
	}

	if (map[0] == true)
	{
		if (map[1] == true)
		{
			if (map[2] == true)
			{
				if (map[3] == true)
					return 'P';
				else if (map[3] == false)
					return 'O';
			}
			else if (map[2] == false)
			{
				if (map[3] == true)
					return 'N';
				else if (map[3] == false)
					return 'M';
			}
		}
		else if (map[1] == false)
		{
			if (map[2] == true)
			{
				if (map[3] == true)
					return 'L';
				else if (map[3] == false)
					return 'K';
			}
			else if (map[2] == false)
			{
				if (map[3] == true)
					return 'J';
				else if (map[3] == false)
					return 'I';
			}
		}
	}
	else if (map[0] == false)
	{
		if (map[1] == true)
		{
			if (map[2] == true)
				if (map[3] == true)
					return 'H';
				else
					return 'G';
			else
				if (map[3] == true)
					return 'F';
				else
					return 'E';
		}
		else if (map[1] == false)
		{
			if (map[2] == true)
				if (map[3] == true)
					return 'D';
				else
					return 'C';
			else
				if (map[3] == true)
					return 'B';
				else
					return 'A';
		}
	}
	return 'A';
}
void lookForDoors(char(&maze)[ROW][COL], int xPos, int yPos)
{
	char around[4];
	lookBack(maze, around, xPos, yPos);
	maze[yPos][xPos] = assignDoorValue(around);
}