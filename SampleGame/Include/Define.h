#pragma once

#ifndef __DEFINE_H__

#define	SCENE_CHANGED	1
#define OBJ_DEAD		2

typedef struct tagVector2
{
	tagVector2() { x = 0, y = 0; };
	tagVector2(int _x, int _y) { x = _x, y = _y; };
	bool	operator==(const tagVector2& _rhs) const
	{
		return x == _rhs.x && y == _rhs.y;
	}
	int x;
	int y;
} vec2;

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif 

#define __DEFINE_H__
#endif // !__DEFINE_H__