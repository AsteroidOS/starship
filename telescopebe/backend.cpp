#include <QtQml>
#include <QtQml/QQmlContext>
#include "backend.h"
#include "../starfish/servicecontrol.h"
#include "../starfish/watch.h"
#include "../starfish/watches.h"
#include "mytype.h"


void BackendPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Telescope"));

    qmlRegisterUncreatableType<Watch>(uri, 1, 0, "Watch", "Get them from the model");
    qmlRegisterType<Watches>(uri, 1, 0, "Watches");
    qmlRegisterType<ServiceControl>(uri, 1, 0, "ServiceController");
    qmlRegisterType<MyType>(uri, 1, 0, "MyType");
}

void BackendPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}
