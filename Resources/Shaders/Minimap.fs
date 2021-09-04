precision mediump float;
uniform sampler2D u_texture;
uniform mat2 u_spriteScale;
uniform float u_playerPosX;
uniform float u_playerPosY;
varying vec2 v_uv;
varying vec2 v_pos;
void main()
{
	vec2 playerPos= vec2(u_playerPosX,u_playerPosY);
	vec2 pos =v_pos;
	float dis = length(pos - playerPos);
	vec4 defaults = vec4(0.0,0.0,0.0,1.0);
	float lerpValue  = clamp((dis - 0.01)/0.1,0.0,1.0);
	vec4 results = texture2D(u_texture, u_spriteScale * v_uv);
	gl_FragColor = lerpValue*defaults + (1.0- lerpValue)*results;//vec4(1,0,0,1); 
	//gl_FragColor = mix(results, defaults, lerpVal);
}
