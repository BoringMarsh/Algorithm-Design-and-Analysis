#include<iostream>
#include<vector>
#include<stack>
using namespace std;

/*记录坐标的结构体*/
struct point {
	int line;
	int row;

	point(const int _line = -1, const int _row = -1) :line(_line), row(_row) {}
};

/***************************************************************************
  函数名称：direction_count
  功    能：统计当前位置可以继续行进的方向并保存
  输入参数：vector<vector<maps>>& grid：表示金矿的网格
			vector<vector<bool>>& wayMark：标记当前路径走过的位置的二维数组
			vector<point>& next：下一步可行位置的数组
			const point miner：矿工的当前位置（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void direction_count(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	vector<point>& next,
	const point miner)
{
	next.clear();   /*清空原有记录*/

	/*检查上下左右四个元素，若该元素存在、位置为空且未被标记，则进行统计*/
	/*1、检查上方元素*/
	if (miner.line >= 1 && grid[miner.line - 1][miner.row] != 0 && !wayMark[miner.line - 1][miner.row])
		next.push_back(point(miner.line - 1, miner.row));

	/*2、检查下方元素*/
	if (miner.line < grid.size() - 1 && grid[miner.line + 1][miner.row] != 0 && !wayMark[miner.line + 1][miner.row])
		next.push_back(point(miner.line + 1, miner.row));

	/*3、检查左侧元素*/
	if (miner.row >= 1 && grid[miner.line][miner.row - 1] != 0 && !wayMark[miner.line][miner.row - 1])
		next.push_back(point(miner.line, miner.row - 1));

	/*4、检查右侧元素*/
	if (miner.row < grid[0].size() - 1 && grid[miner.line][miner.row + 1] != 0 && !wayMark[miner.line][miner.row + 1])
		next.push_back(point(miner.line, miner.row + 1));
}

/***************************************************************************
  函数名称：walk
  功    能：往前走一步
  输入参数：vector<vector<maps>>& grid：表示金矿的网格
			vector<vector<bool>>& wayMark：标记当前路径走过的位置的二维数组
			stack<point>& current：记录当前路径的栈
			point& miner：矿工的当前位置
			const point dest：这一步的目标位置（只读）
			int& currentValue：当前黄金数目
  返 回 值：无
  说    明：无
***************************************************************************/
void walk(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	point& miner,
	const point dest,
	int& currentValue)
{
	miner = dest;  /*矿工移动到目标位置*/
	current.push(miner);  /*当前路径记录下这一步*/
	currentValue += grid[miner.line][miner.row];  /*得到该位置的金矿价值*/
	wayMark[miner.line][miner.row] = true;  /*标记该位置为已走过*/
}

/***************************************************************************
  函数名称：back
  功    能：撤销上一次前进的操作
  输入参数：vector<vector<maps>>& grid：表示金矿的网格
			vector<vector<bool>>& wayMark：标记当前路径走过的位置的二维数组
			stack<point>& current：记录当前路径的栈
			point& miner：矿工的当前位置
			int& currentValue：当前黄金数目
  返 回 值：无
  说    明：无
***************************************************************************/
void back(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	point& miner,
	int& currentValue)
{
	miner = current.top();  /*当前路径移除这一步*/
	current.pop();

	currentValue -= grid[miner.line][miner.row];  /*减去该位置的金矿价值*/
	wayMark[miner.line][miner.row] = false;  /*标记该位置为未走过*/
	miner = current.top();  /*矿工回退一步*/
}

/***************************************************************************
  函数名称：getPointMaximumGold
  功    能：查找对于某一特定起点的最优解
  输入参数：vector<vector<maps>>& grid：表示金矿的网格
			vector<vector<bool>>& wayMark：标记当前路径走过的位置的二维数组
			stack<point>& current：记录当前路径的栈
			stack<point>& result：记录最优解的栈
			point& miner：矿工的当前位置
			int& currentValue：当前黄金数目
			int& maxValue：当前最优解黄金数目
  返 回 值：int：对于某一特定起点，最优解的黄金数目
  说    明：无
***************************************************************************/
int getPointMaximumGold(vector<vector<int>>& grid,
	vector<vector<bool>>& wayMark,
	stack<point>& current,
	stack<point>& result,
	point& miner,
	int& currentValue,
	int& maxValue)
{
	vector<point> next;  /*存放可行进位置的向量*/
	direction_count(grid, wayMark, next, miner);  /*统计可行进位置*/

	if (next.empty()) {  /*若无可行进位置，则找到一条路径，根据当前黄金数量更新最优解*/
		if (currentValue > maxValue) {
			maxValue = currentValue;
			result = current;
		}

		return maxValue;
	}

	for (auto iter = next.begin(); iter != next.end(); iter++)  /*若有可行进位置，则对每一个可行进方向进行递归查询*/
	{
		walk(grid, wayMark, current, miner, *iter, currentValue);  /*前进*/

		getPointMaximumGold(grid, wayMark, current, result, miner, currentValue, maxValue);  /*递归查询*/

		back(grid, wayMark, current, miner, currentValue);  /*恢复*/
	}

	return maxValue;
}

/***************************************************************************
  函数名称：getMaximumGold
  功    能：查找黄金数量最大的路径
  输入参数：vector<vector<maps>>& grid：表示金矿的网格
  返 回 值：int：最优解的黄金数目
  说    明：本函数做了未挖到金矿的处理
***************************************************************************/
int getMaximumGold(vector<vector<int>>& grid)
{
	int maxValue = 0;  /*当前最大黄金数量*/
	stack<point> current, result;  /*当前路径、最优解路径*/
	vector<vector<bool>> wayMark(grid.size(), vector<bool>(grid[0].size(), false));  /*记录路径上经过位置的二维数组*/

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (grid[i][j]) {  /*遍历每个不为0的位置，让其作为起点*/
				point miner(i, j);              /*矿工在起点位置*/
				int currentValue = grid[i][j];  /*当前黄金数量，初始为起点的黄金数量*/
				wayMark[i][j] = true;  /*初始位置已走过，做上标记*/
				current.push(miner);   /*当前路径记录下起点*/

				getPointMaximumGold(grid, wayMark, current, result, miner, currentValue, maxValue);  /*找出这个起点的最优解*/

				wayMark[i][j] = false;  /*查找完成，标记取消*/
				current.pop();  /*查找完成，当前路径弹出起点*/
			}
		}
	}

	if (maxValue == 0)
		cout << "未挖到金矿，空手而归！" << endl;
	else
	{
		cout << "一种收集最多黄金的路线是：" << endl;
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

	cout << "黄金总量：" << getMaximumGold(grid) << endl;
	return 0;
}