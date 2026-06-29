#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    //un seul paramètre qui est le fichier 3d, argc == 2 car exec de la commande
    // en +
    fprintf(stderr,
        "un et uniquement un paramètre qui est le nom du fichier obj à convertir\n");
    return EXIT_FAILURE;
  }
  char *filename = argv[1];
  FILE *fobj = fopen(filename, "rb"); //fichier 3d source
  if (fobj == nullptr) {
    fprintf(stderr, "Erreur lors de l'ouverture de %s\n", filename);
    return EXIT_FAILURE;
  }
  //initialise le nom des fichier .h et .c résultant du fichier source
  char base[256];
  strcpy(base, filename);
  slice_by_char(base, '.');
  char Hname[260];
  char Cname[260];
  sprintf(Hname, "%s.h", base);
  sprintf(Cname, "%s.c", base);
  FILE *fhptr = fopen(Hname, "wb");
  if (fhptr == nullptr) {
    fclose(fobj);
    fprintf(stderr, "Erreur lors de la création de %s\n", Hname);
    return EXIT_FAILURE;
  }
  printf("le fichier %s a été crée\n", Hname);
  FILE *fcptr = fopen(Cname, "wb");
  if (fcptr == nullptr) {
    fclose(fobj);
    fclose(fhptr);
    fprintf(stderr, "Erreur lors de la création de %s\n", Cname);
  }
  printf("le fichier %s a été crée\n", Cname);
  fprintf(fcptr, "#include \"%s\"\n\n", Hname);
  char startingF[]
    =
      "  if(cullback){\n    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_BACK);\n  }\n  else{\n    glPolyFmt(POLY_ALPHA(alpha) | POLY_CULL_NONE);\n  }\n";
  char id[3];
  char buffer[100];
  bool firstO = true;
  obj_t objet = {
    objet.n = 0, objet.v_count = 0, objet.vn_count = 0, objet.vt_count = 0
  };
  indexV_t Vlist;
  indexVinit(&Vlist);
  long int k = 0;

  while (fgets(id,3,fobj) != nullptr) {
    printf("id : %c%c\n",id[0],id[1]);
    //lit le premier caractère pour verifier le type d'objet
    if (fgets(buffer, sizeof(buffer), fobj) != nullptr) {
      //on récupère la ligne entière pour la traiter
      if (id[0] == 'o') {
        objet.n = ftell(fobj);
        // cas objet
        if (!firstO) {
          fprintf(fcptr, "}\n");  // sert à fermer les fonctions si c'est pas la
                                  // première ligne
        }
        firstO = false;
        fprintf(fhptr,
            "void draw%s(bool cullback, unsigned int alpha, float x, float y, float z);\n",
            slice_by_char(buffer, (char) 10)); // 10 = caractère \n
        fprintf(fcptr,
            "void draw%s(bool cullback, unsigned int alpha, float x, float y, float z){\n",
            buffer);
        fprintf(fcptr, startingF);
      }
      if (id[0] == 'v' && id[1] == ' ') {
        add_vert(&Vlist,ftell(fobj));
        objet.v_count += 1;
        printf("vertices ligne %ld\n",k);
      }
    } else {
      fprintf(stderr,
          "la fin du fichier est atteinte ou un problème est survenue\n");
      break;
    }
    ++k;
  }
  if(!firstO){
    fprintf(fcptr, "}\n");
  }
  /*
   * cas des différents type d'erreur de fichier à traiter
   */
  fclose(fobj);
  fclose(fhptr);
  fclose(fcptr);
  return EXIT_SUCCESS;
}

char *slice_by_char(char *filename, char c) {
  /*
   * recherche décroissante du caractère C dans la chaine filename
   * pour séparer la chaine de caractère en deux.
   */
  char *p = filename + strlen(filename);
  while (p > filename && *p != c) {
    --p;
  }
  *p = '\0';
  return filename;
}


void indexVinit(indexV_t *v){
  v->size = 4;
  v->n = 0;
  v->l = malloc(v->size * sizeof(long int));
}

void add_vert(indexV_t *v, long int val) {
    if (v->n == v->size) {
        v->size *= 2;
        v->l = realloc(v->l, v->size * sizeof(long int));
    }

    v->l[v->n++] = val;
}

void free_indexV(indexV_t *v) {
    free(v->l);
    v->l = nullptr;
    v->n = 0;
    v->size = 0;
}
