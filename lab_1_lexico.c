/*
Autor: Ian Rickmers Blamey
Asignatura: Procesamiento de Lenguajes Formales 
Profesora: Consuelo Ramírez
Descripción: Programa que lee un archivo de texto y lo analiza léxicamente
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Analizador léxico: recibe el nombre del archivo de entrada y el nombre del archivo de salida
//Selecciona el tipo de palabra que es y la imprime en el archivo de salida
int lexicalAnalyzer(char *inputFilename, char *outputFilename){
    FILE *inputFile;
    FILE *outputFile;
    // Si el archivo de entrada existe
    if ((inputFile = fopen(inputFilename, "r")))
    {
        // Si el archivo de salida existe
        if((outputFile=fopen(outputFilename,"r"))){
            fclose(outputFile);
            printf("Error: El archivo de salida ya existe.\n");
            return 0;
        }
        outputFile = fopen(outputFilename,"w");
        char ch;
        //Palabra que compara si es que es una palabra reservada
        char word[50]="";
        int counter = 0;
        char symbolCopy;
        //Verificador para identificar si es que entró a caso de número entero y es un identificador 
        int verifier = 0;
        while ( (ch = fgetc(inputFile)) != EOF){
            //caso número entero
            if((ch >= '0' && ch <= '9')){
                while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                    ch = fgetc(inputFile);          
                }
                //Caso número real en notación decimal
                if(ch==','){
                    counter=0;
                    ch = fgetc(inputFile);
                    while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                        ch = fgetc(inputFile);
                        counter++;
                    }
                    //Caso número real en notación exponencial
                    if(counter>0){
                        if (ch == 'E'){
                            strncat(word, &ch, 1);
                            verifier = 1;
                            ch = fgetc(inputFile);
                            if (ch == '+' || ch == '-'){
                                symbolCopy = ch; 
                                counter=0;
                                ch = fgetc(inputFile);
                                while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                                    ch = fgetc(inputFile);
                                    counter++;
                                }
                                if (counter>0){
                                    fprintf(outputFile,"EXPONENCIAL\n");
                                    verifier = 0;
                                    memset(word, 0, sizeof(word));
                                }
                                else{
                                    verifier = 0;
                                    fprintf(outputFile,"DECIMAL\n");
                                    fprintf(outputFile,"IDENTIFICADOR\n");
                                    memset(word, 0, sizeof(word));
                                    if (symbolCopy == '+'){
                                        fprintf(outputFile,"+\n");
                                    }
                                    else if (symbolCopy == '-'){
                                        fprintf(outputFile,"-\n");
                                    }
                                }
                            }
                            else if((ch >= '0' && ch <= '9')){
                                while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                                    ch = fgetc(inputFile);
                                }
                                verifier = 0;
                                fprintf(outputFile,"EXPONENCIAL\n");
                            }
                            else{
                                fprintf(outputFile,"DECIMAL\n");
                            }
                        }
                        else{
                            fprintf(outputFile,"DECIMAL\n");
                        }
                    }
                    else{
                        fprintf(outputFile,"ENTERO\n");
                    }
                }
                //Caso número entero en notación exponencial
                else if (ch == 'E'){
                            strncat(word, &ch, 1);
                            verifier = 1;
                            ch = fgetc(inputFile);
                            if (ch == '+' || ch == '-'){
                                symbolCopy = ch; 
                                counter=0;
                                ch = fgetc(inputFile);
                                while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                                    ch = fgetc(inputFile);
                                    counter++;
                                }
                                if (counter>0){
                                    fprintf(outputFile,"EXPONENCIAL\n");
                                    verifier = 0;
                                    memset(word, 0, sizeof(word));
                                }
                                else{
                                    verifier = 0;
                                    fprintf(outputFile,"ENTERO\n");
                                    fprintf(outputFile,"IDENTIFICADOR\n");
                                    memset(word, 0, sizeof(word));
                                    if (symbolCopy == '+'){
                                        fprintf(outputFile,"+\n");
                                    }
                                    else if (symbolCopy == '-'){
                                        fprintf(outputFile,"-\n");
                                    }
                                }
                            }
                            else if((ch >= '0' && ch <= '9')){
                                while ((ch >= '0' && ch <= '9') && (ch != EOF)){
                                    ch = fgetc(inputFile);
                                }
                                verifier = 0;
                                fprintf(outputFile,"EXPONENCIAL\n");
                            }
                            else{
                                fprintf(outputFile,"ENTERO\n");
                            }
                        }
                else{
                    fprintf(outputFile,"ENTERO\n");
                }
            }

            //Caso identificador
            if(ch!='x' && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ){
                verifier = 0;
                counter=0;
                while (ch!='x' && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) && (ch != EOF)){
                    counter ++;
                    if(counter<6){
                        strncat(word, &ch, 1);
                    }
                    ch = fgetc(inputFile);
                    
                }
                //Comparación de palabras reservadas
                if (counter<6){
                    if (strcmp(word,"PI") == 0){
                        fprintf(outputFile,"PI\n");
                    }
                    else if (strcmp(word,"MOD") == 0){
                        fprintf(outputFile,"MOD\n");
                    }
                    else if (strcmp(word,"SQR") == 0){
                        fprintf(outputFile,"SQR\n");
                    }
                    else if (strcmp(word,"CUR") == 0){
                        fprintf(outputFile,"CUR\n");
                    }
                    else if (strcmp(word,"EXP") == 0){
                        fprintf(outputFile,"EXP\n");
                    }
                    else if (strcmp(word,"LN") == 0){
                        fprintf(outputFile,"LN\n");
                    }
                    else if (strcmp(word,"LOG") == 0){
                        fprintf(outputFile,"LOG\n");
                    }
                    else if (strcmp(word,"SGN") == 0){
                        fprintf(outputFile,"SGN\n");
                    }
                    else if (strcmp(word,"INT") == 0){
                        fprintf(outputFile,"INT\n");
                    }
                    else if (strcmp(word,"FIX") == 0){
                        fprintf(outputFile,"FIX\n");
                    }
                    else if (strcmp(word,"FRAC") == 0){
                        fprintf(outputFile,"FRAC\n");
                    }
                    else if (strcmp(word,"ROUND") == 0){
                        fprintf(outputFile,"ROUND\n");
                    }
                    else{
                        fprintf(outputFile,"IDENTIFICADOR\n");
                    }
                }
                else{
                    fprintf(outputFile,"IDENTIFICADOR\n");
                }
                memset(word, 0, sizeof(word));
            }
            //Si llegó hasta acá significa que es un identificador E
            if (verifier == 1){
                fprintf(outputFile,"IDENTIFICADOR\n");
                verifier = 0;
            }
            //caso símbolos
            if (ch == '+'){
                fprintf(outputFile,"+\n");
            }
            if (ch == '-'){
                fprintf(outputFile,"-\n");
            }
            if (ch == 'x'){
                fprintf(outputFile,"x\n");
            }
            if (ch == ':'){
                fprintf(outputFile,":\n");
            }
            if (ch == '/'){
                fprintf(outputFile,"/\n");
            }
            if (ch == '^'){
                fprintf(outputFile,"^\n");
            }
            if (ch == '|'){
                fprintf(outputFile,"|\n");
            }
            if (ch == '!'){
                fprintf(outputFile,"!\n");
            }
            if (ch == '('){
                fprintf(outputFile,"(\n");
            }
            if (ch == ')'){
                fprintf(outputFile,")\n");
            }
            if (ch == '='){
                fprintf(outputFile,"=\n");
            }
            if (ch == EOF){
                break;
            }
            
        }
        fclose(inputFile);
        return 1;
    }
    printf("Error: El archivo de entrada no existe.\n");
    return 0;
}

//Bloque principal
//Se verifica que estén los parámetros adecuados y luego se utiliza el analizador léxico
int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Error: Falta par%cmetro.\nUso: lexico.exe archivo_entrada archivo_salida\n",160);
        return 0;
    }
    if(argc > 3){
        printf("Error: Demasiados par%cmetros.\nUso: lexico.exe archivo_entrada archivo_salida\n",160);
        return 0;
    }
    lexicalAnalyzer(argv[1], argv[2]);
    return 0;
}

