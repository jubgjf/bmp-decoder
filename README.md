# bmp-decoder

简易 BMP 图像文件解码器

## 编译

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## 执行

### 显示文件详细信息

```shell
$ ./decoder <your BMP file>
```

### 显示 (x, y) 坐标颜色

> 像素坐标轴以图像左上角为起点，坐标从 0 开始计数

```shell
$ ./decoder <your BMP file> x y
```
