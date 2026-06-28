#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,
        "un et uniquement un paramètre qui est le nom du fichier obj à convertir\n");
    return EXIT_FAILURE;
  }
  char *filename = argv[1];
  FILE *fobj = fopen(filename, "rb");
  if (fobj == nullptr) {
    fprintf(stderr, "Erreur lors de l'ouverture de %s\n", filename);
    return EXIT_FAILURE;
  }
  slice_by_char(filename, '.');
  printf("%s\n", filename);
  const char *Hname = strcat(filename, ".h");
  FILE *fhptr = fopen(Hname, "wb");
  if (fhptr == nullptr) {
    fclose(fobj);
    fprintf(stderr, "Erreur lors de la création de %s\n", Hname);
    return EXIT_FAILURE;
  }
  printf("le fichier %s a été crée\n", Hname);
  const char *Cname = strcat(slice_by_char(filename, '.'), ".c");
  FILE *fcptr = fopen(Cname, "wb");
  if (fcptr == nullptr) {
    fclose(fobj);
    fclose(fhptr);
    fprintf(stderr, "Erreur lors de la création de %s\n", Cname);
  }
  printf("le fichier %s a été crée\n", Cname);
  int id;
  char buffer[100];
  bool firstOBJ = true;
  while ((id = fgetc(fobj)) != EOF) {
    printf("%ld\n", ftell(fobj));
    firstOBJ = (ftell(fobj) > 1);
    if (fgets(buffer, sizeof(buffer), fobj) != nullptr) {
      if (id == 'o') {
        if(firstOBJ){
          fprintf(fcptr, "}\n");  // sert à fermer les fonctions si c'est pas la première ligne
        }
        fprintf(fhptr, "void draw%s();\n", slice_by_char(buffer, (char) 10));
        fprintf(fcptr, "void draw%s(){\n", buffer);
      }
    } else {
      fprintf(stderr,
          "la fin du fichier est atteinte ou un problème est survenue\n");
      break;
    }
  }
  fclose(fobj);
  fclose(fhptr);
  fclose(fcptr);
  return EXIT_SUCCESS;
}

char *slice_by_char(char *filename, char c) {
  char *p = filename + strlen(filename);
  while (p > filename && *p != c) {
    --p;
  }
  *p = '\0';
  return filename;
}
