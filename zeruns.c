#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAX 100


typedef struct Node{
	struct Node* next;
	int x;
	int y;
} Node;


typedef struct Node_Binary{
	struct Node_Binary* next;
	int test_0;
	int test_1;
	Node* change_ptr;
	int linha;
	int coluna;
} Node_Binary;


FILE *OpenFile ( char *, char * );
int readFile ( char *);
void Fill_Table ( FILE *, int , int **);
void Mutli_tables( char *, FILE *, int **, int * , int *);
int **Allocate_Table (int );
void WriteFile ( char *, char*, int , int , int , int ** );
void Board_info (FILE *, int * , int *);
void Free(int **, int );
int test_inicial(int **, int , int , int );
int test_pares_line(int **, int , int , int );
int test_pares_column(int **, int , int , int );
int test_trios_line(int **, int , int , int );
int test_trios_column(int **, int , int , int );
int test_complete_line(int **, int , int , int );
int test_complete_column(int **, int , int , int );
int test_check(int **, int , int , int , int*);

int run_test_check (int **, int *, Node_Binary *);
void run_test_check_ini (int **, int *);
int solve_game(int **, int *);
Node* clean_Board (Node* , int **);
Node_Binary* Reset(int **, Node_Binary* );
int test0 (int **, int , int , int *, Node_Binary *);
int test1 (int **, int , int , int *, Node_Binary *);
void free_list(Node_Binary *);

Node_Binary* add_front(Node_Binary* head_binary, int linha, int coluna){
	Node_Binary* new_node = (Node_Binary *)malloc(sizeof(Node_Binary));
	new_node->test_0 = 0;
	new_node->test_1 = 0;
	new_node->linha = linha;
	new_node->coluna = coluna;
	new_node->change_ptr = NULL;
	if(head_binary != NULL){
		new_node->next = head_binary;
		(head_binary) = new_node;
	}else{
		new_node->next = NULL;
		(head_binary) = new_node;
	}
	return head_binary;
}

Node* add_front_coord(Node* head, int x, int y){
	Node* new_node = (Node *)malloc(sizeof(Node));
	new_node->x = x;
	new_node->y = y;
	if(head != NULL){
		new_node->next = head;
		(head) = new_node;
	}else{
		new_node->next = NULL;
		(head) = new_node;
	}
	return head;
}



/***********************************************
*******testar 0***************************
*************************************************/
int test0 (int **Board, int linha, int coluna, int *size, Node_Binary *finds)
{
	int impossible;

	Board[linha][coluna] = 0;
	impossible = run_test_check(Board, size, finds);
	if (impossible == -69){
		finds->test_0 = 10;
	}
	else finds->test_0 = 11;

	return impossible;
}


/***********************************************
*******testar 1***************************
*************************************************/
int test1 (int **Board, int linha, int coluna, int *size, Node_Binary *finds)
{
	int impossible;

	Board[linha][coluna] = 1;
	impossible = run_test_check(Board, size, finds);
	if (impossible == -69){
		finds->test_1 = 10;
	}
	else finds->test_1 = 11;

	return impossible;
}



/*******************************************************
************** Reset **********************************
****volta a meter tudo a 9s e tests a 0****************************
**********************************************************/
Node_Binary* Reset(int **Board, Node_Binary* finds)
{
   Node_Binary* aux;

   Board[finds->linha][finds->coluna] = 9;

   finds->change_ptr = clean_Board (finds->change_ptr, Board);
   aux = finds;
   finds = finds -> next;
   free(aux);

   return finds;
}

Node * clean_Board (Node* head, int **Board)
{
	Node* tmp;
	
	while (head != NULL)
    {
       Board[head->x][head->y]=9;
       tmp = head;
       head = head->next;
       free(tmp);
    }

    return head;	
}

void free_list(Node_Binary *finds)
{
	Node_Binary *aux;
	Node *tmp;

	while(finds != NULL)
	{
		while (finds->change_ptr != NULL)
    	{
       		tmp = finds->change_ptr;
       		finds->change_ptr = finds->change_ptr->next;
       		free(tmp);
    	}

		aux=finds;
		finds=finds->next;
		free(aux);
	}
}

/***************************************
* percorrer matriz até encontrar um 9 e substituir por um 0
* construindo uma lista de listas
*******************************************/

int solve_game(int **Board, int *size)
{
	int linha, coluna, impossible , el_counter=0, tumae = 0, x=0;	
	Node_Binary *finds = NULL;

	for(;;){
		for (linha=0; linha<*size; linha++){
			for (coluna=0; coluna<*size; coluna++){

				if (Board[linha][coluna]==9 || tumae == 1){
					if(tumae == 0){
						x++;
						finds = add_front (finds, linha, coluna); /* aloca nó para a lista binaria */}

					tumae = 0;

					/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("1 \n");
				}*/

					if (finds->test_0 != 10){
						impossible = test0(Board, linha, coluna, size, finds); /* testa o valor 0 na matriz*/
						if (impossible != -69) continue;
					}

					/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("2 \n");}*/

					finds->change_ptr = clean_Board(finds->change_ptr, Board);

					/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("3 \n");}*/

					impossible = test1(Board, linha, coluna, size, finds);
					if (impossible != -69) continue;

					/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("4 \n");}*/

					if (finds -> next == NULL)
					{
						finds = Reset(Board, finds);
						return 0; /* 0 significa que n ha soluçao*/
					}

					finds = Reset(Board, finds);

					/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("5 \n");}*/

					while (finds->test_1 == 11){
						if (finds -> next == NULL){
							finds = Reset(Board, finds);
						 return 0;}

						/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("6 \n");}*/
						finds = Reset(Board, finds);

						/*if(linha == 7){
					for(i=0;i<*size;i++){
						for(j=0;j<*size;j++)
						printf("%d ", Board[j][i]);
						printf("\n");}
					printf("7 \n");}*/

						el_counter++;
						/*printf("contador %d\n", el_counter);*/
					}
					finds->test_0 = 10;
					tumae = 1;

					if (finds->coluna >= 0){
						coluna = (finds ->coluna)-1;
						linha = finds->linha;
					}
				}
				if (linha == *size-1 && coluna == *size-1){
					free_list(finds);
					return 1; /* significa que preencheu tudo*/
				}
			}
		}
	}
}




/******************************************************************************
 * OpenFile()
 *
 * Arguments: name - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/

FILE *OpenFile ( char *name, char *mode )
{
  FILE *f;
  f = fopen ( name, mode );
  if ( f == NULL ) {
    exit ( 0 );
  }
  return (f);
}

int readFile ( char *name)
{
	int size, variant, max=0, aux, i=0;
	FILE *f;
	f = OpenFile(name, "r");
	
	while(1)
	{
		if(fscanf(f, "%d %d", &size, &variant)==2)
		{
			if(size > max)
				max = size;
			for(i=0;i<size*size;i++)
				fscanf(f, "%d", &aux);
		}
		if(feof(f))
			break;
	}

	/*for(;fgets( line, MAX, f)!= NULL;)
	{
		aux = strtok(line, " ");
		size = atoi(aux);
		if(size > max)
			max = size;
		for(i=0;i<=size;i++){
			if(fgets( line, MAX, f)==NULL){
				fclose(f);
				return max;
			}
		}
	}*/

	fclose(f);
	return max;
}

void Board_info (FILE *f, int *variant, int *size)
{
	if(fscanf(f, "%d %d", size, variant)!=2)
		exit(0);
}


void Fill_Table ( FILE *f, int size, int **Board)
{
	int i=0 , j=0;

	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			fscanf(f,"%d",&Board[i][j]);
}

void run_test_check_ini (int **Board, int *size)
{
	int x;

	int Change, linha=0, coluna=0;
	while (1){
		Change = 0;
		for (linha = 0; linha < *size; linha++){
			for (coluna = 0; coluna < *size; coluna++){
				if (Board[linha][coluna] == 9){ 
					x = test_check(Board, *size, linha, coluna, &Change);
				}
			}
		}
		if (Change == 0 || x == 4) break;
	}
}

int run_test_check (int **Board, int *size, Node_Binary *finds )
{
	int Change, linha=0, coluna=0, test=0;
	while (1){
		Change = 0;
		for (linha = 0; linha < *size; linha++){
			for (coluna = 0; coluna < *size; coluna++){
				if (Board[linha][coluna] == 9){ 
					test = test_check(Board, *size, linha, coluna, &Change);
					if (test == 69) return -69;
					if (Change != 0) finds->change_ptr = add_front_coord(finds->change_ptr, linha, coluna);
				}
			}
		}
		if (Change == 0) break;
	}
	return 0;
}

void Mutli_tables( char *name, FILE *f, int **Board, int *variant, int *size)
{
	int game_state = 2;
	int contador=0;

	WriteFile (name,"w", *variant, *size, game_state, Board);

	while(1)
	{
		if (fscanf(f,"%d %d",size, variant) == 2){
			Fill_Table(f, *size, Board);
			run_test_check_ini (Board, size);

			game_state = solve_game(Board, size);

			contador++;

			WriteFile (name,"a+", *variant, *size, game_state, Board);
		}
		else if(feof(f))
			break;
	}
	printf("%d\n",contador);
} 


int **Allocate_Table (int size)
{
	int **Table = (int**) malloc ((size) * sizeof(int*));
	int i;

    if ( Table == NULL ) {
    	exit ( 0 );
  	}

	for (i=0; i<size; i++){
		Table[i] = (int*) malloc ((size) * sizeof(int));

	    if ( Table[i] == NULL ) {
    		exit ( 0 );
  		}
	}

	return Table;
}

void Free(int **Board, int size)
{
	int i;

	for (i=0; i<size; i++){
		free(Board[i]);
	}
	free(Board);
}


/******************************************************************************
 * WriteFile()
 *
 * Arguments: file - pointer to string holding name of file to save
 *            st_texto - pointer to structure where information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
void WriteFile ( char *name, char *mode, int variant, int size, int game_state, int **Board )
{
	int linha, coluna;
  char extension[7] = ".query";
  char *output_name = (char*) malloc ((strlen(name)+1+strlen(extension))*sizeof(char));

  strcpy (output_name , name);

  output_name[strlen(name)-4]='\0';

  FILE *f = fopen(strcat(output_name, extension), mode);

if(strcmp(mode,"w")!=0 && game_state == 0){
  fprintf (f, "%d %d -1\n\n", size, variant);
  return;
}

else if(strcmp(mode,"w")!=0 && game_state == 1){
  fprintf (f, "%d %d\n", size, variant);

  for (linha = 0; linha < size; linha++){
  	for (coluna = 0; coluna < size; coluna++){
  		fprintf (f, "%d ", Board[linha][coluna]);
  	}
  	fprintf(f, "\n");
  }
  fprintf(f, "\n");
}

  fclose (f);
  free(output_name);

  return;
}

int test_inicial(int **Board, int size, int linha, int coluna)
{
	int i;

	i = Board[linha][coluna];

	if(i!=9)
		return i;
	else return -1;
}

int test_pares_line_esquerdo(int **Board, int size, int linha, int coluna)
{
	int l1, r1;

	l1 = coluna-2;
	r1 = coluna-1;

	if(l1 >= 0 && r1 >= 0 && Board[linha][l1] == Board[linha][r1] &&  Board[linha][l1] == 0)
		return 1;
	else if(l1 >= 0 && r1 >= 0 && Board[linha][l1] == Board[linha][r1] &&  Board[linha][l1] == 1)
		return 0;
	else return -1;
}

int test_pares_line_direito(int **Board, int size, int linha, int coluna)
{
	int l2, r2;

	l2 = coluna+1;
	r2 = coluna+2;

	if(l2 < size && r2 < size && Board[linha][l2] == Board[linha][r2] &&  Board[linha][l2] == 0)
		return 1;
	else if(l2 < size && r2 < size && Board[linha][l2] == Board[linha][r2] &&  Board[linha][l2] == 1)
		return 0;
	else return -1;
}

int test_pares_column_baixo(int **Board, int size, int linha, int coluna)
{
	int d1, u1;

	d1 = linha-2;
	u1 = linha-1;

	if(d1 >= 0 && u1 >= 0 && Board[d1][coluna] == Board[u1][coluna] && Board[d1][coluna] == 0)
		return 1;
	else if(d1 >= 0 && u1 >= 0 && Board[d1][coluna] == Board[u1][coluna] && Board[d1][coluna] == 1)
		return 0;
	else return -1;

}

int test_pares_column_cima(int **Board, int size, int linha, int coluna)
{
	int d2, u2;

	d2 = linha+1;
	u2 = linha+2;

	if(d2 < size && u2 < size && Board[d2][coluna] == Board[u2][coluna] && Board[d2][coluna] == 0)
		return 1;
	else if(d2 < size && u2 < size && Board[d2][coluna] == Board[u2][coluna] && Board[d2][coluna] == 1)
		return 0;
	else return -1;

}

int test_trios_line(int **Board, int size, int linha, int coluna)
{
    int l, r;

    l = coluna-1;
    r = coluna+1;

    if(l >= 0 && r < size && Board[linha][l] == Board[linha][r] && Board[linha][l] == 1)
        return 0;
    else if(l >= 0 && r < size && Board[linha][l] == Board[linha][r] && Board[linha][l] == 0)
        return 1;
    else return -1;
}

int test_trios_column(int **Board, int size, int linha, int coluna)
{
    int d, u;

    d = linha-1;
    u = linha +1;

    if(d >= 0 && u < size && Board[d][coluna] == Board[u][coluna] && Board[d][coluna] == 0)
        return 1;
    else if(d >= 0 && u < size && Board[d][coluna] == Board[u][coluna] && Board[d][coluna] == 1)
        return 0;
    else return -1;
}

int test_complete_line(int **Board, int size, int linha, int coluna)
{
	int i, count1=0, count0=0;

	for(i=0;i<size;i++)
	{
		if(Board[linha][i] == 0)
			count0++;
		if(Board[linha][i] == 1)
			count1++;
	}

	if (count1 == count0 && count0 == size/2) 
		return -1;
	else if(count1 == (size/2))
		return 0;
	else if(count0 == (size/2))
		return 1;
	else return -1;
}

int test_complete_column(int **Board, int size, int linha, int coluna)
{
	int i, count1=0, count0=0;

	for(i=0;i<size;i++)
	{
		if(Board[i][coluna] == 0)
			count0++;
		if(Board[i][coluna] == 1)
			count1++;
	}

	if(count1 == count0 && count0 == size/2)
		return -1;
	else if(count1 == (size/2))
		return 0;
	else if(count0 == (size/2))
		return 1;
	else return -1;
}

/*int test_comb_elimination_line(int **Board, int size, int linha, int coluna)
{
	int i, j, x, count=0, equals=0;

	for(i=0;i<size;i++)
		if(Board[linha][i]==1 || Board[linha][i]==0)
			count++;

	if(count == size-2)
		for(i=0;i<size,i!=linha;i++)
			for(j=0;j<size;j++)
			{
				if(Board[linha][j]!=9 && Board[linha][j]==Board[i][j])
					equals++;
				if(equals == 4)
					x = i;
			}

	if(Board[i][coluna]==0)
		return 1;
	else if(Board[i][coluna]==1)
		return 0;
	else return -1;
}

int test_comb_elimination_column(int **Board, int size, int linha, int coluna)
{
	int i, j, x, count=0, equals=0;

	for(i=0;i<size;i++)
		if(Board[i][coluna]==1 || Board[i][coluna]==0)
			count++;

	if(count == size-2)
		for(i=0;i<size;i++)
			for(j=0;j<size,j!=coluna;j++)
			{
				if(Board[i][coluna]!=9 && Board[i][coluna]==Board[i][j])
					equals++;
				if(equals == 4)
					x = j;
			}

	if(Board[linha][j]==0)
		return 1;
	else if(Board[linha][j]==1)
		return 0;
	else return -1;
}
*/

int test_check(int **Board, int size, int linha, int coluna, int *Change)
{
	
	int i, x[9], count1=0, count0=0;

	x[0] = test_inicial(Board, size, linha, coluna);

	x[1] = test_pares_line_direito(Board, size, linha, coluna);

	x[2] = test_pares_line_esquerdo(Board, size, linha, coluna);

	x[3] = test_pares_column_cima(Board, size, linha, coluna);

	x[4] = test_pares_column_baixo(Board, size, linha, coluna);

	x[5] = test_trios_line(Board, size, linha, coluna);

	x[6] = test_trios_column(Board, size, linha, coluna);

	x[7] = test_complete_column(Board, size, linha, coluna);

	x[8] = test_complete_line(Board, size, linha, coluna);


/*	i = test_comb_elimination_column(Board, size, linha, coluna)
	if(i==valor)
		return 1;
	else if(i!=valor && i!= -1)
		return 0;

	i = test_comb_elimination_line(Board, size, linha, coluna)
	if(i==valor)
		return 1;
	else if(i!=valor && i!= -1)
		return 0;*/

	for(i=0;i<9;i++){
		if(x[i]==0)
			count0++;
		else if(x[i]==1)
			count1++;
	}

	if(count0 > 0 && count1 > 0) return 69;
	else if (count0 > 0 && Board[linha][coluna] == 9) {
		Board[linha][coluna] = 0;
		(*Change)++;
	}
	else if (count1 > 0 && Board[linha][coluna] == 9) {
		Board[linha][coluna] = 1;
		(*Change)++;
	}

	return -1;
}

int main ( int argc, char **argv )
{
	int **Board = NULL;
	int max, size, variant;
	FILE *f;


	if ( argc < 2 ) {
    	exit ( 0 );
  	}

  	max = readFile(argv[1]);
  	Board = Allocate_Table(max);
  	f = OpenFile(argv[1], "r");
	/*Board_info (f, &linha , &coluna , &valor, &size);
	if(linha < size && coluna < size && linha >= 0 && coluna >= 0 && (valor == 1 || valor == 0))
	{
		Fill_Table(f, size, Board);
		test = test_check(Board, size, linha, coluna, valor);
	}
	else test = 2;

	WriteFile (argv[1],"a+", linha, coluna, valor, size, test, Board);
	printf("1\n");*/
	Mutli_tables(argv[1], f, Board, &variant, &size);

	fclose(f);
	Free(Board, max);

  	return (0);
}
