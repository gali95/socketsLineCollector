/*
 * LineCollection.h
 *
 *  Created on: Dec 23, 2018
 *      Author: temp
 */

#ifndef LINES_LINECOLLECTION_H_
#define LINES_LINECOLLECTION_H_

#include <map>

using namespace std;

class LineCollection
{
public:
	bool HasLine(int lineNumber);
	bool AddLine(int lineNumber, string Line);
	bool AddShareableLine(int lineNumber, string Line);
	map<int, string> GetLines();

private:

	map<int, string> m_lines;
	int m_indexOfLineToBeShared;

};

#endif /* LINES_LINECOLLECTION_H_ */
