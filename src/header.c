#include "header.h"

BMP_FILE_HEADER* read_bmp_file_header(FILE* fp) {
    BMP_FILE_HEADER* file_header = malloc(sizeof(BMP_FILE_HEADER));

    fread(&(file_header->type), sizeof(file_header->type), 1, fp);
    fread(&(file_header->size), sizeof(file_header->size), 1, fp);
    fread(&(file_header->reserved1), sizeof(file_header->reserved1), 1, fp);
    fread(&(file_header->reserved2), sizeof(file_header->reserved2), 1, fp);
    fread(&(file_header->offset), sizeof(file_header->offset), 1, fp);

    return file_header;
}

int show_bmp_file_header(BMP_FILE_HEADER* file_header) {
    // 读取 BMP 文件类型
    char type_high = (char)file_header->type;
    char type_low  = (char)(file_header->type >> 8);
    if (type_high == 'B' && type_low == 'M') { // Windows 3.1x, 95, NT, ... etc
        printf("[File type]: BM (BMP for Windows 3.1x, 95, NT, ... etc)\n");
    } else {
        printf("Not a BMP file, or this BMP type not supported!\n");
        if ((type_high == 'B' && type_low == 'A') || // OS/2 struct Bitmap Array
            (type_high == 'C' && type_low == 'I') || // OS/2 struct Color Icon
            (type_high == 'C' && type_low == 'P') || // OS/2 const Color Pointer
            (type_high == 'I' && type_low == 'C') || // OS/2 struct Icon
            (type_high == 'P' && type_low == 'T')) { // OS/2 Pointer
            printf("Possible BMP type: %c%c\n", type_high, type_low);
        }
        return 1;
    }

    // 读取文件大小
    printf("[File size(byte)]: %u\n", file_header->size);

    return 0;
}

BMP_INFO_HEADER* read_bmp_info_header(FILE* fp) {
    BMP_INFO_HEADER* info_header = malloc(sizeof(BMP_INFO_HEADER));

    fread(&(info_header->size), sizeof(info_header->size), 1, fp);
    fread(&(info_header->width), sizeof(info_header->width), 1, fp);
    fread(&(info_header->height), sizeof(info_header->height), 1, fp);
    fread(&(info_header->planes), sizeof(info_header->planes), 1, fp);
    fread(&(info_header->bit_count), sizeof(info_header->bit_count), 1, fp);
    fread(&(info_header->compression), sizeof(info_header->compression), 1, fp);
    fread(&(info_header->image_size), sizeof(info_header->image_size), 1, fp);
    fread(&(info_header->resolution_x), sizeof(info_header->resolution_x), 1,
          fp);
    fread(&(info_header->resolution_y), sizeof(info_header->resolution_y), 1,
          fp);
    fread(&(info_header->colors), sizeof(info_header->colors), 1, fp);
    fread(&(info_header->colors_important),
          sizeof(info_header->colors_important), 1, fp);

    return info_header;
}

int show_bmp_info_header(BMP_INFO_HEADER* info_header) {
    // 验证信息头大小
    if (info_header->size != sizeof(BMP_INFO_HEADER)) {
        printf("Wrong info header size!\n");
        printf("Current info header size = %u\n", info_header->size);
        return 1;
    }

    // 图像宽度和高度
    printf("[Image size(px)]: %dx%d\n", info_header->width,
           info_header->height);
    if (info_header->height < 0) {
        // '\u2169': top left arrow: ↖
        printf("[Start point]: top left %s\n", "\u2169");
    } else if (info_header->height > 0) {
        // '\u2199': bottom left arrow: ↙
        printf("[Start point]: bottom left %s\n", "\u2199");
    }

    // 色深
    printf("[Color depth]: %u\n", info_header->bit_count);

    // 压缩方式
    char compression[40] = {0};
    switch (info_header->compression) {
    case BI_RGB:
        strcpy(compression, "BI_RGB (no compression)");
        break;
    case BI_RLE8:
        strcpy(compression, "BI_RLE8");
        break;
    case BI_RLE4:
        strcpy(compression, "BI_RLE4");
        break;
    case BI_BITFIELDS:
        strcpy(compression, "BI_BITFIELDS");
        break;
    case BI_JPEG:
        strcpy(compression, "BI_JPEG");
        break;
    case BI_PNG:
        strcpy(compression, "BI_PNG");
        break;
    case BI_ALPHABITFIELDS:
        strcpy(compression, "BI_ALPHABITFIELDS");
        break;
    case BI_CMYK:
        strcpy(compression, "BI_CMYK");
        break;
    case BI_CMYKRLE8:
        strcpy(compression, "BI_CMYKRLE8");
        break;
    case BI_CMYKRLE4:
        strcpy(compression, "BI_CMYKRLE4");
        break;
    default:
        printf("Compression method not supported!\n");
        return 2;
    }
    printf("[Compression method]: %s\n", compression);

    // 水平和垂直分辨率
    printf("[Resolution(px/m)]: %dx%d\n", info_header->resolution_x,
           info_header->resolution_y);

    // 调色板颜色数
    if (info_header->colors == 0) {
        printf("[Colors]: 2^%u\n", info_header->bit_count);
    } else {
        printf("[Colors]: %u\n", info_header->colors);
    }

    return 0;
}
