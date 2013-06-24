#include <eeros/control/TimeDomain.hpp>
#include <eeros/control/AnSignal.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/BlockOutput.hpp>
#include <eeros/control/Step.hpp>

#include <eeros/sequencer/Sequence.hpp>

//TODELETE
#include <iostream>

#include "MySequence.hpp"
#include "MySubSequence.hpp"

MySequence::MySequence(std::string name, TimeDomain* ptimeDomain):
eeros::sequencer::Sequence(name, ptimeDomain),
currentSubSequence(0){
	//next( (static_cast<eeros::sequencer::Sequence::method>(&MySequence::Init) ));
	next( (eeros::sequencer::Sequence::method)(&MySequence::Init) );
}


MySequence::~MySequence(void){
	deleteAllSubSequences();
}

void MySequence::Init(){
	std::cout << "Init" << std::endl;
	std::cout << "Going to Initialising" << std::endl;
	next((eeros::sequencer::Sequence::method)(&MySequence::Initialising));
}

/** Initialising
*/
void MySequence::Initialising(){
	std::cout << "Initialising" << std::endl;
	std::cout << "Going to Initialised" << std::endl;
	//Create blocks for control
	AnSignal* sig1 = new AnSignal("s1", "m");
	AnSignal* sig2 = new AnSignal("s2", "m");
	
	Step* step = new Step(*sig1, 1, 5, 0.5);
	Gain* gain = new Gain(*sig2, 10);
	BlockOutput* output = new BlockOutput();
	gain->in.connect(step->out);
	output->in.connect(gain->out);
	//add the blocks to the time domain
	timeDomain->addBlock(step);
	timeDomain->addBlock(gain);
	timeDomain->addBlock(output);

	next((eeros::sequencer::Sequence::method)(&MySequence::Initialised));
}

/** Initialised
*/
void MySequence::Initialised(){
	std::cout << "Initialised" << std::endl;
	std::cout << "Going to Homed" << std::endl;
	next((eeros::sequencer::Sequence::method)(&MySequence::Homed));
}

/** Homed
*/
void MySequence::Homed(){
	std::cout << "Homed" << std::endl;
	std::cout << "Going to Move" << std::endl;
	next((eeros::sequencer::Sequence::method)(&MySequence::Move));
}

/** Move
*/
void MySequence::Move(){
	std::cout << "Move" << std::endl;
	//Version: Waiting until the SubSequence has finished
	if(!currentSubSequence){
		currentSubSequence = new MySubSequence("SubSequence", timeDomain);
		currentSubSequence->start();
	}
	
	//waits until the subsequence has finished
	if(currentSubSequence && currentSubSequence->getStatus() == kStopped){
		currentSubSequence = 0;
		std::cout << "Going to Moving" << std::endl;
		next((eeros::sequencer::Sequence::method)(&MySequence::Moving));
	}
	//wait in an other step for example in Stopped
}

/** Moving waits until the Move is completed
*/
void MySequence::Moving(){
	std::cout << "Moving" << std::endl;
	std::cout << "Going to Stopping" << std::endl;
	next((eeros::sequencer::Sequence::method)(&MySequence::Stopping));
}

/** Stopping
*/
void MySequence::Stopping(){
	std::cout << "Stopping" << std::endl;
	std::cout << "End of Sequence!" << std::endl;
	stop();
}
