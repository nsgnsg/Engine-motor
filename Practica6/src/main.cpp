/*
#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
*/

#include "Buffer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "State.h"
#include "utils.h"
#include "Entity.h"
#include "Mesh.h"
#include "World.h"
#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "BlendMode.h"
#include "Emitter.h"


using namespace std;

#define FULLSCREEN false


/*
vector<Vertex> triangleVertex = {
//triangulo1
Vertex(0,1, 0,0,0),
Vertex(-1,-1, 0,0,0),
Vertex(1,-1, 0,0,0)


};

vector<Vertex> squareFrontVertex = {
//cuadrado1
Vertex(glm::vec3(-0.5, 0.5, 0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(-0.5,-0.5 , 0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(0.5, -0.5, 0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(0.5, 0.5, 0.5) ,glm::vec2(1,1)),

//cuadrado2
Vertex(glm::vec3(0.5, 0.5, 0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(0.5, -0.5, 0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(0.5, -0.5, -0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(0.5, 0.5 , -0.5) ,glm::vec2(1,1)),

//cuadrado3
Vertex(glm::vec3(0.5, 0.5, -0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(0.5, -0.5, -0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(-0.5,-0.5 , -0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(-0.5, 0.5, -0.5) ,glm::vec2(1,1)),

//cuadrado4
Vertex(glm::vec3(-0.5, 0.5, -0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(-0.5,-0.5 , -0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(-0.5, -0.5, 0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(-0.5, 0.5 , 0.5) ,glm::vec2(1,1))

};


vector<Vertex> squareTopVertex = {
//cuadrado1
Vertex(glm::vec3(-0.5, 0.5, -0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(-0.5, 0.5, 0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(0.5, 0.5, 0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(0.5, 0.5 , -0.5) ,glm::vec2(1,1)),


//cuadrado2
Vertex(glm::vec3(-0.5,-0.5 , -0.5) ,glm::vec2(0,1)),
Vertex(glm::vec3(-0.5, -0.5, 0.5) ,glm::vec2(0,0)),
Vertex(glm::vec3(0.5, -0.5, 0.5) ,glm::vec2(1,0)),
Vertex(glm::vec3(0.5, -0.5, -0.5) ,glm::vec2(1,1))


};

//vector<uint32_t> triangleIndex = { 0,1,2 };

vector<uint32_t> squareFrontIndex = { 0,1,2,0,2,3,
4,5,6,4,6,7,
8,9,10,8,10,11,
12,13,14,12,14,15};

vector<uint32_t> squareTopIndex = { 0,1,2,0,2,3,
4,5,6,4,6,7 };

*/


bool init() {

	// init glew
	if (glewInit()) {
		cout << "could not initialize glew" << endl;
		return false;
	}
	// enable gl states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);

	//create default shader 
	// read shaders
	string vertexShader = readString("data/shader.vert");
	string fragmentShader = readString("data/shader.frag");
	if (vertexShader == "" || fragmentShader == "") {
		cout << "could not load shaders" << endl;
		return false;
	}

	//Create shader and programs

	Shader shader = Shader(vertexShader, fragmentShader);
	// use program
	shader.use();

	//asign default shader
	State::defaultShader = make_shared<Shader>(shader);

	return true;
}




void configureEmitter(std::shared_ptr<Emitter>& emitter, glm::vec4 minColorRange, glm::vec4 maxColorRange,
	float minLifetimeRange, float maxLifetimeRange, float minRateRange, float maxRateRange,
	float minScaleRange, float maxScaleRange, glm::vec3 minVelocityRange, glm::vec3 maxVelocityRange,
	float minSpinRange, float maxSpinRange, bool emitting)
{
	emitter->setColorRange(minColorRange, maxColorRange);
	emitter->setLifetimeRange(minLifetimeRange, maxLifetimeRange);
	emitter->setRateRange(minRateRange, maxRateRange);
	emitter->setScaleRange(minScaleRange, maxScaleRange);
	emitter->setVelocityRange(minVelocityRange, maxVelocityRange);
	emitter->setSpinVelocityRange(minSpinRange, maxSpinRange);
	emitter->emit(emitting);
}


//Active cam´s movement
void cameraMove(GLFWwindow* window, shared_ptr<Camera> cam, float deltaTime) {

	//move WASD
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP)) {
		cam->move(glm::vec3(0.0f, 0.0f, -1.0f)*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT)) {
		cam->move(glm::vec3(-1.0f, 0.0f, 0.0f)*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN)) {
		cam->move(glm::vec3(0.0f, 0.0f, 1.0f)*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT)) {
		cam->move(glm::vec3(1.0f, 0.0f, 0.0f)*deltaTime);
	}



	//turn camera with smoothnes
	glm::vec2 viewportCenter = { cam->getViewport().z, cam->getViewport().w };
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	glm::vec2 cursorPos(mouseX, mouseY);
	cursorPos = (viewportCenter - cursorPos) / viewportCenter;

	//Separate the two axis in order to avoid problems
	glm::quat turningX = glm::rotate(glm::quat(), cursorPos.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat turningY = glm::rotate(glm::quat(), cursorPos.y, glm::vec3(1.0f, 0.0f, 0.0f));
	cam->setRotation(turningX * turningY);

}
int main(int, char**) {


	if (glfwInit() != GLFW_TRUE) {
		cout << "could not initalize glfw" << endl;
		return -1;
	}
	// create window
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "U-gine", FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!window) {
		cout << "could not create glfw window" << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	//disable mouse cursor
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);





	if (init())
		atexit(glfwTerminate);
	else
		return -1;


	//create the world
	shared_ptr<World> world = make_shared<World>();

	//create the main camera
	shared_ptr<Camera> mainCamera = make_shared<Camera>();
	mainCamera->setPosition(glm::vec3(0.0, 5, 25));
	//glm::quat rot = glm::rotate(glm::quat(), glm::radians(-25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//mainCamera->setRotation(rot);
	//mainCamera->setRotation(mainCamera->getRotation() * glm::quat(glm::radians(glm::vec3(-20, 0, 0))));
	//mainCamera->move(glm::vec3(0.0f, 5.0f, 25.0f));
	mainCamera->setClearColor(glm::vec3(0, 0, 0));

	//add entities to the world
	world->addEntity(mainCamera);

	

	//create buffers
	//shared_ptr<Buffer> frontBuffer = make_shared<Buffer>(squareFrontVertex, squareFrontIndex);
	//shared_ptr<Buffer> topBuffer = make_shared<Buffer>(squareTopVertex, squareTopIndex);
	//create the mesh and load textures
	//shared_ptr<Mesh> mesh = make_shared<Mesh>();

	shared_ptr<Mesh> mesh = Mesh::load("data/column.msh.xml");
	if (mesh == nullptr) {
		cout << "Could not load the mesh" << endl;
		return 0;
	}
	//create the model

	shared_ptr<Model> model = make_shared<Model>(mesh);
	//model->setRotation(glm::rotate(glm::quat(), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	model->setScale(glm::vec3(0.01, 0.01, 0.01));
	world->addEntity(model);


	// Create fire emitter
	
	Material fireMaterial = Material(Texture::load("data/flame.png"));
	fireMaterial.setCulling(false);
	fireMaterial.setLighting(false);
	fireMaterial.setBlendMode(BlendMode::​ADD​);
	std::shared_ptr<Emitter> fireEmitter = std::make_shared<Emitter>(fireMaterial, true);
	fireEmitter->setPosition(glm::vec3(0, 6.5, 0));

	configureEmitter(fireEmitter,
		glm::vec4(1,1,1,1), glm::vec4(1,1,1,1),//color
		0.5f, 0.5f,//lifetime
		10.0f, 25.0f,//rate
		0.025f, 0.1f,//scale
		glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f),//velocity
		0.0f, 0.0f,//spin velocity
		true);
	

	// Create the smoke emitter

	Material smokeMaterial = Material(Texture::load("data/smoke.png"));
	smokeMaterial.setCulling(false);
	smokeMaterial.setLighting(false);
	smokeMaterial.setBlendMode(BlendMode::ALPHA);
	std::shared_ptr<Emitter> smokeEmitter = std::make_shared<Emitter>(smokeMaterial, true);
	smokeEmitter->setPosition(glm::vec3(0, 7, 0));

	configureEmitter(smokeEmitter,
		glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1),//color
		1.0f, 5.0f,//lifetime
		5.0f, 10.0f,//rate
		0.05f, 0.1f,//scale
		glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f),//velocity
		30.0f, 60.0f, //spin velocity
		true);

	
	world->addEntity(smokeEmitter);
	world->addEntity(fireEmitter);
	
	
	//Lights and ambient
	world->setAmbient(glm::vec3(0.3f, 0.3f, 0.3f));
	/*
	shared_ptr<Light> directionalLight = make_shared<Light>(DIRECTIONAL);
	//dLight->setColor(glm::vec3(1, 1, 1));
	directionalLight->setPosition(glm::vec3(1, 1, 1));
	world->addEntity(directionalLight);

	*/
	
	shared_ptr<Light> pointLight = make_shared<Light>(POINT);
	pointLight->setColor(glm::vec3(1, 1, 1));
	pointLight->setLinearAttenuation(0.2);
	pointLight->setPosition(glm::vec3(1, 1, 1));

	world->addEntity(pointLight);
	


	float lastTime = static_cast<float>(glfwGetTime());
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// update times
		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = newTime - lastTime;
		lastTime = newTime;

		// get updated screen size
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);

		// report screen size
		//std::stringstream ss;
		//ss << screenWidth << "x" << screenHeight;
		//glfwSetWindowTitle(window, ss.str().c_str());

		//Prepare camera
		mainCamera->setProjection(glm::perspective(glm::radians(60.0f), static_cast<float>(screenWidth) / screenHeight, 0.1f, 100.0f));
		mainCamera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));
		mainCamera->prepare();


		//Active camera´s movement
		//cameraMove(window, mainCamera, deltaTime);


		//update and draw

		/*
		for (int i = 0; i < world->getNumEntities(); i++) {
		shared_ptr<Camera> isCamera = dynamic_pointer_cast<Camera>(world->getEntity(i));
		if (!isCamera) {
		//world->getEntity(i)->setRotation(world->getEntity(i)->getRotation() * glm::quat(glm::radians(glm::vec3(0, 64.0f * deltaTime, 0))));
		}
		}
		*/
		mainCamera->setRotation(mainCamera->getRotation() * glm::quat(glm::radians(glm::vec3(0, -30 * deltaTime, 0))));
		mainCamera->setPosition(glm::vec3(0, 6, 0));
		mainCamera->move(glm::vec3(0, 0, 25));

		/*
		pointLight->setRotation(pointLight->getRotation() * glm::quat(glm::radians(glm::vec3(0, -30 * deltaTime, 0))));
		pointLight->setPosition(glm::vec3(0, 0, 0));
		pointLight->move(glm::vec3(0, 0, 5));
		*/
		world->update(deltaTime);
		world->draw();

		// update swap chain & process events
		glfwSwapBuffers(window);
		glfwPollEvents();



	}

	// delete vertex buffer
	//glDeleteBuffers(1, &buffer);
	return 0;
}