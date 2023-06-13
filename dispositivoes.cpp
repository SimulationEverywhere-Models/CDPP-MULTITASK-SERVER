#include "dispositivoes.h"


DispositivoES::DispositivoES(const string &name): Atomic(name), in(addInputPort("in")),  done(addOutputPort("done")) {
	//constructor

	//lee paramatros de .MA
	tam_ES = atoi(ParallelMainSimulator::Instance().getParameter(description(), "tam_ES").c_str());
	velocidad = atoi(ParallelMainSimulator::Instance().getParameter(description(), "velocidad").c_str());
}


Model& DispositivoES::initFunction() {
	//funcion de inicalizacion

	passivate();

	return *this;
}


Model& DispositivoES::externalFunction(const ExternalMessage& msg) {
	//funcion de transicion externa

	if (msg.port() == in) {
		id_trabajo_actual = msg.value();
		VTime tiempo_proceso(0,0,0,(float)tam_ES/(float)velocidad);
		holdIn(AtomicState::active, tiempo_proceso);
	}

	return *this;
}


Model& DispositivoES::internalFunction(const InternalMessage& msg) {
	//funcion de transicion interna

	passivate();
	
	return *this;
}


Model& DispositivoES::outputFunction(const CollectMessage& msg) {
	//funcion de output

	sendOutput(msg.time(), done, id_trabajo_actual);
	
	return *this ;
}
