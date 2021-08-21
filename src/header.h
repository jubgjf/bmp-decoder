#pragma once

#include "def.h"
#include <stdint.h>
#include <stdio.h>

/**
 * @brief BMP 文件头
 */
typedef struct BMP_FILE_HEADER {
    uint16_t type;      // 文件类型：BM/BA/CI/CP/IC/PT
    uint32_t size;      // BMP 文件大小，单位为字节
    uint16_t reserved1; // 保留，实际值因创建程序而异
    uint16_t reserved2; // 保留，实际值因创建程序而异
    uint32_t offset;    // 从文件头到实际图像数据之间的偏移量
} BMP_FILE_HEADER;

/**
 * @brief 读取 BMP 文件头
 *
 * @param fp BMP 文件指针
 * @return BMP_FILE_HEADER* 返回读取到的 BMP 文件头结构体指针，
 *                          若读取失败，则返回 NULL
 */
BMP_FILE_HEADER* read_bmp_file_header(FILE* fp);

/**
 * @brief 输出 BMP 文件头中的信息
 *
 * @param file_header BMP 文件头结构体
 * @return int 若无错误则返回 0，否则返回 1
 */
int show_bmp_file_header(BMP_FILE_HEADER* file_header);

/**
 * @brief 压缩方式
 */
typedef enum COMPRESSION {
    BI_RGB            = 0, // 不压缩
    BI_RLE8           = 1,
    BI_RLE4           = 2,
    BI_BITFIELDS      = 3,
    BI_JPEG           = 4,
    BI_PNG            = 5,
    BI_ALPHABITFIELDS = 6,
    BI_CMYK           = 11,
    BI_CMYKRLE8       = 12,
    BI_CMYKRLE4       = 13
} COMPRESSION;

/**
 * @brief BMP 信息头
 */
typedef struct BMP_INFO_HEADER {
    uint32_t size;             // 信息头大小，单位为字节
    int32_t  width;            // 图像宽度，单位为像素
    int32_t  height;           // 图像高度，单位为像素；
                               // 若为正数，则图象从左下角开始；
                               // 若为负数，则图象从左上角开始；
    uint16_t planes;           // 颜色平面数，必须为 1
    uint16_t bit_count;        // 色深（每个像素所占位数）；
                               // 取值一般有：1/4/8/16/24/32
    COMPRESSION compression;   // 图像压缩方式
    uint32_t    image_size;    // 原始图像大小，单位为字节；
                               // 当 compression == 0 时，可以设置为 0
    int32_t  resolution_x;     // 水平分辨率，单位为像素/米
    int32_t  resolution_y;     // 垂直分辨率，单位为像素/米
    uint32_t colors;           // 调色板的颜色数；
                               // 为 0 时，颜色数为默认的 2^色深 个
    uint32_t colors_important; // 重要的颜色数；
                               // 为 0 时，表示都重要
} BMP_INFO_HEADER;

/**
 * @brief 读取 BMP 信息头
 *
 * @param fp BMP 文件指针
 * @return BMP_INFO_HEADER* 返回读取到的 BMP 信息头结构体指针，
 *                          若读取失败，则返回 NULL
 */
BMP_INFO_HEADER* read_bmp_info_header(FILE* fp);

/**
 * @brief 输出 BMP 信息头中的信息
 *
 * @param file_header BMP 信息头结构体
 * @return int 若无错误则返回 0，
 *             若信息头大小不匹配则返回 1，
 *             若压缩方式不识别则返回 2
 */
int show_bmp_info_header(BMP_INFO_HEADER* info_header);

/**
 * @brief 调色板
 */
struct COLOR_TABLE {
    byte_t blue;     // 蓝色强度
    byte_t green;    // 绿色强度
    byte_t red;      // 红色强度
    byte_t reserved; // 保留
};
