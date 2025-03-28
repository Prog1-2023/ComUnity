#include "Grid.h"

Grid::Grid(Level* _level) : Actor(_level)
{
	Reset();
    displayName = "Grid";
}
void Grid::GenerateGridVertices()
{
    for (int _index = -gridSize; _index <= gridSize; _index++) {
        float _pos = _index * spacing;
        vertices.insert(vertices.end(), { _pos, 0.0f, -gridSize * spacing, _pos, 0.0f, gridSize * spacing });
        vertices.insert(vertices.end(), { -gridSize * spacing, 0.0f, _pos, gridSize * spacing, 0.0f, _pos });
    }
}

void Grid::Reset()
{
	vertices = vector<float>();
	gridSize = 0;
	spacing = 0.f;
	shaderProgram = 0;
	VAO = 0;
	VBO = 0;
	viewID = 0;
	projectionID = 0;
	vertexShaderPath = "GridShader.vert";
	fragmentShaderPath = "GridShader.frag";
}

void Grid::InitShader()
{
    // VertexShader
    unsigned int _vertexShader = CreateShader(vertexShaderPath, true);
    Assert(CheckShaderForErrors(_vertexShader, "VertexShader"), "Failed to initialize VertexShader!");

    // FragmentShader
    unsigned int _fragmentShader = CreateShader(fragmentShaderPath, false);
    Assert(CheckShaderForErrors(_fragmentShader, "FragmentShader"), "Failed to initialize FragmentShader!");

    // Link shaders into the program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, _vertexShader);
    glAttachShader(shaderProgram, _fragmentShader);
    glLinkProgram(shaderProgram);
    Assert(CheckShaderForErrors(shaderProgram, "ShaderProgram"), "Failed to initialize ShaderProgram!");

    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);
}

unsigned int Grid::CreateShader(const string& _shaderPath, const bool& _isVertex)
{
    unsigned int _shader = glCreateShader(_isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const string& _shaderCode = Shader::ReadShader(GetPath(SHADERS) + _shaderPath);
    const char* _shaderData = _shaderCode.c_str();
    glShaderSource(_shader, 1, &_shaderData, NULL);
    glCompileShader(_shader);
    return _shader;
}

bool Grid::CheckShaderForErrors(const GLuint& _shader, const string& _shaderName)
{
    int _success;
    char _logs[512];

    glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success);

    if (!_success)
    {
        glGetShaderInfoLog(_shader, 512, NULL, _logs);
        cerr << "Error => Initialization of " + _shaderName + " failed!\n" << _logs << endl;
    }
    return _success;
}

void Grid::Tick(const float _deltaTime)
{
    SUPER::Tick(_deltaTime);
    //Draw();
}

void Grid::Draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);

}

void Grid::InitBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Grid::Init(const int& _gridSize, const float& _spacing)
{
	Reset();
    InitShader();
    gridSize = _gridSize;
    spacing = _spacing;
    GenerateGridVertices();
    InitBuffers();
    modelID = glGetUniformLocation(shaderProgram, "model");
    viewID = glGetUniformLocation(shaderProgram, "view");
    projectionID = glGetUniformLocation(shaderProgram, "projection");
}
