#include "RTPlotXWPluginExample.h"

// cumbia-tango
#include <cuserviceprovider.h>
#include <cumacros.h>
// cumbia-tango

#include <QGridLayout>
#include <QVariant>
#include <QCoreApplication>
#include <quxtrawidgetpluginloader.h>

RTPlotXWPluginExample::RTPlotXWPluginExample(CumbiaTango *cut, QWidget *parent) :
    QWidget(parent)
{
    // cumbia-tango
    cu_t = cut;
    m_log = new CuLog(&m_log_impl);
    cu_t->getServiceProvider()->registerService(CuServices::Log, m_log);
    // cumbia-tango

    QGridLayout *lo = new QGridLayout(this);
    QuXtraWidgetPluginLoader xwpl;
    QuXtraWidgetPluginI *pi = xwpl.getPlugin("QuRTPlot");
    if(pi) {
        QWidget *rtPlot = pi->create("QuRTPlot", parent, cut, this->cu_tango_r_fac);
        lo->addWidget(rtPlot);
        printf("plot created\n");
        rtPlot->setObjectName("rtPlot");
        // either use the "source" property
        printf("setting source %s\n", qstoc(qApp->arguments()[1]));
        rtPlot->setProperty("source", qApp->arguments()[1]);
        // or
        // dynamic_cast<QuXtraWidgetI *>(rtPlot)->setLink(qApp->arguments().at(1));
    }

}

RTPlotXWPluginExample::~RTPlotXWPluginExample()
{

}
