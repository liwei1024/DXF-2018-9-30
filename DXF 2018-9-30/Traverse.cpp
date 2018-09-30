#include "pch.h"
#include "Traverse.h"
#include "Utils.h"

using namespace std;

Traverse::Traverse()
{
}


Traverse::~Traverse()
{
}

ObjectInfo Traverse::TraverseObjectInfo(DWORD ObjectPointer) 
{
	ObjectInfo _ObjectInfo;
	DWORD PosPointer;
	_ObjectInfo.address = ObjectPointer;
	_ObjectInfo.type = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.camp = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.health_point = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.code = _Process.ReadInteger(ObjectPointer + __类型偏移);
	_ObjectInfo.name = _Process.ReadString(_Process.ReadInteger(ObjectPointer + __名称偏移), 100);
	if (_ObjectInfo.type == 273)
	{
		PosPointer = _Process.ReadInteger(_Process.ReadInteger(__人物基址) + __人物坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0x10);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 0x14);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 0x18);
	}
	else {
		PosPointer = _Process.ReadInteger(_Process.ReadInteger(__人物基址) + __坐标偏移);
		_ObjectInfo.pos.x = (int)_Process.ReadFloat(PosPointer + 0);
		_ObjectInfo.pos.y = (int)_Process.ReadFloat(PosPointer + 4);
		_ObjectInfo.pos.z = (int)_Process.ReadFloat(PosPointer + 8);
	}
	return _ObjectInfo;
}

MapInfo Traverse::TraverseMapInfo() 
{
	MapInfo _MapInfo;
	_MapInfo.start_address = _Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __首地址);
	_MapInfo.end_address = _Process.ReadInteger(_Process.ReadOfset(__人物基址, { __地图偏移 }) + __尾地址);
	_MapInfo.object_count = (_MapInfo.end_address - _MapInfo.start_address) / 4;
	return _MapInfo;
}

KnapsackInfo Traverse::TraverseKnapsackInfo() 
{
	KnapsackInfo _KnapsackInfo;
	_KnapsackInfo.knapsack_address = _Process.ReadInteger(__背包基址);
	_KnapsackInfo.knapsack_start_address = _Process.ReadInteger(_KnapsackInfo.knapsack_address + 88);
	_KnapsackInfo.goods_start_address = _KnapsackInfo.knapsack_start_address + 36;
	return _KnapsackInfo;
}


TaskInfo Traverse::TraverseAllTaskInfo()
{
	TaskInfo _TaskInfo;
	_TaskInfo.start_address = _Process.ReadOfset(__任务基址, { 104 });
	_TaskInfo.end_address = _Process.ReadOfset(__任务基址, { 108 });
	_TaskInfo.task_count = (_TaskInfo.end_address - _TaskInfo.start_address) / 4;
	return _TaskInfo;
}

TaskObject Traverse::TraverseTaskObject(DWORD ObjectPointer)
{
	TaskObject _TaskObject;
	_TaskObject.address = ObjectPointer;
	_TaskObject.task_id = _Process.ReadInteger(ObjectPointer);
	_TaskObject.type = _Process.ReadInteger(ObjectPointer + 308);
	_TaskObject.copy_id = _Process.ReadInteger(ObjectPointer + 676);
	_TaskObject.materials = _Process.ReadInteger(ObjectPointer + 1424);
	_TaskObject.task_length = _Process.ReadInteger(ObjectPointer + 28);
	_TaskObject.condition_type = _Process.ReadString(_Process.ReadInteger(ObjectPointer + 720),100);
	if (_TaskObject.task_length > 7)
	{
		_Process.ReadString(_Process.ReadInteger(ObjectPointer + 8), 100);
	}
	else {
		_Process.ReadString(ObjectPointer + 8, 100);
	}
	return _TaskObject;
}


TaskInfo Traverse::TraverseReceivedTaskInfo()
{
	TaskInfo _TaskInfo;
	_TaskInfo.start_address = _Process.ReadOfset(__任务基址, { 8 });
	_TaskInfo.end_address = _Process.ReadOfset(__任务基址, { 12 });
	_TaskInfo.task_count = (_TaskInfo.end_address - _TaskInfo.start_address) / 12;
	return _TaskInfo;
}




VOID Traverse::OutputMapInfo()
{
	string str;
	ObjectInfo _ObjectInfo;
	MapInfo _MapInfo;

	_MapInfo = TraverseMapInfo();
	for (size_t i = 0; i < _MapInfo.object_count; i++)
	{
		_ObjectInfo = TraverseObjectInfo(_MapInfo.start_address + i * 4);
		str += "地址:" + FormatString("0x%8x", _ObjectInfo.address);
		str += "\t代码:" + FormatString("%8d", _ObjectInfo.code);
		str += "\t类型:" + FormatString("%8d", _ObjectInfo.type);
		str += "\t阵营:" + FormatString("%8d", _ObjectInfo.camp);
		str += "\t血量:" + FormatString("%16d", _ObjectInfo.health_point);
		str += "\t位置:" + FormatString("%d,%d,%d",_ObjectInfo.pos.x, _ObjectInfo.pos.y, _ObjectInfo.pos.z);
		str += "\t名称:" + FormatString("%s", _ObjectInfo.name);
		str += "\n";
	}
	青色打印("%s", str.c_str());
	str.clear();
}


VOID Traverse::OutputTaskInfo(int task_type)
{
	TaskInfo _TaskInfo;
	TaskObject _TaskObject;
	string str;
	if (task_type == -1)
	{
		_TaskInfo = TraverseAllTaskInfo();
	}
	else if(task_type == 0){
		_TaskInfo = TraverseReceivedTaskInfo();
	}
	for (size_t i = 0; i < _TaskInfo.task_count; i++)
	{
		_TaskObject = TraverseTaskObject(_TaskInfo.start_address + i * 4);
		if (_TaskObject.type == task_type)
		{
			str += "地址:" + FormatString("0x%8x", _TaskObject.address);
		}
		else {

		}
	}
}