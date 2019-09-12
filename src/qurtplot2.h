#ifndef QURTPLOT2_H
#define QURTPLOT2_H

#include <quspectrumplot.h>
#include <cudata.h>
#include <cudatalistener.h>
#include <quxtrawidgetplugininterface.h>

class QuRTPlot2 : public QuSpectrumPlot, public QuXtraWidgetI
{
    Q_OBJECT
    Q_PROPERTY(QStringList sources READ sources WRITE setSources)

public:
    QuRTPlot2(QWidget *parent, Cumbia *cumbia, const CuControlsReaderFactoryI &r_fac);
    QuRTPlot2(QWidget *parent, CumbiaPool *cumbia_pool, const CuControlsFactoryPool &fpool);

    ~QuRTPlot2();

    QStringList sources() const;

protected:
    void contextMenuEvent(QContextMenuEvent *e);

public slots:
    void setSources(const QStringList& srcs);

    void configureRT();

    // QuXtraWidgetI interface
public:
    CuContext *getContext() const;
    QString link() const;
    void setLink(const QString &s);
    void unsetLink();
    Type getType() const;
};

#endif // QURTPLOT2_H
