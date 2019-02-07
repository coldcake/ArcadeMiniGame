#pragma once
using namespace std;
#include <string>
#include "Timer.h"

namespace GameDev2D {
    class Block {
    public:
        Block(string blockName, int levelNum, double movement);
        ~Block();

        void Update(double delta);
        void Draw();

        bool GetLocked();
        void SetLocked(bool isLocked);

        int GetColumn();
        void SetColumn(int column);

		Timer* GetTimer();

		void SetBlockPosition(float x, float y);
		float GetBlockX();

    private:
        Sprite * m_Block;
        int m_Level;
        Timer* m_MovementSpeed;

        bool m_Locked;
        int m_Column;
    };
}