## AVS Video Decoder

This software is used for decoding .avs videos into .jpeg image frames.

## Dependency
The AVS decoder only support for Windows platform, and depends on serveral softwares:
1. Microsoft Visual Studio 2008
2. opencv2.3.1
3. AVS_dll_new

Note that opencv2.3.1 and AVS_dll_new are no need to install, for that their .dll and .lib files have been included.

## Usage
```bash
AVS/Debug/AVS.exe your_video_name.avs your_result_images_path
```

