/*
 * Config.h
 *
 *  Created on: Dec 20, 2018
 *      Author: temp
 */

#ifndef CONFIG_THREADCONFIG_H_
#define CONFIG_THREADCONFIG_H_


class ThreadConfig
{
public:
	int getNumOfClients() const;
	void setNumOfClients(int numOfClients);
	int getNumOfServers() const;
	void setNumOfServers(int numOfServers);

private:
	bool IsConfigOk();
	int m_numOfServers;
	int m_numOfClients;
};

inline int ThreadConfig::getNumOfClients() const {
	return m_numOfClients;
}

inline void ThreadConfig::setNumOfClients(int numOfClients) {
	m_numOfClients = numOfClients;
}

inline int ThreadConfig::getNumOfServers() const {
	return m_numOfServers;
}

inline void ThreadConfig::setNumOfServers(int numOfServers) {
	m_numOfServers = numOfServers;
}

#endif /* CONFIG_THREADCONFIG_H_ */
