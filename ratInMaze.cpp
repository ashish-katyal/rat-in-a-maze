#include<bits/stdc++.h>
#include<graphics.h>
#include<chrono>
#include<thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


void printMaze(char maze[][10], int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0 and j == 0)
			{
				setfillstyle(SOLID_FILL, YELLOW);
				bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);
			}
			else if (i == m - 1 and j == n - 1)
			{
				setfillstyle(SOLID_FILL, YELLOW);
				bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);
			}
			else if (maze[i][j] == 'O')
			{
				setfillstyle(SOLID_FILL, BLUE);
				bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);
			}
			else
			{
				setfillstyle(SOLID_FILL, RED);
				bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);
			}
		}
	}
}

void printSoln(char soln[][10], int m, int n)
{
	system("cls");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << soln[i][j] << " ";
		}
		cout << endl;
	}
}

bool ratInMaze(char maze[][10], char soln[][10], int i, int j, int m, int n)
{
	if (i == m - 1 and j == n - 1)
	{
		soln[m - 1][n - 1] = '*';
		printSoln(soln, m, n);
		setfillstyle(SOLID_FILL, GREEN);
		bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);

		cout << endl << "Maze Solved";

		sleep_until(system_clock::now() + seconds(10));

		exit(0);
	}

	if (i >= m or j >= n)
		return false;

	if (maze[i][j] == 'X')
		return false;

	soln[i][j] = '*';
	printSoln(soln, m, n);
	setfillstyle(SOLID_FILL, GREEN);
	bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);

	sleep_until(system_clock::now() + seconds(1));

	bool rightSuccess = ratInMaze(maze, soln, i, j + 1, m, n);
	bool downSuccess = ratInMaze(maze, soln, i + 1, j, m, n);

	soln[i][j] = 'O';
	printSoln(soln, m, n);
	setfillstyle(SOLID_FILL, BLUE);
	bar(50 + j * 50, 50 + i * 50, 50 + j * 50 + 50, 50 + i * 50 + 50);

	sleep_until(system_clock::now() + seconds(1));

	if (rightSuccess or downSuccess)
	{
		return true;
	}
	return false;
}

int main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, (char*)"");

	char maze[10][10] = {
		"OOXOOXOO",
		"OOOXOOOX",
		"OOXOOOXO",
		"XOOOOOOX",
		"XXOOXXOO",
		"OOOOOXOX",
		"OOXOOOXO",
		"XOOOXOOO",
	};

	int m, n;

	m = 8;
	n = 8;

	printMaze(maze, m, n);

	char soln[10][10] ;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			soln[i][j] = maze[i][j];
		}
	}

	printSoln(soln, m, n);
	sleep_until(system_clock::now() + seconds(1));
	bool ans = ratInMaze(maze, soln, 0, 0, m, n);

	if (ans == false)
		cout << endl << "Maze can't be solved";
}
