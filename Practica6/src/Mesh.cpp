
#include "Mesh.h"


using namespace std;




std::vector<std::string> splitString(const std::string& str, char delim) {
	std::vector<std::string> elems;
	std::stringstream sstream(str);
	std::string item;
	if (str != "") {
		while (std::getline(sstream, item, delim)) {
			elems.push_back(item);
		}
	}
	return elems;
}

template <typename T>
T numberFromString(const std::string& str) {
	T number;
	std::istringstream stream(str);
	stream >> number;
	return number;
}




Mesh::Mesh()  
{
	
}

void Mesh::addBuffer(const shared_ptr<Buffer>& buffer, const Material& material)
{
	
	Mesh::buffers.push_back(pair<shared_ptr<Buffer>, Material>(buffer, material));
	
}

size_t Mesh::getNumBuffers() const
{
	return Mesh::buffers.size();
}

const shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
	return Mesh::buffers.at(index).first;
	
}

shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return Mesh::buffers.at(index).first;
	
}

const Material & Mesh::getMaterial(size_t index) const
{
	return Mesh::buffers.at(index).second;
}

Material & Mesh::getMaterial(size_t index)
{
	return Mesh::buffers.at(index).second;
}




std::shared_ptr<Mesh> Mesh::load(const char * filename, const std::shared_ptr<Shader>& shader)
{
	
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);


	if (!result) {
		cout << result.description() <<  endl;
		return nullptr;
	}


	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	pugi::xml_node meshNode = doc.child("mesh");
	pugi::xml_node buffersNode = meshNode.child("buffers");

	//iterate buffers
	for (pugi::xml_node bufferNode = buffersNode.child("buffer"); bufferNode; bufferNode = bufferNode.next_sibling("buffer")) {
		float n;
		//obtain material
		pugi::xml_node materialNode = bufferNode.child("material");

	
		Material material;
		if (materialNode.child("texture")) {
			string textureStr = materialNode.child("texture").text().as_string();
			//std::cout << textureStr << endl;
			//All the textures MUST BE in the folder data
			string texturePath = "data/" + textureStr;
			material = Material(Texture::load(texturePath.c_str()), shader);

		}
		
		if (materialNode.child("color")) {
			vector<std::string> colorString = splitString(materialNode.child("color").text().as_string(), ',');
			vector<float> colorVector;
			float aux1;
			for (auto i : colorString) {
				aux1 = numberFromString<float>(i);
				colorVector.push_back(aux1);
			}
			glm::vec4 color;
			color.x = colorVector[0];
			color.y = colorVector[1];
			color.z = colorVector[2];
			color.w = colorVector[3];
			material.setColor(color);

		}


		if (materialNode.child("shininess")) {
			uint8_t shininess = materialNode.child("shininess").text().as_int();
			material.setShininess(shininess);

		}

		//indices
		vector<std::string> indicesString = splitString(bufferNode.child("indices").text().as_string(), ',');
		vector<uint32_t> indices;
		for (auto i : indicesString) {
			n = numberFromString<float>(i);
			indices.push_back(n);
		}


		//coords
		int numVertex = 0;

		vector<std::string> coordsString = splitString(bufferNode.child("coords").text().as_string(), ',');
		vector<float> coords;
		for (auto i : coordsString) {
			n = numberFromString<float>(i);
			coords.push_back(n);
		}

		vector<glm::vec3> coordsV;
		for (auto i = coords.begin(); i < coords.end(); i += 3) {
			numVertex++;
			coordsV.push_back(glm::vec3(*i, *(i + 1), *(i + 2)));
		}

		//texcoords
		vector<glm::vec2> texcoordsV;

		if (bufferNode.child("texcoords")) {
			vector<std::string> texcoordsString = splitString(bufferNode.child("texcoords").text().as_string(), ',');
			vector<float> texcoords;
			for (auto i : texcoordsString) {
				n = numberFromString<float>(i);
				texcoords.push_back(n);
			}


			for (auto i = texcoords.begin(); i < texcoords.end(); i += 2) {
				texcoordsV.push_back(glm::vec2(*i, *(i + 1)));
			}
		}
		else {
			for (int i = 0; i < numVertex; i++) {
				texcoordsV.push_back(glm::vec2(0, 0));
			}
		}

		//normals

		vector<Vertex> vertices;

		if (bufferNode.child("normals")) {
			vector<std::string> normalsString = splitString(bufferNode.child("normals").text().as_string(), ',');
			vector<float> normals;
			for (auto i : normalsString) {
				n = numberFromString<float>(i);
				normals.push_back(n);
			}

			vector<glm::vec3> normalsV;
			for (auto i = normals.begin(); i < normals.end(); i += 3) {
				normalsV.push_back(glm::vec3(*i, *(i + 1), *(i + 2)));
			}





			auto coordsPtr = coordsV.begin();
			auto texcoordsPtr = texcoordsV.begin();
			auto normalsPtr = normalsV.begin();

			while (coordsPtr != coordsV.end() && texcoordsPtr != texcoordsV.end() && normalsPtr != normalsV.end()) {
				vertices.push_back(Vertex(*coordsPtr, *texcoordsPtr, *normalsPtr));
				coordsPtr++;
				texcoordsPtr++;
				normalsPtr++;
			}
		}
		else {


			auto coordsPtr = coordsV.begin();
			auto texcoordsPtr = texcoordsV.begin();

			while (coordsPtr != coordsV.end() && texcoordsPtr != texcoordsV.end()) {
				vertices.push_back(Vertex(*coordsPtr, *texcoordsPtr));
				coordsPtr++;
				texcoordsPtr++;
			}
		}



		shared_ptr<Buffer> buffer = make_shared<Buffer>(vertices, indices);

		mesh->addBuffer(buffer, material);


	}

	return mesh;



}


void Mesh::draw()
{

	for (auto &i : buffers) {
		//Buffer
		auto buffer = i.first;

		//Material
		Material material = i.second;

		material.prepare();


		buffer->draw(*(material.getShader()));

	}

}
