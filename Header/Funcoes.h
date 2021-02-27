/* --- Fun��es ---*/

//define quantidade de nucleos
void DefineNucleos(){
	
	//configura��o para informa��es do sistema
	#ifdef _WIN32 
		#ifndef _SC_NPROCESSORS_ONLN
			SYSTEM_INFO info;
			GetSystemInfo(&info);
			#define sysconf(a) info.dwNumberOfProcessors
			#define _SC_NPROCESSORS_ONLN
		#endif
	#endif
	
	//numero de nucleos dispon�veis
	nprocs = sysconf(_SC_NPROCESSORS_ONLN); 
	
}	

//inicia a fila
void IniciaFila(struct Fila *fila){
	fila->frente = 0;
	fila->tras = 0;
	strcpy(fila->linha[fila->frente].conteudo, "");
}

//enfileira
void Enfileira(struct Fila *fila){
	
	//vari�vel que representa uma linha
	struct Linha l;
	
	//Leitura do arquivo
	FILE *pont_arq;
 	char texto_str[tamLinha];
  
	//abrindo o arquivo_frase em modo "somente leitura"
	pont_arq = fopen("./Arquivo/arquivo.txt", "r");
	
	//enquanto n�o for fim de arquivo o looping ser� executado e ser� impresso o texto
	while(fgets(texto_str, tamLinha, pont_arq) != NULL){
		
		//adiciona valores a struct linha
			strcpy(l.conteudo, texto_str);
			
			//enfileira linha
			strcpy(fila->linha[fila->tras].conteudo, l.conteudo);
			fila->tras=fila->tras+1;	
		
	}
	
		
}

//desenfileira uma posicao da fila
int Desenfileira(struct Fila *fila){
		
	//variaveis de intera��o
	int i=0, j=0, k=0;
	
	//string que representa uma linha
	char l[tamLinha] = "";
	
	//zona cr�tica executada pelas threads uma por vez
	#pragma omp critical 
	{
		//se ainda existir elementos na fila
		if (fila->frente < fila->tras){
			
			//transforma linha em mai�sculas
			for (i=0;i<strlen(fila->linha[fila->frente].conteudo);i++){
				l[i] = toupper (fila->linha[fila->frente].conteudo[i]);	
			}
		
			//executa fun��o de contagem de ocorrencias
		    Substring_count(l, palavra);
		}
		
	    //desenfileira uma posicao
		fila->frente += 1;
	}
	
	//verifica se j� n�o percorreu toda a fila
	if (fila->frente > fila->tras){
		return 0;
	}
	
	return 1;
}

//fun��o que faz a contagem de ocorrencias de substring em string
void Substring_count(char* string, char* substring) {
	int i, j, l1, l2;
	int found = 0;
	
	//tamanho das strings	
	l1 = strlen(string);
	l2 = strlen(substring);
	
	for(i = 0; i < l1; i++) {
		found = 1;
		for(j = 0; j < l2; j++) {
		  if(string[i+j] != substring[j]) {
		    found = 0;
		    break;
		  }
		}
		
		if(found == 1) {
	 		contador++;
  			i = i + l2 -1;
	   	}			
	}
	
}

//Fun��o teste para exibir a fila
void ExibeFila(struct Fila *fila){
	int i;
	for (i=fila->frente;i<fila->tras;i++){
		printf ("%s", fila->linha[i].conteudo);
	}
	
}

//transforma palavra pesquisada em uppercase
void TransformaPalavra(char palavraPesquisada[]){
	
	//strcpy de palavra pesquisada
	strcpy(palavra, palavraPesquisada);
	
	int i; 
	
	//converte palavra para mai�scula
	for (i=0;i<strlen(palavra);i++){
		palavra[i] = toupper(palavra[i]);
	}
		
}

//exibe ocorrencias de palavra no texto
void ExibeOcorrencia(){
	
	printf ("----------- INFORMACOES DO SISTEMA -------------\n\n");
	printf ("       %d nucleos do processador em uso\n\n\n", nprocs);
	
	printf ("----------------- OCORRENCIAS ------------------\n\n");
	printf ("  %d ocorrencia(s) da palavra %s no texto\n", contador, palavra);
	
	
}


