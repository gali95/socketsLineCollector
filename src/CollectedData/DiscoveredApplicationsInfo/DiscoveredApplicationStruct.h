/*
 * DiscoveredApplicationStruct.h
 *
 *  Created on: Jan 6, 2019
 *      Author: temp
 */

#ifndef COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONSTRUCT_H_
#define COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONSTRUCT_H_

#include <string>

using namespace std;

struct DiscoveredApplicationStruct
{

	string serverOrClient;
	bool compatibleWithOurApp;

};

#endif /* COLLECTEDDATA_DISCOVEREDAPPLICATIONSINFO_DISCOVEREDAPPLICATIONSTRUCT_H_ */
