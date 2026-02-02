#include "Skybox.h"
#include "../NewLightRelated/Shader.h"

SkyBox::SkyBox(Level* _level) : Actor(_level)
{
    Reset();
    displayName = "Skybox";
    vertexShaderPath = "";
    fragmentShaderPath = "";
}

void SkyBox::Reset()
{
    texturesName = vector<string>();
    vertices = vector<float>();

    cubemapTexture = 0;
    shaderProgram = 0;
    modelID = 0;
    viewID = 0;
    projectionID = 0;

    skyboxVAO = 0;
    skyboxVBO = 0;
}

void SkyBox::Init(const vector<string>& _textures, const float& _scale)
{
    Reset();
    vertexShaderPath = "CubeMap.vert";
    fragmentShaderPath = "CubeMap.frag";
    InitTextures(_textures);
    cubemapTexture = LoadCubemap();
    InitShaders();
    modelID = glGetUniformLocation(shaderProgram, "model");
    viewID = glGetUniformLocation(shaderProgram, "view");
    projectionID = glGetUniformLocation(shaderProgram, "projection");
    glUseProgram(shaderProgram);

    InitVertices();
    if (_scale != 1 && _scale > 0) SetScale(_scale);
    InitBuffers();
}

void SkyBox::InitTextures(const vector<string>& _textures)
{
    const int _size = _textures.size();
    const string& _path = GetPath(TEXTURES) + "Skybox/";
    for (int _index = 0; _index < _size; _index++)
    {
        texturesName.push_back(_path + _textures[_index]);
    }
}

vector<float> SkyBox::InitVertices()
{
    vertices = {
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f
    };
    return vertices;
}

GLuint SkyBox::InitShaders()
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

    // Clean up shaders after linking
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    return shaderProgram;
}

void SkyBox::InitBuffers()
{
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

unsigned int SkyBox::CreateShader(const string& _shaderPath, const bool& _isVertex)
{
    unsigned int _shader = glCreateShader(_isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const string& _shaderCode = Shader::ReadShader(GetPath(SHADERS) + _shaderPath);
    const char* _shaderData = _shaderCode.c_str();
    glShaderSource(_shader, 1, &_shaderData, NULL);
    glCompileShader(_shader);
    return _shader;
}

void SkyBox::Draw()
{
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void SkyBox::Tick(const float _deltaTime)
{
    SUPER::Tick(_deltaTime);
    //Draw();
}

bool SkyBox::CheckShaderForErrors(const GLuint& _shader, const string& _shaderName)
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

GLuint SkyBox::LoadCubemap()
{
    if (texturesName.empty()) return 0;
    GLuint _textureID;
    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    int _width, _height, _nrChannels;
    for (GLuint _index = 0; _index < texturesName.size(); _index++) {
        unsigned char* _data = stbi_load(texturesName[_index].c_str(), &_width, &_height, &_nrChannels, 0);
        if (_data)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + _index, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
        else
            cerr << "Failed to load cubemap texture at path: " << texturesName[_index] << endl;
        stbi_image_free(_data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return _textureID;
}
