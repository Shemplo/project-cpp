#ifndef MACHINEINFO_H
#define MACHINEINFO_H

#include <QHash>

class MachineInfo {
		
	public:
		MachineInfo ();
		
		// Structure of keeping
		// data about machine (...)
		struct Machine {
			qint32 id    = 0;
			qint32 level = 0;
			QString name;
			
			qreal health = 0, armor    = 0;
			qreal speed  = 0, rotate   = 0;
			qreal damage = 0, duration = 0;
			qreal bullet = 0, capacity = 0;
			qreal penetration = 0;
			
			qint32 width = 40, height = 20;
		};
		
		// Get informaton about machine
		// with given number (id)
		Machine getInfo (qint32 id);
		
	private:
		QHash <qint32, Machine> machines;
		
};

#endif // MACHINEINFO_H
