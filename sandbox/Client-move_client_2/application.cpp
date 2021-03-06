#include "application.h"
#include "ui_application.h"

Application::Application (QWidget *parent) : QMainWindow (parent),
												ui (new Ui::Application) {
	QMainWindow::setWindowFlags (Qt::CustomizeWindowHint);
	
	this->socket = new QTcpSocket (this);
	this->connected = false;
	
	ui->setupUi (this);
	slotSwitchForm (1);
}

void Application::connectHost (QString host, qint32 port) {
	std::cout << "[CLIENT] Connecting to " 
			  << host.toStdString () 
			  << ":" << port 
			  << std::endl;
	
	socket->connectToHost (host, port);
	
	connect (socket, &QTcpSocket::connected,
			 this, &Application::slotConnected);
	connect (socket, &QTcpSocket::disconnected,
			 this, &Application::slotDisconnected);
	connect (socket, &QTcpSocket::readyRead,
			 this, &Application::slotReadStream);
}

void Application::disconnectHost () {
	std::cout << "[CLIENT] Disconnects from host" 
			  << std::endl;
	socket->close ();
}

void Application::slotReadStream () {
	while (socket->bytesAvailable () > 0) {
		bufferArray.append (socket->readAll ());
		
		while (bufferArray.size () >= sizeof (qint32) && need == 0) {
			QDataStream input (&bufferArray, QIODevice::ReadOnly);
			/*Reading size of input data line*/ input >> need;
			bufferArray.remove (0, sizeof (qint32));
			
			if (bufferArray.size () >= need && need != 0) {
				//std::cout << bufferArray.left (need).toStdString () 
				//		  << std::endl;
				emit signalReceivedData (bufferArray.left (need));
				bufferArray.remove (0, need);
				need = 0;
			}
		}
		
		//if (bufferArray.size () >= sizeof (qint32) && need == 0) {
		//	QDataStream input (&bufferArray, QIODevice::ReadOnly);
		//	/*Reading size of input data line*/ input >> need;
		//	bufferArray.remove (0, sizeof (qint32));
		//}
		
		//if (bufferArray.size () >= need && need != 0) {
		//	emit signalReceivedData (bufferArray.left (need));
		//	bufferArray.remove (0, need);
		//	need = 0;
		//}
	}
}

void Application::closeApplication () {
	disconnectHost ();
	this->close ();
}

bool Application::isConnected () {
	return this->connected;
}

void Application::writeInSocket (QByteArray data) {
	QByteArray length;
	QDataStream lenout (&length, QIODevice::WriteOnly);
	lenout << data.size ();
	
	socket->write (length);
	socket->write (data);
}

void Application::slotConnected () {
	std::cout << "[CLIENT] Connected to server" 
			  << std::endl;
	
	connected = true;
}

void Application::slotDisconnected () {
	this->connected = false;
}

void Application::slotSwitchForm (int form) {
	ui->centralWidget->deleteLater ();
	
	if (form == 1) {
		UserForm* widget = new UserForm (this);
		
		ui->centralWidget->setStyle (widget->style ());
		this->setFixedSize (widget->size ());
		ui->centralWidget = widget;
		ui->centralWidget->show ();
		
		connect (widget, &UserForm::signalSwitchForm,
				 this, &Application::slotSwitchForm);
		connect (socket, &QTcpSocket::connected,
				 widget, &UserForm::slotConnected);
		connect (socket, &QTcpSocket::disconnected,
				 widget, &UserForm::slotDisconnected);
	} else if (form == 2) {
		QueueForm* widget = new QueueForm (this);
		
		ui->centralWidget->setStyle (widget->style ());
		this->setFixedSize (widget->size ());
		ui->centralWidget = widget;
		ui->centralWidget->show ();
		
		connect (widget, &QueueForm::signalSwitchForm,
				 this, &Application::slotSwitchForm);
		connect (socket, &QTcpSocket::disconnected,
				 widget, &QueueForm::slotDisconnected);
	} else if (form == 3) {
		GameForm* widget = new GameForm (this);
		
		ui->centralWidget->setStyle (widget->style ());
		this->setFixedSize (widget->size ());
		ui->centralWidget = widget;
		ui->centralWidget->show ();
		
		connect (widget, &GameForm::signalSwitchForm,
				 this, &Application::slotSwitchForm);
		connect (socket, &QTcpSocket::disconnected,
				 widget, &GameForm::slotDisconnected);
	}
}

Application::~Application () {
	delete ui;
}
