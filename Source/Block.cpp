#include "Block.h"
#include "Timer.h"
#include "Game.h"
using namespace std;

namespace GameDev2D
{
    Block::Block(string blockName, int levelNum, double movement)
    {
        m_Block = new Sprite(blockName);
        m_Block->SetAnchor(Vector2(0.5f, 0.5f));
        m_Level = levelNum;
        m_MovementSpeed = new Timer(movement);

        m_Locked = false;
        m_Column = -1;
    }

    Block::~Block()
    {
        SafeDelete(m_Block);
        SafeDelete(m_MovementSpeed);
    }

    void Block::Update(double delta)
    {

    }
    void Block::Draw()
    {
        m_Block->Draw();
    }
    bool Block::GetLocked()
    {
        return m_Locked;
    }
    void Block::SetLocked(bool isLocked)
    {
        m_Locked = isLocked;
    }
	int Block::GetColumn()
    {
        return m_Column;
    }
    void Block::SetColumn(int column)
    {
        m_Column = column;
    }

	Timer* Block::GetTimer() 
	{
		return m_MovementSpeed;
	}
	void Block::SetBlockPosition(float x, float y)
	{
		m_Block->SetPosition(Vector2(x, y));
	}
	float Block::GetBlockX() 
	{
		return(m_Block->GetPosition().x);
	}
}