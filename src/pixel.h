#pragma once

#include "def.h"
#include "header.h"
#include <stdint.h>
#include <stdio.h>

/**
 * @brief 24 位位图的一个像素所含信息；
 *        蓝色：8位，
 *        绿色：8位，
 *        红色：8位
 */
typedef struct PIXEL_24 {
    byte_t blue;
    byte_t green;
    byte_t red;
} PIXEL_24;

/**
 * @brief 输出 BMP 文件中，一个指定像素的颜色信息；
 *        像素坐标轴以图像左上角为起点，坐标从 0 开始计数
 *
 * @param info_header BMP 信息头
 * @param fp BMP 文件指针
 * @param x 指定像素的 x 坐标
 * @param y 指定像素的 y 坐标
 * @return int 若像素读取正常则返回 0，否则返回 1
 */
int show_pixel_info(BMP_INFO_HEADER* info_header, FILE* fp, int32_t x,
                    int32_t y);
