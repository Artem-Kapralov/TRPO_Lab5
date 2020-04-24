#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

class cPaddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}
	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	friend ostream & operator<<(ostream & o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}
};
class cGameManger
{
private:
	int width, height;
	char up1, down1, up2, down2;
	bool quit;
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManger(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		width = w; height = h;
		player1 = new cPaddle(1, h / 2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}
	~cGameManger()
	{
		delete player1, player2;
	}
	void Draw()
	{
		system("cls");

		for (int i = 0; i < width + 2; i++) //верхняя граница
			cout << "=";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int player1x = player1->getX();
				int player2x = player2->getX();
				int player1y = player1->getY();
				int player2y = player2->getY();

				if (j == 0) // левые ворота
					cout << "#";

				else if (player1x == j && player1y == i) //первый игрок
					cout << "|";
				else if (player2x == j && player2y == i)
					cout << "|";

				//первый игрок
				else if (player1x == j && player1y + 1 == i)
					cout << "|";
				else if (player1x == j && player1y + 2 == i)
					cout << "|";
				else if (player1x == j && player1y + 3 == i)
					cout << "|";

				else if (player2x == j && player2y + 1 == i)
					cout << "|";
				else if (player2x == j && player2y + 2 == i)
					cout << "|";
				else if (player2x == j && player2y + 3 == i)
					cout << "|";
				else
					cout << " ";

				if (j == width - 1) //правые ворота
					cout << "#";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++) //нижняя граница
			cout << "=";
		cout << endl;
	}
	void Input()
	{
		int player1x = player1->getX();
		int player2x = player2->getX();
		int player1y = player1->getY();
		int player2y = player2->getY();

		if (_kbhit()) //движение платформ 
		{
			char current = _getch();
			if (current == up1)
				if (player1y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2y > 0)
					player2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2y + 4 < height)
					player2->moveDown();

			if (current == 'q') //выход из игры
				quit = true;
		}
	}
	void Run()
	{
		while (!quit) //цикл игры
		{
			Draw();
			Input();
		}
	}
};
int main()
{
	cGameManger c(60, 18);
	c.Run();
	return 0;
}