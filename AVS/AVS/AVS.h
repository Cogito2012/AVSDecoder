#ifdef DLL_API
#else
#define DLL_API extern "C" _declspec(dllimport)
#endif

DLL_API int avsCreateCapture(char *filename);			//Initialize the decoders, return the decoder identifier cap
DLL_API void avsGetCaptureProperty(int cap, int *width,int *height);	//Get width and height of the video

DLL_API unsigned char *avsQueryFrame(int cap);
DLL_API unsigned char *avsQueryFrame2(int cap);
DLL_API unsigned char *avsQueryBackgroundFrame(int cap);
DLL_API void avsResetCap(int cap_temp);
DLL_API int cvLoadImageYUV(unsigned char *avsFrame, int w, int h,const char* pic_path);

DLL_API int avsQueryFrame_pic(int cap, int width, int height,const char* pic_path);//save as pic_path
DLL_API int avsDestroyCapture(int cap);