#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"
#include "signaldata.h"

#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	mPlot = new Plot(this);
	ui->horizontalLayout->addWidget(mPlot, 10);

	// use map to sort values
	QMap<QString, QPortSettings::BaudRate> map;
	// values stolen from qportsettings.h
#ifdef TNX_POSIX_SERIAL_PORT
	map.insert("BAUDR_50", QPortSettings::BAUDR_50);
	map.insert("BAUDR_75", QPortSettings::BAUDR_75);
	map.insert("BAUDR_134", QPortSettings::BAUDR_134);
	map.insert("BAUDR_150", QPortSettings::BAUDR_150);
	map.insert("BAUDR_200", QPortSettings::BAUDR_200);
	map.insert("BAUDR_1800", QPortSettings::BAUDR_1800);
#endif
#ifdef Q_OS_LINUX
	map.insert("BAUDR_230400", QPortSettings::BAUDR_230400);
	map.insert("BAUDR_460800", QPortSettings::BAUDR_460800);
	map.insert("BAUDR_500000", QPortSettings::BAUDR_500000);
	map.insert("BAUDR_576000", QPortSettings::BAUDR_576000);
	map.insert("BAUDR_921600", QPortSettings::BAUDR_921600);
#endif
#ifdef TNX_WINDOWS_SERIAL_PORT
	map.insert("BAUDR_14400", QPortSettings::BAUDR_14400);
	map.insert("BAUDR_56000", QPortSettings::BAUDR_56000);
	map.insert("BAUDR_128000", QPortSettings::BAUDR_128000);
	map.insert("BAUDR_256000", QPortSettings::BAUDR_256000);
#endif
	// baud rates supported by all OSs
	map.insert("BAUDR_110", QPortSettings::BAUDR_110);
	map.insert("BAUDR_300", QPortSettings::BAUDR_300);
	map.insert("BAUDR_600", QPortSettings::BAUDR_600);
	map.insert("BAUDR_1200", QPortSettings::BAUDR_1200);
	map.insert("BAUDR_2400", QPortSettings::BAUDR_2400);
	map.insert("BAUDR_4800", QPortSettings::BAUDR_4800);
	map.insert("BAUDR_9600", QPortSettings::BAUDR_9600);
	map.insert("BAUDR_19200", QPortSettings::BAUDR_19200);
	map.insert("BAUDR_38400", QPortSettings::BAUDR_38400);
	map.insert("BAUDR_57600", QPortSettings::BAUDR_57600);
	map.insert("BAUDR_115200", QPortSettings::BAUDR_115200);

	for (int i = 0; i < map.count(); i++) {
		ui->portBaudRateComboBox->addItem(map.keys().at(i), map.values().at(i));
	}
	ui->portBaudRateComboBox->setCurrentIndex(
				ui->portBaudRateComboBox->findText("BAUDR_9600"));

#ifdef Q_OS_LINUX
	ui->portNameLineEdit->setText("/dev/ttyUSB0");
#endif
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_startButton_clicked()
{
	QVariant baudVariant = ui->portBaudRateComboBox->itemData(
				ui->portBaudRateComboBox->currentIndex());
	QPortSettings::BaudRate baud = (QPortSettings::BaudRate)baudVariant.toInt();
	SignalData::instance().start(ui->portNameLineEdit->text(), baud);
}
