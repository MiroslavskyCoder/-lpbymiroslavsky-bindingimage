#include "global.h"
#include "Frame.h"

NAN_MODULE_INIT(init) 
{ 
    Frame::Initialize(target);
}

NODE_MODULE(bindingimage, init);