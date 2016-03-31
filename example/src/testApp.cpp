/// \file
/// \brief testApp class
/// \author Alexander Konin
/// \date 08.Apr.2015

#include "testApp.h"

void testApp::setup()
{
	setupDetector();
	setupSequenceDetector();

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofBackground(255);
	ofSetColor(100);
	ofSetVerticalSync(true);
	font.loadFont("DIN.otf", 14);  // works if bin/data/DIN.otf presents
	//font.loadFont("/Users/Akon/DIN.otf", 14);  // works!
}

void testApp::update()
{
	// Get next whistle, it may be null whistle (Whistle::isNull()) if no whistle is detected
	const ofxIntegratedWhistleDetector::Whistle whistle = detector.getNextWhistle();

	// Regardless of we got a whistle or not, we need to update whistle sequence detector
	const ofxWhistleSequenceDetector::Transition transition =
		sequenceDetector.update(!whistle.isNull());

	// Check if we below the final state, i.e. below 100% certainty (this is mode 1 - collecting
	// 100% certainty)
	if (!transition.isToFinal()) { // == transition.certaintyPercent() < 100
		// There is no actual transition. In this case we have two or more whistles those look like
		// one already counted whistle, i.e. pause between the whistles less then
		// ofxWhistleSequenceDetector::msecsPerStateGap() msecs.
		// Nothing needs to be done in this case
		if (!transition.hasTransition())
			;
		// Else we have real transition from one state to another. Here it is not possible to meet
		// final 100% certainty state, because we check this condition on upper level
		else {
			// Initial state. We go to initial state after the first line timeout
			// ofxWhistleSequenceDetector::msecsPerStateTimeout() or the second line timeout
			// ofxWhistleSequenceDetector::msecsPerFinalStateTimeout()
			if (transition.isToInitial()) {
				int x = 0; (void)x;
				// TurnOffAllLEDs();
				// ...

				// If we go to initial state from final 100% certainty state, i.e. from
				// mode 2 - playing, do something
				if (transition.isFromFinal()) {
					int x = 0; (void)x;
					// Some special processing
				}
				// Here we go to initial state from non-final state, i.e. we do not reach 100%
				// certainty and begin from zero due to timeot
				else {
					int x = 0; (void)x;
					// May be some processing is needed here
				}
			}
			// Here only can be some non-initial and non-final state
			else {
				int x = 0; (void)x;
				// TurnOnSomeLEDs(transition.certaintyPercent() - describes how many LEDs);
			}
		}
	}
	// Here we are in final state, after 100% certainty (this is mode 2 - playing). In this state
	// we will stay exactly ofxWhistleSequenceDetector::msecsPerFinalStateTimeout() msecs. (this is
	// the second line timeout) regardless of any whistles
	else {
		// If we detect a separate whistle, do some LED animation
		if (!whistle.isNull()) {
			int x = 0; (void)x;
			// DoLEDAnimation(whistle.frequency())
			// ...
		}
	}

	// NOTE: Elsewhere you can call ofxWhistleSequenceDetector::reset() to force to initial state.

	// Here the end of your handling. Handling below prints info for me for debugging. Don't
	// include this in your code

	if (transition.hasTransition() || (/*transition.isToFinal() &&*/ !whistle.isNull())) {
		// Put the transition and the whistle to the queue to be printed on screen
		if (MaxTransitions == transitions.size())
			transitions.pop_front();  // remove oldest element
		transitions.push_back(make_pair(transition, whistle));  // add current element
	}
}

void testApp::draw()
{
	string msg = getDetectorParamsAsString() + "\n" + getSequenceDetectorParamsAsString() +
		"\nNow listening for a whistle series...\n" + getTransitionsAsString();
	font.drawString(msg, 20, 20);
}

void testApp::setupDetector()
{
	// Set detector parameters
	/* Use default parameters
	detector.setHzPerWindow(130);
	detector.setWhistlePowerThresholdPercent(90);
	detector.setMsecsPerWhistleDuration(150);
	detector.setHzPerWhistleFrequencyDeviation(130);
	detector.setFramePowerThreshold(0.001f);
	detector.setUseOvertoneDetector(true);
	*/

	// Open detector. As a result the detector starts working in separate thread and collects
	// detected whistles in internal buffer. ofxIntegratedWhistleDetector::getNextWhistle() must be
	// used to retrieve available whistles in FIFO order from the buffer
	detector.open();
}

void testApp::setupSequenceDetector()
{
	// Set sequence detector parameters
	/* Use default parameters */
	sequenceDetector.setWhistleCountInSequence(4);
	sequenceDetector.setMsecsPerStateGap(1000);
	sequenceDetector.setMsecsPerStateTimeout(10 * 1000);
	sequenceDetector.setMsecsPerFinalStateTimeout(60 * 1000);
	/**/
}

string testApp::getDetectorParamsAsString() const
{
	// Print detector parameters actual values (these are corrected in accordance with FFT
	// resolution and processing step)
	string msg = "Detector Parameters:\n";
	msg += "hzPerWindow = " + ofToString(detector.hzPerWindow()) + "\n";
	msg += "whistlePowerThresholdPercent = " + ofToString(detector.whistlePowerThresholdPercent()) + "\n";
	msg += "msecsPerWhistleDuration = " + ofToString(detector.msecsPerWhistleDuration()) + "\n";
	msg += "hzPerWhistleFrequencyDeviation = " + ofToString(detector.hzPerWhistleFrequencyDeviation()) + "\n";
	msg += "framePowerThreshold = " + ofToString(detector.framePowerThreshold()) +
		" - MIC & MIXER SETTINGS DEPENDENT, CALIBRATION MAY NEED!\n";
	msg += "useOvertoneDetector = " + ofToString(detector.useOvertoneDetector() ? "Yes" : "No") + "\n";
	return msg;
}

string testApp::getSequenceDetectorParamsAsString() const
{
	// Print sequence detector parameters actual values
	string msg = "Sequence Detector (State Machine) Parameters:\n";
	msg += "whistleCountInSequence = " + ofToString(sequenceDetector.whistleCountInSequence()) + "\n";
	msg += "msecsPerStateGap = " + ofToString(sequenceDetector.msecsPerStateGap()) + "\n";
	msg += "msecsPerStateTimeout = " + ofToString(sequenceDetector.msecsPerStateTimeout()) + "\n";
	msg += "msecsPerFinalStateTimeout = " + ofToString(sequenceDetector.msecsPerFinalStateTimeout()) + "\n";
	return msg;
}

string testApp::getTransitionsAsString() const
{
	string msg;
	for (deque<pair<ofxWhistleSequenceDetector::Transition,
		ofxIntegratedWhistleDetector::Whistle> >::const_iterator i = transitions.begin();
		i != transitions.end(); ++i) {
		const ofxWhistleSequenceDetector::Transition& transition = i->first;
		const ofxIntegratedWhistleDetector::Whistle& whistle = i->second;
		msg += "-> " + transition.toString() + ".\n   " +
			(whistle.isNull() ?
				string("Go to initial state due to timeout.") :
				whistle.toString()) +
			"\n";
	}
	return msg;
}


/* ==TRASH==
*/
