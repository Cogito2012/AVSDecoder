
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <ml.h>
#include <highgui.h>
#include <cxcore.h>
#include <cv.h>
#include <direct.h>  
#include "AVS.h"
using namespace std;

bool YV12ToBGR24_Native(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    const long len = width * height;
    unsigned char* yData = pYUV;
    unsigned char* vData = &yData[len];
    unsigned char* uData = &vData[len >> 2];

    int bgr[3];
    int yIdx,uIdx,vIdx,idx;
    for (int i = 0;i < height;i++){
        for (int j = 0;j < width;j++){
            yIdx = i * width + j;
            vIdx = (i/2) * (width/2) + (j/2);
            uIdx = vIdx;
        
            bgr[0] = (int)(yData[yIdx] + 1.732446 * (uData[vIdx] - 128));                                    // b分量
            bgr[1] = (int)(yData[yIdx] - 0.698001 * (uData[uIdx] - 128) - 0.703125 * (vData[vIdx] - 128));    // g分量
            bgr[2] = (int)(yData[yIdx] + 1.370705 * (vData[uIdx] - 128));                                    // r分量

            for (int k = 0;k < 3;k++){
                idx = (i * width + j) * 3 + k;
                if(bgr[k] >= 0 && bgr[k] <= 255)
                    pBGR24[idx] = bgr[k];
                else
                    pBGR24[idx] = (bgr[k] < 0)?0:255;
            }
        }
    }
    return true;
}

int main(int argc,char *argv[])	
{

	int write_count=0;
	
	int width=0,height=0;
	unsigned char *avsFrame=NULL;
	int cap;
	int i;

	cap=avsCreateCapture(argv[1]);	
	avsGetCaptureProperty(cap,&width,&height);

	/*test for avs lib*/
	_mkdir(argv[2]);
	unsigned char *im_data;
	unsigned char *im_rgb;
	im_rgb = (unsigned char *) malloc(sizeof(unsigned char) * width * height * 3);
	while(1)
	{
		char k[10];
		itoa(write_count+1,k,10);
		IplImage* p;
		string s=argv[2];
		s+="//";
		s+=k;
		s+=".jpg";

		// method 1: avsQueryFrame
		im_data = avsQueryFrame(cap);
		if(!im_data){
			break;
		}
		memset(im_rgb,0,sizeof(unsigned char) * width * height * 3);
		YV12ToBGR24_Native(im_data,im_rgb,width,height);
		cv::Mat im = cv::Mat(height,width,CV_8UC3);
		im.data = im_rgb;
		cv::imwrite(s.c_str(),im);

		// method 2: avsQueryFrame_pic
		//if(!avsQueryFrame_pic(cap,width,height,s.c_str()))
		//	break;

		write_count++;
	}

	free(im_rgb);
	free(im_data);
	avsDestroyCapture(cap);
	return 0;
}
