# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight (vec3 direction, vec4 lightcolor, vec3 normal, vec3 halfvec, vec4 mydiffuse, vec4 myspecular, float myshininess) {

        float nDotL = dot(normal, direction);         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;
}       

void main (void) 
{       
    if (enablelighting) {       
        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

        // Color all pixels black for now, remove this in your implementation!
        vec3 eye_pos = vec3(0,0,0);
        vec4 ver_pos = modelview * myvertex;
        vec3 eye_dir = normalize(eye_pos-(ver_pos.xyz/ver_pos.w));

        vec3 frg_normal = normalize(mat3(transpose(inverse(modelview)))*mynormal);
        vec4 tmp_color = vec4(0,0,0,0);
        for(int i = 0;i < numLights;++ i){
            vec4 light_pos = lightposn[i];
            vec4 light_col = lightcolor[i];
            vec3 light_dir;
            if(light_pos.w==0){
                light_dir = normalize(light_pos.xyz);
            }else if(light_pos.w == 1){
                light_dir = normalize(light_pos.xyz/light_pos.w - (ver_pos.xyz/ver_pos.w));
            }
            vec3 half_vec = normalize(eye_dir+light_dir);
            tmp_color += ComputeLight(light_dir,light_col,frg_normal,half_vec,diffuse,specular,shininess);
        }
        fragColor = ambient + emission + tmp_color;
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}
