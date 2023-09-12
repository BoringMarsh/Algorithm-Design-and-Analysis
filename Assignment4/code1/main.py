from seam_carving import SeamCarver

import os


if __name__ == '__main__':
    input_folder = 'in'    # 输入图片所在文件夹
    output_folder = 'out'  # 输出图片所在文件夹

    input_filename = 'image.png'   # 输入图片文件名
    output_filename = 'image_result.png'  # 输出图片文件名

    input_file_path = os.path.join(input_folder, input_filename)   # 输入图片路径
    output_file_path = os.path.join(output_folder, output_filename)  # 输出图片路径

    output = SeamCarver(input_file_path)  # 读入并处理图像
    output.save_result(output_file_path)  # 保存输出图像
