/*Este codigo fue elaborado por Rolando Jesús Duarte Mejias para el 
curso FS0733 - Tópicos de Metodos Matematicos de Fisica: Fisica
computacional en C de la Escuela de Fisica de la Universidad de 
Costa Rica.*/

#include<stdio.h>
#include<math.h>

/*s_m se refiere al angulo, u a la variable que es el inverso del radio y 
v_m derivada de u*/

double function_one(double s_m, double u_m, double v_m){
    double result = v_m; 
    return result;
}

double function_two(double s_m, double u_m, double v_m){
    double m = 1.0;    /*masa*/
    double l = 1.0;   /*momento angular*/
    double k = 1.0;      /*constante gravitacional*/

    double result = - u_m + k * m / pow(l, 2);
    return result;
}

void k_matrix(double matrix[2][4], double h, double s_m, double u_m, double v_m){
    /*Matriz de los valores de k 2x4*/
    matrix[0][0] = h * function_one(s_m, u_m, v_m);
    matrix[1][0] = h * function_two(s_m, u_m, v_m);
    matrix[0][1] = h * function_one(s_m + (h / 2), u_m + (matrix[0][0] / 2), v_m + (matrix[1][0] / 2));
    matrix[1][1] = h * function_two(s_m + (h / 2), u_m + (matrix[0][0] / 2), v_m + (matrix[1][0] / 2));
    matrix[0][2] = h * function_one(s_m + (h / 2), u_m + (matrix[0][1] / 2), v_m + (matrix[1][1] / 2));
    matrix[1][2] = h * function_two(s_m + (h / 2), u_m + (matrix[0][1] / 2), v_m + (matrix[1][1] / 2));
    matrix[0][3] = h * function_one(s_m + (h), u_m + matrix[0][2], v_m + matrix[1][2]);
    matrix[1][3] = h * function_two(s_m + (h), u_m + matrix[0][2], v_m + matrix[1][2]);
}

void create_file(char name[32], double v_m){
    /*Funcion para crear los archivos necesarios según el nombre que se le de con las condicion necesaria
    para calcular las distintas secciones conicas que se da en este problema*/
    double matrix[2][4]; /*matriz de los valores k para la solucion*/
    double h = 0.001;
    double s_m = M_PI_2;
    double u_m = 0.1;
    char c[100];
    FILE* file;
    file = fopen(name, "wt");
    k_matrix(matrix, h, s_m, u_m, v_m);

    double x = cos(s_m) / u_m;
    double y = sin(s_m) / u_m;
    sprintf(c, "%f %f\n", x, y);
    fputs(c, file);
    for (int i = 0; i<200; i++){
        u_m = u_m + (matrix[0][0] + 2 * matrix[0][1] + 2 * matrix[0][2] + matrix[0][3]) / 6;
        v_m = v_m + (matrix[1][0] + 2 * matrix[1][1] + 2 * matrix[1][2] + matrix[1][3]) / 6;
        s_m = s_m + (i + 1) * h;
        x = cos(s_m) / u_m;
        y = sin(s_m) / u_m;
        sprintf(c, "%f %f\n", x, y);
        fputs(c, file);
        k_matrix(matrix, h, s_m, u_m, v_m); 
    }
    fclose(file);
    printf("Proceso Terminado\n");
}

int main(){
    create_file("data_circle.txt", 0.0); /*Circular*/
    create_file("data_ellipse.txt", -0.4); /*Elipse*/
    create_file("data_parabole.txt", -1.0); /*Parabola*/ 
    create_file("data_hyperbole.txt", -10.0); /*Hipérbola*/
    return 0;
}