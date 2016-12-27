#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include <QVector>
#include <QObject>

#include <server.h>

class Game : public QObject {
		
	Q_OBJECT
		
	public:
		explicit Game (Server* app);
		
		bool addPlayer   (Client* client);
		void closeAdding ();
		
	public slots:
		void slotClientReady (qint32 id);
		//void slotClientDied  ();
		void slotSecondLeft  ();
		void slotGameTick    ();
		
	private:
		Server* server;
		qint32 status = 0;
		
		QVector <Client*> clients;
		QVector <bool> readyMask;
		
		QTimer* stopwatch;
		qint32 countdown = -1;
		qint32 minutes = 0, seconds = 0;
		bool isSingle = false;
		
		void startGame ();
		QTimer* gameTimer;
		
		QVector <std::pair <qreal, 
							qreal>> spawns;
		qint32 awidth  = 490;
		qint32 aheight = 490;
		
		struct Dron {
			qreal x = 0, y = 0; 
			qreal angle    = 0;
			qreal diagonal = 0;
			
			qreal health = 0, armor    = 0;
			qreal speed  = 0, rotate   = 0;
			qreal damage = 0, duration = 0;
			qreal bullet = 0, capacity = 0;
			qint32 width = 0, height   = 0;
			
			bool forward = false, 
				 left    = false, 
				 right   = false;
		};
		
		QVector <Dron*> players;
		bool playing = false;
		
		void moveDrons ();
		bool checkArenaBounds (QString asix, 
							   qreal x, 
							   qreal y, 
							   qreal angle, 
							   qreal diagonal,
							   qreal dalpha);
		qreal rad (qreal angle);
		
};

#endif // GAME_H