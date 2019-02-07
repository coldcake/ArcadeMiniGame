#include "Game.h"
#include "Timer.h"
#include "Block.h"
#include "Constants.h"

namespace GameDev2D
{
	Game::Game()
	{
        //Load Audio
        LoadAudio("LevelUp");
        LoadAudio("Music");
        LoadAudio("Strike");
        LoadAudio("Victory");

        //Load Textures
        LoadTexture("Background");
        LoadTexture("Block");
        LoadTexture("Level1");
        LoadTexture("Level2");
        LoadTexture("Level3");
        LoadTexture("Level4");
        LoadTexture("Level5");
        LoadTexture("Winner");

        //Create Block Objects
        m_Block1 = new Block("Block", 1, 0.21);
        m_Block2 = new Block("Block", 2, 0.16);
        m_Block3 = new Block("Block", 3, 0.11);
        m_Block4 = new Block("Block", 4, 0.06);
        m_Block5 = new Block("Block", 5, 0.02);

        //Create Audio Objects
        m_LevelUp = new Audio("LevelUp");
        m_Music = new Audio("Music");
        m_Strike = new Audio("Strike");
        m_Victory = new Audio("Victory");

        //Create Texture Objects
        m_Background = new Sprite("Background");
        m_Level1 = new Sprite("Level1");
        m_Level2 = new Sprite("Level2");
        m_Level3 = new Sprite("Level3");
        m_Level4 = new Sprite("Level4");
        m_Level5 = new Sprite("Level5");

        m_Level1_Right = new Sprite("Level1");
        m_Level2_Right = new Sprite("Level2");
        m_Level3_Right = new Sprite("Level3");
        m_Level4_Right = new Sprite("Level4");
        m_Level5_Right = new Sprite("Level5");

        m_Winner_Left = new Sprite("Winner");
		m_Winner_Right = new Sprite("Winner");

		m_Winner_Left->SetPosition(Vector2(LEFT_LABEL_X, LEFT_LABEL_y));
		m_Winner_Right->SetPosition(Vector2(RIGHT_LABEL_X, RIGHT_LABEL_Y));

        m_Music->Play();
        m_Music->SetDoesLoop(true);

        m_Blocks = { m_Block1, m_Block2, m_Block3, m_Block4, m_Block5 }; 
        m_Levels_Left = { m_Level1, m_Level2, m_Level3, m_Level4, m_Level5 };
        m_Levels_Right = { m_Level1_Right, m_Level2_Right, m_Level3_Right, m_Level4_Right, m_Level5_Right };

        for (int i = 0; i < NUM_LEVELS; i++) {
            m_Levels_Left[i]->SetPosition(Vector2(LEFT_LABEL_X, LEFT_LABEL_y));
            m_Levels_Right[i]->SetPosition(Vector2(RIGHT_LABEL_X, RIGHT_LABEL_Y));
        }

		//set initial position of blocks
		m_Block_Height = { 88.0f, 224.0f, 360.0f, 496.0f, 632.0f };
		for (int i = 0; i < NUM_LEVELS; i++) 
			m_Blocks[i]->SetBlockPosition(GetScreenWidth()/2, m_Block_Height[i]);

		moveLeft = true;
		isDone = false;
		m_CurrentLevel = STARTING_LEVEL;
		m_CurrentColumn = STARTING_COLUMN;
		m_CurrentTimer = m_Blocks[m_CurrentLevel]->GetTimer();
		m_CurrentTimer->Start();
	}

    Game::~Game()
    {
        //Unload Audio assets
        UnloadAudio("LevelUp");
        UnloadAudio("Music");
        UnloadAudio("Strike");
        UnloadAudio("Victory");

        //Unload Texture assets
        UnloadTexture("Background");
        UnloadTexture("Block");
        UnloadTexture("Level1");
        UnloadTexture("Level2");
        UnloadTexture("Level3");
        UnloadTexture("Level4");
        UnloadTexture("Level5");
        UnloadTexture("Winner");

        //Delete Block objects
        SafeDelete(m_Block1);
        SafeDelete(m_Block2);
        SafeDelete(m_Block3);
        SafeDelete(m_Block4);
        SafeDelete(m_Block5);

        //Delete Audio objects
        SafeDelete(m_LevelUp);
        SafeDelete(m_Music);
        SafeDelete(m_Strike);
        SafeDelete(m_Victory);

        //Dekete Texture objects
        SafeDelete(m_Background);
        SafeDelete(m_Level1);
        SafeDelete(m_Level2);
        SafeDelete(m_Level3);
        SafeDelete(m_Level4);
        SafeDelete(m_Level5);
        SafeDelete(m_Level1_Right);
        SafeDelete(m_Level2_Right);
        SafeDelete(m_Level3_Right);
        SafeDelete(m_Level4_Right);
        SafeDelete(m_Level5_Right);
        SafeDelete(m_Winner_Left);
		SafeDelete(m_Winner_Right);
	}

	void Game::Update(double delta)
	{
		//Move the current block
		m_CurrentTimer->Update(delta);
		if (m_CurrentTimer->IsDone()) {
			m_Blocks[m_CurrentLevel]->SetColumn(m_CurrentColumn);
			if (m_Blocks[m_CurrentLevel]->GetLocked() == false) {
				if (moveLeft == true) {
					m_CurrentColumn--;
					m_Blocks[m_CurrentLevel]->SetBlockPosition(m_Blocks[m_CurrentLevel]->GetBlockX() - (BLOCK_X_Y + BETWEEN_BLOCKS), m_Block_Height[m_CurrentLevel]);
					if (m_CurrentColumn == MIN_COLUMN)
						moveLeft = false;
				}
				else {
					m_CurrentColumn++;
					m_Blocks[m_CurrentLevel]->SetBlockPosition(m_Blocks[m_CurrentLevel]->GetBlockX() + (BLOCK_X_Y + BETWEEN_BLOCKS), m_Block_Height[m_CurrentLevel]);
					if (m_CurrentColumn == MAX_COLUMN) 
						moveLeft = true;
				}
				m_CurrentTimer->Restart();
			}
		}
	}

	void Game::Draw()
	{
        m_Background->Draw();
		m_Blocks[m_CurrentLevel]->Draw();

		if (isDone == true) { 
			m_Winner_Left->Draw();
			m_Winner_Right->Draw();
		}
		else {
			m_Levels_Left[m_CurrentLevel]->Draw();
			m_Levels_Right[m_CurrentLevel]->Draw();
		}
		for (int i = 0; i < NUM_BLOCKS; i++) {
			if (m_Blocks[i]->GetLocked() == true)
				m_Blocks[i]->Draw();
		}
    }

	void Game::HandleLeftMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleRightMouseClick(float aMouseX, float aMouseY)
	{

	}

	void Game::HandleMouseMove(float aMouseX, float aMouseY, float aPreviousX, float aPreviousY)
	{
		
	}

	void Game::HandleKeyPress(Keyboard::Key aKey)
	{
		if (aKey == Keyboard::Spacebar) {
			//Lock BLock in place
			m_Blocks[m_CurrentLevel]->SetLocked(true);
			m_Blocks[m_CurrentLevel]->SetColumn(m_CurrentColumn);
			moveLeft = true;
			if (m_CurrentLevel + 1 == 1) {
				m_LevelUp->Play();
				m_CurrentColumn = STARTING_COLUMN;
				m_CurrentTimer = m_Blocks[m_CurrentLevel]->GetTimer();
				m_CurrentTimer->Start();
				m_CurrentLevel++;
			}
			else if (m_Blocks[m_CurrentLevel]->GetColumn() == m_Blocks[m_CurrentLevel - 1]->GetColumn() || m_CurrentLevel + 1 == 1) {
				if (m_CurrentLevel + 1 == NUM_LEVELS) {
					m_Music->Stop();
					m_Victory->Play();
					isDone = true;
				}
				else {
					m_CurrentLevel++;
					m_LevelUp->Play();
					m_CurrentColumn = STARTING_COLUMN;
					m_CurrentTimer = m_Blocks[m_CurrentLevel]->GetTimer();
					m_CurrentTimer->Start();
				}
			}
			else if (m_Blocks[m_CurrentLevel]->GetColumn() != m_Blocks[m_CurrentLevel - 1]->GetColumn() || m_CurrentLevel + 1 == 1) {
				m_Strike->Play();
				m_CurrentLevel = STARTING_LEVEL;
				m_CurrentColumn = STARTING_COLUMN;
				m_CurrentTimer = m_Blocks[0]->GetTimer();
				moveLeft = true;
				for (int i = 0; i < NUM_BLOCKS; i++) {
					m_Blocks[i]->SetLocked(false);
					m_Blocks[i]->SetColumn(UNLOCKED_BLOCK_COLUMN);
				}
				for (int i = 0; i < NUM_LEVELS; i++)
					m_Blocks[i]->SetBlockPosition(GetScreenWidth() / 2, m_Block_Height[i]);
			}
		}
		else if (aKey == Keyboard::R) {
            //Reset
			m_Music->Play();
            m_CurrentLevel = STARTING_LEVEL;
			m_CurrentColumn = STARTING_COLUMN;
			moveLeft = true;
            for (int i = 0; i < NUM_BLOCKS; i++) {
                m_Blocks[i]->SetLocked(false);
				m_Blocks[i]->SetColumn(UNLOCKED_BLOCK_COLUMN);
            }
			for (int i = 0; i < NUM_LEVELS; i++)
				m_Blocks[i]->SetBlockPosition(GetScreenWidth() / 2, m_Block_Height[i]);
        }
	}

	void Game::HandleKeyReleased(Keyboard::Key key)
	{

	}
}