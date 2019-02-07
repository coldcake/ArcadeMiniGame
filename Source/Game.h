#pragma once
#include <GameDev2D.h>
#include "Block.h"

namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor
		~Game(); //Destructor

		//Write game logic in the Update method
		void Update(double delta);

		//Render game objects in the Draw method
		void Draw();

		//Input methods
		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);
		
	private:
		//Member variables GO HERE 
        Audio* m_LevelUp;
        Audio* m_Music;
        Audio* m_Strike;
        Audio* m_Victory;

        Sprite* m_Background;
        Sprite* m_Level1;
        Sprite* m_Level2;
        Sprite* m_Level3;
        Sprite* m_Level4;
        Sprite* m_Level5;
        Sprite* m_Level1_Right;
        Sprite* m_Level2_Right;
        Sprite* m_Level3_Right;
        Sprite* m_Level4_Right;
        Sprite* m_Level5_Right;

        Sprite* m_Winner_Left;
		Sprite* m_Winner_Right;

        Block* m_Block1;
        Block* m_Block2;
        Block* m_Block3;
        Block* m_Block4;
        Block* m_Block5;

        int m_CurrentLevel;
        int m_CurrentColumn;
        vector<Block*> m_Blocks;
        vector<Sprite*> m_Levels_Left;
        vector<Sprite*> m_Levels_Right;

		vector<float> m_Block_Height;

		bool isDone;
		bool moveLeft;

		Timer* m_CurrentTimer;
	};
}
