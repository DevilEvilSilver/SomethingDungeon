uniform mat4 u_wvp;
uniform sampler2D u_heightmap;
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec3 v_pos;
varying vec2 v_uv;
void main()
{
	vec4 h_map = texture2D(u_heightmap, a_uv);
	vec3 pos = a_posL + vec3(0, h_map.r * 20.0 - 0.95, 0);
	vec4 posL = u_wvp * vec4(pos, 1.0);
	gl_Position = posL;
	v_pos = pos;
	v_uv = a_uv;
}
   