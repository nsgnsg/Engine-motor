#pragma once
#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "common.h"
#include "Vertex.h"

using namespace std;

class Shader {
private:
	uint32_t program;
	//Podria ser estatico
	char errorLog[1024];
	int vposLoc, vtexLoc, vnormalLoc;
	uint32_t vs, fs;

public:

	Shader(const string &vertex_shader, const string &fragment_shader);

	~Shader();
	/*
	protected:

	static shared_ptr<Shader> create(const string &vs, const string &fs) {
	shared_ptr<Shader> p(new Shader(vs, fs), destroy);
	if (strcmp(p->errorLog, "") == 0) {
	p = nullptr;
	}
	return p;
	}
	*/


	// Devuelve el identificador de OpenGL del programa
	uint32_t	getId() const;

	// Obtiene el mensaje de error generado al compilar o enlazar
	const char*	getError() const;

	// Activa el uso de este programa
	void		use() const;

	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void		setupAttribs() const;

	// Obtiene la localización de una variable uniform
	int		getLocation(const char* name) const;

	// Da valor a una variable uniform
	void		setInt(int loc, int val);
	void		setFloat(int loc, float val);
	void		setVec3(int loc, const glm::vec3& vec);
	void		setVec4(int loc, const glm::vec4& vec);
	void		setMatrix(int loc, const glm::mat4& matrix);


	/*
	static void destroy(Shader * p) {

	delete p;
	}

	*/


};