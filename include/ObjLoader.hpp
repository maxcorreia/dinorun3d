#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <vector>
#include <string>

struct Vertex{
    float x,y,z;    // position
	float r,g,b; 	// color
	float nx,ny,nz; // normals
};

struct TextureCoords{
    float u, v;       // texture coordinates
};

struct Normal{
    float nx, ny, nz; // normals
};


struct Triangle{
    Vertex vertices[3]; // 3 vertices per triangle
    Normal normals[3];  // 3 normals per triangle
    TextureCoords textures[3]; // 3 texture coordinates per triangle
};

struct Face {
    int vertexIndices[3];    // indices for the vertices
    int textureIndices[3];   // indices for the texture coordinates
    int normalIndices[3];    // indices for the normals
};

class ObjLoader {
public:
    ObjLoader(const std::string& filename, int type);
    std::string getTextureName() const;
    std::vector<Vertex> getVertices() const;
    std::vector<TextureCoords> getTextures() const;
    std::vector<Normal> getNormals() const;
    std::vector<Triangle> getTriangles() const;
    int modelType;

private:
    std::vector<Vertex> vertices;
    std::vector<TextureCoords> textures;
    std::vector<Normal> normals;
    std::vector<Face> faces;
    std::string textureName;
    void load(const std::string& filename);
};

#endif // OBJLOADER_HPP
