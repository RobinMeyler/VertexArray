#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}

MyVector3 cornerVec[8] = {
	{0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f } };

// Vertices for one Triangle
float vertices[] = { 1.0f,  1.0f, -1.0f,
					-1.0f,  1.0f, -1.0f,
					-1.0f, -1.0f, -1.0f,

					-1.0f, -1.0f, -1.0f,
					 1.0f, -1.0f, -1.0f,
					 1.0f,  1.0f, -1.0f,

					 1.0f,  1.0f, -1.0f,
					 1.0f,  1.0f,  1.0f,
					 1.0f, -1.0f,  1.0f,

					1.0f,  -1.0f, 1.0f,
					1.0f,  -1.0f, -1.0f,
					1.0f,  1.0f,  -1.0f,

					-1.0f,  1.0f, -1.0f,
					-1.0f,  1.0f, 1.0f,
					-1.0f,  -1.0f, 1.0f,

					-1.0f,  -1.0f, 1.0f,
					-1.0f,  -1.0f, -1.0f,
					-1.0f,  1.0f, -1.0f,

					-1.0f,  1.0f, 1.0f,
					1.0f,  1.0f, 1.0f,
					-1.0f,  -1.0f, 1.0f,

					-1.0f,  -1.0f, 1.0f,
					1.0f,  -1.0f, 1.0f,
					1.0f,  1.0f, 1.0f,

					-1.0f, -1.0f, -1.0f,
					1.0f, -1.0f, -1.0f,
					1.0f, -1.0f, 1.0f,

					1.0f, -1.0f, 1.0f,
					-1.0f, -1.0f, 1.0f,
					-1.0f, -1.0f, -1.0f, 

					-1.0f, 1.0f, -1.0f,
					1.0f, 1.0f, -1.0f,
					1.0f, 1.0f, 1.0f,

					1.0f, 1.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,
					-1.0f, 1.0f, -1.0f
};

// Colors for those vertices
float colors[] = {  1.0f, 0.0f, 0.0f, 
					1.0f, 0.0f, 0.0f, 
					1.0f, 0.0f, 0.0f,

					0.0f, 1.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 

					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f,

					0.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f, 

					1.0f, 0.0f, 1.0f,
					1.0f, 0.0f, 1.0f,
					1.0f, 0.0f, 1.0f, 

					1.0f, 1.0f, 0.0f,
					1.0f, 1.0f, 0.0f,
					1.0f, 1.0f, 0.0f, 

					0.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f, 

					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 1.0f, 0.0f,

					1.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f,
					1.0f, 1.0f, 0.0f,

					1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 

					0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f,
					1.0f, 1.0f, 1.0f,

					1.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 0.0f,
					0.0f, 1.0f, 1.0f };

// Index to be drawn
unsigned int vertex_index[] = { 0, 1, 2, 3, 4, 5 };

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;
	
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 108; i = i + 3)
		{
			bool found = false;
			MyVector3 tempVec = { vertices[i], vertices[i+1], vertices[i+2] };
			for (int j = 0; j < 8; j++)
			{
				if (tempVec == cornerVec[j])
				{
					found = true;
				}
			}
			if (found == false)
			{
				tempVec = (MyMatrix3::rotationZ(0.01) * tempVec);
				for (int t = 0; t < 8; t++)
				{
					if (cornerVec[t] == MyVector3{0.0f, 0.0f, 0.0f })
					{
						cornerVec[t] = tempVec;
						break;
					}
				}
				vertices[i] = tempVec.x;
				vertices[i+1] = tempVec.y;
				vertices[i+2] = tempVec.z;
			}
		}
		for (int i = 0; i < 8; i++)
		{
			cornerVec[i] = { 0.0f, 0.0f, 0.0f };
		}
	}



	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	//glRotatef(40, 1, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

