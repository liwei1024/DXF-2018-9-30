#pragma once
class Traverse
{
public:
	Traverse();
	~Traverse();
	ObjectInfo TraverseObjectInfo(DWORD ObjectPointer);
	MapInfo TraverseMapInfo();
	KnapsackInfo TraverseKnapsackInfo();
	TaskInfo TraverseAllTaskInfo();
	TaskObject TraverseTaskObject(DWORD ObjectPointer);
	TaskInfo TraverseReceivedTaskInfo();
	VOID OutputMapInfo();
	VOID OutputTaskInfo(int type);
};

