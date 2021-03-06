#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <array>
#include <iostream>

#include <QTimer>
#include <QWidget>

#include <dronmodel.h>
#include <gamescene.h>
#include <application.h>
#include <bulletmodel.h>

namespace Ui {
	class gameform;
}

class GameForm : public QWidget {
		
	Q_OBJECT
		
	public:
		explicit GameForm (Application* app);
		~GameForm         ();
		void setDefault   ();
		
		qint32 getAreaWidth  ();
		qint32 getAreaHeight ();
		
		bool isActiveButton (int button);
		void updateData (QString target);
		
		qint32 gameId;
		
		QVector <QPointF> coords;
		QVector <qreal>   angles;
		QVector <qreal>   turretAngles;
		
		QVector <BulletModel*> bullets;
		
	signals:
		void signalSwitchForm (int form);
		
	public slots:
		void slotDisconnected ();
		
	private slots:
		void slotButton (int button, int action);
		void slotReceivedData (QByteArray data);
		void slotSendButtons  ();
		
		void slotSetTarget    (QPointF);
		void slotMakeShot     (int);
		
	private:
		Ui::gameform* ui;
		Application*  app;
		GameScene*    scene;
		qint32        identf;
		
		struct Buttons {
			std::array <bool, 10> buffer;
			
			void reset () {
				for (int i = 0; i < buffer.size (); i ++) {
					buffer.at (i) = false;
				}
			}
			
			bool isAcive (int button) {
				if (button == Qt::Key_W) return buffer [0];
				if (button == Qt::Key_A) return buffer [1];
				if (button == Qt::Key_S) return buffer [2];
				if (button == Qt::Key_D) return buffer [3];
				
				return false;
			}
			
			void setActive (int button, bool state) {
				if (button == Qt::Key_W) buffer [0] = state;
				if (button == Qt::Key_A) buffer [1] = state;
				if (button == Qt::Key_S) buffer [2] = state;
				if (button == Qt::Key_D) buffer [3] = state;
			}
		};
		
		Buttons buttons;
		
		QVector <std::pair <qint32, qint32>> heath;
		QVector <std::pair <qint32, qint32>> points;
		QVector <DronModel*> drons;
		
		QPointF target;
		
		bool playing = false;
		QTimer* sendButtons;
		
};

#endif // GAMEFORM_H
