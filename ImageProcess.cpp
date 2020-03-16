#include "pch.h"
#include "ImageProcess.h"
//#include <vector>
//#include <algorithm>
#include <cmath>
#include "stdafx.cpp"

using namespace cv;

static bool GetValue(int p[], int size, int &value)
{
	//数组中间的值
	int zxy = p[(size - 1) / 2];
	//用于记录原数组的下标
	int *a = new int[size];
	int index = 0;
	for (int i = 0; i<size; ++i)
		a[index++] = i;

	for (int i = 0; i<size - 1; i++)
		for (int j = i + 1; j<size; j++)
			if (p[i]>p[j]) {
				int tempA = a[i];
				a[i] = a[j];
				a[j] = tempA;
				int temp = p[i];
				p[i] = p[j];
				p[j] = temp;

			}
	int zmax = p[size - 1];
	int zmin = p[0];
	int zmed = p[(size - 1) / 2];

	if (zmax>zmed&&zmin<zmed) {
		//if (zxy>zmin&&zxy<zmax)
		//	value = (size - 1) / 2;
		//else
			value = a[(size - 1) / 2];
		delete[]a;
		return true;
	}
	else {
		delete[]a;
		return false;
	}

}


ImageProcess::ImageProcess()
{
}

UINT ImageProcess::medianFilter(LPVOID  p)
{
	ThreadParam* param = (ThreadParam*)p;

	int maxWidth = param->src->GetWidth();
	int maxHeight = param->src->GetHeight();
	int startIndex = param->startIndex;
	int endIndex = param->endIndex;
	int maxSpan = param->maxSpan;
	int maxLength = (maxSpan * 2 + 1) * (maxSpan * 2 + 1);

	byte* pRealData = (byte*)param->src->GetBits();
	int pit = param->src->GetPitch();
	int bitCount = param->src->GetBPP() / 8;

	int *pixel = new int[maxLength];//存储每个像素点的灰度
	int *pixelR = new int[maxLength];
	int *pixelB = new int[maxLength];
	int *pixelG = new int[maxLength];
	int index = 0;
	for (int i = startIndex; i <= endIndex; ++i)
	{
		int Sxy = 1;
		int med = 0;
		int state = 0;
		int x = i % maxWidth;
		int y = i / maxWidth;
		while (Sxy <= maxSpan)
		{
			index = 0;
			for (int tmpY = y - Sxy; tmpY <= y + Sxy && tmpY <maxHeight; tmpY++)
			{
				if (tmpY < 0) continue;
				for (int tmpX = x - Sxy; tmpX <= x + Sxy && tmpX<maxWidth; tmpX++)
				{
					if (tmpX < 0) continue;
					if (bitCount == 1)
					{
						pixel[index] = *(pRealData + pit*(tmpY)+(tmpX)*bitCount);
						pixelR[index++] = pixel[index];

					}
					else
					{
						pixelR[index] = *(pRealData + pit*(tmpY)+(tmpX)*bitCount + 2);
						pixelG[index] = *(pRealData + pit*(tmpY)+(tmpX)*bitCount + 1);
						pixelB[index] = *(pRealData + pit*(tmpY)+(tmpX)*bitCount);
						pixel[index++] = int(pixelB[index] * 0.299 + 0.587*pixelG[index] + pixelR[index] * 0.144);

					}
				}

			}
			if (index <= 0)
				break;
			if ((state = GetValue(pixel, index, med)) == 1)
				break;

			Sxy++;
		};

		if (state)
		{
			if (bitCount == 1)
			{
				*(pRealData + pit*y + x*bitCount) = pixelR[med];

			}
			else
			{
				*(pRealData + pit*y + x*bitCount + 2) = pixelR[med];
				*(pRealData + pit*y + x*bitCount + 1) = pixelG[med];
				*(pRealData + pit*y + x*bitCount) = pixelB[med];

			}
		}

	}



	delete[]pixel;
	delete[]pixelR;
	delete[]pixelG;
	delete[]pixelB;

	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_MEDIAN_FILTER, 1, NULL);
	return 0;
}

UINT ImageProcess::addNoise(LPVOID  p)
{
	ThreadParam* param = (ThreadParam*)p;
	int maxWidth = param->src->GetWidth();
	int maxHeight = param->src->GetHeight();

	int startIndex = param->startIndex;
	int endIndex = param->endIndex;
	byte* pRealData = (byte*)param->src->GetBits();
	int bitCount = param->src->GetBPP() / 8;
	int pit = param->src->GetPitch();

	for (int i = startIndex; i <= endIndex; ++i)
	{
		int x = i % maxWidth;
		int y = i / maxWidth;
		if ((rand() % 1000) * 0.001 < NOISE)
		{
			int value = 0;
			if (rand() % 1000 < 500)
			{
				value = 0;
			}
			else
			{
				value = 255;
			}
			if (bitCount == 1)
			{
				*(pRealData + pit * y + x * bitCount) = value;
			}
			else
			{
				*(pRealData + pit * y + x * bitCount) = value;
				*(pRealData + pit * y + x * bitCount + 1) = value;
				*(pRealData + pit * y + x * bitCount + 2) = value;
			}
		}
	}
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_NOISE, 1, NULL);
	return 0;
}

void ImageProcess::CImage2Mat(CImage* cimage, Mat& mat)
{
	if (true == cimage->IsNull())
	{
		return;
	}
	int nChannels = cimage->GetBPP() / 8;
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = cimage->GetWidth();
	int nHeight = cimage->GetHeight();
	//重建mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if (3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}
	//拷贝数据
	uchar* pucRow;//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage->GetBits();//指向数据区的指针
	int nStep = cimage->GetPitch();//每行的字节数,注意这个返回值有正有负
	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				pucRow[nCol] = *(pucImage + nRow * nStep + nCol);
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					pucRow[nCol * 3 + nCha] = *(pucImage + nRow * nStep + nCol * 3 + nCha);
				}
			}
		}
	}
}

void ImageProcess::Mat2CImage(cv::Mat& mat, CImage& cimage)
{
	if (0 == mat.total())
	{
		return;
	}
	int nChannels = mat.channels();
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = mat.cols;
	int nHeight = mat.rows;
	//重建cimage
	cimage.Destroy();
	cimage.Create(nWidth, nHeight, 8 * nChannels);
	//拷贝数据
	uchar* pucRow;//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();//指向数据区的指针
	int nStep = cimage.GetPitch();//每行的字节数,注意这个返回值有正有负
	if (1 == nChannels)//对于单通道的图像需要初始化调色板
	{
		RGBQUAD* rgbquadColorTable;
		int nMaxColors = 256;
		rgbquadColorTable = new RGBQUAD[nMaxColors];
		cimage.GetColorTable(0, nMaxColors, rgbquadColorTable);
		for (int nColor = 0; nColor < nMaxColors; nColor++)
		{
			rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;
			rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;
			rgbquadColorTable[nColor].rgbRed = (uchar)nColor;
		}
		cimage.SetColorTable(0, nMaxColors, rgbquadColorTable);
		delete[]rgbquadColorTable;
	}
	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				*(pucImage + nRow * nStep + nCol) = pucRow[nCol];
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					*(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];
				}
			}
		}
	}
}

float BiCubicPoly(float x)
{
	float a = -0.5;
	if (abs(x) <= 1)
		return (a + 2) * pow(abs(x), 3) - (a + 3) * pow(abs(x), 2) + 1;
	else if (abs(x) < 2)
		return a * pow(abs(x), 3) - 5 * a * pow(abs(x), 2) + 8 * a * abs(x) - 4 * a;
	else
		return 0;
}

void scaleBicubicInter(Mat& src, Mat& dst, float transMat[3][3])
{
	CV_Assert(src.data);
	CV_Assert(src.depth() != sizeof(uchar));

	// Calculate margin point of dst image
	float x = src.cols * 1.0f;
	float y = 0.0f;
	float u1 = x * transMat[0][0] + y * transMat[0][1];
	float v1 = x * transMat[1][0] + y * transMat[1][1];
	x = src.cols * 1.0f;
	y = src.rows * 1.0f;
	float u2 = x * transMat[0][0] + y * transMat[0][1];
	float v2 = x * transMat[1][0] + y * transMat[1][1];
	x = 0.0f;
	y = src.rows * 1.0f;
	float u3 = x * transMat[0][0] + y * transMat[0][1];
	float v3 = x * transMat[1][0] + y * transMat[1][1];

	float left = min(min(min(0.0f, u1), u2), u3);
	float right = max(max(max(0.0f, u1), u2), u3);
	float top = min(min(min(0.0f, v1), v2), v3);
	float down = max(max(max(0.0f, v1), v2), v3);

	// Create dst image
	dst.create(int(abs(down - top)), int(abs(right - left)), src.type());

	CV_Assert(dst.channels() == src.channels());
	int channels = dst.channels();

	uchar* p;
	uchar* q0;
	uchar* q1;
	uchar* q2;
	uchar* q3;
	for (int i = 0; i < dst.rows; i++) {
		p = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++) {
			/*x = (j + left) / transMat[0][0];
			y = (i + top) / transMat[1][1];*/
			x = (transMat[1][1] * (j + left - transMat[0][2]) - transMat[0][1] * (i + top - transMat[1][2]))
				/ (transMat[0][0] * transMat[1][1] - transMat[0][1] * transMat[1][0]);
			y = (transMat[0][0] * (i + top - transMat[1][2]) - transMat[1][0] * (j + left - transMat[0][2]))
				/ (transMat[0][0] * transMat[1][1] - transMat[0][1] * transMat[1][0]);
			

			int x0 = int(x) - 1;
			int y0 = int(y) - 1;
			int x1 = int(x);
			int y1 = int(y);
			int x2 = int(x) + 1;
			int y2 = int(y) + 1;
			int x3 = int(x) + 2;
			int y3 = int(y) + 2;

			if (x0 >= 0 && x3 < src.cols && y0 >= 0 && y3 < src.rows) {
				q0 = src.ptr<uchar>(y0);
				q1 = src.ptr<uchar>(y1);
				q2 = src.ptr<uchar>(y2);
				q3 = src.ptr<uchar>(y3);

				float dist_x0 = BiCubicPoly(x - x0);
				float dist_x1 = BiCubicPoly(x - x1);
				float dist_x2 = BiCubicPoly(x - x2);
				float dist_x3 = BiCubicPoly(x - x3);
				float dist_y0 = BiCubicPoly(y - y0);
				float dist_y1 = BiCubicPoly(y - y1);
				float dist_y2 = BiCubicPoly(y - y2);
				float dist_y3 = BiCubicPoly(y - y3);

				float dist_x0y0 = dist_x0 * dist_y0;
				float dist_x0y1 = dist_x0 * dist_y1;
				float dist_x0y2 = dist_x0 * dist_y2;
				float dist_x0y3 = dist_x0 * dist_y3;
				float dist_x1y0 = dist_x1 * dist_y0;
				float dist_x1y1 = dist_x1 * dist_y1;
				float dist_x1y2 = dist_x1 * dist_y2;
				float dist_x1y3 = dist_x1 * dist_y3;
				float dist_x2y0 = dist_x2 * dist_y0;
				float dist_x2y1 = dist_x2 * dist_y1;
				float dist_x2y2 = dist_x2 * dist_y2;
				float dist_x2y3 = dist_x2 * dist_y3;
				float dist_x3y0 = dist_x3 * dist_y0;
				float dist_x3y1 = dist_x3 * dist_y1;
				float dist_x3y2 = dist_x3 * dist_y2;
				float dist_x3y3 = dist_x3 * dist_y3;

				if (channels == 3) {
					p[j * 3] = (uchar)(q0[x0 * 3] * dist_x0y0 +
						q1[x0 * 3] * dist_x0y1 +
						q2[x0 * 3] * dist_x0y2 +
						q3[x0 * 3] * dist_x0y3 +
						q0[x1 * 3] * dist_x1y0 +
						q1[x1 * 3] * dist_x1y1 +
						q2[x1 * 3] * dist_x1y2 +
						q3[x1 * 3] * dist_x1y3 +
						q0[x2 * 3] * dist_x2y0 +
						q1[x2 * 3] * dist_x2y1 +
						q2[x2 * 3] * dist_x2y2 +
						q3[x2 * 3] * dist_x2y3 +
						q0[x3 * 3] * dist_x3y0 +
						q1[x3 * 3] * dist_x3y1 +
						q2[x3 * 3] * dist_x3y2 +
						q3[x3 * 3] * dist_x3y3);

					p[j * 3 + 1] = (uchar)(q0[x0 * 3 + 1] * dist_x0y0 +
						q1[x0 * 3 + 1] * dist_x0y1 +
						q2[x0 * 3 + 1] * dist_x0y2 +
						q3[x0 * 3 + 1] * dist_x0y3 +
						q0[x1 * 3 + 1] * dist_x1y0 +
						q1[x1 * 3 + 1] * dist_x1y1 +
						q2[x1 * 3 + 1] * dist_x1y2 +
						q3[x1 * 3 + 1] * dist_x1y3 +
						q0[x2 * 3 + 1] * dist_x2y0 +
						q1[x2 * 3 + 1] * dist_x2y1 +
						q2[x2 * 3 + 1] * dist_x2y2 +
						q3[x2 * 3 + 1] * dist_x2y3 +
						q0[x3 * 3 + 1] * dist_x3y0 +
						q1[x3 * 3 + 1] * dist_x3y1 +
						q2[x3 * 3 + 1] * dist_x3y2 +
						q3[x3 * 3 + 1] * dist_x3y3);

					p[j * 3 + 2] = (uchar)(q0[x0 * 3 + 2] * dist_x0y0 +
						q1[x0 * 3 + 2] * dist_x0y1 +
						q2[x0 * 3 + 2] * dist_x0y2 +
						q3[x0 * 3 + 2] * dist_x0y3 +
						q0[x1 * 3 + 2] * dist_x1y0 +
						q1[x1 * 3 + 2] * dist_x1y1 +
						q2[x1 * 3 + 2] * dist_x1y2 +
						q3[x1 * 3 + 2] * dist_x1y3 +
						q0[x2 * 3 + 2] * dist_x2y0 +
						q1[x2 * 3 + 2] * dist_x2y1 +
						q2[x2 * 3 + 2] * dist_x2y2 +
						q3[x2 * 3 + 2] * dist_x2y3 +
						q0[x3 * 3 + 2] * dist_x3y0 +
						q1[x3 * 3 + 2] * dist_x3y1 +
						q2[x3 * 3 + 2] * dist_x3y2 +
						q3[x3 * 3 + 2] * dist_x3y3);

					float thre = 198.0f;
					if ((abs(p[j * 3] - q1[x1 * 3]) > thre) || (abs(p[j * 3 + 1] - q1[x1 * 3 + 1]) > thre) ||
						(abs(p[j * 3 + 2] - q1[x1 * 3 + 2]) > thre))
					{
						p[j * 3] = q1[x1 * 3];
						p[j * 3 + 1] = q1[x1 * 3 + 1];
						p[j * 3 + 2] = q1[x1 * 3 + 2];
					}
				}
			}
		}
	}
}

void ImageCopy(CImage* pImgSrc, CImage* pImgDst)
{
	int MaxColors = pImgSrc->GetMaxColorTableEntries();
	RGBQUAD* ColorTab;
	ColorTab = new RGBQUAD[MaxColors];

	CDC* pDCsrc, * pDCdrc;
	if (!pImgDst->IsNull())
	{
		pImgDst->Destroy();
	}
	pImgDst->Create(pImgSrc->GetWidth(), pImgSrc->GetHeight(), pImgSrc->GetBPP(), 0);

	if (pImgSrc->IsIndexed())
	{
		pImgSrc->GetColorTable(0, MaxColors, ColorTab);
		pImgDst->SetColorTable(0, MaxColors, ColorTab);
	}

	pDCsrc = CDC::FromHandle(pImgSrc->GetDC());
	pDCdrc = CDC::FromHandle(pImgDst->GetDC());
	pDCdrc->BitBlt(0, 0, pImgSrc->GetWidth(), pImgSrc->GetHeight(), pDCsrc, 0, 0, SRCCOPY);
	pImgSrc->ReleaseDC();
	pImgDst->ReleaseDC();
	delete ColorTab;
}

UINT ImageProcess::scale(CImage* src, float scaleXNum, float scaleYNum)
{
	



	byte* pRealData = (byte*)src->GetBits();
	int channels = src->GetBPP() / 8;
	if (channels != 1 && channels != 3)
	{
		CString channelsException(_T("非单通道或三通道的图片暂时无法处理。"));
		AfxMessageBox(channelsException);
		return -1;
	}



	float transMat[3][3] = {
		{scaleXNum, 0.0f, 0.0f},
		{0.0f, scaleYNum, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};
	Mat ori_mat, dst_mat;
	CImage* srcimg = src;
	CImage2Mat(src, ori_mat);
	
	scaleBicubicInter(ori_mat, dst_mat, transMat);
	CImage dst_image;
	
	Mat2CImage(dst_mat, dst_image);
	
	byte* pBits = (byte*)dst_image.GetBits();
	int dst_pit = dst_image.GetPitch();
	
	
	ImageCopy(&dst_image, srcimg);

	
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_TRANSFORM_SCALE, 1, NULL);
	return 0;
}

UINT ImageProcess::rotate(CImage* src, float angle)
{
	byte* pRealData = (byte*)src->GetBits();
	float degree = angle * PI / 180;

	CImage* srcimg = src;
	/*float transMat[3][3] = {
		{cos(angle), sin(angle),
		-0.5f * (src->GetWidth()) * cos(angle) - 0.5f * (src->GetHeight()) * sin(angle) + 0.5f * (src->GetWidth())},
		{-sin(angle), cos(angle),
		0.5f * (src->GetWidth()) * sin(angle) - 0.5f * (src->GetHeight()) * cos(angle) + 0.5f * (src->GetHeight())},
		{0.0f, 0.0f, 1.0f}
	};*/
	float transMat[3][3] = {
		{cos(degree), sin(degree), 0},
		{-sin(degree), cos(degree), 0},
		{0.0f, 0.0f, 1.0f}
	};
	Mat ori_mat, dst_mat;
	
	CImage2Mat(src, ori_mat);

	scaleBicubicInter(ori_mat, dst_mat, transMat);
	CImage* dst_image;
	dst_image = new CImage();

	Mat2CImage(dst_mat, *dst_image);

	byte* pBits = (byte*)dst_image->GetBits();
	int dst_pit = dst_image->GetPitch();

	float scaleXNum = (float)srcimg->GetWidth() / (float)dst_image->GetWidth();
	float scaleYNum = (float)srcimg->GetHeight() / (float)dst_image->GetHeight();
	float scaleNum = max(scaleXNum, scaleYNum);
//	scale(dst_image, scaleNum, scaleNum);
	ImageCopy(dst_image, srcimg);
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_TRANSFORM_ROTATE, 1, NULL);
	return 0;
}




