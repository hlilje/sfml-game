// Class representing a goal hole, i.e. the hole in which you must fit
// your object to win.

#pragma once
#include "VisibleGameObject.h"

class GoalHole: public VisibleGameObject
{
public:
	GoalHole(void);
	~GoalHole(void);

	void Update(float);

private:

};