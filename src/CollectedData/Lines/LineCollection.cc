/*
 * LineCollection.cc
 *
 *  Created on: Dec 23, 2018
 *      Author: temp
 */

#include "LineCollection.h"
#include <sstream>
#include "../../Log/Logger.h"

using namespace std;

bool LineCollection::HasLine(int lineNumber) {

	stringstream logStream;
	logStream << "Checking if there is line with number: " << lineNumber ;
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	return (m_lines.find(lineNumber) != m_lines.end());

}

bool LineCollection::AddLine(int lineNumber, string Line) {

	stringstream logStream;
	logStream << "LineCollection::AddLine start ";
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	logStream.clear();
	if(lineNumber < 1)
	{
		return false;
	}
	else if(HasLine(lineNumber))
	{
		return false;
	}
	else
	{
		logStream << "Added line with number: " << lineNumber << " and content: " << Line;
		Logger::GetLogger()->Log({"debug1"},logStream.str());
		m_lines[lineNumber] = Line;
		return true;
	}

}

bool LineCollection::AddShareableLine(int lineNumber, string Line) {

	stringstream logStream;
	logStream << "LineCollection::AddShareableLine start ";
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	logStream.clear();
	if(m_indexOfLineToBeShared != -1)
	{
		return false;
	}
	else
	{
		if(AddLine(lineNumber,Line))
		{
			logStream << "Added shareable line with number: " << lineNumber << " and content: " << Line;
			Logger::GetLogger()->Log({"debug1"},logStream.str());
			m_indexOfLineToBeShared = lineNumber;
			return true;
		}
		else
		{
			return false;
		}
	}

}

map<int, string> &LineCollection::GetLines() {

	return m_lines;

}

string LineCollection::GetLine(int lineNumber) {

	stringstream logStream;
	logStream << "Getting line with number: " << lineNumber ;
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	return m_lines[lineNumber];

}

LineCollection::LineCollection() {

	m_indexOfLineToBeShared = -1;

}

int LineCollection::GetNumOfShareableLine() {

	stringstream logStream;
	logStream << "Getting number of shareable line (its " << m_indexOfLineToBeShared << ").";
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	return m_indexOfLineToBeShared;
}

string LineCollection::GetShareableLine() {

	stringstream logStream;
	logStream << "Getting shareable line: " << m_lines[m_indexOfLineToBeShared] ;
	Logger::GetLogger()->Log({"debug1"},logStream.str());
	return m_lines[m_indexOfLineToBeShared];

}
