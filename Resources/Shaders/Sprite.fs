precision mediump float;
uniform sampler2D u_texture;
uniform mat2 u_spriteScale;
varying vec2 v_uv;
void main()
{
	gl_FragColor = texture2D(u_texture, u_spriteScale * v_uv);
}
