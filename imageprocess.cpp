#include "imageprocess.h"
#include <QDebug>
#include "manager.h"

ImageProcess::ImageProcess()
{
}

QString ImageProcess::path() const
{
    return mPath;
}

void ImageProcess::setPath(const QString& path)
{
    mPath = path;
    qDebug() << "setPath: " << path;
}

void ImageProcess::process(QVariant val)
{
    QString path = val.toString();
    qDebug() << "process: " << path;
    if (path.startsWith("file:///")) {
        path = path.right(path.size()-8);
    }
    QPixmap pixmap;
    if (!pixmap.load(path)) {
        qDebug() << "file is not exist or file format is not supported";
        return;
    }
    Manager* mgr = Manager::Instance();
    auto imgProvider = mgr->getImageProvider();
    imgProvider->setPixmap(pixmap);
    imgProvider->update();
}
