precision mediump float;
uniform sampler2D u_texture;
uniform mat2 u_spriteScale;
uniform float u_time;
uniform float u_fade;
varying vec2 v_uv;
void main()
{	
	vec4 color = texture2D(u_texture, u_spriteScale * v_uv);
	vec4 fader = color;
	fader.a = min(u_time / u_fade, color.a);
	gl_FragColor = fader;
}
