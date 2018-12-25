/*
 * LineCollectorConfigCollection.h
 *
 *  Created on: Dec 24, 2018
 *      Author: temp
 */

#ifndef CONFIG_LINECOLLECTORCONFIGCOLLECTION_H_
#define CONFIG_LINECOLLECTORCONFIGCOLLECTION_H_

#include "ThreadConfig.h"
#include "NetworkConfig.h"
#include "LineToShareConfig.h"

struct LineCollectorConfigCollection
{

	ThreadConfig m_threadConfig;
	NetworkConfig m_networkConfig;
	LineToShareConfig m_lineToShareConfig;

};

#endif /* CONFIG_LINECOLLECTORCONFIGCOLLECTION_H_ */
