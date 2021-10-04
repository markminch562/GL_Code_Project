//
// Created by Mark Minch  on 9/27/21.
//

#include "ShaderSystem.h"
namespace ShaderSystems
{
    typedef ShaderProgram SP;
    ShaderProgram::ShaderProgram(std::string _filepath, std::string _fileData) : filepath(_filepath), FileData(_fileData){}
    unsigned int ShaderProgram::getShaderID() const
    {
        return ShaderID;
    }

    void checkType(const std::pair<size_t, size_t>& index , const std::string& data, ShaderProgram& program)
    {
        size_t start = index.first;
        size_t eol = data.find('\n', start);
        size_t delta = eol-start;
        std::string subsearch = data.substr(start, eol-start);
        size_t position;
        if(subsearch.find("Vertex") != std::string::npos)
        {
            //store only the data relevant to compiling the vertex shader in the position data
            program.Vertex.start = eol+1;
            program.Vertex.end = index.second-(delta+1);
        }
        else if(subsearch.find("Fragment") != std::string::npos)
        {
            program.Fragment.start = eol+1;
            program.Fragment.end = index.second-(delta+1);
        }
        else
        {
            program.Geometry.start = eol+1;
            program.Geometry.end = index.second-(delta+1);
        }
    };

    ShaderProgram CreateShader(std::string filepath)
    {
        std::ifstream vertexFile(filepath);
        std::stringstream FileData;
        FileData << vertexFile.rdbuf();
        std::string data = FileData.str();
        ShaderSystems::ShaderProgram program(filepath, FileData.str());

        //seperate the data into diffrent parts based on tokens
        size_t position = 0;
        std::vector<std::pair<size_t, size_t>> stringData;

        while(position < data.size() && position !=std::string::npos)
        {

            position = data.find("#type", position);

            size_t end = data.find("#end", position+5);
            if(end == std::string::npos)
            {
                end = data.size()-1;
            }
            //std::cout<<data.substr(position, position-(end+4));
            stringData.push_back({position, (end)-position});
            position = end+4;
        }
        for(auto& iter : stringData)
        {
            checkType(iter, data,program);
        }
        return program;

    }

    std::string SP::getData(GLenum type) const  {

        if(type == GL_VERTEX_SHADER)
        {
            std::string data = FileData.substr(Vertex.start, Vertex.end);
            return data;
        }
        else if(type == GL_FRAGMENT_SHADER)
        {
            return FileData.substr(Fragment.start, Fragment.end);
        }
        return  FileData.substr(Geometry.start, Geometry.end);
    }
    std::string glEnumToString(GLenum var)
    {
        std::string type;
        switch(var)
        {
            case GL_VERTEX_SHADER:
                type = "---Vertex Shader---";
                break;
            case GL_FRAGMENT_SHADER:
                type = "---Fragment Shader---";
                break;
            case GL_GEOMETRY_SHADER:
                type = "---Geometry Shader---";
                break;
            case GL_COMPILE:
                type = "---Compile Program---";
                break;
            default:
                type = "NO VALID SHADER PASSED";
        }
        return type;
    }
    void CreateShaderID(unsigned int& shader, GLenum shaderType, ShaderProgram& program)
    {

        int success;
        char infoLog[1024];
        if(shaderType != GL_COMPILE)
        {
            std::string Data = program.getData(shaderType);
            const char* data = Data.c_str();
            shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &data , NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        }
        if (!success)
        {

            program.status.successfull = false;
            program.status.statusMessage += glEnumToString(shaderType )+ "\n"+std::string(infoLog) + "\n";
        }
    }
    void CompileProgram(ShaderProgram& program)
    {
        if(program.Vertex.start== std::string::npos ||
        program.Fragment.start == std::string::npos)
        {
            program.status.successfull = false;
            program.status.statusMessage = "Vertex and or Fragment Shader is missing or ont loaded";
            return;
        }//following raii rules uint data is placed after the check leave statement

        unsigned int vertex, fragment, geometry;
        compileStatus Status;
        program.status.successfull = true;
        //CreateShaderID(vertex, GL_VERTEX_SHADER, program);
        //CreateShaderID(fragment,GL_FRAGMENT_SHADER, program);
        CreateShaderID(vertex, GL_VERTEX_SHADER, program);

        CreateShaderID(fragment, GL_FRAGMENT_SHADER, program);



        //create the program and link the files that were create
        unsigned int ProgramID;
        if(program.status.successfull)
        {
            ProgramID = glCreateProgram();
            glAttachShader(ProgramID, vertex);
            glAttachShader(ProgramID, fragment);
            glLinkProgram(ProgramID);
            CreateShaderID(ProgramID, GL_COMPILE, program);
            program.ShaderID = ProgramID;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
}