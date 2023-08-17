#include "../inc/dynamic_data.h"
#include "../inc/graph_funcs.h"
#include "../inc/my_defines.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

struct allocated_data_s global_data;

// void print_queue_array(queue_arr_t queue)
// {
//     // printf("TOTAL: %d\n", queue.total);

//     int *tmp_ptr;
//     tmp_ptr = queue.ptr_start;

//     printf("\033[0;34m");
//     for (int i = 0; i < queue.total; i++)
//     {
//         int val = *(tmp_ptr);
//         tmp_ptr++;

//         if ((tmp_ptr - queue.val) >= QUEUE_SIZE)
//             tmp_ptr -= QUEUE_SIZE;

//         printf("%d ", val);
//     }
//     printf("\033[0m\n");
// }

int read_header(FILE *f, int *size, int *first_node, int *second_node)
{
    int rc = fscanf(f, "%d%d%d", size, first_node, second_node);
    char new_line = 0;
    fread(&new_line, sizeof(char), 1, f);
    if (!feof(f) && new_line == '\r')
        fread(&new_line, sizeof(char), 1, f);

    if (rc != 3 || (new_line != '\n' && !feof(f)))
    {
        return RETURN_WRONG_HEADER;
    }

    return RETURN_SUCCESS;
}

int read_coords(FILE *f, int *x, int *y, int *value)
{
    int rc = fscanf(f, "%d%d%d", y, x, value);
    char new_line;
    fread(&new_line, sizeof(char), 1, f);
    if (!feof(f) && new_line == '\r')
        fread(&new_line, sizeof(char), 1, f);

    if (rc != 3 || (!feof(f) && new_line != '\n') || *x <= 0 || *y <= 0 || *value == 0)
    {
        return RETURN_WRONG_COORDS;
    }
    *x = *x - 1;
    *y = *y - 1;

    return RETURN_SUCCESS;
}

int read_matrix(FILE *f, int ***arr_ptr, int *size, int *first_node, int *second_node)
{
    int rc;
    int val;

    rc = read_header(f, size, first_node, second_node);
    if (rc != RETURN_SUCCESS)
        return rc;
    if (*size <= 0)
    {
        return RETURN_HEADER_CALC;
    }
    *arr_ptr = allocate_matrix(*size, *size);
    if (*arr_ptr == NULL)
        return RETURN_MEMORY_ERROR;

    for (size_t i = 0; i < (size_t)*size; i++)
    {
        for (size_t j = 0; j < (size_t)*size; j++)
        {
            int rc = fscanf(f, "%d", &val);
            if (rc != 1)
            {
                return RETURN_INPUT_ERROR;
            }
            (*arr_ptr)[j][i] = val;
        }

        char new_line;
        fread(&new_line, sizeof(char), 1, f);
        if (!feof(f) && new_line == '\r')
            fread(&new_line, sizeof(char), 1, f);
        if (!feof(f) && new_line != '\n')
        {
            return RETURN_WRONG_COORDS;
        }
    }
    return RETURN_SUCCESS;
}

int read_graph(FILE *f, int ***graph, int *size, int *first_node, int *second_node)
{
    int rc = read_matrix(f, graph, size, first_node, second_node);
    if (rc != RETURN_SUCCESS)
        return rc;
    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if ((*graph)[i][j] != (*graph)[j][i])
            {
                printf("Матрица не симметрична\n");
                return RETURN_WRONG_FORMAT;
            }
        }
    }
    return RETURN_SUCCESS;
}

void print_matrix(int **arr_ptr, int height, int width)
{
    int count = 0;
    int stop = height * width;

    while (count < stop)
    {
        printf("%5d ", arr_ptr[0][count]);
        count++;
        if (count % width == 0)
        {
            printf("\n");
        }
    }
}

void node_to_dot(FILE *f, int **graph, int y, int x)
{
    if (graph[y][x])
    {
        fprintf(f, "%d -- %d;\n", y, x);
    }
}

void matrix_to_dot(FILE *f, const char *tree_name, int **graph, int size)
{
    fprintf(f, "graph \"%s\" {\n", tree_name);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            node_to_dot(f, graph, i, j);
        }
    }

    fprintf(f, "}\n");
}

// int find_path(int **graph, int size, int first_node, int second_node, int length, int path_num)
// {
//     if (length == 0)
//     {
//         return 0;
//     }

//     if (first_node == second_node)
//         return path_num;

//     for (int i = 0; i < size; i++)
//     {
//         if (graph[first_node][i])
//         {
//             // printf("Path: %d - %d length: %d\n", i, second_node, length);
//             int rc = find_path(graph, size, i, second_node, length - 1, (path_num * 10) + (i + 1));
//             if (rc > 0)
//                 return rc;
//         }
//     }
//     return 0;
// }

// int dfs(int **graph, int size, int *visited, int first_node, int second_node)
// {
//     // adj - смежный список
//     // v - посещенный узел (вершина)
//     // t - пункт назначения

//     // это общие случаи
//     // либо достигли пункта назначения, либо уже посещали узел
//     if (first_node == second_node)
//         return 1;
//     if (visited[first_node])
//         return 0;

//     // помечаем узел как посещенный
//     visited[first_node] = 1;
//     // исследуем всех соседей (ближайшие соседние вершины) v

//     for (int i = 0; i < size; i++)
//     {
//         if (graph[first_node][i])
//         {
//             int reached = dfs(graph, size, visited, i, second_node);
//             if (reached)
//                 return 1;
//         }
//     }
//     return 0;
// }

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Неверное кол-во параметров\n");
        return RETURN_NOT_ENOUGH_ARGUMENTS;
    }

    srand(time(NULL));
    int rc = init_global_data();
    if (!rc)
        terminate_program(RETURN_MEMORY_ERROR);

    int **graph;
    int size;
    int first_node, second_node;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Неверное имя файла\n");
        terminate_program(RETURN_NO_FILE);
    }

    rc = read_graph(f, &graph, &size, &first_node, &second_node);
    fclose(f);

    if (rc != RETURN_SUCCESS)
    {
        printf("Ошибка ввода: %d\n", rc);
        terminate_program(rc);
    }

    if (first_node < 0 || first_node >= size || second_node < 0 || second_node >= size)
    {
        printf("Ошибка данных\n");
        terminate_program(RETURN_WRONG_FORMAT);
    }

    print_matrix(graph, size, size);

    // f = fopen("before.gv", "w");
    // matrix_to_dot(f, "TEST", graph, size);
    // fclose(f);

    int path_size;
    int *path;

    int working = 1;

    for (int i = 0; i < size && working; i++)
    {
        for (int i1 = 0; i1 < i && working; i1++)
        {
            for (int j = 0; j < size && working; j++)
            {
                for (int j1 = 0; j1 < j && working; j1++)
                {
                    for (int k = 0; k < size && working; k++)
                    {
                        for (int k1 = 0; k1 < k && working; k1++)
                        {
                            if (graph[i][i1] != 0 && graph[j][j1] != 0 && graph[k][k1] != 0)
                            {
                                graph[i][i1] = 0;
                                graph[i1][i] = 0;

                                graph[j][j1] = 0;
                                graph[j1][j] = 0;

                                graph[k][k1] = 0;
                                graph[k1][k] = 0;

                                rc = bfs(graph, size, first_node, second_node, &path_size, &path);
                                if (rc == 0)
                                {
                                    printf("Можно закрыть пути:\n");
                                    printf("\033[0;34m%d -- %d, %d -- %d, %d -- %d\033[0m\n", i, i1, j, j1, k, k1);
                                    working = 0;
                                    // f = fopen("after.gv", "w");
                                    // matrix_to_dot(f, "TEST", graph, size);
                                    // fclose(f);
                                }

                                f = fopen(argv[1], "r");
                                read_graph(f, &graph, &size, &first_node, &second_node);
                                fclose(f);
                            }
                        }
                    }
                }
            }
        }
    }

    if (working == 1)
        printf("\033[0;34mПерекрыть путь к городу нельзя\033[0m\n");

    terminate_program(0);
}