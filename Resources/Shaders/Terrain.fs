precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float u_textureScale;
varying vec2 v_uv;
void main()
{	
	vec2 terrain_uv = v_uv * u_textureScale;
	vec4 terrainColor = (texture2D(u_texture, v_uv).r * texture2D(u_texture1, terrain_uv) 
		+ texture2D(u_texture, v_uv).g * texture2D(u_texture2, terrain_uv) 
		+ texture2D(u_texture, v_uv).b * texture2D(u_texture3, terrain_uv)) 
		/ (texture2D(u_texture, v_uv).r + texture2D(u_texture, v_uv).g + texture2D(u_texture, v_uv).b);
	gl_FragColor = terrainColor;
}
