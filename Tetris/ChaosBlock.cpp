#include "block.h"

class UBlock : public Block
{
public:
	UBlock()
	{
		id = 8;
		cells[0] = { Position(0, 0), Position(0, 2), Position(1, 0), Position(1, 1), Position(1,2) };
		cells[1] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(2, 0), Position(2,1) };
		cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0), Position(2,2) };
		cells[3] = { Position(0, 1), Position(0, 2), Position(1, 2), Position(2, 1), Position(2,2) };
		Move(0, 3);
	}
};

class FBlock : public Block
{
public:
	FBlock()
	{
		id = 9;
		cells[0] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1), Position(2,2), Position(3,1) };
		cells[1] = { Position(0,0),  Position(0,1),  Position(0,2),  Position(0,3),  Position(1,1), Position(1,3) };
		cells[2] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1), Position(3,0), Position(3,1) };
		cells[3] = { Position(0, 0), Position(0, 2), Position(1, 0), Position(1, 1), Position(1,2), Position(1,3) };
		Move(0, 3);
	}
};

class DotBlock : public Block
{
public:
	DotBlock()
	{
		id = 10;
		cells[0] = { Position(0,1) };
		Move(0, 4);
	}
};

class CommaBlock : public Block
{
public:
	CommaBlock()
	{
		id = 11;
		cells[0] = { Position(0,1), Position(1,1) };
		cells[1] = { Position(0,0), Position(0,1) };
		Move(0, 4);
	}
};

class BigOBlock : public Block
{
public:
	BigOBlock()
	{
		id = 12;
		cells[0] = { Position(0, 0), Position(0, 1), Position(0,2), Position(0,3), Position(1, 0), Position(1, 1), Position(1,2), Position(1,3),
					 Position(2, 0), Position(2, 1), Position(2,2), Position(2,3), Position(3, 0), Position(3, 1), Position(3,2), Position(3,3) };
		Move(0, 4);
	}
};

class BigLBlock : public Block
{
public:
	BigLBlock() {
		id = 1;
		cells[0] = { Position(0,2), Position(0,3), Position(1,0), Position(1,1), Position(1,2), Position(1,3), 
					Position(2,0), Position(2,1), Position(2,2), Position(2,3)};
		cells[1] = { Position(0,0), Position(0,1), Position(1,0), Position(1,1), Position(2,0), Position(2,1), Position(2,2), 
					Position(2,3), Position(3,0), Position(3,1), Position(3,2)};
		cells[2] = { Position(0,0), Position(0,1), Position(0,2),Position(0,3),Position(1,0), Position(1,1), 
					Position(1,2), Position(1,3),Position(2,0), Position(2,1), };
		cells[3] = { Position(0, 0), Position(0, 1), Position(0,2), Position(1,0),Position(1, 1), Position(1,3),
					Position(2,0),Position(2, 1),Position(3,0),Position(3,1), };
		Move(0, 3);

	}
};