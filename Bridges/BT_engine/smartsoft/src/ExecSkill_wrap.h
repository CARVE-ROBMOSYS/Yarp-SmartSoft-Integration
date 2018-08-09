#ifndef EXECUTESKILL_WRAP_H
#define EXECUTESKILL_WRAP_H

enum Status {RUNNING, FAILURE, SUCCESS, ERROR};

extern "C"
{
	int ExecuteSkill(const char *name);
	void ResetSkill(const char *name);
}


#endif // EXECUTESKILL_WRAP_H
