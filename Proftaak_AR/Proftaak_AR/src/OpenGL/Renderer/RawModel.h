#pragma once


namespace OpenGL
{
	class RawModel
	{
		
	private: 
		int vaoID;
		int vertexCount;
	public:
		RawModel(int vaoID, int vertexCount);
		int getVaoID() { return this->vaoID; };
		int getvertexCount() { return this->vertexCount; };

	};
}