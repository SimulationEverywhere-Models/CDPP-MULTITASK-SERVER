#ifndef __DISPOSITIVOES_H
#define __DISPOSITIVOES_H

#include "atomic.h"


class DispositivoES: public Atomic {
	public:
		//Constructores
		DispositivoES(const string &name = "DispositivoES");

	protected:
		//funciones de transicion externa, interna y de output y de inicializacion
		Model& initFunction();
		Model& externalFunction(const ExternalMessage&);
		Model& internalFunction(const InternalMessage&);
		Model& outputFunction(const CollectMessage&);

	private:
		//puertos de entrada
        const Port &in;
        //puertos de salida
		Port &done;
		
		//vairables de estado
		Value id_trabajo_actual;

		//parametros
		int velocidad;
		int tam_ES;
};



#endif __DISPOSITIVOES_H