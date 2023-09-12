import numpy as np
import cv2
import time


class SeamCarver:
    def __init__(self, input_filename):
        # 一、初始化参数
        self.start_time = time.time()     # 总计时起点
        self.last_time = self.start_time  # 上一次的记录点

        # 二、读取输入图片
        self.in_image = cv2.imread(input_filename).astype(np.float64)  # 以float64格式读取
        print(f"读取完成    time:{time.time() - self.start_time}")
        self.in_height, self.in_width = self.in_image.shape[: 2]  # 取得输入图片宽度和高度
        self.out_height, self.out_width = self.in_height, self.in_width  # 输出图片高度

        # 三、初始化输出图片
        self.out_image = np.copy(self.in_image)  # 将输入图片拷贝到输出图片以完成初始化
        print(f"拷贝完成    time:{time.time() - self.start_time}")

        # 四、开始处理
        self.seams_carving()

    def seams_carving(self):
        """
        缩放的主过程
        """
        # 一、计算输入输出的宽度差delta
        print(f"seams_carving开始    time:{time.time() - self.start_time}")
        delta = int(self.in_width / 2)
        print(f"删除width数:{delta}")

        # 二、删除delta个seam
        for dummy in range(delta):
            energy_map = self.calc_energy_map()              # 计算能量图
            dp, k = self.cumulative_map_forward(energy_map)  # 填动态规划表并记录来到每个位置的上一个位置方向
            seam_way_coord = self.find_seam(dp, k)           # 找出seam的具体坐标
            self.delete_seam(seam_way_coord)                 # 删除seam

            time_stamp = time.time()  # 每删除一条seam的计时点
            print(f"seam{dummy + 1}删除完成    "
                  f"time:{round(time_stamp - self.last_time, 2)}    "
                  f"total:{round(time_stamp - self.start_time, 2)}    "
                  f"current_size:{self.out_image.shape[0]}*{self.out_image.shape[1]}")  # 打印删除一条seam后的情况
            self.last_time = time_stamp

    def calc_energy_map(self):
        """
        计算当前图片的能量
        """
        b, g, r = cv2.split(self.out_image)  # 将图片分成B、G、R三个通道
        b_energy = np.absolute(cv2.Scharr(b, -1, 1, 0)) + np.absolute(cv2.Scharr(b, -1, 0, 1))  # 计算B通道能量
        g_energy = np.absolute(cv2.Scharr(g, -1, 1, 0)) + np.absolute(cv2.Scharr(g, -1, 0, 1))  # 计算G通道能量
        r_energy = np.absolute(cv2.Scharr(r, -1, 1, 0)) + np.absolute(cv2.Scharr(r, -1, 0, 1))  # 计算R通道能量
        return b_energy + g_energy + r_energy  # 合并三个通道的能量并返回

    def cumulative_map_forward(self, energy_map):
        """
        填动态规划表，并记录来到每个位置的上一个位置方向
        """
        # 动态规划表，dp[i][j]指的是到i行j列像素能量最小路径的能量总和
        dp = []

        # k[i][j]只可能有三个值-1、0、1。分别表示沿能量最小路径走到i+1行j列像素时，上个位置在当前位置的左上、正上、右上
        # 这个信息不需要记录第一行的，因此k仅有i-1行j列
        k = []

        for i in range(self.out_height):  # 初始化两个表
            dp.append([])

            if i > 0:
                k.append([])

            for j in range(self.out_width):
                dp[i].append(-1)

                if i > 0:
                    k[i - 1].append(0)

        for i in range(self.out_height):  # 遍历dp表的每一个位置，填两个表
            for j in range(self.out_width):
                if i == 0:
                    dp[i][j] = energy_map[i][j]  # 0行所有元素就是自身的能量值
                else:
                    dp[i][j] = energy_map[i][j] + dp[i - 1][j]  # 以从正上方下来的情况作为比较基准
                    k[i - 1][j] = 0

                    # 遍历左上、正上、右上三个位置，找到最小的能量总和并记录上个元素的方向
                    if j == 0:  # 第一列
                        for dir in range(2):
                            this_min = energy_map[i][j] + dp[i - 1][j + dir]

                            if dp[i][j] > this_min:
                                dp[i][j] = this_min
                                k[i - 1][j] = dir

                    elif j == self.out_width - 1:  # 最后一列
                        for dir in range(-1, 1):
                            this_min = energy_map[i][j] + dp[i - 1][j + dir]

                            if dp[i][j] > this_min:
                                dp[i][j] = this_min
                                k[i - 1][j] = dir

                    else:  # 其余情况
                        for dir in range(-1, 2):
                            this_min = energy_map[i][j] + dp[i - 1][j + dir]

                            if dp[i][j] > this_min:
                                dp[i][j] = this_min
                                k[i - 1][j] = dir

        return dp, k

    def find_seam(self, dp, k):
        """
        根据两张表的值，求出seam每一个像素的具体坐标
        """
        current_col = dp[self.out_height - 1].index(min(dp[self.out_height - 1]))  # 在dp最后一行找最小元素，取其下标作为列
        current_row = self.out_height - 1  # 横向缩放高度不变，取图片高度-1作为行
        way_coord = [(current_row, current_col)]  # 将起点加入坐标列表

        for i in range(self.out_height - 2, -1, -1):  # 回溯寻找路径
            current_col += k[i][current_col]  # 若k值是-1，则在左上，列数-1；若k值是0，则在正上，列数不变；若k值是1，则在右上，列数+1
            current_row -= 1  # 每次都上升一行
            way_coord.append((current_row, current_col))  # 将当前点加入坐标列表

        return way_coord

    def delete_seam(self, seam_idx):
        """
        根据seam的具体坐标将其删除
        """
        m, n = self.out_image.shape[: 2]
        output = np.zeros((m, n - 1, 3))  # 创建一个列数是当前图片列数-1的数组
        for coord in range(m):
            row, col = seam_idx[coord][0], seam_idx[coord][1]  # 取像素的坐标并在原图删除后放入output
            output[row, :, 0] = np.delete(self.out_image[row, :, 0], [col])
            output[row, :, 1] = np.delete(self.out_image[row, :, 1], [col])
            output[row, :, 2] = np.delete(self.out_image[row, :, 2], [col])
        self.out_image = np.copy(output)  # 将output拷贝到原图，完成对原图的改变
        self.out_width -= 1  # 原图列数-1，可以减缓动态规划填表的压力

    def save_result(self, output_file_path):
        """
        将输出图片保存到硬盘
        """
        cv2.imwrite(output_file_path, self.out_image.astype(np.uint8))
