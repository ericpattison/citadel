#ifndef _UPDATER_H_
#define _UPDATER_H_

#include "../../keep/types.h"

class Updater {
public:
	virtual Callback handler() = 0;
};

#endif