#include <iostream>
#include "ToolFactory.h"
#include "Tool.h"
#include "Pen.h"
#include "Eraser.h"
#include "CalligraphyPen.h"
#include "SprayCan.h"
#include "Highlighter.h"
#include "Blur.h"
#include "Sharpen.h"
#include "EdgeDetection.h"
#include "MotionBlur.h"
#include "Threshold.h"
#include "Saturate.h"
#include "Channels.h"
#include "Quantize.h"
#include "Stamp.h"
#include "DynBlur.h"
#include "SaltAndPepper.h"

using std::cout;
using std::endl;

template <typename T>
void pushVectorsOfSize(std::vector<std::vector<Tool*> >* tools, int sizes) {
	tools->push_back(std::vector<Tool*>());
	for (int i = 0; i < sizes; i++) tools->back().push_back(new T(i));
}

void pushMotionBlur(std::vector<std::vector<Tool*> >* tools, int sizes, int directions) {
	tools->push_back(std::vector<Tool*>());
	for (int i = 0; i < sizes; i++){
		for (int j = 0; j < directions; j++){
			tools->back().push_back(new MotionBlur(i,j));		
		}
	} 
}
/*ToolFactory is a singleton*/
/*initalize all tools, only called once at the start of program*/
ToolFactory::ToolFactory(){
	// mask based tools, size adjustable

		pushVectorsOfSize<Pen>(&m_tools, 3);
		pushVectorsOfSize<Eraser>(&m_tools, 3);
		pushVectorsOfSize<SprayCan>(&m_tools, 3);
		pushVectorsOfSize<CalligraphyPen>(&m_tools, 3);
		pushVectorsOfSize<Highlighter>(&m_tools, 3);
		pushVectorsOfSize<Stamp>(&m_tools,1);
		pushVectorsOfSize<DynBlur>(&m_tools,3);
		pushVectorsOfSize<Blur>(&m_tools, 21);
		pushVectorsOfSize<Sharpen>(&m_tools,21);
		pushVectorsOfSize<EdgeDetection>(&m_tools,1);
		pushMotionBlur(&m_tools,21,4);
		pushVectorsOfSize<Threshold>(&m_tools,1);
		pushVectorsOfSize<Saturate>(&m_tools,1);
		pushVectorsOfSize<Channels>(&m_tools,1);
		pushVectorsOfSize<Quantize>(&m_tools,1);
		pushVectorsOfSize<SaltAndPepper>(&m_tools,1);
}

ToolFactory::~ToolFactory(){
	for (int i = 0; i < m_tools.size(); i++) {
  		for (std::vector<Tool*>::iterator it = m_tools[i].begin(); it != m_tools[i].end(); ++it) delete *it;
	}
}

/*TODO: is there a way to change int -> ToolType? C style glui*/
/*ToolFactory returns the requested tool instance */
Tool* ToolFactory::getTool(ToolType tool_type, int tool_size){
	if(tool_type < 0 || tool_type >= m_tools.size() || tool_size < 0 || tool_size >= m_tools[tool_type].size()){
		cout << "[ToolFactory] invalid request for tool"<< tool_type<< " size"<<tool_size<<endl;
		return NULL;
	}
	return m_tools[tool_type][tool_size];
}

Tool* ToolFactory::getMotionBlurTool(int tool_size, int direction){
	if(tool_size < 0 || tool_size > 20 || direction < 0 || direction > 4){
		cout << "[ToolFactory] invalid request for tool"<<endl;
		return NULL;
	}
	return m_tools[MOTION_BLUR][tool_size * 4 + direction];
}
