/*
 * res_SOLICITUD_PROCESAMIENTO.c
 */
#include <stdio.h>
#include <commons/collections/dictionary.h>
#include <utilidades/protocol/senders.h>
#include <utilidades/protocol/receive.h>
#include <unistd.h>

#include "../../serverYAMA/responses/responses.h"

YAMA_STATUS res_SOLICITUD_PROCESAMIENTO  (int socket,void*  data, t_dictionary* diccionario){
	payload_SOLICITUD_JOB* payload = data;
	printf("SOLICITUD_JOB recibida\n");
	printf("Archivo: %s, enviando informacion sobre workers\n",payload->nombreArchivo);

	send_JOB(socket,1);

	//DUMMIE WORKERS
	/*send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",38,10180,"Master1-temp38");
	send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",39,10180,"Master1-temp39");
	send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",44,10180,"Master1-temp44");

	sleep(5);*/

	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","Master1-temp38","Master1-tempredLoc1");
	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","Master1-temp39","Master1-tempredLoc1");
	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","Master1-temp44","Master1-tempredLoc1");
	send_FIN_LISTA(socket);

	// Recibir las respuestas de operaciones parciales
	/*int i;
	HEADER_T header;
	for(i = 0; i < 4; i++){
		receive(socket,&header);
	}*/
	HEADER_T header;
	receive(socket,&header);

	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","Master1-tempredLoc38"," ",0);
	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","Master1-tempredLoc39"," ",0);
	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","Master1-tempredLoc44","Master1-tempredGlob44",1);
	send_FIN_LISTA(socket);

	// Recibir respuesta de reduccion global
	receive(socket,&header);

	send_INFO_ALMACENAMIENTO(socket,9095,"127.0.0.1","Master1-tempredGlob44");

	// Recibir respuesta de almacenamiento
	receive(socket,&header);

	return EXITO;
};
