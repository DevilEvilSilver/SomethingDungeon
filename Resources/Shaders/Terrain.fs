precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float u_fogStart;
uniform float u_fogLength;
uniform vec3 u_fogColor;
uniform vec3 u_cameraPos;
varying vec3 v_pos;
varying vec2 v_uv;
void main()
{	
	float lerpVal = length(u_cameraPos - v_pos);
	lerpVal = (lerpVal - u_fogStart) / u_fogLength;
	lerpVal = min(max(lerpVal, 0.0), 1.0);
	vec2 terrain_uv = v_uv * 100.0;
	vec4 terrainColor = (texture2D(u_texture, v_uv).r * texture2D(u_texture1, terrain_uv) 
		+ texture2D(u_texture, v_uv).g * texture2D(u_texture2, terrain_uv) 
		+ texture2D(u_texture, v_uv).b * texture2D(u_texture3, terrain_uv)) 
		/ (texture2D(u_texture, v_uv).r + texture2D(u_texture, v_uv).g + texture2D(u_texture, v_uv).b);
	vec4 fogColor = vec4(u_fogColor, 1.0);
	gl_FragColor = mix(terrainColor, fogColor, lerpVal);
}
