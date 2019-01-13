#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}

float finalVertices[108];

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
unsigned int vertex_index[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
								13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 
								24, 25, 26, 27, 28, 29, 31, 32, 33, 34, 35 };

void Game::run()
{
	initialize();
	Event event;

	while (isRunning) 
	{
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
	for (int i = 0; i < 108; i = i + 3)
	{

		finalVertices[i] = vertices[i] + displacement.x;
		finalVertices[i + 1] = vertices[i+1] + displacement.y;
		finalVertices[i + 2] = vertices[i+2] + displacement.z;
	}
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	rotate();
	scale();
	displace();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glLoadIdentity();
	glTranslatef(0, 0, -10);
	glVertexPointer(3, GL_FLOAT, 0, &finalVertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::rotate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 108; i = i + 3)
		{

			MyVector3 tempVec = { vertices[i], vertices[i + 1], vertices[i + 2] };

			tempVec = (MyMatrix3::rotationZ(0.001) * tempVec);

			vertices[i] = tempVec.x;
			vertices[i + 1] = tempVec.y;
			vertices[i + 2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 108; i = i + 3)
		{

			MyVector3 tempVec = { vertices[i], vertices[i + 1], vertices[i + 2] };

			tempVec = (MyMatrix3::rotationX(0.001) * tempVec);

			vertices[i] = tempVec.x;
			vertices[i + 1] = tempVec.y;
			vertices[i + 2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		for (int i = 0; i < 108; i = i + 3)
		{

			MyVector3 tempVec = { vertices[i], vertices[i + 1], vertices[i + 2] };

			tempVec = (MyMatrix3::rotationY(0.001) * tempVec);

			vertices[i] = tempVec.x;
			vertices[i + 1] = tempVec.y;
			vertices[i + 2] = tempVec.z;

		}
	}
}

void Game::scale()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 108; i = i + 3)
		{
			MyVector3 tempVec = { vertices[i], vertices[i + 1], vertices[i + 2] };
			tempVec = (MyMatrix3::scale(1.001) * tempVec);

			vertices[i] = tempVec.x;
			vertices[i + 1] = tempVec.y;
			vertices[i + 2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 108; i = i + 3)
		{
			MyVector3 tempVec = { vertices[i], vertices[i + 1], vertices[i + 2] };
			tempVec = (MyMatrix3::scale(0.999) * tempVec);

			vertices[i] = tempVec.x;
			vertices[i + 1] = tempVec.y;
			vertices[i + 2] = tempVec.z;

		}
	}
}

void Game::displace()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			if (displacement.z >= 0)
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0, 0.0001 ,0 }) *  displacement);			// Rotate them all
			}
			else
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0, -0.0001 ,0 }) *  displacement);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			if (displacement.z >= 0)
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0, -0.0001 ,0 }) * displacement);			// Rotate them all
			}
			else
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0, 0.0001 ,0 }) *  displacement);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			if (displacement.z >= 0)
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0.0001, 0 ,0 }) * displacement);
			}
			else
			{
				displacement = (MyMatrix3::translation(MyVector3{ -0.0001, 0 ,0 }) *  displacement);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			if (displacement.z >= 0)
			{
				displacement = (MyMatrix3::translation(MyVector3{ -0.0001,0 ,0 }) *  displacement);
			}
			else
			{
				displacement = (MyMatrix3::translation(MyVector3{ 0.0001, 0 ,0 }) *  displacement);
			}
		}
	}

	for (int i = 0; i < 108; i = i + 3)
	{
		finalVertices[i] = vertices[i] + displacement.x;
		finalVertices[i+1] = vertices[i+1] + displacement.y;
		finalVertices[i+2] = vertices[i+2] + displacement.z;
	}
}

