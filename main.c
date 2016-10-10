#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_AEROPORTOS 1000
#define MAX_ID 4

/**********************   Diogo Redin   ********************************
*
*
*   PROGRAMA GESTAO AEROPORTUARIA - PROJETO I IAED
*   https://fenix.tecnico.ulisboa.pt/downloadFile/563568428736753/P1.pdf
*
*
***********************************************************************/

/***********************************************************************
*
*   INDEX
*
*	1. ESTRUTURAS
*		1.1. Aeroportos
*		1.2. Matriz
*		1.3. Inicializadores
*	
*	2. PROTOTIPOS
*		2.1. Funcoes Auxiliares
*		2.2. Comandos
*
*	3. CICLO PRINCIPAL
*
*	4. FUNCOES AUXILIARES
*		4.1. Encontra Aeroporto por ID
*		4.2. Encontra Aeroporto
*		4.3. Posicao Aeroporto
*		4.4. Imprime Aeroportos
*			4.4.1. Por Ordem Insercao
*			4.4.2. Alfabeticamente
*		4.5. Voos do Aeroporto
*		4.6. Voos do Sistema
*
*	5. COMANDOS
*		5.1.  A: Adiciona um novo aeroporto;
*		5.2.  I: Altera capacidade maxima de operacao de um aeroporto;
*		5.3.  F: Adiciona voo de ida e volta;
*		5.4.  G: Adiciona rota;
*		5.5.  R: Remove voo;
*		5.6.  S: Remove voo de ida e volta;
*		5.7.  N: Retorna numero voos;
*		5.8.  P: Aeroporto com o maior numero de voos;
*		5.9.  Q: Aeroporto mais conectado;
*		5.10. V: Voo mais popular;
*		5.11. C: Encerra aeroporto;
*		5.12. O: Reabre aeroporto;
*		5.13. L: Emite listagem;
*		5.14. X: Termina programa;
*
***********************************************************************/

/***********************************************************************
*
*   1. ESTRUTURAS
*
***********************************************************************/

/* 1.1. Aeroportos */
typedef struct {

	/*
	Identificacao: Identificador do aeroporto (3 caracteres)
	Capacidade: Capacidade maxima operacao (numero maximo voos)
	Estado: 0 - Encerrado / 1 - Aberto
	*/

	char identificacao[MAX_ID];
	int capacidade;
	int estado;
	int existe;

} s_Aeroporto;

typedef struct {

	/* Vetor de aeroportos */
	s_Aeroporto aeroportos[MAX_AEROPORTOS];
	int quantidade;

} s_Aeroportos;

/* 1.2. Matriz */
typedef struct {

	int matrix[MAX_AEROPORTOS][MAX_AEROPORTOS];
	int quantidade;

} s_Matriz;

/* 1.3. Inicializadores */
/* Cria array vazia com todos os aeroportos */
/* Pode ser acedida ao longo de todo o programa */
s_Aeroportos array;

/* Cria matriz vazia com as relacoes entre os aeroportos */
/* Linhas - Voos Partida // Colunas - Voos de Chegada */
/* Pode ser acedida ao longo de todo o programa */
s_Matriz m;

/***********************************************************************
*
*   2. PROTOTIPOS (p/ compilador)
*
***********************************************************************/

/* 2.1. Funcoes Auxiliares */
s_Aeroporto encontra_aeroporto();
s_Aeroporto encontra_aeroporto_por_ID( char id_introduzido[MAX_ID] );
void imprime_aeroportos( int criterio );
int aeroporto_posicao( s_Aeroporto aeroporto );
int voos_aeroporto( s_Aeroporto aeroporto );
int voos_sistema();

/* 2.2. Comandos */
void comando_A();
void comando_I();
void comando_F();
void comando_G();
void comando_R();
void comando_S();
void comando_N();
void comando_P();
void comando_Q();
void comando_V();
void comando_L();
void comando_C();
void comando_O();
void comando_X();

/***********************************************************************
*
*   3. CICLO PRINCIPAL
*
***********************************************************************/

int main() {

	/* Comando a executar */
	char executa;
	int i, j;

	/* Iniciamos matriz a 0 */
	for ( i=0; i < MAX_AEROPORTOS; ++i ) {
		for ( j=0; j < MAX_AEROPORTOS; ++j ) {
			m.matrix[i][j] = 0;
		}
	}

	/* Comecamos com 0 aeroportos e maximo definido */
	array.quantidade = 0;
	m.quantidade = MAX_AEROPORTOS;

	while (1) {

		/* le o comando */
		executa = getchar();

		switch ( executa ) {
			case 'A':

				comando_A();
				break;

			case 'I':

				comando_I();
				break;

			case 'F':

				comando_F();
				break;

			case 'G':

				comando_G();
				break;

			case 'R':

				comando_R();
				break;

			case 'S':

				comando_S();
				break;

			case 'N':

				comando_N();
				break;

			case 'P':

				comando_P();
				break;

			case 'Q':

				comando_Q();
				break;

			case 'V':

				comando_V();
				break;

			case 'L':

				comando_L();
				break;

			case 'C':

				comando_C();
				break;

			case 'O':

				comando_O();
				break;

			case 'X':

				/* Imprime Info */
				comando_X();

				/* Termina o programa com sucesso */
				return EXIT_SUCCESS;

				break;

		}

	}

	return EXIT_FAILURE;
}

/***********************************************************************
*
*   4. FUNCOES AUXILIARES
*
***********************************************************************/

/* 4.1. Encontra Aeroporto por ID */
s_Aeroporto encontra_aeroporto_por_ID( char id_introduzido[MAX_ID] ) {

	/* Aeroporto inexistente para retornar caso n seja encontrado nenhum */
	s_Aeroporto aeroporto_inexistente;
	aeroporto_inexistente.existe = 0;
	aeroporto_inexistente.estado = 0;
	strcpy( aeroporto_inexistente.identificacao, id_introduzido );

	/* Inicializadores */
	int aeroporto_posicao = 0;
	char aeroporto_lido_ID[MAX_ID];
	s_Aeroporto aeroporto_lido;

	aeroporto_lido = array.aeroportos[aeroporto_posicao];
	strcpy(aeroporto_lido_ID, aeroporto_lido.identificacao);

	/* Lemos aeroportos da array enquanto o ID n for igual ao procurado */
	while ( strcmp( aeroporto_lido_ID, id_introduzido) != 0 ) {

		aeroporto_posicao = aeroporto_posicao + 1;

		aeroporto_lido = array.aeroportos[aeroporto_posicao];
		strcpy(aeroporto_lido_ID, aeroporto_lido.identificacao);

		/* Se vai ultrapassar array sai */
		if ( aeroporto_posicao + 1 > array.quantidade || aeroporto_posicao + 1 == aeroporto_posicao ) {
			break;
		}

	}

	/* Possivel novo aeroporto */
	aeroporto_lido = array.aeroportos[aeroporto_posicao];

	/* Se estava dentro da array retorna o aeroporto caso contrario retorna vazio */
	if ( ( aeroporto_posicao > array.quantidade ) ||
		 ( strlen( aeroporto_lido.identificacao ) != 3 ) ) {
		return aeroporto_inexistente;
	} else {
		return aeroporto_lido;
	}

}

/* 4.2. Encontra Aeroporto */
s_Aeroporto encontra_aeroporto() {

	/* Pede ID do aeroporto */
	char aeroporto_introduzido[MAX_ID];
	scanf("%s", aeroporto_introduzido);

	/* Aeroporto */
	s_Aeroporto aeroporto_encontrado;
	
	/* Encontra o aeroporto pelo ID introduzido */
	aeroporto_encontrado = encontra_aeroporto_por_ID( aeroporto_introduzido );

	return aeroporto_encontrado;
}

/* 4.3. Posicao Aeroporto */
int aeroporto_posicao( s_Aeroporto aeroporto ) {

	/* Inicializadores */
	int aeroporto_posicao = 0;
	char aeroporto_lido_ID[MAX_ID];
	s_Aeroporto aeroporto_lido;

	aeroporto_lido = array.aeroportos[aeroporto_posicao];
	strcpy(aeroporto_lido_ID, aeroporto_lido.identificacao);

	/* Lemos aeroportos da array enquanto o ID n for igual ao procurado */
	while ( strcmp( aeroporto_lido_ID, aeroporto.identificacao ) != 0 ) {

		aeroporto_posicao = aeroporto_posicao + 1;

		aeroporto_lido = array.aeroportos[aeroporto_posicao];
		strcpy(aeroporto_lido_ID, aeroporto_lido.identificacao);

	}

	return aeroporto_posicao;
}

/* 4.4. Imprime Aeroportos */
void imprime_aeroportos( int criterio ) {

	/* Iteradores */
	int i, j;

	/* Valores */
	int linha = 0;
	int coluna = 0;

	/* Criterio = 0 - Imprime por ordem de insercao no sistema */
	if ( criterio == 0 ) {

		/* Percorre linhas */
		for ( i=0; i < array.quantidade; ++i ) {

			/* Percorre elementos da linha */
			for ( j=0; j < array.quantidade; ++j ) {

				/* Soma elementos */
				linha += m.matrix[i][j];
				coluna += m.matrix[j][i];

			}

			/* Aeroporto */
			s_Aeroporto aeroporto = array.aeroportos[i];

			/* Imprime aeroporto */
			printf("%s:%d:%d:%d\n", aeroporto.identificacao, aeroporto.capacidade, linha, coluna);

			/* Reset */
			linha = 0;
			coluna = 0;

		}

	/* Criterio = 1 - Imprime alfabeticamente */
	} else {

		/* Aeroporto temporario */
		s_Aeroporto aeroporto;

		/* Valores */
		char ids[MAX_AEROPORTOS][MAX_ID];
		char temp[MAX_ID];
		int posi_aeroporto = 0;

		/* Cria array com os IDs */
		for (i = 0; i < array.quantidade; ++i) {
			aeroporto = array.aeroportos[i];
			strcpy( ids[i], aeroporto.identificacao );
		}

		/* Ordena os IDs */
		for (i = 0; i < array.quantidade - 1; ++i) {
			for (j = 0; j < array.quantidade - 1; ++j) {

				if (strcmp (ids[j], ids[j+1]) > 0) {
					strcpy (temp, ids[j]);
					strcpy (ids[j], ids[j+1]);
					strcpy (ids[j+1], temp);
				}

			}
		}

		/* Imprime os IDs // Percorre linhas */
		for (i = 0; i < array.quantidade; ++i) {

			/* Procura o ID */
			aeroporto = encontra_aeroporto_por_ID( ids[i] );

			/* Posicao aeroporto na array original <=> matriz */
			posi_aeroporto = aeroporto_posicao( aeroporto );

			/* Percorre elementos da linha / coluna */
			for ( j=0; j < array.quantidade; ++j ) {

				/* Soma elementos */
				linha += m.matrix[posi_aeroporto][j];
				coluna += m.matrix[j][posi_aeroporto];

			}

			/* Imprime aeroporto */
			printf("%s:%d:%d:%d\n", aeroporto.identificacao, aeroporto.capacidade, linha, coluna);

			/* Reset */
			linha = 0;
			coluna = 0;

		}

	}

}

/* 4.5. Voos do Aeroporto */
int voos_aeroporto( s_Aeroporto aeroporto ) {

	/* Iterador */
	int i;

	/* Contadores */
	int linha = 0;
	int coluna = 0;
	int total = 0;

	/* Posicao */
	int posi_aeroporto = 0;

	/* Posicao na array */
	posi_aeroporto = aeroporto_posicao( aeroporto );

	/* Percorre elementos da linha */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Soma elementos */
		if ( posi_aeroporto != i ) {
			linha += m.matrix[posi_aeroporto][i];
			coluna += m.matrix[i][posi_aeroporto];
		}

	}

	total = linha + coluna;

	return total;

}

/* 4.6. Voos do Sistema */
int voos_sistema() {

	/* Iteradores */
	int i;
	int j;

	/* Contadores */
	int total = 0;

	/* Percorre aeroportos */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Percorre elementos */
		for ( j=0; j < array.quantidade; ++j ) {

			/* Soma elementos */
			total += m.matrix[i][j];

		}

	}

	return total;
}

/***********************************************************************
*
*   5.1. COMANDOS
*	A: Adiciona um novo aeroporto
*
***********************************************************************/

void comando_A() {

	/* Cria novo Aeroporto */
	s_Aeroporto aeroporto_novo;
	s_Aeroporto aeroporto_teste_array;

	/* Capacidade Default */
	aeroporto_novo.capacidade = 0;

	/* Pede ID e capacidade do novo aeroporto */
	scanf("%s", aeroporto_novo.identificacao);
	scanf("%d", &aeroporto_novo.capacidade);

	/* Testa se nao existe ja na array */
	aeroporto_teste_array = encontra_aeroporto_por_ID( aeroporto_novo.identificacao );

	if ( ( strlen( aeroporto_novo.identificacao ) == 3 ) && 
		 ( aeroporto_novo.capacidade > 0 || aeroporto_novo.capacidade == 0 ) && 
		 ( aeroporto_teste_array.existe == 0 ) ) {

		/* Existe */
		aeroporto_novo.existe = 1;

		/* Estado */
		aeroporto_novo.estado = 1;

		/* Guarda novo aeroporto na array */
		array.aeroportos[array.quantidade] = aeroporto_novo;

		/* Atualiza tamanho da array */
		array.quantidade += 1;

	}

}

/***********************************************************************
*
*   5.2. COMANDOS
*	I: Altera capacidade maxima de operacao de um aeroporto
*
***********************************************************************/

void comando_I() {

	int posicao_array = 0;
	int voos = 0;
	int nova_capacidade = 0;

	/* Pede ID do aeroporto e encontra-o na array */
	s_Aeroporto aeroporto = encontra_aeroporto();

	/* Verifica se aeroporto existe e esta aberto */
	if ( ( aeroporto.existe == 1 ) && ( aeroporto.estado == 1 ) ) {

		/* Guarda a posicao do aeroporto na array para o atualizar no final */
		posicao_array = aeroporto_posicao( aeroporto );

		/* Voos Aeroporto */
		voos = voos_aeroporto( aeroporto );

		/* Le nova capacidade */
		scanf("%d", &nova_capacidade);

		if ( ( voos > ( nova_capacidade + aeroporto.capacidade ) ) || 
			 ( ( nova_capacidade + aeroporto.capacidade ) < 0 ) ) {

			printf("*Capacidade de %s inalterada\n", aeroporto.identificacao);

		} else {

			/* Guarda aeroporto modificado na array */
			aeroporto.capacidade = aeroporto.capacidade + nova_capacidade;
			array.aeroportos[posicao_array] = aeroporto;

		}

	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( strlen( aeroporto.identificacao ) == 3 ) {
			printf("*Capacidade de %s inalterada\n", aeroporto.identificacao);
		}

	}

}

/***********************************************************************
*
*   5.3. COMANDOS
*	F: Adiciona voo de ida e volta
*
***********************************************************************/

void comando_F() {

	/* Contadores */
	int capacidade_a = 0;
	int capacidade_b = 0;
	int voos_a = 0;
	int voos_b = 0;

	/* Pede ID dos aeroportos e encontra-os na array */
	/* a - partida / b - chegada */
	s_Aeroporto aeroporto_a = encontra_aeroporto();
	s_Aeroporto aeroporto_b = encontra_aeroporto();

	/* Verifica se aeroportos existem e estao abertos */
	if ( ( aeroporto_a.existe == 1 && aeroporto_b.existe == 1 ) &&
		 ( aeroporto_a.estado == 1 && aeroporto_b.estado == 1 )
		 ) {

		/* Capacidade e Voos */
		capacidade_a = aeroporto_a.capacidade;
		capacidade_b = aeroporto_b.capacidade;
		voos_a = voos_aeroporto( aeroporto_a );
		voos_b = voos_aeroporto( aeroporto_b );

		/* Encontra a posicao dos aeroportos na array para consultar a matriz */
		int posi_aeroporto_a = aeroporto_posicao( aeroporto_a );
		int posi_aeroporto_b = aeroporto_posicao( aeroporto_b );

		/* Testa se ultrapssa capacidade */
		if ( ( voos_a + 2 > capacidade_a ) || ( voos_b + 2 > capacidade_b ) ) {

			printf("*Impossivel adicionar voo RT %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);

		} else {

			/* Adiciona voo de a -> b */
			m.matrix[posi_aeroporto_a][posi_aeroporto_b] += 1;

			/* Adiciona voo de b -> a */
			m.matrix[posi_aeroporto_b][posi_aeroporto_a] += 1;

		}

	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( ( strlen( aeroporto_a.identificacao ) == 3 ) && ( strlen( aeroporto_b.identificacao ) == 3 ) ) {
			printf("*Impossivel adicionar voo RT %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);
		}

	}

}

/***********************************************************************
*
*   5.4. COMANDOS
*	G: Adiciona rota
*
***********************************************************************/

void comando_G() {

	/* Contadores */
	int capacidade_a = 0;
	int capacidade_b = 0;
	int voos_a = 0;
	int voos_b = 0;

	/* Pede ID dos aeroportos e encontra-os na array */
	/* a - partida / b - chegada */
	s_Aeroporto aeroporto_a = encontra_aeroporto();
	s_Aeroporto aeroporto_b = encontra_aeroporto();

	/* Verifica se aeroportos existem e estao abertos */
	if ( ( aeroporto_a.existe == 1 && aeroporto_b.existe == 1 ) &&
		 ( aeroporto_a.estado == 1 && aeroporto_b.estado == 1 )
		 ) {

		/* Capacidade e Voos */
		capacidade_a = aeroporto_a.capacidade;
		capacidade_b = aeroporto_b.capacidade;
		voos_a = voos_aeroporto( aeroporto_a );
		voos_b = voos_aeroporto( aeroporto_b );

		/* Verifica se tem capacidade para voo */
		if ( ( voos_a + 1 > capacidade_a ) || ( voos_b + 1 > capacidade_b ) ) {

			printf("*Impossivel adicionar voo %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);

		} else {

			/* Encontra a posicao dos aeroportos na array para consultar a matriz */
			int posi_aeroporto_a = aeroporto_posicao( aeroporto_a );
			int posi_aeroporto_b = aeroporto_posicao( aeroporto_b );

			/* Adiciona voo a -> b */
			m.matrix[posi_aeroporto_a][posi_aeroporto_b] += 1;

		}

	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( ( strlen( aeroporto_a.identificacao ) == 3 ) && ( strlen( aeroporto_b.identificacao ) == 3 ) ) {
			printf("*Impossivel adicionar voo %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);
		}

	}

}

/***********************************************************************
*
*   5.5. COMANDOS
*	R: Remove voo
*
***********************************************************************/

void comando_R() {

	/* Pede ID dos aeroportos e encontra-os na array */
	/* a - partida / b - chegada */
	s_Aeroporto aeroporto_a = encontra_aeroporto();
	s_Aeroporto aeroporto_b = encontra_aeroporto();

	/* Verifica se aeroportos existem e estao abertos */
	if ( ( aeroporto_a.existe == 1 && aeroporto_b.existe == 1 ) &&
		 ( aeroporto_a.estado == 1 && aeroporto_b.estado == 1 )
		 ) {

		/* Encontra a posicao dos aeroportos na array para consultar a matriz */
		int posi_aeroporto_a = aeroporto_posicao( aeroporto_a );
		int posi_aeroporto_b = aeroporto_posicao( aeroporto_b );

		/* Testa se ha voos para remover */
		if ( m.matrix[posi_aeroporto_a][posi_aeroporto_b] - 1 < 0 ) {

			printf("*Impossivel remover voo %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);

		} else {

			/* Remove voo a -> b */
			m.matrix[posi_aeroporto_a][posi_aeroporto_b] -= 1;

		}
	
	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( ( strlen( aeroporto_a.identificacao ) == 3 ) && ( strlen( aeroporto_b.identificacao ) == 3 ) ) {
			printf("*Impossivel remover voo %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);
		}

	}

}

/***********************************************************************
*
*   5.6. COMANDOS
*	S: Remove voo de ida e volta
*
***********************************************************************/

void comando_S() {

	/* Pede ID dos aeroportos e encontra-os na array */
	/* a - partida / b - chegada */
	s_Aeroporto aeroporto_a = encontra_aeroporto();
	s_Aeroporto aeroporto_b = encontra_aeroporto();

	/* Verifica se aeroportos existem e estao abertos */
	if ( ( aeroporto_a.existe == 1 && aeroporto_b.existe == 1 ) &&
		 ( aeroporto_a.estado == 1 && aeroporto_b.estado == 1 )
		 ) {

		/* Encontra a posicao dos aeroportos na array para consultar a matriz */
		int posi_aeroporto_a = aeroporto_posicao( aeroporto_a );
		int posi_aeroporto_b = aeroporto_posicao( aeroporto_b );

		/* Testa voo se pode remover voo a <-> b */
		if ( ( m.matrix[posi_aeroporto_a][posi_aeroporto_b] - 1 < 0 ) ||
		     ( m.matrix[posi_aeroporto_b][posi_aeroporto_a] - 1 < 0 ) ) {

			printf("*Impossivel remover voo RT %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);

		} else {

			/* Remove voo de a <-> b */
			m.matrix[posi_aeroporto_a][posi_aeroporto_b] -= 1;

			/* Remove voo de b <-> a */
			m.matrix[posi_aeroporto_b][posi_aeroporto_a] -= 1;

		}

	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( ( strlen( aeroporto_a.identificacao ) == 3 ) && ( strlen( aeroporto_b.identificacao ) == 3 ) ) {
			printf("*Impossivel remover voo RT %s %s\n", aeroporto_a.identificacao, aeroporto_b.identificacao);
		}

	}

}

/***********************************************************************
*
*   5.7. COMANDOS
*	N: Numero de voos entre duas cidades
*
***********************************************************************/

void comando_N() {

	/* Contadores */
	int a = 0;
	int b = 0;

	/* Pede ID dos aeroportos e encontra-os na array */
	/* a - partida / b - chegada */
	s_Aeroporto aeroporto_a = encontra_aeroporto();
	s_Aeroporto aeroporto_b = encontra_aeroporto();

	if ( ( aeroporto_a.existe == 1 ) && ( aeroporto_b.existe == 1 ) ) {

		/* Encontra a posicao dos aeroportos na array para consultar a matriz */
		int posi_aeroporto_a = aeroporto_posicao( aeroporto_a );
		int posi_aeroporto_b = aeroporto_posicao( aeroporto_b );

		/* Voos de a -> b */
		a = m.matrix[posi_aeroporto_a][posi_aeroporto_b];
		b = m.matrix[posi_aeroporto_b][posi_aeroporto_a];

		printf("Voos entre cidades %s:%s:%d:%d\n", aeroporto_a.identificacao, aeroporto_b.identificacao, a, b);

	} else {

		/* Testa se foi introduzido formato valido de ID */
		if ( ( strlen( aeroporto_a.identificacao ) == 3 ) && ( strlen( aeroporto_b.identificacao ) == 3 ) ) {
			if ( aeroporto_a.existe == 0 ) { printf("*Aeroporto %s inexistente\n", aeroporto_a.identificacao); }
			if ( aeroporto_b.existe == 0 ) { printf("*Aeroporto %s inexistente\n", aeroporto_b.identificacao); }
		}

	}

}

/***********************************************************************
*
*   5.8. COMANDOS
*	P: Aeroporto com o maior numero de voos
*
***********************************************************************/

void comando_P() {

	/* Valores */
	int linha = 0;
	int coluna = 0;
	int maior = 0;
	int temp = 0;
	int posi_aeroporto = 0;

	/* Iterador */
	int i = 0;

	/* Aeroporto */
	s_Aeroporto aeroporto_mais_rotas;

	/* Array com totais de voos por aeroporto */
	int totais[array.quantidade];

	/* Percorre aeroportos */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Coloca na array nr de voos */
		totais[i] = voos_aeroporto(array.aeroportos[i]);

	}

	/* Encontra maior */
	for ( i=0; i < array.quantidade; ++i ) {

		if ( totais[i] > temp ) {
			temp = totais[i];
			maior = i;
		}

	}

	aeroporto_mais_rotas = array.aeroportos[maior];
	posi_aeroporto = aeroporto_posicao( aeroporto_mais_rotas );

	/* Percorre aeroportos */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Soma elementos */
		linha += m.matrix[posi_aeroporto][i];
		coluna += m.matrix[i][posi_aeroporto];

	}

	printf("Aeroporto com mais rotas %s:%d:%d\n", aeroporto_mais_rotas.identificacao, linha, coluna);

}

/***********************************************************************
*
*   5.9. COMANDOS
*	Q: Aeroporto mais conectado
*
***********************************************************************/

void comando_Q() {

	/* Valores */
	int maior = 0;
	int posicao_array = 0;
	int i, j;

	/* Array com conexoes ordenadas por aeroporto */
	int conexoes[MAX_AEROPORTOS + 1] = {0};

	/* Percorre Aeroportos */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Percorre Voos */
		for ( j=0; j < array.quantidade; ++j ) {

			/* Verifica existencia */
			if ( m.matrix[i][j] != 0 ) {
				conexoes[i] += 1;
			}

			/* Verifica existencia */
			if ( m.matrix[j][i] != 0 && m.matrix[i][j] == 0 ) {
				conexoes[i] += 1;
			}

		}

	}

	/* Encontra maior */
	for ( i=0; i < array.quantidade + 1; ++i ) {

		if ( conexoes[i] > maior ) {
			maior = conexoes[i];
			posicao_array = i;
		}

	}

	s_Aeroporto aeroporto = array.aeroportos[posicao_array];

	printf("Aeroporto com mais ligacoes %s:%d\n", aeroporto.identificacao, maior);

}

/***********************************************************************
*
*   5.10. COMANDOS
*	V: Voo mais popular
*
***********************************************************************/

void comando_V() {

	/* Valores */
	int maior = 0;
	int linha = 0;
	int coluna = 0;

	/* Iteradores */
	int i;
	int j;

	/* Percorre linhas (partidas) */
	for ( i=0; i < array.quantidade; ++i ) {

		/* Percorre elementos da linha */
		for ( j=0; j < array.quantidade; ++j ) {

			/* Encontra maior */
			if ( m.matrix[i][j] > maior ) {

				maior = m.matrix[i][j];

				linha = i;
				coluna = j;
			}

		}

	}

	/* Aeroportos: Partida - a / Chegada - b */
	s_Aeroporto aeroporto_a = array.aeroportos[linha];
	s_Aeroporto aeroporto_b = array.aeroportos[coluna];
	printf("Voo mais popular %s:%s:%d\n", aeroporto_a.identificacao, aeroporto_b.identificacao, maior);

}

/***********************************************************************
*
*   5.11. COMANDOS
*	C: Encerra aeroporto
*
***********************************************************************/

void comando_C() {

	/* Inicializa */
	int i;
	int posi_aeroporto = 0;

	/* Pede ID do aeroporto e encontra-o na array */
	s_Aeroporto aeroporto = encontra_aeroporto();

	/* Verifica se esta definido ou nao esta encerrado */
	if ( aeroporto.existe == 0 ) {
		if ( strlen( aeroporto.identificacao ) == 3 ) {
			printf("*Aeroporto %s inexistente\n", aeroporto.identificacao);
		}
	} else {

		/* Posicao na array */
		posi_aeroporto = aeroporto_posicao( aeroporto );

		/* Altera estado aeroporto */
		aeroporto.estado = 0;

		/* Remove voos partida e chegada */
		for ( i=0; i < array.quantidade; ++i ) {
			m.matrix[posi_aeroporto][i] = 0;
			m.matrix[i][posi_aeroporto] = 0;
		}

		/* Guarda aeroporto modificado na array */
		array.aeroportos[posi_aeroporto] = aeroporto;

	}

}

/***********************************************************************
*
*   5.12. COMANDOS
*	O: Reabre aeroporto
*
***********************************************************************/

void comando_O() {

	/* Inicializa */
	int i;
	int posi_aeroporto = 0;

	/* Pede ID do aeroporto e encontra-o na array */
	s_Aeroporto aeroporto = encontra_aeroporto();

	/* Verifica se esta definido */
	if ( aeroporto.existe == 0 ) {
		if ( strlen( aeroporto.identificacao ) == 3 ) {
			printf("*Aeroporto %s inexistente\n", aeroporto.identificacao);
		}
	} else {

		/* Posicao na array */
		posi_aeroporto = aeroporto_posicao( aeroporto );

		/* Altera estado aeroporto */
		aeroporto.estado = 1;

		/* Inicializa voos partida e chegada */
		for ( i=0; i < array.quantidade; ++i ) {
			m.matrix[posi_aeroporto][i] = 0;
			m.matrix[i][posi_aeroporto] = 0;
		}

		/* Guarda aeroporto modificado na array */
		array.aeroportos[posi_aeroporto] = aeroporto;

	}

}

/***********************************************************************
*
*   5.13. COMANDOS
*	L: Emitir listagem
*
***********************************************************************/

void comando_L() {

	/* Comando a executar */
	int comando = 0;

	/* Valores */
	int nr_voos = 0;
	int i = 0;

	/* Array com conexoes ordenadas por aeroporto */
	int conexoes[MAX_AEROPORTOS + 1] = {0};

	/* Recebe Comando */
	scanf("%d", &comando);

	/* Imprime aeroportos - 0 original */
	if ( comando == 0 ) {
		imprime_aeroportos(0);
	}

	/* Imprime aeroportos - 1 sorted */
	if ( comando == 1 ) {
		imprime_aeroportos(1);
	}

	/* Imprime histograma */
	if ( comando == 2 ) {

		/* Percorre aeroportos */
		for ( i=0; i < array.quantidade; ++i ) {

			/* Nr de voos do aeroporto */
			nr_voos = voos_aeroporto(array.aeroportos[i]);

			/* No indice correspondente ao nr de voos adiciona uma ocorrencia */
			conexoes[nr_voos] = conexoes[nr_voos] + 1;

		}

		/* Percorre ocorrencias */
		for ( nr_voos=0; nr_voos < MAX_AEROPORTOS + 1; ++nr_voos ) {
				
			/* Se houve ocorrencia */
			if ( conexoes[nr_voos] != 0 ) {

				/* Ocorrencia / Nr ocorrencias */
				printf("%d:%d\n", nr_voos, conexoes[nr_voos]);

			}

		}

	}

}

/***********************************************************************
*
*   5.14. COMANDOS
*	X: Termina programa
*
***********************************************************************/

void comando_X() {

	/* Nr. Voos Sistema */
	int nr_voos;

	/* Nr. Aeroportos */
	int nr_aeroportos;

	nr_voos = voos_sistema();
	nr_aeroportos = array.quantidade;

	/* Imprime Nvoos:Naeroportos */
	printf("%d:%d\n", nr_voos, nr_aeroportos);

}