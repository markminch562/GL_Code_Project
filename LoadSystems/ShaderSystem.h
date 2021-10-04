//
// Created by Mark Minch  on 9/27/21.
//

#ifndef RENDERSYSTEMS_SHADERSYSTEM_H
#define RENDERSYSTEMS_SHADERSYSTEM_H
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace ShaderSystems
{
enum UniformType
{
    VECT3, VECT2, VECT4,MATRIX3X3, MATRIX4X4
};

struct compileStatus{
    std::string statusMessage;
    bool successfull = false;
};

class ShaderProgram
{

    //A shader program contains all the needed info for a shader to be compiled
private:
    struct Data
    {
        //Data points to values at the start and end of the shader program
        size_t start = std::string::npos;
        size_t end = std::string::npos;
        //below is meta information about the parsed data
        std::vector<UniformType> Vec3Name;
        GLuint id = 0;
    };
    // this contains data about where the file came from for future referance
    std::string filepath;
    std::string FileData;
    Data Vertex;
    Data Fragment;
    Data Geometry;
    unsigned int ShaderID = 0;
public:
    compileStatus status {"", false};
    unsigned int getShaderID () const;
private:
    friend ShaderProgram CreateShader(std::string filepath);
    friend void checkType(const std::pair<size_t, size_t>& index , const std::string& data, ShaderProgram& program);
    friend void CompileProgram( ShaderProgram& program);
    ShaderProgram(std::string _filepath, std::string _fileData);

public:
    //pass in the enum of the shader type that you want and it will give you back the
    //string of that vertex;
    std::string getData(GLenum type) const ;
};

ShaderProgram CreateShader(std::string filepath);
void CompileProgram(ShaderProgram& program);


};

#endif //RENDERSYSTEMS_SHADERSYSTEM_H
