#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCoreApplication::setOrganizationName("MyCompany");
    QCoreApplication::setApplicationName("WeatherApp");

    QTranslator translator;
    if (translator.load(QLocale(), "weatherapp", "_", ":/i18n")) {
        app.installTranslator(&translator);
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl::fromLocalFile("/home/user/wheatherapp/main.qml"));    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
