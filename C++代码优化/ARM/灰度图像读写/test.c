#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <png.h>
#include "util.h"
#include "util.c"

//8-bit 灰度PNG图片读取与写入
int main()
{

	size_t gx, gy;		//Var für Bild 图像尺寸  size_t = unsigned char
	png_bytep gbild_;	//图像数据首地址 unsigned char *
	readImageData("ggray.png",&gbild_,&gx,&gy);	//Bild lesen 读图

	unsigned char **gbild = malloc(sizeof(char *) * gy);	//定义二维数据
	for(int i = 0 ; i < gy ; i++)
	{
		gbild[i] = gbild_ + i * gx; 
	}

	//二维数组的使用
	unsigned char *gbild_out_ = malloc(sizeof(char) * (gx * gy + 16)); //a[5 + 列数 * 6]
	unsigned char **gbild_out = malloc(sizeof(char * ) * gy);
	for(int i = 0 ; i < gy ; i++)
	{
		gbild_out[i] = gbild_out_ + i * gx;		//gbild_out[1][3]
	}


	uint8x16_t regin, mitt;	//定义NEON向量
	for(int i = 0 ; i < gy ; i++)
	{
		for(int ii = 0 ; ii < gx ; ii += 16)
		{
			regin = vld1q_u8(&gbild[i][ii]);	//数据读取

			mitt = vdupq_n_u8(50);				//duplicates a scalar into every element of the destination vector.
			regin = vqsubq_u8(regin, mitt); //subtracts the elements in the second vector from the corresponding elements in the first vector. If any of the results overflow, they are saturated.
			
			vst1q_u8(&gbild_out[i][ii], regin);	//数据回写
		}
	}
	writeImageData("out.png", gbild_out_, gx, gy, 8);	//制作PNG图
}	
//struct timespec start, end;							//Var für Zeitmessung
//clock_gettime(CLOCK_REALTIME, &start);				//Zeitmessung - Start
//clock_gettime(CLOCK_REALTIME, &end);					//Zeitmessung - End
//float delta_ms = (end.tv_sec - start.tv_sec) * 1E3+ (float) (end.tv_nsec - start.tv_nsec) / 1E6;
//printf("\ndiff_time=%fms\n", delta_ms);

/*
mitt = vdupq_n_u8(50);
regin = vqsubq_u8(regin, mitt);
*/