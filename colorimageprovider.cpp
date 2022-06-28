#include "colorimageprovider.h"
#include <QDebug>
#include <QString>

ColorImageProvider::ColorImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

void ColorImageProvider::setPixmap(shared_ptr<QPixmap> val)
{
    mPixmap = val;
}

void ColorImageProvider::setPixmap(QPixmap val)
{
    mPixmap = std::make_shared<QPixmap>();
    *mPixmap = val;
}

void ColorImageProvider::setImage(QImage& val)
{
    mPixmap = std::make_shared<QPixmap>();
    *mPixmap = QPixmap::fromImage(val);
}

void ColorImageProvider::update()
{
    emit callQmlRefeshImg();
}

QPixmap ColorImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    if (id.startsWith("other")) {
        return requestOtherPixmap(id, size, requestedSize);
    } else {
        return requestColorPixmap(id, size, requestedSize);
    }
}

QPixmap ColorImageProvider::requestColorPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = requestedSize.width() > 0 ? requestedSize.width() : 960;
    int height = requestedSize.height() > 0 ? requestedSize.height() : 720;

    QString arg = QString("color id: %1, size: %2x%3, requestedSize: %4x%5, useSize: %6x%7").arg(id).arg(size->width()).arg(size->height()).arg(requestedSize.width()).arg(requestedSize.height()).arg(width).arg(height);
    qDebug() << arg;

    if (size) {
        size->setWidth(width);
        size->setHeight(height);
    }
    QPixmap pixmap(width, height);
    pixmap.fill(QColor(id).rgba());
    return pixmap;
}

QPixmap ColorImageProvider::requestOtherPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = requestedSize.width() > 0 ? requestedSize.width() : 960;
    int height = requestedSize.height() > 0 ? requestedSize.height() : 720;
    QString arg = QString("other default id: %1, size: %2x%3, requestedSize: %4x%5, useSize: %6x%7").arg(id).arg(size->width()).arg(size->height()).arg(requestedSize.width()).arg(requestedSize.height()).arg(width).arg(height);
    qDebug() << arg;

    if (!mPixmap) {
        if (size) {
            size->setWidth(width);
            size->setHeight(height);
        }
        QPixmap pixmap(width, height);
        pixmap.fill(QColor(0x333333).rgba());
        return pixmap;
    }
    width = mPixmap->width();
    height = mPixmap->height();
    arg = QString("other size: %1x%2").arg(width).arg(height);
    qDebug() << arg;

    if (size) {
        size->setWidth(width);
        size->setHeight(height);
    }
    return *mPixmap;
}
