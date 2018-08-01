

attribute vec3 vpos;
uniform mat4 MVP;
attribute vec2 vtex;
varying vec2 ftex;


attribute vec3 vnormal;

uniform mat4 normalMat;
uniform mat4 MV;




varying vec3 fnormal;
varying vec3 fpos;




void main() {
	gl_Position = MVP * vec4(vpos, 1);
	ftex = vtex;
	
	fnormal = normalize((normalMat * vec4(vnormal, 0.0)).xyz);
	fpos = vec3(MV * vec4(vpos,1));
	
	
	
	
}