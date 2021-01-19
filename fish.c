#include <stdio.h>
// for random number only
#include <time.h>
#include <stdlib.h>

//The algorithm for the AI to choose where to go
void a_movement(int a[2], int px, int py, int board[7][7]);
//return the count of surrounding possible move
int sur_count(int x, int y, int board[7][7]);
//determine if two points form a line
int is_line(int cur_x, int cur_y, int x, int y);
//determine if it's valid to travel from one point to another
int is_valid(int cur_x, int cur_y, int x, int y, int board[7][7]);
//determine if player or AI are stuck
int is_dead(int x, int y, int board[7][7]);
//determine if a point on the board is empty
int is_empty(int x, int y, int board[7][7]);
//clears bufffer to recover from wrong input such as char
void clear_keyboard_buffer();
//prints the board according to the 2D int array
void print_board(int px, int py, int ax, int ay, int board[7][7]);
//print the score of player and AI after the game ends
int print_score(int point[36]);

int main(int argc, char* argv[]) {
	//initialize the random number
	srand(time(NULL));
	//initial state of the board
	int board[7][7] = { {0,0,0,0,0,0,0}, {0,1,1,1,1,1,1}, {0,1,2,2,2,2,1}, {0,1,2,3,3,2,1}, {0,1,2,3,3,2,1}, {0,1,2,2,2,2,1}, {0,1,1,1,1,1,1} };
	//arrays used to track score of both player
	int p_point[36] = { 0 };
	int a_point[36] = { 0 };
	//int used to track position
	int px, py, ax, ay;
	//temperate holder for old position when moving
	int cur_px, cur_py;
	//tracks the amound of spot that each player landed on
	int p_count = 0, a_count = 0;
	//stores the total score for boo th player
	int p_sum, a_sum;
	printf("enter your starting coordinate in the \"row column\" format: ");
	scanf("%d", &py);
	scanf("%d", &px);
	clear_keyboard_buffer();
	while (px != 1 && px != 6 && py != 1 && py != 6) {
		printf("please enter coordinate that has only 1 fish on the board.\n");
		printf("enter your starting coordinate in the \"row column\" format: ");
		scanf("%d", &py);
		scanf("%d", &px);
		clear_keyboard_buffer();
	}
	p_point[p_count] = board[py][px];
	p_count++;
	board[py][px] = 0;
	ay = 6;
	do {
		ax = rand() % 6 + 1;
	} while (ax == px || ax == 2 || ax == 5);
	a_point[a_count] = board[ay][ax];
	a_count++;
	board[ay][ax] = 0;
	int temp[2] = { ax, ay };
	print_board(px, py, ax, ay, board);
	while (!is_dead(px, py, board) || !is_dead(ax, ay, board)) {
		if (!is_dead(px, py, board)) {
			cur_px = px;
			cur_py = py;
			printf("\n\nPLAYER\'S TURN: \n");
			printf("enter your next move in the \"row column\" format: ");
			scanf("%d", &py);
			scanf("%d", &px);
			clear_keyboard_buffer();
			while (!is_valid(cur_px, cur_py, px, py, board)) {
				printf("\nplease enter a point on the board that can be reached.\n");
				printf("\nenter your next move in the \"row column\" format: ");
				scanf("%d", &py);
				scanf("%d", &px);
				clear_keyboard_buffer();
			}
			p_point[p_count] = board[py][px];
			p_count++;
			board[py][px] = 0;
			printf("\n");
			print_board(px, py, ax, ay, board);
		}
		if (!is_dead(ax, ay, board)) {
			printf("\n\nThe AI has made its move:\n\n");
			a_movement(temp, px, py, board);
			ax = temp[0];
			ay = temp[1];
			a_point[a_count] = board[ay][ax];
			a_count++;
			board[ay][ax] = 0;
			print_board(px, py, ax, ay, board);
		}
	}
	printf("\n\nPlayer\'s points: ");
	p_sum = print_score(p_point);
	printf("\n");
	printf("\nAI\'s points: ");
	a_sum = print_score(a_point);
	printf("\n\n");
	if (p_sum > a_sum) {
		printf("Player wins!\n");
	}
	else if (p_sum < a_sum) {
		printf("AI wins!\n");
	}
	else {
		printf("It\'s a draw!\n");
	}
	return 0;
}

void a_movement(int a[2], int px, int py, int board[7][7]) {
	//goes for 3s first
	if (is_valid(a[0], a[1], 3, 4, board)) {
		a[0] = 3;
		a[1] = 4;
	}
	else if (is_valid(a[0], a[1], 4, 3, board)) {
		a[0] = 4;
		a[1] = 3;
	}
	else if (is_valid(a[0], a[1], 4, 4, board)) {
		a[0] = 4;
		a[1] = 4;
	}
	else if (is_valid(a[0], a[1], 3, 3, board)) {
		a[0] = 3;
		a[1] = 3;
	}
	//go close to player to pressure when it's safe
	if (board[a[1]][a[0]] == 0) {
		int n = 0, max = -1;
		//go to a spot near player if there's more than c possible move around the spot
		const int c = 2;
		if (is_valid(a[0], a[1], px, py + 1, board) && sur_count(px, py + 1, board) > c && sur_count(px, py + 1, board) > max) {
			max = sur_count(px, py + 1, board);
			n = 1;
		}
		if (is_valid(a[0], a[1], px, py - 1, board) && sur_count(px, py - 1, board) > c && sur_count(px, py - 1, board) > max) {
			max = sur_count(px, py - 1, board);
			n = 2;
		}
		if (is_valid(a[0], a[1], px + 1, py, board) && sur_count(px + 1, py, board) > c && sur_count(px + 1, py, board) > max) {
			max = sur_count(px + 1, py, board);
			n = 3;
		}
		if (is_valid(a[0], a[1], px + 1, py + 1, board) && sur_count(px + 1, py + 1, board) > c && sur_count(px + 1, py + 1, board) > max) {
			max = sur_count(px + 1, py + 1, board);
			n = 4;
		}
		if (is_valid(a[0], a[1], px + 1, py - 1, board) && sur_count(px + 1, py - 1, board) > c && sur_count(px + 1, py - 1, board) > max) {
			max = sur_count(px + 1, py - 1, board);
			n = 5;
		}
		if (is_valid(a[0], a[1], px - 1, py, board) && sur_count(px - 1, py, board) > c && sur_count(px - 1, py, board) > max) {
			max = sur_count(px - 1, py, board);
			n = 6;
		}
		if (is_valid(a[0], a[1], px - 1, py + 1, board) && sur_count(px - 1, py + 1, board) > c && sur_count(px - 1, py + 1, board) > max) {
			max = sur_count(px - 1, py + 1, board);
			n = 7;
		}
		if (is_valid(a[0], a[1], px - 1, py - 1, board) && sur_count(px - 1, py - 1, board) > c && sur_count(px - 1, py - 1, board) > max) {
			max = sur_count(px - 1, py - 1, board);
			n = 8;
		}
		switch (n)
		{
		case 1:
			a[0] = px;
			a[1] = py + 1;
			break;
		case 2:
			a[0] = px;
			a[1] = py - 1;
			break;
		case 3:
			a[0] = px + 1;
			a[1] = py;
			break;
		case 4:
			a[0] = px + 1;
			a[1] = py + 1;
			break;
		case 5:
			a[0] = px + 1;
			a[1] = py - 1;
			break;
		case 6:
			a[0] = px - 1;
			a[1] = py;
			break;
		case 7:
			a[0] = px - 1;
			a[1] = py + 1;
			break;
		case 8:
			a[0] = px - 1;
			a[1] = py - 1;
			break;
		default:
			break;
		}
	}
	//go to random 2s when 3s are gone and it's not safe to pressure
	if (board[a[1]][a[0]] == 0) {
		int x, y;
		int i = 0;
		do {
			x = rand() % 6 + 1;
			y = rand() % 6 + 1;
			i++;
			if (is_valid(a[0], a[1], x, y, board) && board[y][x] > 1) {
				a[0] = x;
				a[1] = y;
			}
		} while (i < 60 && board[a[1]][a[0]] == 0);
	}
	//go to surrounding area to collect more points
	if (board[a[1]][a[0]] == 0) {
		int n = 0, max = -1;
		int temp;
		if (is_valid(a[0], a[1], a[0], a[1] + 1, board)) {
			temp = sur_count(a[0], a[1] + 1, board);
			if (board[a[1] + 1][a[0]] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 1;
			}
		}
		if (is_valid(a[0], a[1], a[0], a[1] - 1, board)) {
			temp = sur_count(a[0], a[1] - 1, board);
			if (board[a[1] - 1][a[0]] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 2;
			}
		}
		if (is_valid(a[0], a[1], a[0] + 1, a[1], board)) {
			temp = sur_count(a[0] + 1, a[1], board);
			if (board[a[1]][a[0] + 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 3;
			}
		}
		if (is_valid(a[0], a[1], a[0] + 1, a[1] + 1, board)) {
			temp = sur_count(a[0] + 1, a[1] + 1, board);
			if (board[a[1] + 1][a[0] + 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 4;
			}
		}
		if (is_valid(a[0], a[1], a[0] + 1, a[1] - 1, board)) {
			temp = sur_count(a[0] + 1, a[1] - 1, board);
			if (board[a[1] - 1][a[0] + 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 5;
			}
		}
		if (is_valid(a[0], a[1], a[0] - 1, a[1], board)) {
			temp = sur_count(a[0] - 1, a[1], board);
			if (board[a[1]][a[0] - 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 6;
			}
		}
		if (is_valid(a[0], a[1], a[0] - 1, a[1] + 1, board)) {
			temp = sur_count(a[0] - 1, a[1] + 1, board);
			if (board[a[1] + 1][a[0] - 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 7;
			}
		}
		if (is_valid(a[0], a[1], a[0] - 1, a[1] - 1, board)) {
			temp = sur_count(a[0] - 1, a[1] - 1, board);
			if (board[a[1] - 1][a[0] - 1] > 1) {
				temp += 2;
			}
			if (temp > max) {
				max = temp;
				n = 8;
			}
		}
		switch (n)
		{
		case 1:
			a[1]++;
			break;
		case 2:
			a[1]--;
			break;
		case 3:
			a[0]++;
			break;
		case 4:
			a[0]++;
			a[1]++;
			break;
		case 5:
			a[0]++;
			a[1]--;
			break;
		case 6:
			a[0]--;
			break;
		case 7:
			a[0]--;
			a[1]++;
			break;
		case 8:
			a[0]--;
			a[1]--;
			break;
		default:
			break;
		}
	}
}


int sur_count(int x, int y, int board[7][7]) {
	int count = 0;
	if (!is_empty(x, y + 1, board))
		count++;
	if (!is_empty(x, y - 1, board))
		count++;
	if (!is_empty(x + 1, y, board))
		count++;
	if (!is_empty(x + 1, y + 1, board))
		count++;
	if (!is_empty(x + 1, y - 1, board))
		count++;
	if (!is_empty(x - 1, y, board))
		count++;
	if (!is_empty(x - 1, y + 1, board))
		count++;
	if (!is_empty(x - 1, y - 1, board))
		count++;
	return count;
}

int is_line(int cur_x, int cur_y, int x, int y) {
	if (cur_x == x && cur_y == y)
		return 0;
	if (cur_x == x || cur_y == y)
		return 1;
	if (((cur_x - x) == (cur_y - y)) || ((cur_x - x) == -1 * (cur_y - y)))
		return 1;
	return 0;
}

int is_valid(int cur_x, int cur_y, int x, int y, int board[7][7]) {
	//checks if new point is out of bound
	if (x < 1 || x > 6 || y < 1 || y > 6) {
		return 0;
	}
	//check if two points form a line
	if (!is_line(cur_x, cur_y, x, y)) {
		return 0;
	}
	//check if there is empty spot between two points
	if (x == cur_x) {
		if (y < cur_y) {
			for (int i = cur_y - 1; i >= y; i--) {
				if (board[i][x] == 0)
					return 0;
			}
		}
		else {
			for (int i = cur_y + 1; i <= y; i++) {
				if (board[i][x] == 0)
					return 0;
			}
		}
	}
	else if (y == cur_y) {
		if (x < cur_x) {
			for (int i = cur_x - 1; i >= x; i--) {
				if (board[y][i] == 0)
					return 0;
			}
		}
		else {
			for (int i = cur_x + 1; i <= x; i++) {
				if (board[y][i] == 0)
					return 0;
			}
		}
	}
	else if (x > cur_x) {
		if (y > cur_y) {
			for (int i = 1; i <= x - cur_x; i++) {
				if (board[cur_y + i][cur_x + i] == 0)
					return 0;
			}
		}
		else {
			for (int i = 1; i <= x - cur_x; i++) {
				if (board[cur_y - i][cur_x + i] == 0)
					return 0;
			}
		}
	}
	else {
		if (y > cur_y) {
			for (int i = 1; i <= cur_x - x; i++) {
				if (board[cur_y + i][cur_x - i] == 0)
					return 0;
			}
		}
		else {
			for (int i = 1; i <= cur_x - x; i++) {
				if (board[cur_y - i][cur_x - i] == 0)
					return 0;
			}
		}
	}
	return 1;
}

int is_dead(int x, int y, int board[7][7]) {
	//return 0 if there's no possible move as all surrounding is occupied
	return (is_empty(x + 1, y, board)
		&& is_empty(x + 1, y - 1, board)
		&& is_empty(x + 1, y + 1, board)
		&& is_empty(x - 1, y, board)
		&& is_empty(x - 1, y - 1, board)
		&& is_empty(x - 1, y + 1, board)
		&& is_empty(x, y + 1, board)
		&& is_empty(x, y - 1, board));
}

int is_empty(int x, int y, int board[7][7]) {
	if (x < 1 || x>6 || y < 1 || y>6 || board[y][x] == 0) {
		return 1;
	}
	return 0;
}

void print_board(int px, int py, int ax, int ay, int board[7][7]) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i == 0) {
				if (j == 0) {
					printf("  ");
				}
				else {
					printf("%-2d", j);
				}
			}
			else if (j == 0) {
				printf("%-2d", i);
			}
			else if (i == py && j == px) {
				printf("P ");
			}
			else if (i == ay && j == ax) {
				printf("A ");
			}
			else if (board[i][j] == 0) {
				printf(". ");
			}
			else {
				printf("%-2d", board[i][j]);
			}
		}
		printf("\n");
	}
}

int print_score(int point[36]) {
	int sum = 0;
	int i = 0;
	while (i < 35 && point[i + 1] != 0) {
		printf("%d+", point[i]);
		sum += point[i];
		i++;
	}
	sum += point[i];
	printf("%d = %d", point[i], sum);
	return sum;
}

void clear_keyboard_buffer()
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
