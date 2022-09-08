#include "Frame.h"

#include <vector>

Nan::Persistent<v8::FunctionTemplate> Frame::constructor;

void Frame::Initialize(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
    Nan::HandleScope scope;
    
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Frame::New);
    
    constructor.Reset(ctor);
    
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("Frame").ToLocalChecked()); 
 
    Nan::SetPrototypeMethod(ctor, "getWidth", GetWidth);
    Nan::SetPrototypeMethod(ctor, "getHeight", GetHeight);
    Nan::SetPrototypeMethod(ctor, "getPixel", GetPixel);

    Nan::SetPrototypeMethod(ctor, "toBuffer", ToBuffer);

    v8::Local<v8::Context> ctx = Nan::GetCurrentContext();
    
    Nan::Set(target, Nan::New("Frame").ToLocalChecked(), ctor->GetFunction(ctx).ToLocalChecked());
}

NAN_METHOD(Frame::New) {
    if (!info.IsConstructCall()) {
        return Nan::ThrowTypeError("Class constructors cannot be invoked without 'new'");
    } 
    
    Frame* kFrame = nullptr;

    if (info[0]->IsString()) {    
        Nan::Utf8String strUtf8(info[0]); 
        kFrame = new Frame(*strUtf8);
    } else {
        Nan::ThrowReferenceError(Nan::New<v8::String>("Error laod image").ToLocalChecked());
    }

    kFrame->Wrap(info.This()); 
    
    info.GetReturnValue().Set(info.This()); 
}


NAN_METHOD(Frame::GetWidth) {
    Frame *objWrap = Nan::ObjectWrap::Unwrap<Frame>(info.This()); 
    info.GetReturnValue().Set(Nan::New<v8::Number>(objWrap->kImage.size().width));
}

NAN_METHOD(Frame::GetHeight) {
    Frame *objWrap = Nan::ObjectWrap::Unwrap<Frame>(info.This()); 
    info.GetReturnValue().Set(Nan::New<v8::Number>(objWrap->kImage.size().height));
}

NAN_METHOD(Frame::GetPixel) {
    Frame *objWrap = Nan::ObjectWrap::Unwrap<Frame>(info.This()); 

    int x, y;
    if (info[0]->IsNumber()) {
        x = Nan::To<int>(info[0]).FromMaybe(0);
    } else {
        Nan::ThrowReferenceError(Nan::New<v8::String>("Error incorrect pixel coordinates \"x\"").ToLocalChecked());
    }
    if (info[1]->IsNumber()) {
        y = Nan::To<int>(info[1]).FromMaybe(0);
    } else {
        Nan::ThrowReferenceError(Nan::New<v8::String>("Error incorrect pixel coordinates \"y\"").ToLocalChecked());
    }

    cv::Vec3d pixel = objWrap->kImage(x, y);

    v8::Local<v8::Array> pixels = Nan::New<v8::Array>(3);

    Nan::Set(pixels, 0, Nan::New(pixel[0]));
    Nan::Set(pixels, 1, Nan::New(pixel[1]));
    Nan::Set(pixels, 2, Nan::New(pixel[2]));

    info.GetReturnValue().Set(pixels);
}

NAN_METHOD(Frame::ToBuffer) {
    Frame *objWrap = Nan::ObjectWrap::Unwrap<Frame>(info.This()); 

    const char* ext = ".jpg";

    if (info[0]->IsString()) {
        Nan::Utf8String strUtf8(info[0]); 
        ext = (const char*) *strUtf8;
    }

    std::vector<uchar> buffer = {};
    cv::imencode(ext, objWrap->kImage, buffer);

    info.GetReturnValue().Set(Nan::CopyBuffer((const char*)buffer.data(), buffer.size()).ToLocalChecked());
}

Frame::Frame(std::string path) {
    kImage = cv::imread(path);
} 

