#include "elettra.eu.realtimeplot-xwidgetplugin.h"
#include <cucontrolsreader_abs.h>
#include <cucontext.h>
#include "qurtplot.h"
#include "qurtplot2.h"
#include <cumacros.h>

RTPlotXWidgetPlugin::RTPlotXWidgetPlugin(QObject *parent)
    : QObject (parent)
{

}

RTPlotXWidgetPlugin::~RTPlotXWidgetPlugin()
{

}

QWidget *RTPlotXWidgetPlugin::create(const QString &name, QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac)
{
    if(name == "QuRTPlot")
        return new QuRTPlot(parent, cumbia, r_fac);
    else if(name == "QuRTPlot2")
        return new QuRTPlot2(parent, cumbia, r_fac);
    perr("RTPlotXWidgetPlugin.create: RTPlotXWidgetPlugin does not provide the widget \"%s\"", qstoc(name));
    return nullptr;
}

QWidget *RTPlotXWidgetPlugin::create(const QString &name, QWidget *parent, CumbiaPool *cumbia_pool,
                                                const CuControlsFactoryPool &fpool)
{
    if(name == "QuRTPlot")
        return new QuRTPlot(parent, cumbia_pool, fpool);
    else if(name == "QuRTPlot2")
        return new QuRTPlot2(parent, cumbia_pool, fpool);
    perr("RTPlotXWidgetPlugin.create: RTPlotXWidgetPlugin does not provide the widget \"%s\"", qstoc(name));
    return nullptr;
}

QString RTPlotXWidgetPlugin::name() const
{
    return "elettra.eu.rtplotxwidgetplugin";
}

QString RTPlotXWidgetPlugin::description() const
{
    return QString("%1 provides two kind of \"realtime plots\" that connect and display arrays "
                   "from some special Elettra Tango devices exporting \"real time\" commands. "
                   "QuRTPlot2 is the version with the popup dialog configuration, QuRTPlot shows "
                   "a configuration section within the widget itself.").arg(name());
}

QStringList RTPlotXWidgetPlugin::catalogue() const
{
    return QStringList() << "QuRTPlot" << "QuRTPlot2";
}
