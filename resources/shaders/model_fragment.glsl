#version 460 core

in vec2 uv_coords;
in vec3 shading;

uniform sampler2D tex;

out vec4 fragColor;

void main(){
    vec4 color = texture(tex, vec2(uv_coords.y, -uv_coords.x));
    
    fragColor = vec4(color.rgb * shading, 1.0);
}