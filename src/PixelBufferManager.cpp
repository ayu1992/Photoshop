#include <iostream>
#include "PixelBufferManager.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <deque>
using std::deque;
using std::cout;
using std::endl;

PixelBufferManager::PixelBufferManager():m_snapshots(),m_currentIdx(-1),m_maxSize(20){}

PixelBufferManager::~PixelBufferManager(){
	for (std::deque<PixelBuffer*>::iterator it = m_snapshots.begin() ; it != m_snapshots.end(); ++it){
		if(!(*it)) continue;
		delete * it;					// vector auto calls destructors
	}
}
bool PixelBufferManager::canUndo(){
	return (m_currentIdx > 0);
}
bool PixelBufferManager::canRedo(){
	return (m_snapshots.size() > m_currentIdx + 1);
}

// called after undo or redo, return a COPY for display
PixelBuffer* PixelBufferManager::getLatestSnapshot(void){
	if(!m_snapshots.size() || m_currentIdx < 0){
		cout<< "[PBManager] accessing invalid element of m_snapshots"<<endl;
		return NULL;
	}
	cout << "getting image"<< m_currentIdx << endl;
	PixelBuffer* cpy = new PixelBuffer(m_snapshots[m_currentIdx]->getWidth(),m_snapshots[m_currentIdx]->getHeight(),ColorData(0.0,0.0,0.0,0.0));
	PixelBuffer::copyPixelBuffer(m_snapshots[m_currentIdx],cpy);
	return cpy;
}

void PixelBufferManager::undo (void){
	if (canUndo()) m_currentIdx--;
	cout << "current idx = "<<m_currentIdx<<endl;
}
void PixelBufferManager::redo (void){
	if( canRedo()) m_currentIdx++;
	cout << "current idx = "<<m_currentIdx<<endl;
}

void PixelBufferManager::takeSnapshot(PixelBuffer* unsavedCanvas){

	PixelBuffer* cpy = new PixelBuffer(unsavedCanvas->getWidth(),unsavedCanvas->getHeight(),ColorData(0.0,0.0,0.0,0.0));
	PixelBuffer::copyPixelBuffer(unsavedCanvas,cpy);
	//pop dirty frames (after cur+1)
	while(m_snapshots.size() -1 > m_currentIdx){
		delete m_snapshots.back();
		m_snapshots.pop_back();
	}
	//push back one
	m_snapshots.push_back(cpy);
	m_currentIdx++;
	// if length > 20, pop head		
	if(m_currentIdx >= m_maxSize){
		delete m_snapshots.front();
		m_snapshots.pop_front();
		m_currentIdx--;
	}

}


