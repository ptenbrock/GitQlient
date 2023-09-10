#include <QApplication>
#include <QFontDatabase>
#include <QIcon>
#include <QTimer>
#include <QTranslator>

#include <GitQlient.h>
#include <QLogger.h>

using namespace QLogger;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

   QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

   QApplication app(argc, argv);

   QApplication::setOrganizationName("CescSoftware");
   QApplication::setOrganizationDomain("francescmm.com");
   QApplication::setApplicationName("GitQlient");
   QApplication::setApplicationVersion(VER);
   QApplication::setWindowIcon(QIcon(":/icons/GitQlientLogoIco"));

   QFontDatabase::addApplicationFont(":/DejaVuSans");
   QFontDatabase::addApplicationFont(":/DejaVuSansMono");

   QTranslator qtTranslator;
   if (qtTranslator.load(QLocale(), "gitqlient", "_", ":/translations/"))
   {
      app.installTranslator(&qtTranslator);
   }

   QStringList repos;
   if (GitQlient::parseArguments(app.arguments(), &repos))
   {
      GitQlient mainWin;
      mainWin.setRepositories(repos);
      mainWin.restorePinnedRepos();
      mainWin.show();

      return app.exec();
   }

   return 0;
}
