#include "Sphere.h"

// Constructor
Sphere::Sphere(float Radius, int Fidelity)
{
	int VertexAttrib = 8;	// Float components are needed for each vertex point
	int IndexPerQuad = 6;	// Indices needed to create a quad

	// Angles to keep track of the sphere points 
	float Phi = 0.0f;
	float Theta = 0.0f;

	// Create the vertex array to hold the correct number of elements based on the fidelity of the sphere
	int VertexCount = Fidelity * Fidelity * VertexAttrib;
	GLfloat* Vertices = new GLfloat[VertexCount];
	int Element = 0;		

	// Each cycle moves down on the vertical (Y axis) to start the next ring
	for (int i = 0; i < Fidelity; i++)
	{
		// A new  horizontal ring starts at 0 degrees
		Theta = 0.0f;

		// Creates a horizontal ring and adds each new vertex point to the vertex array
		for (int j = 0; j < Fidelity; j++)
		{
			// Calculate the new vertex position point with the new angles
			float x = cos(Phi) * sin(Theta);
			float y = cos(Theta);
			float z = sin(Phi) * sin(Theta);

			// Set the position of the current vertex point
			Vertices[Element++] = x * Radius;
			Vertices[Element++] = y * Radius;
			Vertices[Element++] = z * Radius;
						   		   
			// Set the texture coordinates of the current vertex point
			Vertices[Element++] = (float)i / (Fidelity - 1);
			Vertices[Element++] = 1 - ((float)j / (Fidelity - 1)); // 1 minus in order to flip the direction of 0-1 (0 at the bottom)

			// Set the normal direction of the current vertex point
			Vertices[Element++] = x;
			Vertices[Element++] = y;
			Vertices[Element++] = z;

			// Theta (Y axis) angle is incremented based on the angle created by number of sections
			// As the sphere is built ring by ring, the theta is only needed to do half the circumferance therefore using just PI
			Theta += ((float)M_PI / ((float)Fidelity - 1.0f));
		}

		// Phi angle (X and Z axes) is incremented based on the angle created by the number of sections
		// Angle uses 2*PI to get the full circumference as this layer is built as a full ring
		Phi += (2.0f * (float)M_PI) / ((float)Fidelity - 1.0f);
	}

	// Create the index array to hold the correct number of elements based on the fidelity of the sphere
	IndexCount = Fidelity * Fidelity * IndexPerQuad;
	GLuint* Indices = new GLuint[IndexCount];

	Element = 0;	// Reset the element offset for the new array
	for (int i = 0; i < Fidelity; i++)
	{
		for (int j = 0; j < Fidelity; j++)
		{
			// First triangle of the quad
			Indices[Element++] = (((i + 1) % Fidelity) * Fidelity) + ((j + 1) % Fidelity);
			Indices[Element++] = (i * Fidelity) + (j);
			Indices[Element++] = (((i + 1) % Fidelity) * Fidelity) + (j);

			// Second triangle of the quad
			Indices[Element++] = (i * Fidelity) + ((j + 1) % Fidelity);
			Indices[Element++] = (i * Fidelity) + (j);
			Indices[Element++] = (((i + 1) % Fidelity) * Fidelity) + ((j + 1) % Fidelity);
		}
	}

	// Create the Vertex Array and associated buffers
	GLuint VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,  VertexCount * sizeof(GLfloat), Vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  IndexCount * sizeof(GLuint), Indices, GL_STATIC_DRAW);

	// Vertex Information (Position, Texture Coords and Normals)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	DrawType = GL_TRIANGLES;

	// Clean up the used memory
	delete[] Vertices;
	delete[] Indices;

	SetObjPosition(glm::vec3(0.0, 0.0f, 0.0f));
	SetObjRotation(0.0f);
	SetObjScale(glm::vec3(1.0f, 1.0f, 1.0f));
	
}

// Destructor
Sphere::~Sphere()
{
}

// Render the scene
void Sphere::Draw()
{
	glUseProgram(m_Program);
	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(m_Program, "ImageTexture0"), 0);

	glUniform3fv(glGetUniformLocation(m_Program, "CameraPos"), 1, glm::value_ptr(camera->returnCameraPosition()));

	glUniformMatrix4fv(glGetUniformLocation(m_Program, "PVM"), 1, GL_FALSE, glm::value_ptr(camera->ReturnPersPVM(m_ObjModelMat)));

	glUniformMatrix4fv(glGetUniformLocation(m_Program, "Model"), 1, GL_FALSE, glm::value_ptr(m_ObjModelMat));

	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetTexture());
	glUniform1i(glGetUniformLocation(m_Program, "Skybox"), 0);
	
	LightMan->SendLightDataToShader(m_Program);

	glDrawElements(DrawType, IndexCount, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Sphere::Update(float DeltaTime)
{

}

void Sphere::SetLightManager(LightManager* lightManager)
{
	LightMan = lightManager;
}
