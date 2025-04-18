#include <Shader.hpp>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <direct.h>

std::string readFile(const char* path)
{
    std::ifstream t(path, std::ios::binary);
    t.seekg(0, std::ios::end);
    size_t size = t.tellg();
    std::string buffer(size, ' ');
    t.seekg(0);
    t.read(&buffer[0], size); 
    t.close();
    return buffer;
}

Shader::Shader(const char* frag_path, const char* vert_path)
{
    std::string frag_content = readFile(frag_path);
    std::string vert_content = readFile(vert_path);
    const char* frag_str = frag_content.c_str();
    const char* vert_str = vert_content.c_str();

    int frag_handle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_handle, 1, &frag_str, NULL);
	glCompileShader(frag_handle);

    GLint shaderCompiled;
    glGetShaderiv(frag_handle, GL_COMPILE_STATUS, &shaderCompiled);
    if (!shaderCompiled)
    {
      //error
      GLchar InfoLog[256];
      glGetShaderInfoLog(frag_handle, sizeof(InfoLog), NULL, InfoLog);
      std::cout << "FRAG ERROR:" << InfoLog;
    }

	int vert_handle = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_handle, 1, &vert_str, NULL);
	glCompileShader(vert_handle);

    glGetShaderiv(vert_handle, GL_COMPILE_STATUS, &shaderCompiled);

    if (!shaderCompiled)
    {
      GLchar InfoLog[256];
      glGetShaderInfoLog(vert_handle, sizeof(InfoLog), NULL, InfoLog);
      std::cout << "VERT ERROR:" << InfoLog;
    }

	this->id = glCreateProgram();
	glAttachShader(this->id, frag_handle);
	glAttachShader(this->id, vert_handle);

	glLinkProgram(this->id);
    GLint out;
    glGetProgramiv(this->id, GL_LINK_STATUS, &out);
    //std::cout << out;

	this->Use();
	glDeleteShader(frag_handle);
	glDeleteShader(vert_handle);
}
void Shader::Use()
{
    glUseProgram(this->id);
}


void Shader::UniformFloat(char* name, float value)
{
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
void Shader::UniformVec2(char* name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void Shader::UniformVec3(char* name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void Shader::UniformVec4(char* name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void Shader::UniformInt(char* name, int value)
{
    glUniform1i(glGetUniformLocation(this->id, name), value);
}
void Shader::UniformIvec2(char* name, glm::ivec2 value)
{
    glUniform2i(glGetUniformLocation(this->id, name), value.x, value.y);
}
void Shader::UniformIvec3(char* name, glm::ivec3 value)
{
    glUniform3i(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void Shader::UniformIvec4(char* name, glm::ivec4 value)
{
    glUniform4i(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void Shader::UniformMat2(char* name, glm::mat2 value)
{
    glUniformMatrix2fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::UniformMat3(char* name, glm::mat3 value)
{
    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::UniformMat4(char* name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::UniformViewProjection(ViewProjection vp) {
	this->UniformMat4("view", vp.view);
    this->UniformMat4("projection", vp.projection);
}