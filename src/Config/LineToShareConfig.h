/*
 * LineToShareConfig.h
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#ifndef CONFIG_LINETOSHARECONFIG_H_
#define CONFIG_LINETOSHARECONFIG_H_

#include <string>

using namespace std;

struct LineToShareConfig
{
public:
	const string& getLine() const;
	void setLine(const string& line);
	int getLineNumber() const;
	void setLineNumber(int lineNumber);

private:

	string m_line;
	int m_lineNumber;


};

inline const string& LineToShareConfig::getLine() const {
	return m_line;
}

inline void LineToShareConfig::setLine(const string& line) {
	m_line = line;
}

inline int LineToShareConfig::getLineNumber() const {
	return m_lineNumber;
}

inline void LineToShareConfig::setLineNumber(int lineNumber) {
	m_lineNumber = lineNumber;
}

#endif /* CONFIG_LINETOSHARECONFIG_H_ */
