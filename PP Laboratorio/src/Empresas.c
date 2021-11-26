#include "Empresas.h"


int ValidarIdEmpresas(eEmpresa listaEmpresas[], int tamanioEmpresas, int* id, char* mensaje)
{
	int retorno;
	int i;

	retorno = -1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && id != NULL)
	{
		do
		{
			IngresarEntero(mensaje, "\nID invalido", id, 2);

			for(i = 0; i < tamanioEmpresas; i++)
			{
				if(listaEmpresas[i].id == *id)
				{
					retorno = 0;
				}
			}

		}while(retorno != 0);
	}

	return retorno;
}

int BuscarPorId(eEmpresa listaEmpresas[], int tamanioEmpresas, eLocalidad listaLocalidades[], int tamanioLocalidades, char mensaje[])
{
	int retorno;
	int id;

	retorno = -1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && listaLocalidades != NULL && tamanioLocalidades > 0 && mensaje != NULL)
	{
		if(MostrarListaDeEmpresas(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades) == 1)
		{
			printf("\nAun no se hicieron altas");
		}
		else
		{
			ValidarIdEmpresas(listaEmpresas, tamanioEmpresas, &id, mensaje);

			retorno = BuscarPosicion(listaEmpresas, tamanioEmpresas, id);
		}
	}

	return retorno;
}

int BuscarPosicion(eEmpresa lista[], int tamanio, int id)
{
	int retorno;
	int i;

	retorno = 1;

	if(lista != NULL && tamanio > 0)
	{
		for(i = 0; i < tamanio; i++)
		{
			if(lista[i].id == id)
			{
				retorno = i;
			}
		}
	}

	return retorno;
}

//************************************************************************//

int BuscarPorIdPedido(ePedido listaPedido[], int tamanioPedido, char mensaje[], eEmpresa lista[], int tamanio)
{
	int retorno;
	int id;
	int retornoFuncion;

	retorno = -1;

	if(lista != NULL && tamanio > 0 && mensaje != NULL)
	{
		if(MostrarListaDePedidos(listaPedido, tamanioPedido, lista, tamanio) == 1)
		{
			printf("\nAun no se hicieron altas");
		}
		else
		{
			do
			{
				IngresarEntero(mensaje, "\nID invalido", &id, 2);

				retornoFuncion = BuscarPosicionPedido(listaPedido, tamanioPedido, id);
			}while(retornoFuncion == -1);

			retorno = retornoFuncion;
		}
	}

	return retorno;
}

//************************************************************************//

int InicializarEmpresas(eEmpresa lista[], int tamanio)
{
	int i;
	int retorno;

	retorno = -1;

	if(lista != NULL && tamanio > 0)
	{
		for(i = 0; i < tamanio; i++)
		{
			lista[i].isEmpty = TRUE;
			retorno = 0;
		}
	}

	return retorno;
}

//************************************************************************//

int Alta(eEmpresa lista[], int tamanio, eLocalidad listaLocalidades[], int tamanioLocalidad, int* idContador)
{
	int retorno;
	int i;

		retorno = -1;

	if(lista != NULL && tamanio > 0 && listaLocalidades != NULL && tamanio > 0 && idContador != NULL)
	{
		for(i = 0; i < tamanio; i++)
		{
			if(lista[i].isEmpty == TRUE)
			{
				lista[i] = UnaEmpresa(listaLocalidades, tamanioLocalidad, idContador);
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

eEmpresa UnaEmpresa(eLocalidad listaLocalidades[], int tamanioLocalidad, int* idContador)
{
	eEmpresa unaEmpresa;

	if(listaLocalidades != NULL && tamanioLocalidad > 0 && idContador != NULL)
	{
		if(GenerarId(idContador) != -1)
		{
			unaEmpresa.id = *idContador;

			IngresarCadena(unaEmpresa.nombre, "\nIngrese el nombre de la empresa: ", "\nIngreso invalido", 51, 2); //X
			IngresarEntero("\nIngrese el cuit: ", "\nIngreso invalido", &unaEmpresa.cuit, 2);
			IngresarCadena(unaEmpresa.direccion.calle, "\nIngrese la calle: ", "\nIngreso invalido", 51, 2);
			IngresarEntero("\nIngrese numero del edificio: ", "\nIngreso invalido", &unaEmpresa.direccion.numero, 2);

			MostrarListaLocalidades(listaLocalidades, tamanioLocalidad);
			do
			{
				IngresarEntero("\nIngrese el id de la localidad de la empresa: ", "\nIngreso invalido", &unaEmpresa.idLocalidad, 2);
			}while(ValidarId(listaLocalidades, tamanioLocalidad, unaEmpresa.idLocalidad) != 0);

			unaEmpresa.isEmpty = FALSE;
		}
		else
		{
			printf("\nNo se pudo generar el id");
		}
	}

	return unaEmpresa;
}

//************************************************************************//

int MostrarListaDeEmpresas(eEmpresa listaEmpresas[], int tamanioEmpresas, eLocalidad listaLocalidades[], int tamanioLocalidades)
{
	int retorno;
	int i;

	retorno = 1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && listaLocalidades != NULL && tamanioLocalidades > 0)
	{
		for(i = 0; i < tamanioEmpresas; i++)
		{
			if(listaEmpresas[i].isEmpty == FALSE)
			{
				MostrarUnaEmpresa(listaEmpresas[i], listaLocalidades, tamanioLocalidades);

				retorno = 0;
			}
		}
	}

	return retorno;
}

void MostrarUnaEmpresa(eEmpresa empresa, eLocalidad lista[], int tamanio)
{
	int index;

	if(lista != NULL && tamanio > 0)
	{
		index = BuscarLocalidadPorId(lista, tamanio, empresa.idLocalidad);

		if(index != -1)
		{
			printf("\n%d %s %d %s %d %s", empresa.id, empresa.nombre, empresa.cuit,
										empresa.direccion.calle, empresa.direccion.numero, lista[index].localidad);
		}
	}
}

int MostrarListaDePedidos(ePedido listaPedidos[], int tamanioPedido, eEmpresa listaEmpresas[], int tamanioEmpresas)
{
	int retorno;
	int i;

	retorno = 1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && listaPedidos != NULL && tamanioPedido > 0)
	{
		for(i = 0; i < tamanioPedido; i++)
		{
			if(listaPedidos[i].isEmpty == PENDIENTE)
			{
				MostrarUnPedido(listaPedidos[i], listaEmpresas[i]);

				retorno = 0;
			}
		}
	}

	return retorno;
}

void MostrarUnPedido(ePedido pedido, eEmpresa empresa)
{
	printf("\n%s: %d %.2f", empresa.nombre, pedido.id, pedido.cantidadKilos);
}

//************************************************************************//

int Modificar(eEmpresa listaEmpresas[], int tamanioEmpresas, eLocalidad listaLocalidades[], int tamanioLocalidades)
{
	int retorno;
	int index;
	int opcion;

	retorno = 1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && listaLocalidades != NULL && tamanioLocalidades > 0)
	{
		index = BuscarPorId(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades, "\nIngrese el ID de la empresa en la que quiere realizar una modificacion: ");

		if(index == -1)
		{
			printf("\nNo se encontro ningna empresa con ese id");
		}
		else
		{
			do
			{
				opcion = Menu("\n1. Direccion.\n2. Localidad.\n3. Direccion y localidad\n4. SALIR");

				switch(opcion)
				{
				case 1:
					if(ModificarDireccion(listaEmpresas, tamanioEmpresas, index) == 1)
					{
						printf("\nNo se pudo realizar la modificacion");
					}
					break;
				case 2:
					if(ModificarLocalidad(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades, index) == 1)
					{
						printf("\nNo se pudo realizar la modificacion");
					}
					break;
				case 3:
					if(ModificarDireccion(listaEmpresas, tamanioEmpresas, index) == 1)
					{
						printf("\nNo se pudo realizar la modificacion");
					}
					if(ModificarLocalidad(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades, index) == 1)
					{
						printf("\nNo se pudo realizar la modificacion");
					}
					break;
				case 4:
					printf("\nSALIR");
					break;
				default:
					printf("\nOpcion invalida");
				}
			}while(opcion != 4);

			MostrarUnaEmpresa(listaEmpresas[index], listaLocalidades, tamanioLocalidades);
		}
	}

	return retorno;
}

int ModificarDireccion(eEmpresa lista[], int tamanio, int index)
{
	int retorno;
	int i;
	char auxiliarCalle[51];
	int auxiliarNumero;

	retorno = 1;

	if(lista != NULL && tamanio > 0)
	{
		for(i = 0; i < tamanio; i++)
		{
			if(lista[i].isEmpty == FALSE)
			{
				if(i == index)
				{
					IngresarCadena(auxiliarCalle, "\nIngrese la calle: ", "\nIngreso invalido", 51, 2);
					IngresarEntero("\nIngrese numero del edificio: ", "\nIngreso invalido", &auxiliarNumero, 2);

					strncpy(lista[i].direccion.calle, auxiliarCalle, 51);
					lista[i].direccion.numero = auxiliarNumero;

					retorno = 0;
				}
			}
		}
	}

	return retorno;
}

int ModificarLocalidad(eEmpresa listaEmpresas[], int tamanio, eLocalidad listaLocalidades[], int tamanioLocalidades, int index)
{
	int retorno;
	int i;
	int auxiliarLocalidad;

	retorno = 1;

	if(listaEmpresas != NULL && tamanio > 0)
	{
		for(i = 0; i < tamanio; i++)
		{
			if(listaEmpresas[i].isEmpty == FALSE)
			{
				if(i == index)
				{
					MostrarListaLocalidades(listaLocalidades, tamanioLocalidades);
					IngresarEntero("\nIngrese el id de la nueva localidad: ", "Dato invalido", &auxiliarLocalidad, 2);

					listaEmpresas[i].idLocalidad = auxiliarLocalidad;

					retorno = 0;
				}
			}
		}
	}

	return retorno;
}

//************************************************************************//

int Baja(eEmpresa listaEmpresas[], int tamanioEmpresas, eLocalidad listaLocalidades[], int tamanioLocalidades)
{
	int retorno;
	int index;

	retorno = 1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0)
	{
		index = BuscarPorId(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades, "\nIngrese el ID de la empresa a la que desea dar de baja: ");

		if(index == -1)
		{
			printf("\nNo se encontro ningna empresa con ese ID");
		}
		else
		{
			if(CambiarEstado(listaEmpresas, tamanioEmpresas, index) == 1)
			{
				printf("No se pudo dar de baja");
			}
			else
			{
				printf("\n***********************************************");
				MostrarListaDeEmpresas(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades);
				printf("\n***********************************************");
			}
		}
	}

	return retorno;
}

int CambiarEstado(eEmpresa lista[], int tamanio, int index)
{
	int retorno;
    int i;
    int opcion;

	retorno = 1;

	if(lista != NULL && tamanio > 0)
	{
		for(i = 0; i < tamanio; i++)
		{
			if(lista[i].isEmpty == FALSE)
			{
				if(i == index)
				{
					IngresarEntero("\nIngrese 1 para confirmar la baja, o 0 para cancelarla: ", "Opcion invalida", &opcion, 2);

					if(opcion == 1)
					{
						lista[i].isEmpty = TRUE;
						retorno = 0;
					}
				}
			}
		}
	}

	return retorno;
}

//************************************************************************//

int CrearPedido(eEmpresa listaEmpresas[], int tamanioEmpresas, ePedido listaPedido[], int tamanioPedido, eLocalidad listaLocalidades[], int tamanioLocalidades, eTransporte listaTransportes[], int tamanioTransportes, int* idTransporte, int* idPedido)
{
	int retorno;
	int index;
	int i;

	retorno = -1;

	if(listaEmpresas != NULL && tamanioEmpresas > 0 && listaPedido != NULL && tamanioPedido > 0 && listaLocalidades != NULL && tamanioLocalidades > 0 && listaTransportes != NULL && tamanioTransportes > 0)
	{
		index = BuscarPorId(listaEmpresas, tamanioEmpresas, listaLocalidades, tamanioLocalidades, "\nIngrese el ID de la empresa en la que quiere agregar un pedido: ");

		for(i = 0; i < tamanioPedido; i++)
		{
			if(listaPedido[i].isEmpty == SIN_HACER)
			{
				if(IngresarCantidadDeKilosARecolectar(listaPedido, tamanioPedido, i, idPedido) == 0)
				{
					listaPedido[i].idEmpresa = listaEmpresas[index].id;

					printf("\n***********************************************************");
					MostrarUnPedido(listaPedido[i], listaEmpresas[index]);
					printf("\n***********************************************************");

					if(CargaDelTransporte(listaTransportes, tamanioTransportes, listaLocalidades, tamanioLocalidades, idTransporte) == 0)
					{
						listaPedido[i].idTransporte = *idTransporte;
						printf("\n%d", listaPedido[i].idTransporte);
						printf("\nFUNCIONO");
					}
					retorno = 0;

					break;
				}
			}
		}
	}

	return retorno;
}

//************************************************************************//

int ProcesarResiduos(ePedido listaPedido[], int tamanioPedido, eEmpresa lista[], int tamanio, eTransporte listaTransportes[], int tamanioTransportes)
{
	int retorno;
	int index;
	int retornoFuncion;

	retorno = -1;

	if(listaPedido != NULL && tamanioPedido > 0 && lista != NULL && tamanio > 0 && listaTransportes != NULL && tamanioTransportes > 0)
	{
		index = BuscarPorIdPedido(listaPedido, tamanio, "\nIngrese el ID del pedido que desea setear: ", lista, tamanio);

		do
		{
			retornoFuncion = IngresarCantidadDeKilosPorTipo(listaPedido, index);
		}while(retornoFuncion != 0);

		listaPedido[index].isEmpty = COMPLETADO;

		if(CambiarEstadoTransporte(listaPedido[index].idTransporte, listaTransportes, tamanio, ENVIADO) == 0)
		{
			printf("\nFUNCIONO");
		}

		MostrarCantidadPorTipoDePlatico(listaPedido[index]);

		retorno = 0;
	}

	return retorno;
}
