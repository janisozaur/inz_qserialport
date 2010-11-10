#include "plot.h"
#include "positiondatax.h"
#include "positiondatay.h"
#include "positiondataz.h"
#include <qwt_plot_curve.h>
#include <QDebug>
#include <QTimerEvent>

Plot::Plot(QWidget *parent) :
	QwtPlot(parent),
	mTimerId(-1)
{
	qDebug() << "Plot ctor" << this;
	QwtPlotCurve *curveX = new QwtPlotCurve();
	curveX->setStyle(QwtPlotCurve::Lines);
	curveX->setPen(QPen(Qt::green));
	curveX->setRenderHint(QwtPlotItem::RenderAntialiased, true);
	curveX->setData(new PositionDataX());
	curveX->attach(this);
	mCurves << curveX;
	QwtPlotCurve *curveY = new QwtPlotCurve();
	curveY->setStyle(QwtPlotCurve::Lines);
	curveY->setPen(QPen(Qt::red));
	curveY->setRenderHint(QwtPlotItem::RenderAntialiased, true);
	curveY->setData(new PositionDataY());
	curveY->attach(this);
	mCurves << curveY;
	QwtPlotCurve *curveZ = new QwtPlotCurve();
	curveZ->setStyle(QwtPlotCurve::Lines);
	curveZ->setPen(QPen(Qt::blue));
	curveZ->setRenderHint(QwtPlotItem::RenderAntialiased, true);
	curveZ->setData(new PositionDataZ());
	curveZ->attach(this);
	mCurves << curveZ;
	setAutoReplot(true);
	mTimerId = startTimer(10);
}

Plot::~Plot()
{
	qDebug() << "Plot dtor" << this;
}

void Plot::replot()
{
	//qDebug() << "replotting";
	QwtPlot::replot();
}

void Plot::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == mTimerId) {
		replot();
	}
	QwtPlot::timerEvent(event);
}
