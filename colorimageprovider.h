#ifndef COLORIMAGEPROVIDER_H
#define COLORIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <memory>

using std::shared_ptr;

class ColorImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    ColorImageProvider();

    void setPixmap(shared_ptr<QPixmap> val);
    void setPixmap(QPixmap val);
    void setImage(QImage& val);
    void update();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

signals:
    void callQmlRefeshImg();

private:
    QPixmap requestColorPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    QPixmap requestOtherPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    shared_ptr<QPixmap> mPixmap;
};

#endif // COLORIMAGEPROVIDER_H
