#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>
#include <QVariant>
#include "colorimageprovider.h"
#include <memory>

using std::unique_ptr;

class ImageProcess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
public:
    ImageProcess();
    QString path() const;
    void setPath(const QString& path);

    Q_INVOKABLE void process(QVariant val);

signals:
    void pathChanged();

private:
    QString mPath;
};

#endif // IMAGEPROCESS_H
