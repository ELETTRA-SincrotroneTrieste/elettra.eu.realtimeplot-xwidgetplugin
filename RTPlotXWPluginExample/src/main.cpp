#include <quapplication.h>
#include "RTPlotXWPluginExample.h"

// cumbia-tango
#include <cumbiatango.h>
#include <cuthreadfactoryimpl.h>
#include <qthreadseventbridgefactory.h>
// cumbia-tango

#include <X11/Xlib.h>
#include <QX11Info>


#define CVSVERSION "$Name:  $"


int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("\nUsage: %s a/device/name/string_scalar\n"
                             "       %s a/device/name/string_vector\n"
                             "       %s a/device/name/anything\n", argv[0], argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }
    QuApplication qu_app( argc, argv );
    qu_app.setOrganizationName("$ORGANIZATION_NAME$");
    qu_app.setApplicationName("$APPLICATION_NAME$");
    QString version(CVSVERSION);
    qu_app.setApplicationVersion(version);
    qu_app.setProperty("author", "Giacomo");
    qu_app.setProperty("mail", "giacomo.strangolino@elettra.eu");
    qu_app.setProperty("phone", "+390403758073");
    qu_app.setProperty("office", "T2PT025");
    qu_app.setProperty("hwReferent", "$HW_REFERENT$"); /* name of the referent that provides the device server */
    
    // instantiate CumbiaTango
    CumbiaTango *cu_t = new CumbiaTango(new CuThreadFactoryImpl(), new QThreadsEventBridgeFactory());

    RTPlotXWPluginExample *w = new RTPlotXWPluginExample(cu_t, NULL);
    w->show();

    if(QX11Info::isPlatformX11()) {
        /* register to window manager */
        Display *disp = QX11Info::display();
        Window root_win = (Window) w->winId();
        XSetCommand(disp, root_win, argv, argc);
    }

    // exec application loop
    int ret = qu_app.exec();
    // delete resources and return
    delete w;
    delete cu_t;
    return ret;
}
