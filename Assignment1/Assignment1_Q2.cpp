#include<iostream>
#include<climits>
using namespace std;

/***************************************************************************
  函数名称：combination
  功    能：计算组合数
  输入参数：const int num：参与组合元素个数
		   const int total：元素总数
  返 回 值：long long：组合个数
  说    明：为了使运算数据不会过早溢出，在计算方法上进行了改进
***************************************************************************/
long long combination(const int num, const int total)
{
	if (num == 0) /*无元素参与组合时，组合数为1*/
		return 1;

	int high = total, low = 1;
	double ret = 1.0;  /*涉及乘除，将返回值设为double，防止丢失精度*/
	bool ifHighEnd = false, ifLowEnd = false;

	while (!ifHighEnd || !ifLowEnd) {  /*乘除交替进行来代替阶乘算法，防止数据溢出*/
		if (high < total - num + 1)
			ifHighEnd = true;
		else {
			ret *= high;
			high--;
		}

		if (low > num)
			ifLowEnd = true;
		else {
			ret /= low;
			low++;
		}
	}

	return (long long)(ret + 0.1);  /*加上一个较小的值后转成整数，防止除不尽导致的精度丢失*/
}

/***************************************************************************
  函数名称：numInput
  功    能：在正确控制的情况下，输入一个整数
  输入参数：const int minValue：最小值
		   const int maxValue：最大值
  返 回 值：int：正确输入的数值
  说    明：无
***************************************************************************/
int numInput(const int minValue, const int maxValue)
{
	int ret = 0;

	while (1) {
		cin >> ret;

		if (cin.good() && ret >= minValue && ret <= maxValue)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "输入错误！请重新输入" << endl;
	}

	return ret;
}

/***************************************************************************
  函数名称：main
  功    能：主函数
  输入参数：无
  返 回 值：0
  说    明：程序入口
***************************************************************************/
int main()
{
	int cal, step;  /*能量总数、目标步数*/
	step = numInput(INT_MIN, INT_MAX);
	cal = numInput(INT_MIN, INT_MAX);

	if (step < 0 || cal < 0 || step > cal) {  /*输入非法或无解情况，统一显示为0种方法*/
		cout << 0 << endl;
		return 0;
	}

	/*找出2步走次数最大的解，此时消耗的能量最多，组合数即为消耗能量最多的上楼方法数*/
	for (int k = cal - step; k >= 0; k--)
	{
		if (step - 2 * k >= 0) {  /*保证1步走次数为非负*/
			cout << combination(k, step - k) << endl;
			break;
		}
	}
	
	return 0;
}