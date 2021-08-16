precision mediump float;
uniform sampler2D u_texture;
uniform mat2 u_spriteScale;
uniform float u_time;
uniform float u_fade;
varying vec2 v_uv;
void main()
{	
	vec4 color = texture2D(u_texture, u_spriteScale * v_uv);
	color.a = min(u_time / u_fade, 1.0);
	gl_FragColor = color;
}
