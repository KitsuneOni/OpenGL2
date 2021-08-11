#include "ShaderLoader.h" 
#include<iostream>
#include<fstream>
#include<vector>

// Default Constructor
ShaderLoader::ShaderLoader(void)
{

}

// Default Destructor
ShaderLoader::~ShaderLoader(void) 
{
}

GLuint ShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	// Create the GLuint for the Program ID
	GLuint program;

	// Search through the MAP if the program with the two shaders have been created already.
	// This is done early to not have to recreate the shaders
	std::map <std::string, GLuint>::iterator programMapIterator;
	std::string programName(vertexShaderFilename);
	programName.append(fragmentShaderFilename);
	programMapIterator = programMap.find(programName);
	if (programMapIterator != programMap.end())
	{
		std::cout << "Program ('" << programName << "') located in map" << std::endl;
		program = programMap.find(programName)->second;
		return program;
	}

	std::map <const char*, GLuint>::iterator shaderMapIterator;
	// Create Variables for Vertex and Fragment Shaders
	GLuint vertexShader;
	GLuint fragShader;

	// Check Map for Vertex Shader.
	shaderMapIterator = shaderMap.find(vertexShaderFilename);
	if (shaderMapIterator != shaderMap.end())
	{
		std::cout << "Vertex Shader ('" << vertexShaderFilename << "') located in map" << std::endl;
		vertexShader = shaderMap.find(vertexShaderFilename)->second;
	}
	else
	{
		std::cout << "Vertex Shader ('" << vertexShaderFilename << "') Created and Added to Map" << std::endl;
		vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
		shaderMap.emplace(vertexShaderFilename, vertexShader);
	}

	// Check Map for Fragment Shader.
	// If Found use that
	shaderMapIterator = shaderMap.find(fragmentShaderFilename);
	if (shaderMapIterator != shaderMap.end())
	{
		std::cout << "Fragment Shader ('" << fragmentShaderFilename << "') located in map" << std::endl;
		fragShader = shaderMap.find(fragmentShaderFilename)->second;
	}
	// Create Fragment Shader if no Shader located
	else
	{
		std::cout << "Fragment Shader ('" << fragmentShaderFilename << "') created and Added to Map" << std::endl;
		fragShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);
		shaderMap.emplace(fragmentShaderFilename, fragShader);
	}

	// Create the Program
	std::cout << "Program ('" << programName << "') Created and Added to Map" << std::endl;
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	programMap.emplace(programName, program);

	glLinkProgram(program);


	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		//std::string programName = vertexShaderFilename + *fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	return program;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, const char* shaderName)
{
	// Read the shader files and save the source code as strings
	std::string shaderCode = ReadShaderFile(shaderName);

	// Create the shader ID and create pointers for source code string and length
	GLuint shaderID = glCreateShader(shaderType);

	const GLchar* shader_code_ptr = shaderCode.c_str();
	const GLint shader_code_Length = shaderCode.length();

	glShaderSource(shaderID, 1, &shader_code_ptr, &shader_code_Length);
	glCompileShader(shaderID);
	// ...

	// Populate the Shader Object (ID) and compile



	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		PrintErrorDetails(true, shaderID, shaderName);
		return 0;
	}
	return shaderID;
}

std::string ShaderLoader::ReadShaderFile(const char* filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void ShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}