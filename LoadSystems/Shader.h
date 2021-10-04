//
// Created by Mark Minch  on 9/30/21.
//

#ifndef PATHFINDINGBREADTH_SHADER_H
#define PATHFINDINGBREADTH_SHADER_H

#include "ShaderSystem.h"
#include <vector>
#include <glm/glm.hpp>

namespace ShaderSystems {
    //if the shader is not active then we dont have to do anything
    inline static unsigned int ActiveShader = 0;
    namespace UniformContext {
// utility uniform functions
// ------------------------------------------------------------------------
        void setBool(unsigned int ID, const std::string &name, bool value);

// ------------------------------------------------------------------------
        void setInt(unsigned int ID, const std::string &name, int value);

// ------------------------------------------------------------------------
        void setFloat(unsigned int ID, const std::string &name, float value);

// ------------------------------------------------------------------------
        void setVec2(unsigned int ID, const std::string &name, const glm::vec2 &value);

        void setVec2(unsigned int ID, const std::string &name, float x, float y);

// ------------------------------------------------------------------------
        void setVec3(unsigned int ID, const std::string &name, const glm::vec3 &value);

        void setVec3(unsigned int ID, const std::string &name, float x, float y, float z);

// ------------------------------------------------------------------------
        void setVec4(unsigned int ID, const std::string &name, const glm::vec4 &value);

        void setVec4(unsigned int ID, const std::string &name, float x, float y, float z, float w);

// ------------------------------------------------------------------------
        void setMat2(unsigned int ID, const std::string &name, const glm::mat2 &mat);

// ------------------------------------------------------------------------
        void setMat3(unsigned int ID, const std::string &name, const glm::mat3 &mat);

// ------------------------------------------------------------------------
        void setMat4(unsigned int ID, const std::string &name, const glm::mat4 &mat);
    }
    class BasicUniform
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 lightIntinsity;
    };

}
#endif //PATHFINDINGBREADTH_SHADER_H
