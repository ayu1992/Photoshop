#ifndef PIXELBUFFERMANAGER_H
#define PIXELBUFFERMANAGER_H
#include <deque>
#include "PixelBuffer.h"


class PixelBufferManager
{

public:

	PixelBufferManager();
	~PixelBufferManager();

	//Photoshop 121
	bool canUndo();
	bool canRedo();

	// only after undo, redo
	PixelBuffer* getLatestSnapshot(void);
	// on mouse up or any function applied
	void takeSnapshot(PixelBuffer* pb);

	// writeImage
	void undo(void);
	void redo(void);
	//PixelBuffer* redo(void);

private:
	std::deque<PixelBuffer *> m_snapshots;
	int m_currentIdx;
	int m_maxSize;			//max size of m_Snapshots
	
};
#endif