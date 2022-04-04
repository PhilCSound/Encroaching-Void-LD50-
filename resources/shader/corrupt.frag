#version 120
uniform float iTime;
uniform float corrAmt;
uniform sampler2D texture;
uniform vec2 textDim;
uniform sampler2D noiseText;
uniform vec2 noiseDim;
in vec2 fragCoord;
out vec4 fragColor;

void main()
{   
    vec2 x = gl_TexCoord[0].xy;
    vec4 pixel = texture2D(texture, x);

    vec4 noisePixel = texture2D(noiseText, x);
    pixel.w = 1.0-noisePixel.x * corrAmt;
    fragColor = pixel;
}