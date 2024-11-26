#include "ObjLoader.hpp"
#include "globals.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string gTextureName;

ObjLoader::ObjLoader(const std::string& filename, int type) {
    load(filename);
    textureName = gTextureName;
    modelType = type;
}

void ObjLoader::load(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    std::string directory = filename.substr(0, filename.find_last_of('/'));

    std::string mtlFilename;
    std::string textureName;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") { // Vertex position
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "vt") { // Texture coordinate
            TextureCoords texture;
            iss >> texture.u >> texture.v;
            textures.push_back(texture);
        } else if (prefix == "vn") { // Vertex normal
            Normal normal;
            iss >> normal.nx >> normal.ny >> normal.nz;
            normals.push_back(normal);
        } else if (prefix == "f") { // Face
            Face face;
            for (int i = 0; i < 3; ++i) {
                iss >> face.vertexIndices[i];
                if (iss.peek() == '/') {
                    iss.get();
                    if (iss.peek() != '/') {
                        iss >> face.textureIndices[i];
                    }
                    if (iss.peek() == '/') {
                        iss.get();
                        iss >> face.normalIndices[i];
                    }
                }
                --face.vertexIndices[i];  // obj indices start at 1
                --face.textureIndices[i]; // obj indices start at 1
                --face.normalIndices[i];  // obj indices start at 1
            }
            faces.push_back(face);
        } else if (prefix == "mtllib") { // Material library
            iss >> mtlFilename;
            std::ifstream mtlFile(directory + "/" + mtlFilename);
            std::string mtlLine;
            while (std::getline(mtlFile, mtlLine)) {
                std::istringstream mtlIss(mtlLine);
                std::string mtlPrefix;
                mtlIss >> mtlPrefix;
                if (mtlPrefix == "map_Kd") { // Diffuse texture map
                    mtlIss >> textureName;
                    gTextureName = directory + "/" + textureName;
                    break;
                }
            }
        }
    }
}

std::string ObjLoader::getTextureName() const {
    return textureName;
}

std::vector<Vertex> ObjLoader::getVertices() const {
    return vertices;
}

std::vector<TextureCoords> ObjLoader::getTextures() const {
    return textures;
}

std::vector<Normal> ObjLoader::getNormals() const {
    return normals;
}

std::vector<Triangle> ObjLoader::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Face& face : faces) {
        Triangle triangle;
        for (int i = 0; i < 3; ++i) {
            triangle.vertices[i] = vertices[face.vertexIndices[i]];
            triangle.normals[i] = normals[face.normalIndices[i]];
            triangle.textures[i] = textures[face.textureIndices[i]];
        }
        triangles.push_back(triangle);
    }
    return triangles;
}
