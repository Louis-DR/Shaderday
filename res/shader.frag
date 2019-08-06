// uniform sampler2D texture;
// uniform sampler2D shift;

// vec3 hsl2rgb(vec3 c) {
//     vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
//     vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
//     return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
// }

// void main() {
//     vec4 old = texture2D(texture, gl_TexCoord[0].xy);
//     vec4 new = texture2D(shift, old.rg);
//     new.ba = old.ba;
//     new = vec4(hsl2rgb(new.rgb), 1.0);
//     gl_FragColor = new;
// }

uniform sampler2D texture;
uniform sampler2D shift;
uniform float opacity;

vec3 hsl2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec4 old = texture2D(texture, gl_TexCoord[0].xy);
    float hue = texture2D(shift, vec2(old.r,0)).r;
    float sat = texture2D(shift, vec2(old.g,0)).g;
    float lum = texture2D(shift, vec2(old.b,0)).b;
    vec4 new = vec4(hue,sat,lum, 255);
    new = vec4(hsl2rgb(new.rgb), opacity);
    gl_FragColor = new;
}