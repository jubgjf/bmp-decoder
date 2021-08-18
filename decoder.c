#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // 检验参数数量
    if (argc <= 1) {
        printf("argc = %d, arguments not enough!\n", argc);
        return 1;
    } else if (argc >= 3) {
        printf("argc = %d, arguments too many!\n", argc);
        return 1;
    }

    // 查找参数指定的 BMP 文件
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("File not found!\n");
        return 1;
    }

    // 读取 BMP 文件头信息
    BMP_FILE_HEADER* file_header = malloc(sizeof(BMP_FILE_HEADER));
    fread(&(file_header->type), sizeof(file_header->type), 1, fp);
    fread(&(file_header->size), sizeof(file_header->size), 1, fp);
    fread(&(file_header->reserved1), sizeof(file_header->reserved1), 1, fp);
    fread(&(file_header->reserved2), sizeof(file_header->reserved2), 1, fp);
    fread(&(file_header->offset), sizeof(file_header->offset), 1, fp);

    // 读取 BMP 文件类型
    char type_high = (char)file_header->type;
    char type_low  = (char)(file_header->type >> 8);
    if (type_high == 'B' && type_low == 'M') { // Windows 3.1x, 95, NT, ... etc
        printf("Type: BM (BMP for Windows 3.1x, 95, NT, ... etc)\n");
    } else {
        printf("Not a BMP file, or this BMP type not supported!\n");
        if (type_high == 'B' && type_low == 'A' || // OS/2 struct Bitmap Array
            type_high == 'C' && type_low == 'I' || // OS/2 struct Color Icon
            type_high == 'C' && type_low == 'P' || // OS/2 const Color Pointer
            type_high == 'I' && type_low == 'C' || // OS/2 struct Icon
            type_high == 'P' && type_low == 'T') { // OS/2 Pointer
            printf("Possible BMP type: %c%c\n", type_high, type_low);
        }
        return 1;
    }

    // 读取文件大小
    printf("size: %d bytes\n", file_header->size);

    return 0;
}
