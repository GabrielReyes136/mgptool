#pragma once
#include <fstream>
#include <filesystem>
#include "../common/util.h"

/*
This source file was extracted from Xavier's NOESIS MDP plugin
https://github.com/Jayveer/MGS-MDP-Noesis/blob/master/mgs/mdp/mdp.h

TODO: utility to dump .MDP from RAM.DUMP
*/


/*
@size im memory (bytes) : 0x10
*/
struct vec4 {
	float x;
	float y;
	float z;
  //default value believed to be 0x3F80
	float w;
};

/*
@size im memory (bytes) : 0x08
*/
struct vec2Short {
	uint16_t x;
	uint16_t y;
};

/*
@size im memory (bytes) : 0x0C
*/
struct vec3Short {
	uint16_t x;
	uint16_t y;
	uint16_t z;
};

/*
@size im memory (bytes) : 0x10
*/
struct vec4Short {
	uint16_t x;
	uint16_t y;
	uint16_t z;
  //default value beleived to be 0x3F80
	uint16_t w;
};

/*
@size im memory (bytes) : 0x10
*/
struct vec4Byte {
	uint8_t x;
	uint8_t y;
	uint8_t z;
  //default value believed to be 0x3F80
	uint8_t w;
};

/*
@size im memory (bytes) : 0x50
*/
struct MdpHeader {
	uint32_t magic;
	uint32_t numBones;
	uint32_t numGroups;
	uint32_t numMeshes;
	uint32_t strcode;
	uint32_t boneOffset;
	uint32_t groupOffset;
	uint32_t meshOffset;
	uint32_t unknown;
  //PAD0
	uint32_t internal;
  //PAD1
	uint32_t pad1;
  //PAD2
	uint32_t pad2;
	vec4 max;
	vec4 min;
};

/*
@size im memory (bytes) : 0x50
*/
struct MdpBone {
	uint32_t strcode;
	uint32_t y0;
	int32_t parent;
	uint32_t w0;
	vec4 parentPos;
	vec4 worldPos;
	vec4 max;
	vec4 min;
};


/*
@size im memory (bytes) : 0x10
*/
struct MdpGroup {
	uint32_t strcode;
	uint32_t flag;
	uint32_t parent;
  //replace to GRP{0 - 0xFF} omit terminator
	uint32_t pad0;
};

/*
@size im memory (bytes) : 0x50
*/
struct MdpMesh {
	uint32_t strcode;
	uint32_t flag;
	uint32_t numFaceIndex;
	uint32_t faceIndexOffset;
	uint32_t vertexBufferOffset;
	uint32_t skinOffset;
	uint32_t numVertexBuffer;
  //replace to MSH{0 - 0xFF} omit terminator
  //used internally by the game. Believed to be texture related
	uint32_t pad0;
	vec4 max;
	vec4 min;
	vec4 pos;
};

/*
@size im memory (bytes) : 0x0C
*/
struct MdpFace {
	uint16_t unknown;
	uint16_t faceBufferSize;
	uint32_t faceBufferOffset;
	uint32_t matOffset;
};

/*
@size im memory (bytes) : 0x18
*/
struct MdpMat {
	uint32_t strcode;
	uint32_t unknown;
	uint32_t r;
	uint32_t g;
	uint32_t b;
	float specularPower;
};

/*
@size im memory (bytes) : 0x04 + hex(numBones)
*/
struct MdpSkin {
	uint16_t pad;
	uint16_t numBones;
  //PSP bone limit believed to be 8
	uint8_t  boneID[];
};

struct MdpVertexBuffer01 {
	uint8_t weightA;
	uint8_t weightB;
	vec2Short uv;
	vec3Short normal;
	vec3Short vertex;
};

struct MdpVertexBuffer02 {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	vec2Short uv;
	vec3Short normal;
	vec3Short vertex;
};

struct MdpVertexBuffer03 {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	uint8_t weightE;
	uint8_t weightF;
	uint8_t weightG;
	uint8_t weightH;
	vec2Short uv;
	vec3Short normal;
	vec3Short vertex;
};

struct MdpVertexBuffer04 {
	vec2Short uv;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	vec3Short normal;
	vec3Short vertex;
};

struct MdpVertexBuffer09 {
	uint8_t weightA;
	uint8_t weightB;
	vec2Short uv;
	vec4Byte normal;
	vec3Short vertex;
};

struct MdpVertexBuffer0A {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	vec2Short uv;
	vec4Byte normal;
	vec3Short vertex;
};

struct MdpVertexBuffer0B {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	uint8_t weightE;
	uint8_t weightF;
	uint8_t weightG;
	uint8_t weightH;
	vec2Short uv;
	vec4Byte normal;
	vec3Short vertex;
};

struct MdpVertexBuffer0C {
	uint8_t weightA;
	uint8_t weightB;
	vec2Short uv;
	uint16_t unknown;
	vec4Byte normal;
	vec3Short vertex;
};

struct MdpVertexBuffer0D {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	vec2Short uv;
	uint16_t unknown;
	vec4Byte normal;
	vec3Short vertex;
};

struct MdpVertexBuffer0E {
	uint8_t weightA;
	uint8_t weightB;
	uint8_t weightC;
	uint8_t weightD;
	uint8_t weightE;
	uint8_t weightF;
	uint8_t weightG;
	uint8_t weightH;
	vec2Short uv;
	uint16_t unknown;
	vec4Byte normal;
	vec3Short vertex;
};

class Mdp {
public:
	Mdp(std::string filename);
	~Mdp();

	void open();
private:
		std::string filename;
};
