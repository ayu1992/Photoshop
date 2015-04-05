//
//  PaintShop.h
//
//  Created by CSCI3081W Guru on 1/15/15.
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//
//  The PaintShop class.  This class sets up the GUI and the display pixelBuffer.


#ifndef PAINTSHOP_H
#define PAINTSHOP_H

#include "BaseGfxApp.h"
#include "ToolFactory.h"
#include "Tool.h"

class ColorData;
class PixelBuffer;
class Tool;

class PaintShop : public BaseGfxApp 
{
public:
	
	PaintShop(int argc, char* argv[], int width, int height, ColorData backgroundColor);
	virtual ~PaintShop();
	
	// Glut overrided function
	void mouseDragged(int x, int y) ;
	void mouseMoved(int x, int y);
	void leftMouseDown(int x, int y);
	void leftMouseUp(int x, int y);
	void display();
	void gluiControl(int controlID);
	
	
private:
	GLUI_Spinner *spinner1;
	GLUI_Spinner *spinner2;
	GLUI_Spinner *spinner3;
	// GLUI INTERFACE ELEMENTS
	enum UIControlType 
	{
		UI_TOOLTYPE,
		UI_COLOR_R,
		UI_COLOR_G,
		UI_COLOR_B,
		UI_PRESET_RED,
		UI_PRESET_ORANGE,
		UI_PRESET_YELLOW,
		UI_PRESET_GREEN,
		UI_PRESET_BLUE,
		UI_PRESET_PURPLE,
		UI_PRESET_WHITE,
		UI_PRESET_BLACK,
		UI_MASK_RADIO,
		UI_QUIT
	};
	
	
	// PRIVATE MEMBER TASKS
	// PaintShop specific functions
	void initGlui();
	void initializeBuffers(ColorData initialColor, int width, int height);
	
	//  MEMBER VARAIBLES
	
	// This is the pointer to the buffer where the display PixelBuffer is stored
	PixelBuffer* m_displayBuffer;
	
	// These are used to store the selections from the GLUI user interface
	int m_curTool;
	int m_curSize;
	float m_curColorRed, m_curColorGreen, m_curColorBlue;
	ToolFactory m_toolFactory;
	
};

#endif
