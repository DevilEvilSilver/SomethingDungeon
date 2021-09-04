precision mediump float;
uniform sampler2D u_texture;
uniform mat2 u_spriteScale;
varying vec2 v_uv;
varying float v_length;
void main()
{
	vec4 defaults = vec4(1.0,1.0,1.0,0.0);
	float lerpValue  = clamp((v_length - 0.001)/0.09,0.0,1.0);
	vec4 results = texture2D(u_texture, u_spriteScale * v_uv);
	gl_FragColor = lerpValue*defaults + (1.0- lerpValue)*results;
}
