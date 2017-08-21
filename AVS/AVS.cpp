
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

int main(int argc,char *argv[])	
{

	int write_count=0;
	
	int width=0,height=0;
	unsigned char *avsFrame=NULL;
	int cap;
	int i;

	//cap=avsCreateCapture("1.avs");	
	cap=avsCreateCapture(argv[1]);	
	avsGetCaptureProperty(cap,&width,&height);
	printf("width=%d,height=%d\n",width,height);

	/*test for avs lib*/
	_mkdir(argv[2]);
	while(1)
	{
		char k[10];
		itoa(write_count+1,k,10);
		IplImage* p;
		//string s="fra1//";
		string s=argv[2];
		s+="//";
		s+=k;
		s+=".jpg";
		if(!avsQueryFrame_pic(cap,width,height,s.c_str()))
			break;
		write_count++;
	}

	avsDestroyCapture(cap);
	return 0;
}
