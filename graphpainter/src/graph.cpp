#include "graph.h"
#include <iostream>
#include <QTextStream>
#include <QFile>

namespace graph {

// ----------------------------------------------------------------

Line::Line() {
	m_sFrom = "";
	m_sTo = "";
	m_sLabel = "";
}

// ----------------------------------------------------------------

Line::Line(QString sFrom, QString sTo, QString sLabel) {
	m_sFrom = sFrom;
	m_sTo = sTo;
	m_sLabel = sLabel;
}

// ----------------------------------------------------------------

Line::Line(QString sFrom, QString sTo) {
	m_sFrom = sFrom;
	m_sTo = sTo;
	m_sLabel = "";
}

// ----------------------------------------------------------------

QString Line::getDotString() {
	return m_sFrom + " -> " + m_sTo + " [ label = \"" + m_sLabel + "\" ];";
}

// ----------------------------------------------------------------

QString Line::from() const {
	return m_sFrom;
}

// ----------------------------------------------------------------

QString Line::to() const {
	return m_sTo;
}

// ----------------------------------------------------------------

QString Line::label() const {
	return m_sLabel;
}

// ----------------------------------------------------------------

bool Line::equal(const Line &line) {
	return line.from() == m_sFrom && line.to() == m_sTo;
}

// ----------------------------------------------------------------

Graph::Graph() {
	// nothing
}

// ----------------------------------------------------------------

void Graph::addPoint(QString name) {
	if (!m_vPoints.contains(name))
		m_vPoints.push_back(name);
}

// ----------------------------------------------------------------

void Graph::addLine(Line line) {
	if (!m_vPoints.contains(line.from()))
		m_vPoints.push_back(line.from());
		
	if (!m_vPoints.contains(line.to()))
		m_vPoints.push_back(line.to());

	if (!containsLine(line))
		m_vLines.push_back(line);
}

// ----------------------------------------------------------------

void Graph::removeLine(Line line) {
	for (int i = 0; i < m_vLines.size(); i++) {
		if (m_vLines[i].equal(line)) {
			m_vLines.remove(i);
			return;
		}
	}
}

// ----------------------------------------------------------------

bool Graph::containsLine(Line line) {
	for (int i = 0; i < m_vLines.size(); i++) {
		if (m_vLines[i].equal(line))
			return true;
	}
	return false;
}

// ----------------------------------------------------------------

bool Graph::containsPoint(QString name) {
	return m_vPoints.contains(name);
}

// ----------------------------------------------------------------

void Graph::searchParents(QString name, QVector<QString> &parents) {
	for (int i = 0; i < m_vLines.size(); i++) {
		if (m_vLines[i].to() == name)
			parents.push_back(m_vLines[i].from());
	}
}

// ----------------------------------------------------------------

void Graph::searchLinesTo(QString name, QVector<Line> &lines) {
	for (int i = 0; i < m_vLines.size(); i++) {
		if (m_vLines[i].to() == name)
			lines.push_back(Line(m_vLines[i].from(), m_vLines[i].to(), m_vLines[i].label()));
	}
}

// ----------------------------------------------------------------

void Graph::searchChildren(QString name, QVector<QString> &children) {
	for (int i = 0; i < m_vLines.size(); i++) {
		if (m_vLines[i].from() == name)
			children.push_back(m_vLines[i].to());
	}
}

// ----------------------------------------------------------------

void Graph::removeCycles(QString rootName) {
	QVector<QString> vPath;
	vPath.push_back(rootName);
	removeCyclesRecoursive(vPath);
}

// ----------------------------------------------------------------

void Graph::removeCyclesRecoursive(QVector<QString> vPath) {
	QString node = vPath[vPath.size()-1];

	QVector<QString> parents;
	this->searchParents(node, parents);
	if (parents.size() == 0) {
		return;
	}
	
	for (int i = 0; i < parents.size(); i++) {
		QString parentNode = parents[i];
		if (vPath.contains(parentNode)) {
			std::cout << " found cycl! and removed. Path:";
			for (int g = 0; g < vPath.size(); g++) {
				std::cout << vPath[g].toStdString() << "/";
			}
			std::cout << "In link: " << parentNode.toStdString() << " -> " << node.toStdString() << "\n";
			this->removeLine(Line(parentNode, node));
			return;
		} else {
			vPath.push_back(parentNode);
			removeCyclesRecoursive(vPath);
			vPath.pop_back();
		}
	}
}

// ----------------------------------------------------------------

void Graph::exportToFileDot(QString filename) {
	QFile file(filename);

	if (file.exists()) {
		file.remove();
	}
	
	if ( file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
		QTextStream stream( &file );
		stream << "digraph some_graph {" << "\n";
		for (int i = 0; i < m_vPoints.size(); i++) {
			stream << "\t" << m_vPoints[i] << ";" << "\n";
		}
		for (int i = 0; i < m_vLines.size(); i++) {
			stream << "\t" << m_vLines[i].getDotString() << "\n";
		}
		stream << "}" << "\n";
		file.close();
	}
}

// ----------------------------------------------------------------

QString Graph::generateOperation() {
	int nOper = qrand() % 3;
	QString sResult = "";
	if (nOper == 0) {
		sResult = "&";
	} else if (nOper == 1) {
		sResult = "|";
	} else if (nOper == 2) {
		sResult = "^";
	}
	return sResult;
}

// ----------------------------------------------------------------

void Graph::modifyRandomGraph() {

	// if o00 has a lot of lines
	{
		QVector<QString> parents;
		this->searchParents("o00", parents);
		if (parents.size() > 5) {
			for (int i = 0; i < parents.size()-5; i++) {
				this->removeLine(graph::Line(parents[0], "o00"));
				QString m = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
				this->addLine(graph::Line(parents[0], m, this->generateOperation()));
				this->addLine(graph::Line(m, "o00", this->generateOperation()));
			}
		}
	}

	// remove random lines
	int nCount = 150;
	for (int i = 0; i < nCount; i++) {
		QString m0 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		QString m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		while (m0 == m1) {
			m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		}
		QString in = "i" + QString::number(qrand() % 128, 16).rightJustified(2, '0');
		int v = qrand() % 4;

		if (v == 0) {
			this->removeLine(graph::Line(in, m0));
		} else if (v == 1) {
			this->removeLine(graph::Line(in, m1));
		} else if (v == 2) {
			this->removeLine(graph::Line(m0, m1));
		} else if (v == 3) {
			this->removeLine(graph::Line(m1, m0));
		}
	}
	
	// add random lines
	for (int i = 0; i < nCount; i++) {
		QString m0 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		QString m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		while (m0 == m1) {
			m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		}
		QString in = "i" + QString::number(qrand() % 128, 16).rightJustified(2, '0');
		int v = qrand() % 4;

		if (v == 0) {
			this->addLine(graph::Line(in, m0, this->generateOperation()));
		} else if (v == 1) {
			this->addLine(graph::Line(in, m1, this->generateOperation()));
		} else if (v == 2) {
			this->addLine(graph::Line(m0, m1, this->generateOperation()));
		} else if (v == 3) {
			this->addLine(graph::Line(m1, m0, this->generateOperation()));
		}
	}

	
	// if m has not parents
	for (int i = 0; i < 1000; i++) {
		QString m = "m" + QString::number(i, 16).rightJustified(3, '0');
		if (this->containsPoint(m)) {
			QVector<QString> parents;
			this->searchParents(m, parents);
			if (parents.size() == 0) {
				QString in = "i" + QString::number(qrand() % 128, 16).rightJustified(2, '0');
				this->addLine(graph::Line(in, m, this->generateOperation()));
			}
		}
	}
	
	// if i has not children
	for (int i = 0; i < 128; i++) {
		QString in = "i" + QString::number(i, 16).rightJustified(2, '0');
		QVector<QString> children;
		this->searchChildren(in, children);
		if (children.size() == 0) {
			QString m = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
			this->addLine(graph::Line(in, m, this->generateOperation()));
		}
	}

	// if m has not children
	for (int i = 0; i < 1000; i++) {
		QString m = "m" + QString::number(i, 16).rightJustified(3, '0');
		if (this->containsPoint(m)) {
			QVector<QString> children;
			this->searchChildren(m, children);
			if (children.size() == 0) {
				this->addLine(graph::Line(m, "o00", this->generateOperation()));
			}
		}
	}

	this->removeCycles("o00");
}

// ----------------------------------------------------------------

void Graph::generateRandomGraph() {
	for (int i = 0; i < 128; i++) {
		QString pointName = "i" + QString::number(i, 16).rightJustified(2, '0');
		this->addPoint(pointName);
	}

	int nCount = 1000;

	for (int i = 0; i < nCount; i++) {
		QString m0 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		QString m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		while (m0 == m1) {
			m1 = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
		}
		QString in = "i" + QString::number(qrand() % 128, 16).rightJustified(2, '0');
		int v = qrand() % 4;

		if (v == 0) {
			this->addLine(graph::Line(in, m0, this->generateOperation()));
		} else if (v == 1) {
			this->addLine(graph::Line(in, m1, this->generateOperation()));
		} else if (v == 2) {
			this->addLine(graph::Line(m0, m1, this->generateOperation()));
		} else if (v == 3) {
			this->addLine(graph::Line(m1, m0, this->generateOperation()));
		}
	}

	// if m has not parents
	for (int i = 0; i < nCount; i++) {
		QString m = "m" + QString::number(i, 16).rightJustified(3, '0');
		if (this->containsPoint(m)) {
			QVector<QString> parents;
			this->searchParents(m, parents);
			if (parents.size() == 0) {
				QString in = "i" + QString::number(qrand() % 128, 16).rightJustified(2, '0');
				this->addLine(graph::Line(in, m, this->generateOperation()));
			}
		}
	}
	
	// if i has not children
	for (int i = 0; i < 128; i++) {
		QString in = "i" + QString::number(i, 16).rightJustified(2, '0');
		QVector<QString> children;
		this->searchChildren(in, children);
		if (children.size() == 0) {
			QString m = "m" + QString::number(qrand() % 1000, 16).rightJustified(3, '0');
			this->addLine(graph::Line(in, m, this->generateOperation()));
		}
	}
	
	// if m has not children
	this->addPoint("o00");
	for (int i = 0; i < nCount; i++) {
		QString m = "m" + QString::number(i, 16).rightJustified(3, '0');
		if (this->containsPoint(m)) {
			QVector<QString> children;
			this->searchChildren(m, children);
			if (children.size() == 0) {
				this->addLine(graph::Line(m, "o00", this->generateOperation()));
			}
		}
	}

	
	this->removeCycles("o00");
}

// ----------------------------------------------------------------

void Graph::save(QString filename) {
	QFile file(filename);
	if (file.exists()) {
		file.remove();
	}
	if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
		std::cout << "error save " << filename.toStdString() << "\n";
		return;
	}
	QTextStream stream( &file );
	for (int i = 0; i < m_vPoints.size(); i++) {
		stream << "point " << m_vPoints[i] << "\n";
	}
	for (int i = 0; i < m_vLines.size(); i++) {
		stream << "line " << m_vLines[i].from() << " " << m_vLines[i].to() << " " << m_vLines[i].label() << "\n";
	}
	file.close();
}

// ----------------------------------------------------------------

void Graph::load(QString filename) {
	QFile file(filename);

	if(!file.open(QIODevice::ReadOnly)) {
		std::cout << "error load " << filename.toStdString() << "\n";
		return;
	}
	m_vPoints.clear();
	m_vLines.clear();
	
	QTextStream in(&file);
	while(!in.atEnd()) {
		QString line = in.readLine();    
		QStringList command = line.split(" ");
		if (command.size() > 0) {
			if (command.at(0) == "point") {
				this->addPoint(command.at(1));
			} else if (command.at(0) == "line" && command.size() == 4) {
				this->addLine(Line(command.at(1), command.at(2), command.at(3)));
			} else {
				std::cout << "uknown command: " << command.at(0).toStdString() << "\n";
			}
		} else {
			std::cout << "error command: " << line.toStdString() << "\n";
		}
	}
	file.close();
}

// ----------------------------------------------------------------		

const QVector<QString> &Graph::points() {
	return m_vPoints;
}

// ----------------------------------------------------------------

const QVector<Line> &Graph::lines() {
	return m_vLines;
}

// ----------------------------------------------------------------

Calculate::Calculate(Graph *pGraph) {
	m_pGraph = pGraph;
}

// ----------------------------------------------------------------

bool Calculate::calc(QString node, QMap<QString, bool> input) {
	m_mapCache.clear();
	foreach (QString key, input.keys()) {
		m_mapCache[key] = input.value(key);
	}
	return getValue(node);
}

// ----------------------------------------------------------------

bool Calculate::getValue(QString node) {
	bool bResult = false;
	if (m_mapCache.contains(node)) {
		bResult = m_mapCache[node];
	} else {
		QVector<Line> lines;
		m_pGraph->searchLinesTo(node, lines);
		if (lines.size() > 0) {
			for (int i = 0; i < lines.size(); i++) {
				QString sOper = lines[i].label();
				bool bValue = getValue(lines[i].from());
				if (sOper == "|") {
					bResult = bResult | bValue;
				} else if (sOper == "&") {
					bResult = bResult & bValue;
				} else if (sOper == "^") {
					bResult = bResult ^ bValue;
				}
			}
			m_mapCache[node] = bResult;
		}
	}
	return bResult;
}

// ----------------------------------------------------------------

void Calculate::setValue(QString node, bool bValue) {
	m_mapCache[node] = bValue;
}

// ----------------------------------------------------------------

}; // namespace graph
