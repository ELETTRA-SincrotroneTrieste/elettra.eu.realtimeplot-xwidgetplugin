#ifndef RTPLOTXWIDGETPLUGIN_H
#define RTPLOTXWIDGETPLUGIN_H

#include <quxtrawidgetplugininterface.h>
#include <QObject>

class RTPlotXWidgetPlugin : public QObject, public QuXtraWidgetPluginI
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "elettra.eu.realtimeplot-xwidgetplugin.json")

public:
    explicit RTPlotXWidgetPlugin(QObject *parent = nullptr);
    ~RTPlotXWidgetPlugin();

    Q_INTERFACES(QuXtraWidgetPluginI)

    // QuXtraWidgetPluginI interface
    QWidget *create(const QString &name, QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac);
    QWidget *create(const QString &name, QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool);
    QString name() const;
    QString description() const;
    QStringList catalogue() const;
};














#endif // CUMBIACOPYSOURCECTXMENUACTION_H
