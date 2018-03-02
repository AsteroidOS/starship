#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "servicecontrol.h"
#include "../starfish/watch.h"
#include "../starfish/watches.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<Watch>("Telescope", 1, 0, "Watch", "Get them from the model");
    qmlRegisterType<Watches>("Telescope", 1, 0, "Watches");
    qmlRegisterType<ServiceControl>("Telescope", 1, 0, "ServiceController");

    QQuickView view;
    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit);

    view.setSource(QUrl(QStringLiteral("qrc:///qml/telescope.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
