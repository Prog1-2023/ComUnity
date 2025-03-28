#pragma once
#include "../Utils/CoreMinimal.h"
#include "Actor.h"

class Skybox : public Actor
{
    vector<string> texturesName;
    vector<float> vertices;

    GLuint cubemapTexture;
    GLuint shaderProgram;
    GLuint modelID;
    GLuint viewID;
    GLuint projectionID;

    GLuint skyboxVAO;
    GLuint skyboxVBO;

    string vertexShaderPath;
    string fragmentShaderPath;

public:
    /// <summary>
    /// Sets the scale of the Skybox by modifying the vertices.
    /// </summary>
    /// <param name="_scale">The scale factor to apply to all vertices.</param>
    FORCEINLINE void SetScale(const float& _scale)
    {
        if (_scale < 0) return;
        const int _size = vertices.size();
        for (int _index = 0; _index < _size; _index++)
        {
            vertices[_index] *= _scale;
        }

        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /// <summary>
    /// Retrieves all the vertices of the Skybox.
    /// </summary>
    /// <returns>A vector containing all the vertices.</returns>
    FORCEINLINE vector<float> GetVertices() const { return vertices; }

    /// <summary>
    /// Sets the model, view, and projection matrices for rendering.
    /// </summary>
    /// <param name="_model">The model matrix.</param>
    /// <param name="_view">The view matrix.</param>
    /// <param name="_projection">The projection matrix.</param>
    FORCEINLINE void SetMVP(const mat4& _model, const mat4& _view, const mat4& _projection)
    {
        glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(_model));
        glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(_view));
        glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(_projection));
    }

    /// <summary>
    /// Retrieves all the texture names used in the Skybox.
    /// </summary>
    /// <returns>A vector containing the names of all the textures.</returns>
    FORCEINLINE vector<string> GetTexturesName() const { return texturesName; }

public:
    /// <summary>
    /// Constructor to initialize a Skybox instance with a given world.
    /// </summary>
    /// <param name="_world">The world that this Skybox belongs to.</param>
    Skybox(Level* _level);

private:
    /// <summary>
    /// Initializes the textures for the Skybox from the provided texture names.
    /// </summary>
    /// <param name="_textures">A list of texture names.</param>
    void InitTextures(const vector<string>& _textures = vector<string>());

    /// <summary>
    /// Initializes the vertices for the Skybox.
    /// </summary>
    /// <returns>A vector containing the vertices for the Skybox.</returns>
    vector<float> InitVertices();

    /// <summary>
    /// Initializes shaders and links them to the shader program.
    /// </summary>
    /// <returns>The shader program ID.</returns>
    GLuint InitShaders();

    /// <summary>
    /// Initializes VAO and VBO buffers for rendering the Skybox.
    /// </summary>
    void InitBuffers();

    /// <summary>
    /// Checks for errors in shader compilation.
    /// </summary>
    /// <param name="_shader">The shader ID.</param>
    /// <param name="_shaderName">The name of the shader for logging purposes.</param>
    /// <returns>True if there are no errors, false otherwise.</returns>
    bool CheckShaderForErrors(const GLuint& _shader, const string& _shaderName);

    /// <summary>
    /// Loads the cubemap texture.
    /// </summary>
    /// <returns>The cubemap texture ID.</returns>
    GLuint LoadCubemap();

    /// <summary>
    /// Creates a shader from the provided shader path.
    /// </summary>
    /// <param name="_shaderPath">The path to the shader file.</param>
    /// <param name="_isVertex">Indicates whether the shader is a vertex shader (true) or a fragment shader (false).</param>
    /// <returns>The created shader ID.</returns>
    unsigned int CreateShader(const string& _shaderPath, const bool& _isVertex);

    /// <summary>
    /// Draws the Skybox using the current shader program and cubemap texture.
    /// </summary>
    void Draw();

    virtual void Tick(const float _deltaTime) override;

public:
    /// <summary>
    /// Initializes the Skybox with the given textures and scale.
    /// </summary>
    /// <param name="_textures">A list of texture names to use for the Skybox please dont forget to put the textures name in this order : 
    /// "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg".</param>
    /// <param name="_scale">An optional scale factor for the Skybox (default is 1).</param>
    void Init(const vector<string>& _textures, const float& _scale = 1.0f);
};
