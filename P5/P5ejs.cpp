MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		

		
		
// Copiar esto dentro de la función main, ...

Dbg dbg(true);
vector<thread> hilos(NRO_HILOS);
contador = 0;
for (int i = 0; i < NRO_HILOS; i++) {
	HiloNoReentranteSimple(i);
}
dbg.Print("Contador vale: %d (cálculo secuencial)\n", contador);
contador = 0;
for (int i = 0; i < NRO_HILOS; i++) {
	hilos[i] = thread(HiloNoReentranteSimple, i);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();
dbg.Print("Contador vale: %d (cálculo con hilos)\n", contador);


dbg.Print("\nEjecución secuencial HiloNoReentranteNoTanSimple\n");

for (int i = 0; i < NRO_HILOS; i++)
	HiloNoReentranteNoTanSimple(i);

dbg.Print("\nEjecución con hilos HiloNoReentranteNoTanSimple\n");
for (int i = 0; i < NRO_HILOS; i++) {
	hilos[i] = thread(HiloNoReentranteNoTanSimple, i);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();

// << Hasta aquí


// puntos de entrada de los hilos
#define NRO_INCREMENTOS 10000
#define NRO_HILOS 10
static int contador = 0;


void HiloNoReentranteSimple(int nroHilo) {
	for (int i = 0; i < NRO_INCREMENTOS; i++) {
		contador += nroHilo + 1;
		contador -= nroHilo + 1;
		Sleep(0);  // No espera nada, solo fuerza más cambios de contexto
	}
}
void HiloNoReentranteNoTanSimple(int nroHilo) {
	// Código de HiloNoReentranteNoTanSimple
	printf("\n");
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("hilo %i iniciado >>", nroHilo);
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("<< hilo %i finalizado\n", nroHilo);
}



// Código para el ejercicio 17
HANDLE actual, siguiente;	
actual = CreateEventA(NULL, FALSE, FALSE, NULL);
dbg.CheckError(NULL == actual, 1, "Error al crear mútex");
dbg.Print("\nEjecución con hilos HiloNoReentranteNoTanSimple\n");
for (int i = 0; i < NRO_HILOS; i++) {
	siguiente = CreateEventA(NULL, FALSE, FALSE, NULL);
	hilos[i] = thread(HiloNoReentranteNoTanSimple, i, actual, siguiente);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	actual = siguiente;
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();



//////////////////////////////////////////////////
//   
// SESION 2.
/////////////////////////////

//Pasa a mayusculas LCMapString  en el servidor
LCMapStringA(LOCALE_USER_DEFAULT, LCMAP_UPPERCASE,BEntrada, Leidos, BEntrada, Leidos);
// Poner esta función tras la llamada a Beep(1000, 200);...
// y descomentar el envio de respuesta al cliente,,,
// Si enviamos respuesta al cliente:
















	Dbg dbg(true);
	std::cout.imbue(std::locale(""));
	dbg.CheckError(argc < 2, 1, "Falta el nombre del directorio");

	auto rutaDir = path(argv[1]);
	cout << "Calculando tamaño del directorio...\n\n";

	dbg.CronoInicio();
	auto archivos = dbg.ArchivosEnDirectorio(rutaDir.string().c_str());
	dbg.CronoFin();
	cout << archivos.size() << " Archivos en el directorio " << rutaDir.lexically_normal() << "\n   ";
	cout << "    Calculado en: " << dbg.CronoSegs << " segs \n\n";

	archivos.clear();
	dbg.CronoInicio();
	dbg.ArchivosEnDirectorioHilos(archivos, rutaDir.string().c_str());
	dbg.CronoFin();
	cout << archivos.size() << " Archivos en el directorio (varios hilos) " << rutaDir.lexically_normal() << "\n   ";
	cout << "    Calculado en: " << dbg.CronoSegs << " segs \n\n";





void Dbg::ArchivosEnDirectorioHilos(vector<path> & res, const char* nombreDir, bool imprimir)
{
	//// Enlentecer: Si ArchivosEnDirectorio tarda menos de 1 segundo, descomentar el for y copiarlo también a ArchivosEnDirectorio 
	////      para que se puedan comparar tiempos de ejecución 
	// for (volatile int i = 0; i < 1000 * 1000; i++) {}
	auto ruta = path(nombreDir);
	if (!exists(ruta))
	{
		Print("El directorio %s no existe\n", nombreDir);
	}
	else if (!is_directory(ruta))
	{
		Print("La ruta %s no es un directorio\n", nombreDir);
	}
	else {
		if (imprimir)
			printf("Archivos en el directorio %s:\n", nombreDir);
		for (auto x : directory_iterator(ruta)) {
			if (imprimir)
			{
				if (x.is_directory())
					cout << x.path().filename() << "  (Directorio)\n";
				else
					cout << x.path().filename() << '\n';
			}
			if (x.is_directory())
			{
				vector<path> nuevos;
				//Crea un hilo con un método como punto de entrada
				auto ruta = x.path().string();
				auto hilo= thread(&Dbg::ArchivosEnDirectorioHilos, this,  std::ref(nuevos), ruta.c_str(), imprimir);
				hilo.join();
				res.insert(res.end(), nuevos.begin(), nuevos.end());
			}
			else
			{
				res.push_back(x.path());
			}
		}
	}
}

















































