/*
 * LineCollectorLogicBuilder.h
 *
 *  Created on: Dec 25, 2018
 *      Author: temp
 */

#ifndef LINECOLLECTORLOGIC_BUILDER_LINECOLLECTORLOGICBUILDER_H_
#define LINECOLLECTORLOGIC_BUILDER_LINECOLLECTORLOGICBUILDER_H_

#include <vector>

#include "../LineCollectorLogic.h"

class LineCollectorLogicBuilder
{
public:
	static LineCollectorLogic BuildDefault();
	static vector<LineCollectorLogic> BuildForLocalHost(int numOfCollectors);
};

#endif /* LINECOLLECTORLOGIC_BUILDER_LINECOLLECTORLOGICBUILDER_H_ */
