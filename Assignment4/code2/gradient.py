import numpy as np


def func(x1, x2):
    """
    求函数值
    """
    return np.power(np.e, x1 + 3 * x2 - 0.1) + np.power(np.e, x1 - 3 * x2 - 0.1) + np.power(np.e, -1 * x1 - 0.1)


def df_dx1(x1, x2):
    """
    求对x1的偏导数函数值
    """
    return np.power(np.e, x1 + 3 * x2 - 0.1) + np.power(np.e, x1 - 3 * x2 - 0.1) - np.power(np.e, -1 * x1 - 0.1)


def df_dx2(x1, x2):
    """
    求对x2的偏导数函数值
    """
    return 3 * np.power(np.e, x1 + 3 * x2 - 0.1) - 3 * np.power(np.e, x1 - 3 * x2 - 0.1)


if __name__ == "__main__":
    # 一、迭代前准备
    x1, x2 = 0, 0   # 两个自变量
    learning_rate = 1e-3  # 学习率
    z = func(x1, x2)  # 初始函数值
    eta = 1e-16  # 阈值

    # 二、进行迭代
    while True:
        # 1.求梯度方向
        dx1 = df_dx1(x1, x2)
        dx2 = df_dx2(x1, x2)

        # 2.向梯度方向的反方向移动，并得到新函数值
        x1 -= dx1 * learning_rate
        x2 -= dx2 * learning_rate
        z_temp = func(x1, x2)

        # 3.比较迭代前后的函数值，低于阈值时终止
        if np.abs(z - z_temp) > eta:
            z = z_temp
        else:
            print(f"x1*= {x1} x2*= {x2}")
            print(f"f*= {z_temp}")
            break
