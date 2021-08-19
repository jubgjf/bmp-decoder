#include "header.h"

/**
 * @brief 检验主函数参数是否合法；
 *
 *        要求主函数只能有两个参数，
 *        第一个参数是可执行文件路径（默认传入，不做检验），
 *        第二个参数是 BMP 文件路径，检验是否存在此文件；
 *
 *        若参数符合要求，则返回 0；
 *        若参数数量太少，则返回 1；
 *        若参数数量太多，则返回 2；
 *        若 BMP 文件找不到，则返回 3；
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
    if (argc <= 1) {
        return 1;
    } else if (argc >= 3) {
        return 2;
    }

    // 查找参数指定的 BMP 文件
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        fpp = NULL;
        return 3;
    }
    *fpp = fp;

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
        break;
    case 1:
        printf("argc = %d, arguments not enough!\n", argc);
        return 1;
    case 2:
        printf("argc = %d, arguments too many!\n", argc);
        return 1;
    case 3:
        printf("File not found!\n");
        return 1;
    default:
        printf("Unexpected error\n");
        return 1;
    }

    // BMP 文件头
    BMP_FILE_HEADER* file_header = read_bmp_file_header(fp);
    show_bmp_file_header(file_header);

    // BMP 信息头
    BMP_INFO_HEADER* info_header = read_bmp_info_header(fp);
    show_bmp_info_header(info_header);

    return 0;
}
