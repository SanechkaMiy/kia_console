#include <QCoreApplication>
#include <workwithmain.h>
#include <csignal>
void sigHandler(int s)
{
    std::signal(s, SIG_DFL);
    qApp->quit();
}

int main(int argc, char *argv[])
{
    setlocale(LC_NUMERIC, "French_Canada.1252");
    QCoreApplication a(argc, argv);
    //QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));
    WorkWithMain wwMain(2529);
    //qApp->quit();
    std::signal(SIGINT, sigHandler);
    std::signal(SIGTERM, sigHandler);

    return a.exec();
}
