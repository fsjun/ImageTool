#include "manager.h"

Manager* Manager::Instance() {
    static Manager inst;
    return &inst;
}

Manager::Manager()
{
    mImageProvider = new ColorImageProvider();
}

ColorImageProvider* Manager::getImageProvider()
{
    return mImageProvider;
}
