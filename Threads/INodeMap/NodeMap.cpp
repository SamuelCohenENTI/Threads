#include "NodeMap.h"

NodeMap::NodeMap(Vector2 size, Vector2 offset)
{
	_size = size;
	_offset = offset;

	for (int x = 0; x < _size.X; x++)
	{ 
		NodeColumn *= new NodeColumn();
	
		for (int y = 0; y < _size.Y; y++)
		{
			column->push_back(new Node(Vector2(x, y)));

			
		}

		_grid.push_back(column);
	}
}

Vector2 NodeMap::GetSize()
{
	_sizeMutex.lock();
	Vector2 size = _size;
	_sizeMutex.unlock();

	return size;
}

void NodeMap::UnsafeDraw()
{
	for (NodeColumn* column : :grid)
	{
		for (Node* node : *column)
		{
			node->DrawContent(_offset);
		}
	}
}

void NodeMap::SafePickMode(Vector2 position, SafeMultiPick safePickAction)
{
	_sizeMutex.lock();
	_gridMutex.lock();

	Node* node = UnsafeGetNode(position);

	_gridMutex.unlock();
	_sizeMutex.unlock();

	node->Lock();
	safePickAction(node);
	node->Unlock();
}

void NodeMap::SafeMultiPickMode(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction)
{
	std::list<Node*>nodes = std::list<Node*>();
	_sizeMutex.lock();
	_gridMutex.lock();

	for (Vector2 pos : positions)
	{
		Node* node = UnsafeGetNode(pos);
		nodes.push_back(node);
	}
	_gridMutex.unlock();
	_sizeMutex.unlock();

	_safeMultiNodeMutex.lock();

	for (Node* node : nodes)
	{
		if (node != nullptr)
		{
			node->Lock();
		}
	}
	_safeMultiNodeMutex.unlock();
	safeMultiPickAction(nodes);

	_safeMultiNodeMutex.unlock();

	for (Node* node : nodes)
	{
		if (node != nullptr)
		{
			node->Unlock();
		}
	}
}

Node* NodeMap::UnsafeGetNode(Vector2 position)
{
	if (position.X >= _size.X || position.Y >= _size.Y || position.X<0 || position.Y<0)
	{
		return nullptr;
	}
	NodeColumn* column = _grid[position.X];
	Node* node = (*column)[position.Y];

	return node;
}
