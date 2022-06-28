#ifndef MANAGER_H
#define MANAGER_H

#include "colorimageprovider.h"
#include <memory>

class Manager
{
public:
    static Manager* Instance();
    ColorImageProvider* getImageProvider();

private:
    Manager();

private:
//    std::unique_ptr<ColorImageProvider> mImageProvider;
    ColorImageProvider* mImageProvider = nullptr;
};

#endif // MANAGER_H
