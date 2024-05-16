#include "../thirdparty/GLAD/include/glad/glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shaders
{
public:
  unsigned int ID;
  Shaders(const char* vertexPath, const char* fragmentPath) 
  {
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
      vShaderFile.open("vertexshader.vert");
      fShaderFile.open("fragmentshader.frag");
      stringstream vShaderStream, fShaderStream;

      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertexCode   = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    } 
    catch(ifstream::failure& e) {
      cout << "ERROR: FILE NOT FOUND " << e.what() << "\n";
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();


    // compile shaders
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // clean up
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  void use() { glUseProgram(ID); }

  void setBool(const string &name, bool value) 
  {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
  }

  void setInt(const string& name, int value)
  {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
  }

  void setFloat(const string& name, float value)
  {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);   
  }

  void checkCompileErrors(unsigned int shader, string type) 
  {
    int success;
    char infoLog[1024];
    if(type != "PROGRAM")
    {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success) 
      {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        cerr << "ERROR: SHADER COMPILATION FAILED " << type << "\n"
             << infoLog << "\n";
      }
    } else 
    {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      if(!success)
      {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        cerr << "ERROR: PROGRAM LINK FAILED " << type << "\n" << infoLog << "\n";
      }
    }
  }
  };