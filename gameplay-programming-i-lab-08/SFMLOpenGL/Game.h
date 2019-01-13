#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <MyVector3.h>
#include <Matrix3.h>


using namespace std;
using namespace sf;


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void rotate();
	void scale();
	void displace();

	MyVector3 displacement{ 1.0f,1.0f,1.0f};
	
	Clock clock;
	Time elapsed;

	float rotationAngle = 0.0f;
};