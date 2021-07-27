precision mediump float;
uniform samplerCube u_cubeMap;
varying vec3 v_pos;
void main()
{
	gl_FragColor = textureCube(u_cubeMap, v_pos);
}
