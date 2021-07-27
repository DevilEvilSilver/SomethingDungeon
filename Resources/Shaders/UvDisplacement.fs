precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform float u_time;
varying vec2 v_uv;
void main()
{	
	vec2 displace = texture2D(u_texture1, vec2(v_uv.s, v_uv.t + u_time)).rg;
	vec2 offset = (2.0 * displace - 1.0) * 0.08;
	vec2 uvOffset = v_uv + offset;
	vec4 fire_color = texture2D(u_texture, uvOffset);
	vec4 alphaVal = texture2D(u_texture2, v_uv);
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, alphaVal.r);
}
