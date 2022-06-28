#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QLocale>
#include <QTranslator>
#include "colorimageprovider.h"

#include "imageprocess.h"
#include "manager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ImageProcess>("com.image", 1, 0, "ImageProcess");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ImageTool_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    Manager* mgr = Manager::Instance();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("ImageProvider", mgr->getImageProvider());
    engine.addImageProvider(QLatin1String("colors"), mgr->getImageProvider());
//    QQmlEngine::setObjectOwnership(mgr->getImageProvider(), QQmlEngine::CppOwnership);
    const QUrl url(u"qrc:/ImageTool/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
