#ifndef DRONMODEL_H
#define DRONMODEL_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

class GameForm;

class DronModel : public QObject, public QGraphicsItem {
		
	Q_OBJECT
		
	public:
		explicit DronModel (GameForm* form, qint32 number);
		
	protected:
		QRectF boundingRect () const;
		void paint (QPainter* painter,
					const QStyleOptionGraphicsItem* option,
					QWidget* widget);
		
	private:
		qint32 width, height;
		qint32 number;
		
		QRectF    bounds;
		GameForm* form;
		
};

#endif // DRONMODEL_H
