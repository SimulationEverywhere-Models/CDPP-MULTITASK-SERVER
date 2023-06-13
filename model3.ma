[top]
components : servmt_cola
components : dispes_cola
components : gen@Generator
components : trans@Transducer
out : throughput
Link : out@gen in@servmt_cola
Link : out@gen arrived@trans
Link : solved@servmt_cola solved@trans
Link : out@servmt_cola in@dispes_cola
Link : done@dispes_cola done@servmt_cola
Link : throughput@trans throughput

[servmt_cola]
components : servMT@ServMT
components : cola1@Queue
in : in done
out : out solved
Link : in in@cola1
Link : done doneES@servMT
Link : out@servMT out
Link : solved@servMT solved
Link : out@cola1 in@servMT
Link : done@servMT done@cola1

[servMT]
max_threads : 3
tiempo_cambio_de_contexto : 00:00:40:000
tiempo_CPU : 00:00:10:000

[cola1]
preparation : 00:00:00:000

[dispes_cola]
components : disp@DispositivoES
components : cola2@Queue
out : done
in : in
Link : in in@cola2
Link : done@disp done
Link : out@cola2 in@disp
Link : done@disp done@cola2

[disp]
tam_ES : 30000
velocidad : 1

[cola2]
preparation : 00:00:00:000

[gen]
distribution : normal
mean : 2
deviation : 1

[trans]
frecuence : 00:10:00:000