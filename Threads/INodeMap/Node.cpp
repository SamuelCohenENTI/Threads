#include "Node.h"
#include ...\utils\ConsoleControl.h"

Node::Node(Vector2 position)
{
	_position = position;
	
}

INodeContent* Node::Getcontent()
{
	return newContent;
}

void Node::SetContent(INodeContent* content)
{
	_content = newContent;
}

void Node::Draw(Vector2 offset)
{
	Vector2 drawPosition = _position + offset;
	if (_content= nullptr)
	{
		CC::Lock();
		CC::SetPosition(pos.X, pos.Y);
		std::cout << "";
		CC::Unlock();
		return;
	}

	_content->Draw(pos);
}

void Node::Lock()
{
	_classMutex.lock();
}
void Node::Unlock()
{
	_classMutex.unlock();
}
