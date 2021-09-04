uniform mat4 u_wvp;
uniform float u_playerPosX;
uniform float u_playerPosY;
attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying float v_length;

void main()
{
	vec4 posL = u_wvp * vec4(a_posL, 1.0);
	gl_Position = posL;
	v_uv = a_uv;
	v_length = length(vec2(u_playerPosX,u_playerPosY) - vec2(posL.x,posL.y));
}
   