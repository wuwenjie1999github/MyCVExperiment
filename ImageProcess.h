#pragma once
#include <atlimage.h>
#include <opencv.hpp>
#pragma once
#define NOISE 0.2
#define PI 3.14159265358979
struct ThreadParam
{
	CImage * src;
	int startIndex;
	int endIndex;
	int maxSpan;//为模板中心到边缘的距离
};

static bool GetValue(int p[], int size, int &value);

class ImageProcess
{
public:
	ImageProcess();
	static UINT medianFilter(LPVOID  param);
	static UINT addNoise(LPVOID param);
	static UINT scale(CImage* src, float scaleXNum, float scaleYNum);
	static UINT rotate(CImage* src, CImage* des, float angle);
	static void CImage2Mat(CImage* cimage, cv::Mat& mat);
	static void Mat2CImage(cv::Mat& mat, CImage& cimage);
};