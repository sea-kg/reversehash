#include "helpers.h"
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include <QCryptographicHash>

namespace reverse_hash {


}

int loadPersent(QString filename){
	int nPersent = 0;
	// load persent
	QFile file(filename);
	if (!file.exists()) {
		qDebug().noquote().nospace() << "Helpers/loadPersent:  File did not exists: " << filename;
	}else{
		if (!file.open(QIODevice::ReadOnly) ) {
			qDebug().noquote().nospace() << "Helpers/loadPersent: Could not open file " << filename;
		}else{
			QDataStream stream(&file);
			stream >> nPersent;
		}
	}
	return nPersent;
}

void savePersent(QString filename, int nPersent){
	QFile file(filename);
	if (file.exists()) {
		file.remove();
	}
	if ( !file.open(QIODevice::WriteOnly) ) {
		qDebug().noquote().nospace() << "Helpers/savePersent: Could not write file: " << filename;
		return;
	}
	QDataStream stream( &file );
	stream << nPersent;
	file.close();
}

QString prepareName(int bitid){
    return QString::number(bitid).rightJustified(3, '0');
}

QString prepareSubdir(int bitid){
    QString m_sBitid = QString::number(bitid).rightJustified(3, '0');
    return m_sBitid[0] + "/" + m_sBitid[1] + "/" + m_sBitid[2];
}