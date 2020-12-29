#include <stdio.h>

#define NONE                "\e[0m"         //清除颜色，即之后的打印为正常输出，之前的不受影响
#define BLACK               "\e[0;30m"      //深黑
#define L_BLACK             "\e[1;30m"      //亮黑，偏灰褐
#define RED                 "\e[0;31m"      //深红，暗红
#define L_RED               "\e[1;31m"      //鲜红
#define GREEN               "\e[0;32m"      //深绿，暗绿
#define L_GREEN             "\e[1;32m"      //鲜绿
#define BROWN               "\e[0;33m"      //深黄，暗黄
#define YELLOW              "\e[1;33m"      //鲜黄
#define BLUE                "\e[0;34m"      //深蓝，暗蓝
#define L_BLUE              "\e[1;34m"      //亮蓝，偏白灰
#define PURPLE              "\e[0;35m"      //深粉，暗粉，偏暗紫
#define L_PURPLE            "\e[1;35m"      //亮粉，偏白灰
#define CYAN                "\e[0;36m"      //暗青色
#define L_CYAN              "\e[1;36m"      //鲜亮青色
#define GRAY                "\e[0;37m"      //灰色
#define WHITE               "\e[1;37m"      //白色，字体粗一点，比正常大，比bold小
#define BOLD                "\e[1m"         //白色，粗体
#define UNDERLINE           "\e[4m"         //下划线，白色，正常大小
#define BLINK               "\e[5m"         //闪烁，白色，正常大小
#define REVERSE             "\e[7m"         //反转，即字体背景为白色，字体为黑色
#define HIDE                "\e[8m"         //隐藏
#define CLEAR               "\e[2J"         //清除
#define CLRLINE             "\r\e[K"        //清除行

int print_test(void)
{
	printf("This is a character control test!\n");
	printf("[%2u]" CLEAR "CLEAR\n" NONE, __LINE__);
	printf("[%2u]" BLACK "BLACK " L_BLACK "L_BLACK\n" NONE, __LINE__);
	printf("[%2u]" RED "RED " L_RED "L_RED\n" NONE, __LINE__);
	printf("[%2u]" GREEN "GREEN " L_GREEN "L_GREEN\n" NONE, __LINE__);
	printf("[%2u]" BROWN "BROWN " YELLOW "YELLOW\n" NONE, __LINE__);
	printf("[%2u]" BLUE "BLUE " L_BLUE "L_BLUE\n" NONE, __LINE__);
	printf("[%2u]" PURPLE "PURPLE " L_PURPLE "L_PURPLE\n" NONE, __LINE__);
	printf("[%2u]" CYAN "CYAN " L_CYAN "L_CYAN\n" NONE, __LINE__);
	printf("[%2u]" GRAY "GRAY " WHITE "WHITE\n" NONE, __LINE__);
	printf("[%2u]" BOLD "BOLD\n" NONE, __LINE__);
	printf("[%2u]" UNDERLINE "UNDERLINE\n" NONE, __LINE__);
	printf("[%2u]" BLINK "BLINK\n" NONE, __LINE__);
	printf("[%2u]" REVERSE "REVERSE\n" NONE, __LINE__);
	printf("[%2u]" HIDE "HIDE\n" NONE, __LINE__);

	printf(L_RED "L_RED\n");

	return 0;

}

int main()
{
	printf("\033[1;33;41mtestffff\033[0m\n");
	printf("\033[32mtestffff\033[0m\n");
	print_test();
	return 0;
}