/*
 * NetworkConfig.h
 *
 *  Created on: Dec 20, 2018
 *      Author: temp
 */

#ifndef CONFIG_NETWORKCONFIG_H_
#define CONFIG_NETWORKCONFIG_H_

#include <string>

using namespace std;

class NetworkConfig
{
public:
	string getEndIp() const;
	void setEndIp(string endIp);
	int getEndPort() const;
	void setEndPort(int endPort);
	string getStartIp() const;
	void setStartIp(string startIp);
	int getStartPort() const;
	void setStartPort(int startPort);

private:
	string m_startIP,m_endIP;
	int m_startPort,m_endPort;
};

inline string NetworkConfig::getEndIp() const {
	return m_endIP;
}

inline void NetworkConfig::setEndIp(string endIp) {
	m_endIP = endIp;
}

inline int NetworkConfig::getEndPort() const {
	return m_endPort;
}

inline void NetworkConfig::setEndPort(int endPort) {
	m_endPort = endPort;
}

inline string NetworkConfig::getStartIp() const {
	return m_startIP;
}

inline void NetworkConfig::setStartIp(string startIp) {
	m_startIP = startIp;
}

inline int NetworkConfig::getStartPort() const {
	return m_startPort;
}

inline void NetworkConfig::setStartPort(int startPort) {
	m_startPort = startPort;
}

#endif /* CONFIG_NETWORKCONFIG_H_ */
