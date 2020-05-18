//#pragma once
//
//#include "RawModel.h"
//#include <GLFW/glfw3.h>
//#include <GL/glew.h>
//
//namespace OpenGL {
//	class Loader {
//	private:
//		int createVAO();
//		void storeDataInAttributeList(int attributeNumber, float data[]);
//		void unbindVao();
//	public:
//		RawModel loadToVAO(float positions[]);
//	};
//}

#include "RawModel.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


namespace OpenGL {
	class Loader {
	private:
		int createVAO();
		void storeDataInAttributeList(int attributeNumber, std::vector<float> data);
		void unbindVao();
		std::vector<unsigned int> vaos;
		std::vector<unsigned int> vbos;
	public:
		RawModel loadToVAO(std::vector<float> postitions);
		void cleanup();
	};
}