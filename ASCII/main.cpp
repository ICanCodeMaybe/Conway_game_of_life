#include <iostream>
#include <windows.h>

int speed = 2;
int gravity = 1;

double seconds;

class World {
private:
	static char m_world[100][100];
	static int m_bounds[100][100];

	int m_sizeX, m_sizeY;
	char background;

public:

	 World(char vypln, int sizeX, int sizeY) : background(vypln), m_sizeX(sizeX), m_sizeY(sizeY)
	 {
		for (int i = 0; i < m_sizeY+ 1; i++) {
			for (int k = 0; k < m_sizeX + 1; k++) {
				m_world[i][k] = background;
				m_bounds[i][k] = 0;
			}
		}
	 }

	void show() {

		system("cls");
		for (int i = 0; i < m_sizeY + 1; i++) {
			for (int k = 0; k < m_sizeX +1; k++) {

				std::cout << m_world[i][k];
			}
			std::cout << ' ' << std::endl;
		}
	}

	void setBounds(bool horizontal, int startX, int startY, int size) {
		if (horizontal == true) {
			for (int x = startX; x < size + 1; x++) {
				m_world[startY][x] = '_';
				m_bounds [startY][x] = 2;
			}
		}
		else {
			for (int y = startY; y < size + 1; y++) {
				m_world[y][startX] = '|';
				m_bounds[y][startX] = 1;
			}
		}
	}

	friend class Object;
};

char World::m_world[100][100];
int World::m_bounds[100][100];

class Object : public World {
public:
	int m_coordsX, m_coordsY, m_newCoordsX, m_newCoordsY, m_width, m_height;
	char vypln;

public:
	Object(World world, char vypln) : World(world), vypln(vypln)
	{

	}

	void SetObj(char vypln) {
		for (int y = m_coordsY; y < m_coordsY + m_height; y++) {
			for (int x = m_coordsX; x < m_coordsX + m_width; x++) {
				m_world[y][x] = vypln;
			}
		}
	}
	void SetSize(int width, int height){
		m_width = width;
		m_height = height;
	}

	void SetPosition(int coordsX, int coordsY) {
		m_coordsX = coordsX;
		m_coordsY = coordsY;

		SetObj(vypln);
	}

	void move(int x, int y) {

		//set + check new coords
		m_newCoordsX = m_coordsX + x;
		m_newCoordsY = m_coordsY + y;

		if (checkBounds() == false) {
			//clear last position
			SetObj(background);

			//move
			m_coordsX += x;
			m_coordsY += y;

			SetObj(vypln);
		}
	}

	bool checkBounds() {
		for (int y = m_newCoordsY; y < m_newCoordsY + m_height; y++) {
			for (int x = m_newCoordsX; x < m_newCoordsX + m_width; x++) {
				if (m_bounds[y][x] == 1 || m_bounds[y][x] == 2) {
					if (m_bounds[y][x] == 2) {
						gravity *= -1;
					}
					else if (m_bounds[y][x] == 1)
						speed *= -1;
					return true;
				}
			}
		}
		return false;
	}
};


int main()
{
	World wrl(' ', 50, 25);
	Object obj(wrl, '0');

	wrl.setBounds(false, 0, 0, 25);
	wrl.setBounds(false, 50, 0, 25);

	wrl.setBounds(true, 0, 0, 50);
	wrl.setBounds(true, 0, 25, 50);

	obj.SetSize(2, 2);
	obj.SetPosition(3, 5);

	wrl.show();

	std::cin.get();

	obj.move(2, 2);
	wrl.show();


	while (1) {
			
		Sleep(100);

		obj.move(speed, gravity);
		wrl.show();

	}

}