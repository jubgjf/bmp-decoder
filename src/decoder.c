#include "header.h"
#include "pixel.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 检验主函数参数是否合法；
 *
 *        要求主函数只能有两个参数或四个参数，
 *        第一个参数是可执行文件路径（默认传入，不做检验），
 *        第二个参数是 BMP 文件路径，检验是否存在此文件；
 *        第三个和第四个参数是选择的像素的 x 轴和 y 轴坐标，坐标从 0 开始计数；
 *
 *        若参数数量符合要求，则返回 0；否则返回 1；
 *        若在参数数量符合要求的前提下，坐标出现负数，则返回 2；
 *        若在参数数量符合要求的前提下，找不到 BMP 文件，则返回 3；
 *
 *        若一切正常，则并将找到的 BMP 文件指针赋值给 fp，
 *        否则 fp 赋值为 NULL
 *
 * @param argc 参数个数
 * @param argv 参数列表
 * @param fpp  成功找到文件时的文件指针
 * @return int 返回参数合法性
 */
int check_arg_legal(int argc, char* argv[], FILE** fpp) {
    if (argc != 2 && argc != 4) {
        return 1;
    }

    // 查找参数指定的 BMP 文件
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        free(fp);
        return 3;
    }
    *fpp = fp;

    // 检验坐标是否有负数
    if (argc == 4) {
        if (atoi(argv[2]) < 0 || atoi(argv[3]) < 0) {
            free(fp);
            *fpp = NULL;
            return 2;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    FILE* fp = NULL;

    // 检验参数
    switch (check_arg_legal(argc, argv, &fp)) {
    case 0:
        if (!fp) {
            printf("Unexpected error\n");
            return 1;
        }

        // BMP 文件头
        BMP_FILE_HEADER* file_header = read_bmp_file_header(fp);
        // BMP 信息头
        BMP_INFO_HEADER* info_header = read_bmp_info_header(fp);

        if (argc == 2) {
            if (show_bmp_file_header(file_header) ||
                show_bmp_info_header(info_header)) {
                free(file_header);
                free(info_header);
                return 1;
            }

            // TODO 暂不支持非 24 位位图
            if (info_header->bit_count != 24) {
                printf("Color depth not supported yet!\n");
                free(file_header);
                free(info_header);
                return 1;
            }

            // TODO 暂不支持调色板
            if (info_header->colors) {
                printf("Color table not supported yet!\n");
                free(file_header);
                free(info_header);
                return 1;
            }
        } else if (argc == 4) {
            int32_t x = atoi(argv[2]);
            int32_t y = atoi(argv[3]);

            if (show_pixel_info(info_header, fp, x, y)) {
                printf("Please check the value of x and y!\n");
                free(file_header);
                free(info_header);
                return 1;
            }
        }

        break;
    case 1:
        printf("argc = %d, arguments not enough or too many!\n", argc);
        return 1;
    case 2:
        printf("Illegal coordination!\n");
        return 1;
    case 3:
        printf("File not found!\n");
        return 1;
    default:
        printf("Unexpected error\n");
        return 1;
    }

    return 0;
}
