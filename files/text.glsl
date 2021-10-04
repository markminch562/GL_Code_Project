#type Vertex

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 transform;
out vec3 ourColor;
void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor;
}

#end

#type Fragment

#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}

#end


#type Geometry
this is some random bs text
please just kill me
i want to die
#end