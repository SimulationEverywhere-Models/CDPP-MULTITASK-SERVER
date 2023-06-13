/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "pmodeladm.h" 
#include "parsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "constgenerat.h" //class ConstGenerator
#include "servmt.h"
#include "dispositivoes.h"

void ParallelMainSimulator::registerNewAtomics()
{
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<ConstGenerator>() , "ConstGenerator" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<ServMT>() , "ServMT" ) ;
	SingleParallelModelAdm::Instance().registerAtomic( NewAtomicFunction<DispositivoES>() , "DispositivoES" ) ;
}
