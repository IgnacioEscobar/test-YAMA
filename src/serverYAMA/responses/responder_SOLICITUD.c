/*
 * responder_SOLICITUD.c
 */

#include <utilidades/protocol/types.h>
#include <commons/collections/dictionary.h>
#include <stdio.h>
#include "../../serverYAMA/responses/responses.h"

YAMA_STATUS responder_SOLICITUD(int socket, HEADER_T tipoDeMensaje,void* data ,t_dictionary* diccionario){
	YAMA_STATUS status;
	switch (tipoDeMensaje){
		case SOLICITUD_JOB:
			status = res_SOLICITUD_PROCESAMIENTO   (socket, data, diccionario);
		break;
		default:
		break;
	}
	return status;
}
