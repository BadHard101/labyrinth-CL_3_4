#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<stdlib.h>
#include<vector>
using namespace std;
void mazemake(int**, int, int); // Собственно алгоритм
void visual(int**, int, int); // Изображение результата с помощью консольной графики
const int wall = 0, pass = 1;

void right_hand_run(int** maze, string& prev, int& robot_i, int& robot_j)
{
	if (prev == "bottom")
	{
		if (maze[robot_i][robot_j - 1] == 0) {
			prev = "left";
			robot_j -= 1;
		}
		else if (maze[robot_i + 1][robot_j] == 0) {
			prev = "bottom";
			robot_i += 1;
		}
		else if (maze[robot_i][robot_j + 1] == 0) {
			prev = "right";
			robot_j += 1;
		}
		else {
			prev = "top";
			robot_i -= 1;
		}
	}
	else if (prev == "right")
	{
		if (maze[robot_i + 1][robot_j] == 0) {
			prev = "bottom";
			robot_i += 1;
		}
		else if (maze[robot_i][robot_j + 1] == 0) {
			prev = "right";
			robot_j += 1;
		}
		else if (maze[robot_i - 1][robot_j] == 0) {
			prev = "top";
			robot_i -= 1;
		}
		else {
			prev = "left";
			robot_j -= 1;
		}
	}
	else if (prev == "top")
	{
		if (maze[robot_i][robot_j + 1] == 0) {
			prev = "right";
			robot_j += 1;
		}
		else if (maze[robot_i - 1][robot_j] == 0) {
			prev = "top";
			robot_i -= 1;
		}
		else if (maze[robot_i][robot_j - 1] == 0) {
			prev = "left";
			robot_j -= 1;
		}
		else {
			prev = "bottom";
			robot_i += 1;
		}
	}
	else if (prev == "left")
	{
		if (maze[robot_i - 1][robot_j] == 0) {
			prev = "top";
			robot_i -= 1;
		}
		else if (maze[robot_i][robot_j - 1] == 0) {
			prev = "left";
			robot_j -= 1;
		}
		else if (maze[robot_i + 1][robot_j] == 0) {
			prev = "bottom";
			robot_i += 1;
		}
		else {
			prev = "right";
			robot_j += 1;
		}
	}
}

void visual(int** maze, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			cout << maze[i][j];
		cout << endl;
	}
	cout << endl;
}

void mazemake(int** maze, int height, int width) {
	string line;
	size_t pos = 0;
	string token;
	for (int i = 0; i < height; i++)
	{
		getline(cin, line);
		for (int j = 0; j < width; j++)
		{
			maze[i][j] = atoi(line.substr(0, 1).c_str());
			line.erase(0, 1);
		}
	}
}

struct Maze_coords {
	int start_i, start_j;
};

void realMaze(int start_i, int start_j, int robot_i, int robot_j, vector<Maze_coords>& coords)
{
	Maze_coords new_maze;
	bool is_same_maze = false;
	if (start_i == robot_i && start_j == robot_j)
		cout << "There is no way out of the maze (" << start_i + 1 << ", " << start_j + 1 << ")\n";
	else
	{
		for (int i = 0; i < coords.size(); i++)
		{
			if (coords[i].start_i == robot_i && coords[i].start_j == robot_j)
				is_same_maze = true;
		}
		if (!is_same_maze)
		{
			cout << "Maze (" << start_i + 1 << ", " << start_j + 1 << ") (" << robot_i + 1 << ", " << robot_j + 1 << ")\n";
			new_maze.start_i = start_i;
			new_maze.start_j = start_j;
			coords.push_back(new_maze);
		}
	}
}

void find_Maze(int start_i, int start_j, int robot_i, int robot_j, vector<Maze_coords>& coords, bool& Maze_found)
{
	if (start_i == robot_i && start_j == robot_j)
		cout << "There is no way out of the maze (" << start_i + 1 << ", " << start_j + 1 << ")\n";
	else
	{
		cout << "Maze (" << start_i + 1 << ", " << start_j + 1 << ") (" << robot_i + 1 << ", " << robot_j + 1 << ")\n";
		Maze_found = true;
	}
}



int main() {

	srand((unsigned)time(NULL));

	int start_i;
	int start_j;
	int robot_i;
	int robot_j;

	bool Maze_found = false;
	int i_line;
	int j_line;
	string prev;
	vector<Maze_coords> coords;
	int height = 22, width = 22;

	int** maze = new int* [height];
	for (int i = 0; i < height; i++)
		maze[i] = new int[width];

	mazemake(maze, height, width);
	cout << endl;
	visual(maze, height, width);

	i_line = 0;
	for (int j = 1; j < width - 1; j++)
	{
		if (maze[i_line + 1][j] == 0)
		{
			start_i = i_line;
			start_j = j;
			robot_i = i_line + 1;
			robot_j = j;
			prev = "bottom";
			while ((robot_i != 0) && (robot_i != (height - 1)) && (robot_j != 0) && (robot_j != (width - 1)))
				right_hand_run(maze, prev, robot_i, robot_j);
			//cout << "Robot: " << start_i << " " << start_j << " " << robot_i << " " << robot_j << endl;
			find_Maze(start_i, start_j, robot_i, robot_j, coords, Maze_found);
			if (Maze_found) return 0;
		}
	}

	j_line = width - 1;
	for (int i = 1; i < height - 1; i++)
	{
		if (maze[i][j_line - 1] == 0)
		{
			start_i = i;
			start_j = j_line;
			robot_i = i;
			robot_j = j_line - 1;
			prev = "left";
			while ((robot_i != 0) && (robot_i != (height - 1)) && (robot_j != 0) && (robot_j != (width - 1)))
				right_hand_run(maze, prev, robot_i, robot_j);
			//cout << "Robot: " << start_i << " " << start_j << " " << robot_i << " " << robot_j << endl;
			find_Maze(start_i, start_j, robot_i, robot_j, coords, Maze_found);
			if (Maze_found) return 0;
		}
	}

	i_line = height - 1;
	for (int j = width - 2; j > 1; j--)
	{
		if (maze[i_line - 1][j] == 0)
		{
			start_i = i_line;
			start_j = j;
			robot_i = i_line - 1;
			robot_j = j;
			prev = "top";
			while ((robot_i != 0) && (robot_i != (height - 1)) && (robot_j != 0) && (robot_j != (width - 1)))
				right_hand_run(maze, prev, robot_i, robot_j);
			//cout << "Robot: " << start_i << " " << start_j << " " << robot_i << " " << robot_j << endl;
			find_Maze(start_i, start_j, robot_i, robot_j, coords, Maze_found);
			if (Maze_found) return 0;
		}
	}

	j_line = 0;
	for (int i = height - 2; i > 1; i--)
	{
		if (maze[i][j_line + 1] == 0)
		{
			start_i = i;
			start_j = j_line;
			robot_i = i;
			robot_j = j_line + 1;
			prev = "right";
			while ((robot_i != 0) && (robot_i != (height - 1)) && (robot_j != 0) && (robot_j != (width - 1)))
				right_hand_run(maze, prev, robot_i, robot_j);
			//cout << "Robot: " << start_i << " " << start_j << " " << robot_i << " " << robot_j << endl;
			find_Maze(start_i, start_j, robot_i, robot_j, coords, Maze_found);
			if (Maze_found) return 0;
		}
	}

	for (int i = 0; i < height; i++)
		delete[] maze[i];
	delete[] maze;

	return 0;
}