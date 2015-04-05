#ifndef TOOLFACTORY_H
#define TOOLFACTORY_H
#include <vector>
#include "Tool.h"
#include "MotionBlur.h"
#include "Threshold.h"
#include "Saturate.h"
#include "Channels.h"
#include "Quantize.h"
#include "Stamp.h"
#include "DynBlur.h"
#include "SaltAndPepper.h"

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
		QUANTIZE,
		SALTANDPEPPER
	};
	
	ToolFactory();
	~ToolFactory();
	
	Tool* getTool(ToolType tool_type, int tool_size); //returns the correct tool instance from m_tools
	Threshold* getThresholdTool(void);
	Saturate* getSaturateTool(void);
	Channels* getChannelsTool(void);
	Quantize* getQuantizeTool(void);
	Stamp * getStampTool(void);
	Tool* getMotionBlurTool(int tool_size, int direction);
private:
	std::vector<std::vector<Tool *> > m_tools; //m_tools is a vector of tool instances
};

#endif
