/// \file
/// \brief testApp class
/// \author Alexander Konin
/// \date 25.Aug.2014

#pragma once

#include <ofxIntegratedWhistleDetector.h>
#include <ofxWhistleSequenceDetector.h>
#include "ofMain.h"
#include <deque>

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

private:
	ofTrueTypeFont font;
	ofxIntegratedWhistleDetector detector;  // separate whistle detector
	ofxWhistleSequenceDetector sequenceDetector;  // state machine

	// Count of last transitions and transition queue (with whistles those cause transitions) to be
	// printed on screen
	static const size_t MaxTransitions = 10;
	deque<pair<ofxWhistleSequenceDetector::Transition,
		ofxIntegratedWhistleDetector::Whistle> > transitions;

	void setupDetector();
	void setupSequenceDetector();
	string getDetectorParamsAsString() const;
	string getSequenceDetectorParamsAsString() const;
	string getTransitionsAsString() const;
};


/* ==TRASH==
*/

