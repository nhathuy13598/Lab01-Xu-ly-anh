// Lab01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
int HSV2RGB(const Mat & sourceImage, Mat & destinationImage)
{
	if (sourceImage.data == NULL) {
		return 1;
	}
	int row = sourceImage.rows;
	int col = sourceImage.cols;
	int channel = sourceImage.channels();

	if ((row != destinationImage.rows) || (col != destinationImage.cols) || (channel != destinationImage.channels())) {
		return 1;
	}

	int widthStep = sourceImage.step[0];


	uchar* pData = sourceImage.data;
	uchar* pDataDes = destinationImage.data;

	for (int i = 0; i < row; i++, pData += widthStep, pDataDes += widthStep) {
		uchar* pRow = pData;
		uchar* pRowDes = pDataDes;
		for (int j = 0; j < col; j++, pRow += channel, pRowDes += channel) {
			float fH = float(pRow[0] * 2);
			float fS = float(pRow[1]) / 255;
			float fV = float(pRow[2]) / 255;



			float fC = fS * fV;
			float fHComma = fH / 60;
			float fX = fC * (1 - abs((int(fHComma) % 2 - 1)));
			
			float fR1, fG1, fB1;
			fR1 = fG1 = fB1 = 0;
			if (fHComma >= 0 && fHComma <= 1) {
				fR1 = fC;
				fG1 = fX;
				fB1 = 0;
			}
			else if (fHComma <= 2) {
				fR1 = fX;
				fG1 = fC;
				fB1 = 0;
			}
			else if (fHComma <= 3) {
				fR1 = 0;
				fG1 = fC;
				fB1 = fX;
			}
			else if (fHComma <= 4) {
				fR1 = 0;
				fG1 = fX;
				fB1 = fC;
			}
			else if (fHComma <= 5) {
				fR1 = fX;
				fG1 = 0;
				fB1 = fC;
			}
			else if (fHComma <= 6) {
				fR1 = fC;
				fG1 = 0;
				fB1 = fX;
			}

			float m = fV - fC;
			float fR, fG, fB;
			fR = fR1 + m;
			fG = fG1 + m;
			fB = fB1 + m;
			pRowDes[0] = uchar(fB * 255 );
			pRowDes[1] = uchar(fG * 255 );
			pRowDes[2] = uchar(fR * 255 );
		}
	}
	return 0;
}
int main()
{
	Mat a = imread("input.jpg", CV_LOAD_IMAGE_COLOR);
	imshow("input.jpg", a);
	Mat b(a.rows, a.cols, CV_8UC3);
	HSV2RGB(a, b);
	/*cvtColor(a, b, CV_HSV2BGR);*/
	


	imwrite("output.jpg", b);
	imshow("output.jpg", b);
	
	waitKey(0);
	return 0;
}

