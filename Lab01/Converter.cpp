#include "stdafx.h"
#include "Converter.h"

int Converter::RGB2HSV(const Mat & sourceImage, Mat & destinationImage)
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
			uchar blue = pRow[0];
			uchar green = pRow[1];
			uchar red = pRow[2];

			float fBlue = blue / 255;
			float fGreen = green / 255;
			float fRed = red / 255;

			float max, min, H, S, V;
			if (blue == red && red == green) {
				max = min = fBlue;
			}
			else {
				/* blue>red */
				if (blue > red) {


					/* red>green */
					if (red > green) {
						/* blue>red>green */
						max = fBlue;
						min = fGreen;
					}


					/* green>red */
					else {
						if (blue > green) {
							/* blue>green>red */
							max = fBlue;
							min = fRed;
						}

						/* green>blue */
						else {
							/* green>blue>red */
							max = fGreen;
							min = fRed;
						}
					}
				}



				/* blue<red */
				else {
					/* blue>green */
					if (blue > green) {
						/* red>blue>green */
						max = fRed;
						min = fGreen;
					}
					/* green>blue */
					else {
						/* green>red */
						if (green > red) {
							/* green>red>blue */
							max = fGreen;
							min = fBlue;
						}
						/* green<red */
						else {
							/* red>green>blue */
							max = fRed;
							min = fBlue;
						}
					}
				}
			}

			V = max;
			if (max == 0) {
				S = 0;
			}
			else {
				S = (max - min) / max;
			}

			if (max == min) {
				H = 0;
			}
			else if (max == fRed) {
				H = 60 * (fGreen - fBlue) / (max - min);
			}
			else if (max = fGreen) {
				H = 60 * (2 + (fBlue - fRed) / (max - min));
			}
			else if (max == fBlue) {
				H = 60 * (4 + (fRed - fGreen) / (max - min));
			}
			if (H < 0) {
				H += 360;
			}
			uchar iV = uchar(V * 255);
			uchar iS = uchar(S * 255);
			uchar iH = uchar(H / 2);

			pRowDes[0] = iH;
			pRowDes[1] = iS;
			pRowDes[2] = iV;
		}
	}
	return 0;
}

