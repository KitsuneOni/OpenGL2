#include "ObjectFactory.h"

std::vector<Sphere*> ObjectFactory::CreateSpheres(Camera* camera, LightManager* lightman, SkyBox* skybox, int NumberofSpheres, glm::vec2 ExtentsX, glm::vec2 ExtentsY, glm::vec2 ExtentsZ)
{
	std::vector<Sphere*> SphereVector;

	for (int i = 0; i < NumberofSpheres; i++)
	{
		float XPos = rand() % (int)((ExtentsX.y - ExtentsX.x) + 1) + ExtentsX.x;
		float YPos = rand() % (int)((ExtentsY.y - ExtentsY.x) + 1) + ExtentsY.x;
		float ZPos = rand() % (int)((ExtentsZ.y - ExtentsZ.x) + 1) + ExtentsZ.x;

		Sphere* sphere = new Sphere(2.0f, 100);

		sphere->SetTexture("Resources/Textures/Rayman.jpg");
		sphere->SetProgram("Resources/Shaders/3D_Normals.vs", "Resources/Shaders/3DLight_BlinnPhong.fs");
		sphere->SetCamera(camera);
		sphere->SetLightManager(lightman);
		sphere->SetObjPosition(glm::vec3(XPos, YPos, ZPos));
		sphere->skybox = skybox;

		SphereVector.emplace_back(sphere);
	}

	return SphereVector;
}

Cube* ObjectFactory::CreateCube(const char* TextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera, LightManager* lightman, SkyBox* skybox)
{
	// Creates a new Cube and applies all the settings to it.
	Cube* cube = new Cube;
	cube->SetTexture(TextureName);
	cube->SetProgram(VertexShader, FragmentShader);
	cube->SetObjPosition(Position);
	cube->SetObjScale(Scale);
	cube->SetCamera(camera);
	cube->offset = Position.x;
	cube->SetLightManager(lightman);
	cube->sky = skybox;
	// Returns the Created Cube
	return cube;
}

Quad* ObjectFactory::CreateHoverQuad(const char* TextureName, const char* HoverTextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera)
{
	// Creates a new Quad and applies all the settings to it.
	Quad* quad = new Quad;
	quad->SetTexture(TextureName);
	quad->SetHoverTexture(HoverTextureName);
	quad->SetProgram(VertexShader, FragmentShader);
	quad->SetObjPosition(Position);
	quad->SetObjScale(Scale);
	quad->SetCamera(camera);
	// Returns the Created Quad
	return quad;
}

Pyramid* ObjectFactory::CreatePyramid(const char* TextureName, const char* VertexShader, const char* FragmentShader, glm::vec3 Position, glm::vec3 Scale, Camera* camera)
{
	// Creates a new Pyramid
	Pyramid* pyramid = new Pyramid;
	pyramid->SetTexture(TextureName);
	pyramid->SetProgram(VertexShader, FragmentShader);
	pyramid->SetObjPosition(Position);
	pyramid->SetObjScale(Scale);
	pyramid->SetCamera(camera);
	return pyramid;
}
