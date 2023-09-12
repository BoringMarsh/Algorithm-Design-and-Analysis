#include<iostream>
#include<climits>
using namespace std;

/***************************************************************************
  �������ƣ�combination
  ��    �ܣ����������
  ���������const int num���������Ԫ�ظ���
		   const int total��Ԫ������
  �� �� ֵ��long long����ϸ���
  ˵    ����Ϊ��ʹ�������ݲ������������ڼ��㷽���Ͻ����˸Ľ�
***************************************************************************/
long long combination(const int num, const int total)
{
	if (num == 0) /*��Ԫ�ز������ʱ�������Ϊ1*/
		return 1;

	int high = total, low = 1;
	double ret = 1.0;  /*�漰�˳���������ֵ��Ϊdouble����ֹ��ʧ����*/
	bool ifHighEnd = false, ifLowEnd = false;

	while (!ifHighEnd || !ifLowEnd) {  /*�˳��������������׳��㷨����ֹ�������*/
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

	return (long long)(ret + 0.1);  /*����һ����С��ֵ��ת����������ֹ���������µľ��ȶ�ʧ*/
}

/***************************************************************************
  �������ƣ�numInput
  ��    �ܣ�����ȷ���Ƶ�����£�����һ������
  ���������const int minValue����Сֵ
		   const int maxValue�����ֵ
  �� �� ֵ��int����ȷ�������ֵ
  ˵    ������
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
		cout << "�����������������" << endl;
	}

	return ret;
}

/***************************************************************************
  �������ƣ�main
  ��    �ܣ�������
  �����������
  �� �� ֵ��0
  ˵    �����������
***************************************************************************/
int main()
{
	int cal, step;  /*����������Ŀ�경��*/
	step = numInput(INT_MIN, INT_MAX);
	cal = numInput(INT_MIN, INT_MAX);

	if (step < 0 || cal < 0 || step > cal) {  /*����Ƿ����޽������ͳһ��ʾΪ0�ַ���*/
		cout << 0 << endl;
		return 0;
	}

	/*�ҳ�2���ߴ������Ľ⣬��ʱ���ĵ�������࣬�������Ϊ��������������¥������*/
	for (int k = cal - step; k >= 0; k--)
	{
		if (step - 2 * k >= 0) {  /*��֤1���ߴ���Ϊ�Ǹ�*/
			cout << combination(k, step - k) << endl;
			break;
		}
	}
	
	return 0;
}