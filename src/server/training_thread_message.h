#ifndef TRINAING_THREAD_MESSAGE_H
#define TRINAING_THREAD_MESSAGE_H

#include <QString>
#include <QJsonObject>

#include "training_thread_item.h"

class TrainingThreadMessage {
	public:
		TrainingThreadMessage();
		TrainingThreadMessage(TrainingThreadItem *pItem);
		int id();
		QString bitid();
		void setMessage(QString message);
		QString message();
		bool equals(TrainingThreadMessage &msg);
		void setLastSuccessPersents(int lp);
		int lastSuccessPersents();
		QJsonObject toJson();
		void setPercent(int nPersent);
		int percent();
		void setMaxExperiments(int nMaxExperiments);
		int maxExperiments();
		void setCompletedExperiments(int nCompletedExperiments);
		int completedExperiments();
		
	private:
		QString m_sBitid;
		int m_nBitid;
		QString m_sMessage;
		int m_nLastSuccessPersents;
		int m_nPercent;
		int m_nMaxExperiments;
		int m_nCompletedExperiments;
};

#endif // TRINAING_THREAD_MESSAGE_H
