#include<iostream>
#include"D:/Tool Kit/LinkedSet/LinkedSet.h"
#include"D:/Tool Kit/LinkedStack/LinkedStack.h"
using namespace std;

#define LEVELS 5
#define POSITIONS 15
int solution_count = 0;
int solution_1 = 0;
int solution_5 = 0;
int solution_7 = 0;
int solution_10 = 0;
int solution_13 = 0;

struct position {
	int num;
	int level;
	bool isEmpty;

	position(const int n = -1, const int l = -1, const bool empty = false) :num(n), level(l), isEmpty(empty) {}

	inline bool operator>(const position p)
	{
		return this->num > p.num;
	}
	inline bool operator<(const position p)
	{
		return this->num < p.num;
	}
	inline bool operator>=(const position p)
	{
		return this->num >= p.num;
	}
	inline bool operator<=(const position p)
	{
		return this->num <= p.num;
	}
};

struct boardmove {
	int num;
	int direction;

	boardmove(const int n = 0, const int d = 0) :num(n), direction(d) {}

	friend ostream& operator<<(ostream& out, const boardmove b)
	{
		out << b.num << ' ' << b.direction << endl;
		return out;
	}
};

bool find(position* board, const int num, const int direction, int* pos)
{
	/*此处num取值为1-15*/
	if (direction == 1) {
		if (num < 3)
			return false;

		position other[2] = { board[num - 2], board[num - 3] };

		if (other[0].level == other[1].level && other[0].level == board[num - 1].level
			&& !other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = num - 2;
			pos[1] = num - 3;
			return true;
		}
	}

	if (direction == 2) {
		if (num < 6)
			return false;

		const int gap1 = board[num - 1].level;
		const int pos1 = num - gap1 - 1;
		const int gap2 = board[pos1].level;
		const int pos2 = pos1 - gap2;
		position other[2] = { board[pos1], board[pos2] };

		if (other[0].level + 1 == board[num - 1].level && other[1].level + 1 == other[0].level
			&& !other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = pos1;
			pos[1] = pos2;
			return true;
		}
	}

	if (direction == 3) {
		if (num < 4)
			return false;

		const int gap1 = board[num - 1].level - 1;
		const int pos1 = num - gap1 - 1;
		const int gap2 = board[pos1].level - 1;
		const int pos2 = pos1 - gap2;
		position other[2] = { board[pos1], board[pos2] };

		if (other[0].level + 1 == board[num - 1].level && other[1].level + 1 == other[0].level
			&& !other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = pos1;
			pos[1] = pos2;
			return true;
		}
	}

	if (direction == 4) {
		if (num < 4)
			return false;

		position other[2] = { board[num], board[num + 1] };

		if (other[0].level == other[1].level && other[0].level == board[num - 1].level
			&& !other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = num;
			pos[1] = num + 1;
			return true;
		}
	}

	if (direction == 5) {
		if (num > 6)
			return false;

		const int gap1 = board[num - 1].level + 1;
		const int pos1 = num + gap1 - 1;
		const int gap2 = board[pos1].level + 1;
		const int pos2 = pos1 + gap2;
		position other[2] = { board[pos1], board[pos2] };

		if (!other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = pos1;
			pos[1] = pos2;
			return true;
		}
	}

	if (direction == 6) {
		if (num > 6)
			return false;

		const int gap1 = board[num - 1].level;
		const int pos1 = num + gap1 - 1;
		const int gap2 = board[pos1].level;
		const int pos2 = pos1 + gap2;
		position other[2] = { board[pos1], board[pos2] };

		if (!other[0].isEmpty && !other[1].isEmpty) {
			pos[0] = pos1;
			pos[1] = pos2;
			return true;
		}
	}

	return false;
}

void jump(position* board,
	LinkedSet<int>& openlist,
	LinkedStack<boardmove>& solution,
	const int num,
	const int direction,
	int* pos)
{
	board[num - 1].isEmpty = false;
	board[pos[0]].isEmpty = true;
	board[pos[1]].isEmpty = true;
	openlist.delMember(board[num - 1].num);
	openlist.addMember(board[pos[0]].num);
	openlist.addMember(board[pos[1]].num);
	solution.push(boardmove(num, direction));
}

void resume(position* board,
	LinkedSet<int>& openlist,
	LinkedStack<boardmove>& solution,
	const int num,
	const int direction,
	int* pos)
{
	board[num - 1].isEmpty = true;
	board[pos[0]].isEmpty = false;
	board[pos[1]].isEmpty = false;
	openlist.addMember(board[num - 1].num);
	openlist.delMember(board[pos[0]].num);
	openlist.delMember(board[pos[1]].num);
	boardmove b;
	solution.pop(b);
}

bool findStep(position* board,
	LinkedSet<int>& openlist,
	LinkedStack<boardmove>& solution,
	const int num)
{
	if (openlist.GetSize() == 14) {
		solution_count++;
		boardmove b;
		solution.getTop(b);

		switch (b.num) {
		case 1:
			solution_1++;
			break;
		case 5:
			solution_5++;
			break;
		case 7:
			solution_7++;
			break;
		case 10:
			solution_10++;
			break;
		case 13:
			solution_13++;
			break;
		}

		return true;
	}

	for (int i = 0; i < 6; i++)
	{
		int pos[2] = { 0, 0 };

		if (find(board, num, i + 1, pos)) {
			jump(board, openlist, solution, num, i + 1, pos);  /*进行跳跃*/

			/*遍历所有空位递归查询*/
			SetNode<int>* ptr = openlist.getHead()->link;
			const int size = openlist.GetSize();
			int list[15];

			for (int i = 0; i < size; i++)
			{
				list[i] = ptr->data;
				ptr = ptr->link;
			}

			for (int i = 0; i < size; i++)
			{
				const bool ret = findStep(board, openlist, solution, list[i]);

				if (ret)
					break;
			}

			resume(board, openlist, solution, num, i + 1, pos);  /*恢复*/
		}
	}

	return false;
}

int main()
{
	position board[15];
	LinkedSet<int> openlist;
	LinkedStack<boardmove> solution;
	int count = 0;
	for (int i = 1; i <= LEVELS; i++)
	{
		for (int j = 1; j < i + 1; j++)
		{
			board[count].num = count + 1;
			board[count].level = i;
			board[count].isEmpty = false;
			count++;
		}
	}
	board[12].isEmpty = true;
	openlist.addMember(board[12].num);

	findStep(board, openlist, solution, 13);

	cout << solution_count << endl;
	cout << double(solution_1) / solution_count << endl;
	cout << double(solution_5) / solution_count << endl;
	cout << double(solution_7) / solution_count << endl;
	cout << double(solution_10) / solution_count << endl;
	cout << double(solution_13) / solution_count << endl;
	return 0;
}