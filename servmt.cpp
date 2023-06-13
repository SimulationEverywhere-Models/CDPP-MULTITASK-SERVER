#include "servmt.h"


ServMT::ServMT(const string &name): Atomic(name), in(addInputPort("in")), doneES(addInputPort("doneES")), done(addOutputPort("done")), solved(addOutputPort("solved")), out(addOutputPort("out")) {
	//constructor

	//lee paramatros de .MA
	max_threads = atoi(ParallelMainSimulator::Instance().getParameter(description(), "max_threads").c_str());
	tiempo_cambio_de_contexto = ParallelMainSimulator::Instance().getParameter(description(), "tiempo_cambio_de_contexto");
	tiempo_CPU = ParallelMainSimulator::Instance().getParameter(description(), "tiempo_CPU");
}


Model& ServMT::initFunction() {
	//funcion de inicalizacion

	cant_threads_libres = max_threads;
	passivate();

	return *this;
}


Model& ServMT::externalFunction(const ExternalMessage& msg) {
	//funcion de transicion externa

	VTime t_trabajado;
	t_trabajado = msg.time() - t_comienzo;

	if (msg.port() == in) {
		id_trabajo_actual = msg.value();
		cant_threads_libres = cant_threads_libres-1;
		if (cant_threads_libres == max_threads-1)
			holdIn(procesando, tiempo_CPU);
		else
			holdIn(cambio_de_contexto, tiempo_cambio_de_contexto);
	}

	else if (msg.port() == doneES) {

		id_trabajo_finalizado = msg.value();
		//printf ("doneES '%d'\n", id_trabajo_finalizado);

		if (state() == AtomicState::passive) 
			holdIn(terminando, 0);
		else if (S == procesando) 
			t_remanente = tiempo_CPU - t_trabajado;
		else if (S == cambio_de_contexto) 
			t_remanente = tiempo_cambio_de_contexto - t_trabajado;

		if (S == procesando || S == cambio_de_contexto) {
			S_ant = S;
			holdIn(interrumpido, 0);
		}
    }
	return *this;
}


Model& ServMT::internalFunction(const InternalMessage& msg) {
	//funcion de transicion interna

	t_comienzo = msg.time();

	switch (S) {
		case cambio_de_contexto:
			holdIn(procesando, tiempo_CPU);
			break;
		case procesando:
			passivate();
			break;
		case terminando:
			passivate();
			break;
		case interrumpido:
			holdIn(S_ant, t_remanente);
			break;
	}

	return *this;
}


Model& ServMT::outputFunction(const CollectMessage& msg) {
	//funcion de output

	if (S == procesando) {
		sendOutput(msg.time(), out, id_trabajo_actual);
		if (cant_threads_libres > 0) {
			sendOutput(msg.time(), done, (Value)0);
		}
	}
	else if (S == terminando || S == interrumpido) {
		sendOutput(msg.time(), solved, id_trabajo_finalizado);
		cant_threads_libres = cant_threads_libres+1;
		if (cant_threads_libres == 1) {
			sendOutput(msg.time(), done, (Value)0);
		}
	}

	return *this;
}


void ServMT::holdIn(ServMT::Estado e, const VTime& t) {

	S = e;
	Atomic::holdIn(AtomicState::active, t);
}

