#ifndef __SERVMT_H
#define __SERVMT_H

#include "atomic.h"


class ServMT: public Atomic {
	public:
		//Constructores
		ServMT(const string &name = "ServMT");
		enum Estado {transductor_in, terminando, cambio_de_contexto, procesando, interrumpido};

	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model& initFunction();
 		Model& externalFunction(const ExternalMessage&);
		Model& internalFunction(const InternalMessage&);
		Model& outputFunction(const CollectMessage&);
		void holdIn(ServMT::Estado, const VTime&);

	private:
		//puertos de entrada
        const Port &in;
        const Port &doneES;
		//puertos de salida
		Port &done;
		Port &solved;
		Port &out;

		//vairables de estado
		int cant_threads_libres;
		Value id_trabajo_actual;
		Value id_trabajo_finalizado;
		Estado S;
		Estado S_ant;
		VTime t_remanente;
		VTime t_comienzo;

		//parametros
		int max_threads;
		VTime tiempo_cambio_de_contexto;
		VTime tiempo_CPU;
};


#endif __SERVMT_H