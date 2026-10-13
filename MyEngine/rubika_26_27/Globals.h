#pragma once

class DebugMgr;
class Logger;
class TextureMgr;

class Globals
{
public:
	Globals();
	~Globals();

	void Init();
	void Shut();
	void Destroy();

	void IncrementFrameCount();

	unsigned long long FrameCount;

	DebugMgr* DebugMgr;
	Logger* Logger;
	TextureMgr* TextureManager;
};

extern Globals gData;