#include "GameScene.h"
#include "SceneObject.h"
#include "Button.h"
#include "Rectangle.h"

GameScene::GameScene()
{
	//temp_big_circle = addObject(new TempCircle(RX / 2, RY / 2, 500, sf::Color::Green));
	button1 = dynamic_cast<Button*>(
		addObject(new Button(200, 50, 400, 100, sf::Color::Cyan, L"MENU"))
		); button1->setEvent(1000, true);
	left_wall = dynamic_cast<Rectangle*>(addObject(new Rectangle(0, 0,left_margin, RY * 2,0, sf::Color::White, sf::Color::Black, 1)));
	right_wall = dynamic_cast<Rectangle*>(addObject(new Rectangle(RX, 0,right_margin, RY * 2,0, sf::Color::White, sf::Color::Black, 1)));
	ball1 = dynamic_cast<Ball*>(addObject(new Ball(RX/2,300,20,sf::Color::Red,1)));
	collider1 = dynamic_cast<Collider*>(addObject(new Collider(RX/2, RY - 20, 100, 10, left_margin, right_margin, sf::Color::Green, 2)));
	grid1 = dynamic_cast<Grid*>(addObject(new Grid(RX/2,0,RX-left_margin,(RX-left_margin)/4, ROWS,COLS, 1)));
	populateGrid(grid1);
}

void GameScene::sceneUpdate(float delta_time)
{
	if (ball1 != nullptr) 
	{
		if (ball1->getEventToScene() == 1) 
		{
			markToDelete(ball1);
			ball1 = nullptr;
		}
		if (ball1 != nullptr)
		{
			ball1->step(delta_time);
		}
	}

	//if (temp_big_circle != nullptr)
	//{
	//	if (temp_big_circle->getEventToScene() == 1)
	//	{
	//		markToDelete(temp_big_circle);
	//		temp_big_circle = nullptr; // make sure to reset after deletion (here it is not needed)
	//		temp_big_circle = addObject(new TempCircle(RX / 2, RY / 2 + 300, 50, sf::Color::Green));
	//		addObject(new TempCircle(RX / 2, RY / 2 - 300, 50, sf::Color::Green));
	//	}

	//	TempCircle* temp_circle = dynamic_cast<TempCircle*>(temp_big_circle);
	//	if (temp_circle != nullptr)
	//		temp_circle->step(delta_time);
	//}
}

void GameScene::populateGrid(Grid* grid)
{
	for (size_t row = 0; row < ROWS; row++)
	{
		for (size_t col = 0; col < COLS; col++)
		{
			dynamic_cast<Brick*>(addObject(new Brick(left_margin/2 + grid->position_x[col]-grid->brickw/2, grid->position_y[row]-grid->brickh/2,grid->brickw-1,grid->brickh-1, sf::Color::Magenta, sf::Color::Yellow, 3)));
		}
	}
}
