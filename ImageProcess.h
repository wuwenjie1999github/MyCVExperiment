#pragma once
#include <atlimage.h>
#pragma once
#define NOISE 0.2
struct ThreadParam
{
	CImage * src;
	int startIndex;
	int endIndex;
	int maxSpan;//Ϊģ�����ĵ���Ե�ľ���
};

static bool GetValue(int p[], int size, int &value);

class ImageProcess
{
public:
	ImageProcess();
	static UINT medianFilter(LPVOID  param);
	static UINT addNoise(LPVOID param);
};