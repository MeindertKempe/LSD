#version 460 core


layout (location = 0) uniform vec2 windowSize;
layout (location = 1) uniform float time;

out vec4 FragColor;

mat2 rot2D(float angle){
    float s = sin(angle);
    float c = cos(angle);
    return mat2(c, -s, s, c);
}

float opSmoothUnion( float d1, float d2, float k )
{
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h);
}

float sdSphere(vec3 p, float radius){
    return length(p) - radius;
}

float map(vec3 p){
    vec3 pointCopy = p;
    pointCopy.z += time * 0.001;
    pointCopy = fract(pointCopy) - .5;
    float sphere = sdSphere(pointCopy, 0.1);

    return sphere;
}

vec3 palette( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.28318*(c*t+d) );
}


void main(){
    vec2 uv = (gl_FragCoord.xy * 2 - windowSize) / windowSize.y;

    vec3 ro = vec3(0, 0, -3);
    vec3 rd = normalize(vec3(uv * 0.7, 1.0));
    vec3 col = vec3(0);

    float dist = 0.;

    int i;
    for(i = 0; i < 80; i++){
        vec3 p = ro + rd * dist;
        p.xy *= rot2D(sin(dist*0.2));
        p.z += sin(dist)*0.1;
        float d = map(p);
        dist += d;

        if(d < 0.01 || dist > 100.0) break;
    }

    col = palette(dist*0.01 + float(i)*0.005, vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5),	vec3(1.0, 1.0, 1.0),	vec3(0.30, 0.20, 0.20));

    FragColor = vec4(col, 1.0);
}