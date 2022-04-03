#version 120
uniform float iTime;
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
    x = x + vec2(iTime, iTime);
    x = x * .5;
    vec2 z = vec2(1.0, 1.0);
    z = z - x + vec2(0, iTime);
    z = z * .5;
    vec4 noisePixel = texture2D(noiseText, x);
    vec4 noise2Pixel = texture2D(noiseText, z);
    pixel.xyz = pixel.xyz + (pixel.w * .3 * noisePixel.xyz) - (pixel.w * .1 * noise2Pixel.xyz);
    fragColor = pixel;
}