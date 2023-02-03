// testJpegLib.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include "rxregsvc.h"
#include "tchar.h"
#include <string>
#include "atlstr.h"

#include "jpeglib.h"
#include "jconfig.h"
#include "jmorecfg.h"

//#pragma comment(lib,"D:/dev/podofo0.9.8/jpegsr6b/jpeg-6b/libjpeg.lib")
#pragma comment(lib,"D:/dev/podofo0.9.8/jpegsr9e/jpeg-9e/Debug/x64/jpegd.lib")
//#pragma comment(lib,"legacy_stdio_definitions.lib")
//extern "C" {FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

int main()
{
	const wchar_t* jpgFileNameW = _T("123.jpg");
	const char* jpgFileName = "123.jpg";
	FILE* infile;

	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jerr;
	JSAMPARRAY buffer;
	int row_stride;

	//绑定标准错误结构;
	cInfo.err = jpeg_std_error(&jerr);
	//初始化jpeg对象;
	jpeg_create_decompress(&cInfo);

	/* Specify data source for decompression */
	//指定图像文件;
	errno_t et = fopen_s(&infile, jpgFileName, "rb");
	if (et != 0)
	{
		printf("cant't open %s \n", jpgFileName);
		return et;
	}
	jpeg_stdio_src(&cInfo, infile);

	/* Read file header, set default decompression parameters */
	(void)jpeg_read_header(&cInfo, TRUE);

	//设定解压参数
	cInfo.scale_num = 1;
	cInfo.scale_denom = 1;

	//start decompressor(开始解压图像);
	(void)jpeg_start_decompress(&cInfo);

	//
	row_stride = cInfo.output_width * cInfo.output_components;
	buffer = (*cInfo.mem->alloc_sarray)((j_common_ptr)&cInfo, JPOOL_IMAGE, row_stride, 1);

	//读取数据;
	int grayDegree = 0;
	int firstNum, secondNum, thirdNum,j = 0;
	while(cInfo.output_scanline < cInfo.output_height)
	{
		(void)jpeg_read_scanlines(&cInfo,buffer,1);
		//output_scanline是从1开始，所以需要减1;
		int line = cInfo.output_scanline - 1;
		for(int i = 0; i < cInfo.output_width; i++)
		{
			firstNum = buffer[0][i * 3];
			secondNum = buffer[0][i * 3 + 1];
			thirdNum = buffer[0][i * 3 + 2];
			grayDegree = floor(0.299 * firstNum + 0.587 * secondNum + 0.114 * secondNum);
			std::cout << firstNum << "........." << secondNum << "........." << thirdNum ;
			std::cout << "........." << grayDegree;
			std::cout << "     " << j++ << std::endl;
		}
	}

	//输出jpeg尺寸
	std::cout << "width = " << cInfo.output_width << "    height = " << cInfo.output_height << std::endl;
    std::cout << "Hello World!\n";

	//结束解压操作
	(void)jpeg_finish_decompress(&cInfo);
	//释放资源
	jpeg_destroy_decompress(&cInfo);
	fclose(infile);

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
