#pragma once

class Command {
public:
	bool isDone = false;
public:
	virtual void Execute() { isDone = true; }
};
