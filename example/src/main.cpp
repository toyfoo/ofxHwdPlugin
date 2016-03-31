#include "ofMain.h"
#include "testApp.h"

// Entry

int main( )
{
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
}


/* ==TRASH==
// WhistleHandler

class WhistleHandler
{
public:
	static void whistleEventHandler(Akon::HwdLib::IntegratedWhistleDetector* sender,
		double whistleFrequency, double whistleCertainty, void* userData)
	{
		WhistleHandler* asThis = static_cast<WhistleHandler*>(userData);
		asThis->whistleEventHandler(whistleFrequency, whistleCertainty);
	}
	void whistleEventHandler(double whistleFrequency, double whistleCertainty)
	{
		std::cout << "Whistle detected: frequency " << whistleFrequency
			<< "Hz, certainty (Ewin/Eblock) " << whistleCertainty << std::endl;
	}
};

	WhistleHandler whistleHandler;

	Akon::HwdLib::IntegratedWhistleDetector detector(&WhistleHandler::whistleEventHandler,
		&whistleHandler);

	// Setting algorithm parameters
	detector.setHzPerWindow(100);
	detector.setPowerThresholdPercent(80);
	detector.setMsecsPerWhistleDuration(250);
	detector.setHzPerFrequencyDeviation(20);

	// Print the parameters actual values (these are corrected in accordance with FFT resolution
	// and processing step)
	std::cout << "Parameters:\n"
		<< "\thzPerWindow = " << detector.hzPerWindow() << std::endl
		<< "\tpowerThresholdPercent = " << detector.powerThresholdPercent() << std::endl
		<< "\tmsecsPerWhistleDuration = " << detector.msecsPerWhistleDuration() << std::endl
		<< "\thzPerFrequencyDeviation = " << detector.hzPerFrequencyDeviation() << std::endl;

	detector.open();
	std::cout << "\nNow listening for a whistle...\nto close the app press Ctrl+C\n";
*/

