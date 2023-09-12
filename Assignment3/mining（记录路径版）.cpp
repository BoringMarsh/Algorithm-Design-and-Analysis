#include<iostream>
#include<vector>
#include<stack>
using namespace std;

/*��¼����Ľṹ��*/
struct point {
	int line;
	int row;

	point(const int _line = -1, const int _row = -1) :line(_line), row(_row) {}
};

/***************************************************************************
  �������ƣ�direction_count
  ��    �ܣ�ͳ�Ƶ�ǰλ�ÿ��Լ����н��ķ��򲢱���
  ���������vector<vector<maps>>& grid����ʾ��������
			vector<vector<bool>>& wayMark����ǵ�ǰ·���߹���λ�õĶ�ά����
			vector<point>& next����һ������λ�õ�����
			const point miner���󹤵ĵ�ǰλ�ã�ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void direction_count(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	vector<point>& next,
	const point miner)
{
	next.clear();   /*���ԭ�м�¼*/

	/*������������ĸ�Ԫ�أ�����Ԫ�ش��ڡ�λ��Ϊ����δ����ǣ������ͳ��*/
	/*1������Ϸ�Ԫ��*/
	if (miner.line >= 1 && grid[miner.line - 1][miner.row] != 0 && !wayMark[miner.line - 1][miner.row])
		next.push_back(point(miner.line - 1, miner.row));

	/*2������·�Ԫ��*/
	if (miner.line < grid.size() - 1 && grid[miner.line + 1][miner.row] != 0 && !wayMark[miner.line + 1][miner.row])
		next.push_back(point(miner.line + 1, miner.row));

	/*3��������Ԫ��*/
	if (miner.row >= 1 && grid[miner.line][miner.row - 1] != 0 && !wayMark[miner.line][miner.row - 1])
		next.push_back(point(miner.line, miner.row - 1));

	/*4������Ҳ�Ԫ��*/
	if (miner.row < grid[0].size() - 1 && grid[miner.line][miner.row + 1] != 0 && !wayMark[miner.line][miner.row + 1])
		next.push_back(point(miner.line, miner.row + 1));
}

/***************************************************************************
  �������ƣ�walk
  ��    �ܣ���ǰ��һ��
  ���������vector<vector<maps>>& grid����ʾ��������
			vector<vector<bool>>& wayMark����ǵ�ǰ·���߹���λ�õĶ�ά����
			stack<point>& current����¼��ǰ·����ջ
			point& miner���󹤵ĵ�ǰλ��
			const point dest����һ����Ŀ��λ�ã�ֻ����
			int& currentValue����ǰ�ƽ���Ŀ
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void walk(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	point& miner,
	const point dest,
	int& currentValue)
{
	miner = dest;  /*���ƶ���Ŀ��λ��*/
	current.push(miner);  /*��ǰ·����¼����һ��*/
	currentValue += grid[miner.line][miner.row];  /*�õ���λ�õĽ���ֵ*/
	wayMark[miner.line][miner.row] = true;  /*��Ǹ�λ��Ϊ���߹�*/
}

/***************************************************************************
  �������ƣ�back
  ��    �ܣ�������һ��ǰ���Ĳ���
  ���������vector<vector<maps>>& grid����ʾ��������
			vector<vector<bool>>& wayMark����ǵ�ǰ·���߹���λ�õĶ�ά����
			stack<point>& current����¼��ǰ·����ջ
			point& miner���󹤵ĵ�ǰλ��
			int& currentValue����ǰ�ƽ���Ŀ
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void back(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	point& miner,
	int& currentValue)
{
	miner = current.top();  /*��ǰ·���Ƴ���һ��*/
	current.pop();

	currentValue -= grid[miner.line][miner.row];  /*��ȥ��λ�õĽ���ֵ*/
	wayMark[miner.line][miner.row] = false;  /*��Ǹ�λ��Ϊδ�߹�*/
	miner = current.top();  /*�󹤻���һ��*/
}

/***************************************************************************
  �������ƣ�getPointMaximumGold
  ��    �ܣ����Ҷ���ĳһ�ض��������Ž�
  ���������vector<vector<maps>>& grid����ʾ��������
			vector<vector<bool>>& wayMark����ǵ�ǰ·���߹���λ�õĶ�ά����
			stack<point>& current����¼��ǰ·����ջ
			stack<point>& result����¼���Ž��ջ
			point& miner���󹤵ĵ�ǰλ��
			int& currentValue����ǰ�ƽ���Ŀ
			int& maxValue����ǰ���Ž�ƽ���Ŀ
  �� �� ֵ��int������ĳһ�ض���㣬���Ž�Ļƽ���Ŀ
  ˵    ������
***************************************************************************/
int getPointMaximumGold(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	stack<point>& result,
	point& miner,
	int& currentValue,
	int& maxValue)
{
	vector<point> next;  /*��ſ��н�λ�õ�����*/
	direction_count(grid, wayMark, next, miner);  /*ͳ�ƿ��н�λ��*/

	if (next.empty()) {  /*���޿��н�λ�ã����ҵ�һ��·�������ݵ�ǰ�ƽ������������Ž�*/
		if (currentValue > maxValue) {
			maxValue = currentValue;
			result = current;
		}

		return maxValue;
	}

	for (auto iter = next.begin(); iter != next.end(); iter++)  /*���п��н�λ�ã����ÿһ�����н�������еݹ��ѯ*/
	{
		walk(grid, wayMark, current, miner, *iter, currentValue);  /*ǰ��*/

		getPointMaximumGold(grid, wayMark, current, result, miner, currentValue, maxValue);  /*�ݹ��ѯ*/

		back(grid, wayMark, current, miner, currentValue);  /*�ָ�*/
	}

	return maxValue;
}

/***************************************************************************
  �������ƣ�getMaximumGold
  ��    �ܣ����һƽ���������·��
  ���������vector<vector<maps>>& grid����ʾ��������
  �� �� ֵ��int�����Ž�Ļƽ���Ŀ
  ˵    ��������������δ�ڵ����Ĵ���
***************************************************************************/
int getMaximumGold(vector<vector<int>>& grid)
{
	int maxValue = 0;  /*��ǰ���ƽ�����*/
	stack<point> current, result;  /*��ǰ·�������Ž�·��*/
	vector<vector<bool>> wayMark(grid.size(), vector<bool>(grid[0].size(), false));  /*��¼·���Ͼ���λ�õĶ�ά����*/

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j]) {  /*����ÿ����Ϊ0��λ�ã�������Ϊ���*/
				point miner(i, j);              /*�������λ��*/
				int currentValue = grid[i][j];  /*��ǰ�ƽ���������ʼΪ���Ļƽ�����*/
				wayMark[i][j] = true;  /*��ʼλ�����߹������ϱ��*/
				current.push(miner);   /*��ǰ·����¼�����*/

				getPointMaximumGold(grid, wayMark, current, result, miner, currentValue, maxValue);  /*�ҳ�����������Ž�*/

				wayMark[i][j] = false;  /*������ɣ����ȡ��*/
				current.pop();  /*������ɣ���ǰ·���������*/
			}
		}
	}

	if (maxValue == 0)
		cout << "δ�ڵ���󣬿��ֶ��飡" << endl;
	else
	{
		cout << "һ���ռ����ƽ��·���ǣ�" << endl;
		vector<point> way;

		while (!result.empty()) {
			way.push_back(result.top());
			result.pop();
		}

		for (auto iter = way.end() - 1; iter != way.begin(); iter--)
		{
			cout << (*iter).line << ' ' << (*iter).row << endl;
		}

		cout << way[0].line << ' ' << way[0].row << endl;
	}

	return maxValue;
}

int main()
{
	vector<vector<int>> grid(4, vector<int>(3, 0));

	grid[0][0] = 0;
	grid[0][1] = 6;
	grid[0][2] = 0;
	grid[1][0] = 5;
	grid[1][1] = 8;
	grid[1][2] = 7;
	grid[2][0] = 0;
	grid[2][1] = 9;
	grid[2][2] = 0;

	cout << "�ƽ�������" << getMaximumGold(grid) << endl;
	return 0;
}