uniform mat4 u_wvp;
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec2 v_pos;
void main()
{
	vec4 posL = u_wvp * vec4(a_posL, 1.0);
	gl_Position = posL;
	v_uv = a_uv;
	v_pos = vec2(posL.x,posL.y);
}
   