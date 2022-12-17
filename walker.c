#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>
#include <string.h>

void Print_caminho(int k, int var, int** caminho, FILE *fp)
{
    int i;

    if (caminho == NULL)
    {
        //printf("Erro 03\n");
        return;
    }


    if ( var != 3)
    {

        for ( i = (k-1); i >= 0; i-- )
        {
            fprintf(fp, "%d %d %d\n", caminho[i][0], caminho[i][1], caminho[i][2]);
        }

        fprintf(fp, "\n");
    }

    else
    {
        for ( i = 1; i < k+1 ; i++)
        {
            fprintf(fp, "%d %d %d\n", caminho[i][0], caminho[i][1], caminho[i][2]);
        }

        fprintf(fp, "\n");
    }

    return;
}
/* recebe as coordenadas x,y do ponto a analisar e verifica se as celulas adjacentes cumprem a condicao escolhida*/
/* liga Root as celulas que cumprem a condicao*/
/*caminho so vai tomar valor 1 caso alguma celula adjacente tenha um valor maior que a original*/

int Crescente (int x, int y, int k, int C, int L, int var, int** caminho, int **vtab)
{
    int valor;
    int i, j;
    int find = 0;

    valor = vtab[y][x];

    if ( k == 0)
    {
        caminho[k][0] = y;
        caminho[k][1] = x;
        caminho[k][2] = valor;

        return 1;
    }

    if ( k < 0)
    {
        return -1;
    }


    if ( k > 0)
    {
        for (i = y - 1; i <= y + 1 && i < L ; i++)
        {
            if (i<0)
            {
                i = y;
                //continue;
            }

            for (j = x-1; j <= x + 1 && j < C; j++ )
            {
                if (j<0)
                {
                    j = x;
                    //continue;
                }

                if ( i == y && j == x)
                {
                    continue;
                }

                else
                {

                    if (vtab[i][j] > valor)
                    {

                        find = Crescente ( j, i, k-1, C, L, var, caminho, vtab);

                        if (find == 1)
                        {

                            caminho[k][0] = y;
                            caminho[k][1] = x;
                            caminho[k][2] = valor;

                            return find;
                        }
                    }

                    else
                    {
                        continue;
                    }
                }
            }

        }

    }

    return find;
}

int Crescente2 (int x, int y, int k, int k_max, int* find,  int C, int L, int var, int** caminho, int **vtab)
{
    int valor;
    int i, j;
    int k_max_aux;

    k_max_aux = k_max;

    valor = vtab[y][x];

    for (i = y - 1; i <= y + 1 && i < L ; i++)
    {
        if (i<0)
        {
            i = y;
        }

        for (j = x-1; j <= x + 1 && j < C; j++ )
        {
            if (j<0)
            {
                j = x;
            }

            if ( i == y && j == x)
            {
                continue;
            }

            else
            {

                if (vtab[i][j] > valor)
                {

                    k_max_aux = Crescente2 ( j, i, k+1, k_max, find, C, L, var, caminho, vtab);

                    if (k_max_aux != k_max)
                    {

                        caminho[k][0] = y;
                        caminho[k][1] = x;
                        caminho[k][2] = valor;
                        k_max = k_max_aux;
                    }
                }

                else
                {
                    continue;
                }
            }
        }

    }

    if ( k > 0 && k > k_max )
    {
        caminho[k][0] = y;
        caminho[k][1] = x;
        caminho[k][2] = valor;
        return k;
    }

    else
    {
        return k_max_aux;
    }

}


int Par (int x, int y, int k, int C, int L, int var, int** caminho, int **vtab)
{
    int valor;
    int i, j;
    int find = 0;

    valor = vtab[y][x];
/*
    if ( var == 2 && valor % 2 != 0 )
    {
        return find;
    }
*/
    if ( k == 0)
    {
        caminho[k][0] = y;
        caminho[k][1] = x;
        caminho[k][2] = valor;
        return 1;
    }

    if ( k < 0)
    {
        return -1;
    }


    if ( k > 0)
    {

        for (i = y - 1; i <= y + 1 && i < L; i++)
        {
            if (i<0)
            {
                i = y -1;
                continue;
            }

            for (j = x-1; j <= x + 1 && j < C; j++ )
            {
                if (j<0)
                {
                    j = x-1;
                    continue;
                }


                else if ( i == y && j == x)
                {
                    continue;
                }

                else
                {
                    if (vtab[i][j] % 2 == 0)
                    {
                        vtab[y][x] = -1;
                        find = Par( j, i, k-1, C, L, var, caminho, vtab);
                        vtab[y][x] = valor;
                        if (find == 1)
                        {
                            caminho[k][0] = y;
                            caminho[k][1] = x;
                            caminho[k][2] = valor;
                            return find;
                        }
                    }

                    else
                    {
                        continue;
                    }
                }
            }

        }

    }

    return find;
}


int Par2 (int x, int y, int k, int k_max,  int C, int L, int var, int** caminho, int **vtab)
{
    int valor;
    int i, j;
    int k_max_aux;

    k_max_aux = k_max;

    valor = vtab[y][x];

    for (i = y - 1; i <= y + 1 && i < L ; i++)
    {
        if (i<0)
        {
            i = y;
        }

        for (j = x-1; j <= x + 1 && j < C; j++ )
        {
            if (j<0)
            {
                j = x;
            }

            if ( i == y && j == x)
            {
                continue;
            }

            else
            {

                if (vtab[i][j] % 2 == 0)
                {
                    vtab[y][x] = -1;
                    k_max_aux = Par2 ( j, i, k+1, k_max, C, L, var, caminho, vtab);
                    vtab[y][x] = valor;

                    if (k_max_aux != k_max)
                    {

                        caminho[k][0] = y;
                        caminho[k][1] = x;
                        caminho[k][2] = valor;
                        k_max = k_max_aux;
                        if (k_max  == ((L*C)-1) )
                        {
                            return k_max;
                        }
                    }
                }

                else
                {
                    continue;
                }
            }
        }

    }

    if ( k > 0 && k > k_max )
    {
        caminho[k][0] = y;
        caminho[k][1] = x;
        caminho[k][2] = valor;
        return k;
    }

    else
    {
        return k_max_aux;
    }

}



void varianteA (int x, int y, int k, int** vtab, int L, int C, FILE *fp2)
{
    int i = 0;
    int var = 1;
    int find;
    int** caminho;

    caminho = (int **) malloc( (k+1) * sizeof( int *));

    for ( i = 0; i < k+1; i++)
    {
        caminho[i]= (int *) malloc( 3 * sizeof( int ));
    }

    find = Crescente(x, y, k, C, L, var, caminho, vtab);

    if (find == 0)
    {

        fprintf(fp2, "%d %d A %d %d %d -1\n\n", L, C, y, x, k);
    }

    if (find == 1)
    {
        fprintf(fp2, "%d %d A %d %d %d %d\n", L, C, y, x, k, k);
        Print_caminho(k, var, caminho, fp2);

    }

    for ( i = 0; i < k+1; i++)
    {
        free (caminho[i]);
    }

    free(caminho);


    return;
}


void varianteB (int x, int y, int k, int** vtab, int L, int C, FILE *fp2)
{
    int i = 0;
    int find;
    int var = 1;
    int** caminho;

    caminho = (int **) malloc( (k+1) * sizeof( int *));

    for ( i = 0; i < k+1; i++)
    {
        caminho[i]= (int *) malloc( 3 * sizeof( int ));
    }


    find = Par(x, y, k, C, L, var, caminho, vtab);

    if (find == 0)
    {

        fprintf(fp2, "%d %d B %d %d %d -1\n\n", L, C, y, x, k);
    }


    if (find == 1)
    {
        fprintf(fp2, "%d %d B %d %d %d %d\n", L, C, y, x, k, k);
        Print_caminho(k, var, caminho, fp2);

    }

    for ( i = 0; i < k+1; i++)
    {
        free (caminho[i]);
    }

    free(caminho);



    return;
}

void varianteC( int y, int x, int k, int**vtab, int L, int C, FILE *fp2)
{
    int i, j;
    int find = -1;
    int var = 2;
    int** caminho;

    caminho = (int **) malloc( (k+1) * sizeof( int *));

    for ( i = 0; i < k+1; i++)
    {
        caminho[i]= (int *) malloc( 3 * sizeof( int ));
    }

    for ( i = 0; i < L; i++ )
    {
        if ( find == 1)
            break;

        for ( j = 0; j < C; j++)
        {
            if ( find == 1)
                break;
            find = Crescente(j, i, k, C, L, var, caminho, vtab);
        }
    }

    if (find == 0)
    {

        fprintf(fp2, "%d %d C %d %d %d -1\n\n", L, C, y, x, k);
    }


    if (find == 1)
    {
        fprintf(fp2, "%d %d C %d %d %d %d\n", L, C, i-1, j-1, k, k);
        Print_caminho(k, var, caminho, fp2);

    }

    for ( i = 0; i < k+1; i++)
    {
        free (caminho[i]);
    }

    free(caminho);

    return;
}

void varianteD( int y, int x, int k, int**vtab, int L, int C, FILE *fp2)
{
    int i, j;
    int find = -1;
    int var = 2;
    int** caminho;

    if ( k <= L*C && k > 0 )
    {
        caminho = (int **) malloc( (k+1) * sizeof( int *));

        for ( i = 0; i < k+1; i++)
        {
            caminho[i]= (int *) malloc( 3 * sizeof( int ));
        }

        for ( i = 0; i < L; i++ )
        {
            if ( find == 1)
                break;

            for ( j = 0; j < C; j++)
            {
                if ( find == 1 )
                    break;
                find = Par(j, i, k, C, L, var, caminho, vtab);
            }
        }

        if (find == 0)
        {

            fprintf(fp2, "%d %d D %d %d %d -1\n\n", L, C, y, x, k);
        }


        if (find == 1)
        {
            fprintf(fp2, "%d %d D %d %d %d %d\n", L, C, i-1, j-1, k, k);
            Print_caminho(k, var, caminho, fp2);

        }

        for ( i = 0; i < k+1; i++)
        {
            free (caminho[i]);
        }

        free(caminho);
    }

    else
        fprintf(fp2, "%d %d D %d %d %d -1\n\n", L, C, y, x, k);

    return;
}

void varianteE( int y, int x, int k, int**vtab, int L, int C, FILE *fp2)
{
    int i, j;
    int k_max = 0;
    int var = 3;
    int a;
    int *find = &a;
    int** caminho;


    caminho = (int **) malloc( (L*C+1) * sizeof( int *));

    for ( i = 0; i < (L*C+1); i++)
    {
        caminho[i]= (int *) malloc( 3 * sizeof( int ));
    }

    *find = 0;

    for ( i = 0; i < L; i++ )
    {

        for ( j = 0; j < C; j++)
        {
            k_max = Crescente2(j, i, 0, k_max, find,  C, L, var, caminho, vtab);
        }
    }

    if (k_max == 0)
    {

        fprintf(fp2, "%d %d E %d %d %d -1\n\n", L, C, y, x, k);
    }


    if (k_max != 0)
    {
        fprintf(fp2, "%d %d E %d %d %d %d\n", L, C, caminho[0][0], caminho[0][1], k, k_max);
        Print_caminho(k_max, var, caminho, fp2);

    }

    for ( i = 0; i < (L*C-1); i++)
    {
        free(caminho[i]);
    }

    free(caminho);

    return;
}

void varianteF( int y, int x, int k, int**vtab, int L, int C, FILE *fp2)
{
    int i, j;
    int k_max = 0;
    int var = 3;
    int** caminho;

    caminho = (int **) malloc( (L*C) * sizeof( int *));

    for ( i = 0; i < (L*C); i++)
    {
        caminho[i]= (int *) malloc( 3 * sizeof( int ));
    }

    for ( i = 0; i < L; i++ )
    {
        if (k_max == (L*C)-1)
            break;
        for ( j = 0; j < C; j++)
        {
            k_max = Par2(j, i, 0, k_max,  C, L, var, caminho, vtab);
            if (k_max == (L*C)-1)
                break;
        }
    }

    if (k_max == 0)
    {

        fprintf(fp2, "%d %d F %d %d %d -1\n\n", L, C, y, x, k);
    }


    if (k_max != 0)
    {
        fprintf(fp2, "%d %d F %d %d %d %d\n", L, C, caminho[0][0], caminho[0][1], k, k_max);
        Print_caminho(k_max, var, caminho, fp2);

    }

    for ( i = 0; i < (L*C-1); i++)
    {
        free(caminho[i]);
    }

    free(caminho);

    return;
}

int main(int argc, char *argv[])
{
    char *ret = NULL, *arg2 = NULL ;
    char ch = '.';
    char str[] = ".puz";
    char str2[] = ".path";
    int ret2;
    int L, C, l0, c0, k;
    int new_prob = 1;
    char v;
    int i, j=0;
    int **vtab = NULL;
    FILE *fp, *fp2;
    /* variavel para remover warning do fscanf */
    int inutil = 0;
    size_t len1, len2, len3, tamanho;

    if (argc != 2)
    {
        return( 0 );
    }

    ret = strrchr(argv[1], ch); /* lê o que está apartir do ponto, neste caso deveria ser ".puz0" */
    ret2 = strcmp(ret, str);
    if (ret2 != 0)
    {
        return ( 0 );
    }


    fp = fopen ( argv[1], "r" );
    if ( fp == NULL )
    {
        return ( 0 );
    }
    len1 = strlen(argv[1]);
    len2 = strlen(ret);
    len3 = strlen(str2);
    tamanho = len1- len2;
    arg2 = (char*) malloc( tamanho+len3+1 );
    if ( arg2 == NULL )
    {
        return ( 0 );
    }
    memcpy(arg2, argv[1], tamanho);
    memcpy(arg2+tamanho, str2, len3+1);

    /* verifica-se que as extensoes dos argumentos sao as corretas por isso faz sentido criar o ficheito output */
    fp2 = fopen ( arg2, "w" );
    free(arg2);
    if ( fp2 == NULL )
    {
        return 0;
    }

    while(new_prob != -1) /* verifica se há mais problemas , se sim repete o processo de ler do ficheito, allocar memoria para as tablelas, guardar os valores */
    {
        new_prob = fscanf(fp, "%d %d %c %d %d %d", &L, &C, &v, &l0, &c0, &k );

        if(new_prob == -1)
        {
            fclose(fp);
            fclose(fp2);
            return 0;
        }

        if(v==65 || v==66)
        {
            if(l0 < 0 || l0 >= L || c0 < 0 || c0 >= C )
            {
                fprintf(fp2, "%d %d %c %d %d %d -1\n\n", L, C, v, l0, c0, k);
                for(i=0; i<(C*L); i++)
                {
                    inutil= fscanf(fp,"%*d");
                }
                new_prob = fscanf(fp, "%d %d %c %d %d %d", &L, &C, &v, &l0, &c0, &k );
                if(new_prob == -1)
                {
                    return 0;
                }
            }
        }
        if((v==67 || v==68 || v==65 || v==66) && ((k >= (L*C)) || (k < 1)))
        {
            fprintf(fp2, "%d %d %c %d %d %d -1\n\n", L, C, v, l0, c0, k);
            for(i=0; i<(C*L); i++)
            {
                inutil= fscanf(fp,"%*d");
            }
            new_prob = fscanf(fp, "%d %d %c %d %d %d", &L, &C, &v, &l0, &c0, &k );
            if(new_prob == -1)
            {
                return 0;
            }
        }

        /* verifica se a variante é A, B ou C */
        while ( ((v<65)||(v>70)) )
        {
            fprintf(fp2, "%d %d %c %d %d %d -1\n\n", L, C, v, l0, c0, k);
            for(i=0; i<(C*L); i++)
            {
                inutil= fscanf(fp,"%*d");
            }
            new_prob = fscanf(fp, "%d %d %c %d %d %d", &L, &C, &v, &l0, &c0, &k );
            if(new_prob == -1)
            {
                return 0;
            }
        }

        /* alloca memoria para a tabela de inteiros ( vtab )  */
        vtab = (int **) malloc( L * sizeof( int *));
        if (vtab == NULL)
        {
            return 0;
        }

        for ( i=0; i<L; i++)
        {
            vtab[i]= (int *) malloc( C * sizeof( int ));
            if (vtab[i] == NULL)
            {
                return 0;
            }
        }



        /* guarda os valores do mapa numa tabela */
        for ( i=0; i<L; i++)
        {
            for ( j=0; j<C; j++)
            {
                inutil = fscanf(fp, "%d ", &(vtab[i][j]));
                if (inutil != 0)
                {
                    continue;
                }
            }
        }

        if (v == 65)
        {
            varianteA(c0, l0, k, vtab, L, C, fp2);

            /* deallocates memory used*/
            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);

        }
        if (v == 66)
        {
            varianteB(c0, l0, k, vtab, L, C, fp2);

            /* deallocates memory used*/
            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);
        }

        if (v == 67)
        {
            varianteC(l0, c0, k, vtab, L, C, fp2);

            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);
        }

        if (v == 68)
        {
            varianteD(l0, c0, k, vtab, L, C, fp2);

            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);

        }
        if(v==69)
        {
            varianteE(l0, c0, k, vtab, L, C, fp2);

            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);
        }
        if(v==70)
        {
            varianteF(l0, c0, k, vtab, L, C, fp2);

            for ( i=0; i<L; i++)
            {
                free((vtab[i]));
            }
            free(vtab);
        }
    }
    fclose(fp);
    fclose(fp2);


    return 0;

}
