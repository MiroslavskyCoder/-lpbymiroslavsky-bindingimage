#include "global.h"

#include "opencv2/opencv_modules.hpp"
#include "opencv2/opencv.hpp"

class Frame:
    public Nan::ObjectWrap 
{
public:
    
	static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target); 

    static NAN_METHOD(New);

    static NAN_METHOD(GetWidth);
    static NAN_METHOD(GetHeight);
    static NAN_METHOD(GetPixel);
    static NAN_METHOD(ToBuffer);
    
    Frame(std::string path); 
    
private:

    cv::Mat_<cv::Vec3d> kImage;

};