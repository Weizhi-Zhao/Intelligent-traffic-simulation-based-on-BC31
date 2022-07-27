#ifndef __ZWZGRAPHICS__
#define __ZWZGRAPHICS__

#define min(x, y) x < y ? x : y
#define max(x, y) x > y ? x : y

//单独设置一个像素点
void putPixel(long x, long y, int color);

//画水平线，用memset函数，效率较高
void putHorizontalLine(int x1, int x2, int y, int color);

//画正放的长方形
void putBar(int left, int top, int width, int height, int color);

//画三角形
void putTriangle(int x1, int y1, int x2, int y2,  int x3, int y3, int color);

//画凸四边形
void putParallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color);

//用DDA算法画直线
void lineDDA(int x0, int y0, int xEnd, int yEnd, int color);

//把缓冲用memcpy函数复制进显存里
void showFrameBuffer();

//把缓冲全部设为黑色
void clearFrameBuffer();

//从4个源文件里找到缓冲数组
extern char a1[38400];
extern char a2[38400];
extern char a3[38400];
extern char a4[38400];

#endif