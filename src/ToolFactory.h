#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H
#include <vector>
#include "Tool.h"
class ToolFactory {

public:

	enum ToolType{
		// mask based tools
		PEN,
		ERASER,
		SPRAY_CAN,
		CALLIGRAPHY_PEN,
		HIGHLIGHTER,
		// interactive tools
		STAMP,
		DYN_BLUR,
		// convolution tools
		BLUR,
		SHARPEN,
		EDGE_DETECTION,
		MOTION_BLUR,
		// global filters
		THRESHOLD,
		SATURATE,
		CHANNELS,
		QUANTIZE
	};
	
	ToolFactory();
	~ToolFactory();
	
	Tool* getTool(ToolType tool_type, int tool_size); //returns the correct tool instance from m_tools
	Tool* getMotionBlurTool(int tool_size, int direction);
private:
	std::vector<std::vector<Tool *> > m_tools; //m_tools is a vector of tool instances
};

#endif
