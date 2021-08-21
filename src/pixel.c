#include "pixel.h"
#include <stdlib.h>

int show_pixel_info(BMP_INFO_HEADER* info_header, FILE* fp, int32_t x,
                    int32_t y) {
    // 检验坐标是否超出范围
    if (x < 0 || x > info_header->width) {
        return 1;
    }
    if (info_header->height < 0) {
        if (y < 0 || y > -info_header->height) {
            return 1;
        }
    } else if (info_header->height > 0) {
        if (y < 0 || y > info_header->height) {
            return 1;
        }
    }

    // 经过 4 字节对齐后，一行像素所占的字节
    int32_t row_bytes =
        (info_header->width * info_header->bit_count + 31) / 32 * 4;

    // 寻址像素
    long offset = 0;
    if (info_header->height < 0) { // 图像从左上角开始
        offset = row_bytes * y + info_header->bit_count / 8 * x;
    } else { // 图像从左下角开始
        offset = row_bytes * (info_header->height - y - 1) +
                 info_header->bit_count / 8 * x;
    }
    fseek(fp, 14 + info_header->size + offset, SEEK_SET);

    // 读取像素
    PIXEL_24* pixel = malloc(sizeof(PIXEL_24));
    fread(pixel, sizeof(PIXEL_24), 1, fp);

    // 输出像素信息
    printf("[R, G, B] = [%u, %u, %u]\n", pixel->red, pixel->green, pixel->blue);

    return 0;
}
