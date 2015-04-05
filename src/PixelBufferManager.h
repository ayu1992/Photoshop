//
// PixelBufferManager.h
//
// Canvas history management, returns the correct state of the canvas to display

#ifndef PIXELBUFFERMANAGER_H
#define PIXELBUFFERMANAGER_H
#include <deque>
#include "PixelBuffer.h"

class PixelBufferManager
{

public:

	PixelBufferManager();
	~PixelBufferManager();

	// If undo,redo are allowed at the current state
	bool canUndo();
	bool canRedo();

	// Returns the latest(newest) snapshot
	PixelBuffer* getLatestSnapshot(void);

	// Takes a snapshot(and own it) of the displaying canvas
	void takeSnapshot(PixelBuffer* pb);

	// Undo and redo
	void undo(void);
	void redo(void);

private:
	std::deque<PixelBuffer *> m_snapshots;	// use a bi-directional stack to store canvas history
	int m_currentIdx;						// the index of the lastest snapshot
	int m_maxSize;							//max size of m_Snapshots
	
};
#endif