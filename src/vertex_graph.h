#ifndef VERTEX_GRAPH_H
#define VERTEX_GRAPH_H


#include "interfaces/ivertex_in.h"
#include "interfaces/ivertex_out.h"

#include <QString>
#include <QVector>

namespace reversehash {
	class VertexGraph
    {
        public:
			VertexGraph(int nInputs);
			void genBase();
			
			bool out();
			void setIn(const QVector<bool> &in);
			QString conv2dot();
            bool saveToFile(QString filename);
            bool saveToStream(QDataStream &stream);
            bool saveDot(QString filename);
            bool loadFromFile(QString filename);
			bool loadFromStream(QDataStream &stream);
           
			void setLastSuccessPersents(int nVal);
			int lastSuccessPersents();
			
			VertexGraph *clone();
			void copy(VertexGraph *pVertexGraph);
           
			// modifications
			void randomChanges(int n);
			void changeRandomOperation();
			void swapRandomVertexts();
           
		private:
            void writeHeader(QDataStream &stream, int nVersion);
            bool readHeader(QDataStream &stream, int &nVersion);
            void writeDataAsVersion1(QDataStream &stream);
            void readDataAsVersion1(QDataStream &stream);
            IVertexOut *findVertexByName(QString name);

			QVector<IVertexIn *> m_vVertexIn;
			QVector<IVertexOut *> m_vVertexes;
			IVertexOut *m_pOut;
			int m_nInputs;
            int m_nVersion;
            int m_nLastSuccessPersents;
    };
}

#endif // VERTEX_GRAPH_H