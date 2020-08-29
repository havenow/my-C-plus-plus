#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <math.h>
//---------------------------------------------
//
//
//使用NEON的加法,减法,乘法
//
//
//---------------------------------------------
int main()
{
	//定义a, b, c, d, e, f, g
	uint8_t *a = malloc(sizeof(uint8_t) * 256);
	uint8_t *b = malloc(sizeof(uint8_t) * 256);
	uint8_t *c = malloc(sizeof(uint8_t) * 256);
	uint8_t *d = malloc(sizeof(uint8_t) * 256);
	uint8_t *e = malloc(sizeof(uint8_t) * 256);
	uint8_t *f = malloc(sizeof(uint8_t) * 256);
	uint8_t *g = malloc(sizeof(uint8_t) * 256);

	//赋值
	for(int i = 0 ; i < 256 ; i++)
	{
		a[i] = i;
		b[i] = i + 1;
	}


//-------------------------------------------------------------------------------------------
//测试vadd
	uint8x8_t rega_8, regb_8, regc_8, regd_8, rege_8, regf_8, regg_8, regh_8;	//定义a, b, c, d, e, f, g, h 8个寄存器
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regb_8 = vld1_u8(&b[i]);	//加载b
		regc_8 = vadd_u8(rega_8, regb_8);	//计算c = a + b
		vst1_u8(&c[i], regc_8);		//回写c
	}
//-------------------------------------------------------------------------------------------
//测试vaddl
	uint16_t *d_16 = malloc(sizeof(uint32_t) * 256);
	uint16x8_t regd_16;
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regb_8 = vld1_u8(&b[i]);	//加载b
		regd_16 = vaddl_u8(rega_8, regb_8);	//计算d = a + b
		vst1q_u16(&d_16[i], regd_16);		//回写d,注意在回写的时候,d_16是128位寄存器,应用带q的指令回写
	}
//-------------------------------------------------------------------------------------------
//测试vaddw
	uint16_t *b_16 = malloc(sizeof(uint32_t) * 256);
	uint16x8_t regb_16;
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regd_16 = vld1q_u16(&d_16[i]);	//加载d
		regb_16 = vaddw_u8(regd_16, rega_8);	//计算b = d + a
		vst1q_u16(&b_16[i], regb_16);		//回写b,注意在回写的时候,d_16是128位寄存器,应用带q的指令回写
	}
//-------------------------------------------------------------------------------------------
//测试vqadd
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regb_8 = vld1_u8(&b[i]);	//加载b
		regd_8 = vqadd_u8(rega_8, regb_8);	//计算d = a + b
		vst1_u8(&d[i], regd_8);		//回写d
	}
//-------------------------------------------------------------------------------------------
//测试vsub
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regb_8 = vld1_u8(&b[i]);	//加载b	
		rege_8 = vsub_u8(regb_8, rega_8);	//计算e = b - a
		regf_8 = vsub_u8(rega_8, regb_8);	//计算f = a - b
		vst1_u8(&e[i], rege_8);		//回写e
		vst1_u8(&f[i], regf_8);		//回写f
	}
//-------------------------------------------------------------------------------------------
//测试vqsub
	for(int i = 0 ; i < 256 ; i += 8)
	{
		rega_8 = vld1_u8(&a[i]);	//加载a
		regb_8 = vld1_u8(&b[i]);	//加载b	
		regg_8 = vqsub_u8(rega_8, regb_8);	//计算g = a - b
		vst1_u8(&g[i], regg_8);		//回写g
	}
//-------------------------------------------------------------------------------------------
//测试vmulq_n
	uint32_t *a_32 = malloc(sizeof(uint32_t) * 256);
	uint32_t *b_32 = malloc(sizeof(uint32_t) * 256);
	for(int i = 0 ; i < 256 ; i++)
	{
		a_32[i] = i;
	}

	uint32x4_t rega_32, regb_32;
	for(int i = 0 ; i < 256 ; i += 4)
	{
		rega_32 = vld1q_u32(&a_32[i]);	//加载a
		regb_32 = vmulq_n_u32(rega_32, 3);	//计算b_32 = a_32 * 3
		vst1q_u32(&b_32[i], regb_32);		//回写b_32
	}
//-------------------------------------------------------------------------------------------
//debug
/*
	//查看a的值
	printf("a =\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",a[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看b的值
	printf("b =\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",b[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看c的值
	printf("使用vadd计算 c = a + b 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",c[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看d的值
	printf("使用vqadd计算 d = a + b 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",d[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看d_16的值
	printf("使用vaddl计算 d = a + b 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",d_16[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看b_16的值
	printf("使用vaddw计算 b = d + a 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",b_16[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看e的值
	printf("使用vsub计算 e = b -a 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",e[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看f的值
	printf("使用vsub计算 f = a - b 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",f[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看g的值
	printf("使用vqsub计算 g = a - b 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",g[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
/*
	//查看b_32的值
	printf("使用vmulq_n计算 b_32 = a_32 * 3 结果\n");
	for(int i = 0 ; i < 16 ; i++)
	{
		for(int ii = 0 ; ii < 16 ; ii++)
		{
			printf("%d 	",b_32[ii + 16 * i] );
		}
		printf("\n");
	}
	printf("\n");
*/
}