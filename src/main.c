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
  char nom[256];
  sscanf(filename, "%255[^.].obj", nom);
  printf("nom du fichier : %s\n", nom);
  char Hname[258];
  char Cname[258];
  sprintf(Hname, "%s.h", nom);
  sprintf(Cname, "%s.c", nom);
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
  fprintf(fcptr, "#include <nds.h>\n");
  fprintf(fcptr, "#include \"%s\"\n\n", Hname);
  size_t ligne = 0;
  //long pos;
  indexV_t Vlist;
  indexVinit(&Vlist);
  indexV_t VNlist;
  indexVinit(&VNlist);
  char buffer[128];
  //char type;
  char suite[126];
  while (1) {
    //pos = ftell(fobj);
    if (fgets(buffer, sizeof(buffer), fobj) == nullptr) {
      break;
    }
    sscanf(buffer, "%*c%*c %126[^\n]", suite);
    if (strncmp(buffer, "o ", 2) == 0) {
      if (ftell(fhptr) != 0) {
        fprintf(fcptr, "}\n\n");
      }
      fprintf(fhptr,
          "void draw%s(bool cullback);\n\n",
          suite);
      fprintf(fcptr,
          "void draw%s(bool cullback){\n",
          suite);
      fprintf(fcptr,
          "\tglPolyFmt(POLY_ALPHA(31) |(cullback ? POLY_CULL_BACK : POLY_CULL_NONE)| POLY_FORMAT_LIGHT0);\n");
      fprintf(fcptr, "\tglColor3b(255,255,255);\n");
    } else if (strncmp(buffer, "v ", 2) == 0) {     //Vertices
      vert_t vertices = { vertices.x = 0, vertices.y = 0, vertices.z = 0 };
      sscanf(suite, "%f %f %f", &vertices.x, &vertices.y, &vertices.z);
      add_vert(&Vlist, vertices);
      printf("le vertice (%f, %f, %f) ligne %ld à été ajouté\n", vertices.x,
          vertices.y, vertices.z, ligne + 1);
    } else if (strncmp(buffer, "vn", 2) == 0) {     //Normals
      printf("%s\n",suite);
      vert_t normal = { normal.x = 0, normal.y = 0, normal.z = 0 };
      sscanf(suite, " %f %f %f", &normal.x, &normal.y, &normal.z);
      add_vert(&VNlist, normal);
      printf("la normal (%f, %f, %f) ligne %ld à été ajouté\n", normal.x,
          normal.y, normal.z, ligne + 1);
    } else if (strncmp(buffer, "f ", 2) == 0) {     //faces
      unsigned int nbVert = strnombre_vert(suite, strlen(suite));
      printf("%s nombre vertices : %u\n", suite, nbVert);
      char out[14]; //environ taille d'un morceau v/vt/vn
      if (nbVert == 4) {
        fprintf(fcptr, "\tglBegin(GL_QUADS);\n");
        for (int k = 0; k < (int) nbVert; ++k) {
          strFacesCut(suite, out, (size_t) k);
          fprintf(fcptr,
              "\tglNormal(NORMAL_PACK(floattov10(%f),floattov10(%f),floattov10(%f)));\n",
              VNlist.l[get_vn(out) - 1].x, VNlist.l[get_vn(out) - 1].y,
              VNlist.l[get_vn(out) - 1].z);
          fprintf(fcptr,
              "\tglVertex3v16(floattov16(%f), floattov16(%f), floattov16(%f));\n\n",
              Vlist.l[get_v(out) - 1].x,
              Vlist.l[get_v(out) - 1].y, Vlist.l[get_v(out) - 1].z);
        }
        fprintf(fcptr, "\tglEnd();\n");
      }else if(nbVert == 3){
        fprintf(fcptr, "\tglBegin(GL_TRIANGLES);\n");
        for (int k = 0; k < (int) nbVert; ++k) {
          strFacesCut(suite, out, (size_t) k);
          fprintf(fcptr,
              "\tglNormal(NORMAL_PACK(floattov10(%f),floattov10(%f),floattov10(%f)));\n",
              VNlist.l[get_vn(out) - 1].x, VNlist.l[get_vn(out) - 1].y,
              VNlist.l[get_vn(out) - 1].z);
          fprintf(fcptr,
              "\tglVertex3v16(floattov16(%f), floattov16(%f), floattov16(%f));\n\n",
              Vlist.l[get_v(out) - 1].x,
              Vlist.l[get_v(out) - 1].y, Vlist.l[get_v(out) - 1].z);
        }
        fprintf(fcptr, "\tglEnd();\n");
      } else {
        fprintf(stderr,
            "le nombre de vertices présent dans cette face ne respecte la norme nds\n");
      }
    }
    ++ligne;
  }
  fprintf(fcptr, "}");
  fclose(fobj);
  fclose(fhptr);
  fclose(fcptr);
  return EXIT_SUCCESS;
}

void strFacesCut(char *buffer, char *out, size_t index) {
  size_t current = 0;
  size_t start = 0;
  size_t end = 0;
  while (buffer[start] != '\0') {
    if (buffer[start] == ' ') {
      start++;
      continue;
    }
    if (current == index) {
      end = start;
      while (buffer[end] != ' ' && buffer[end] != '\0') {
        end++;
      }
      strncpy(out, buffer + start, end - start);
      out[end - start] = '\0';
      return;
    }
    while (buffer[start] != ' ' && buffer[start] != '\0') {
      start++;
    }
    current++;
  }
  out[0] = '\0';
}

unsigned int strnombre_vert(char *s, size_t n) {
  const char *p = (const char *) s + n;
  unsigned int k = 0;
  while (p >= s) {
    if (*p == ' ') {
      ++k;
    }
    --p;
  }
  return k + 1;
}

int get_v(char *s) {
  int res;
  sscanf(s, "%d", &res);
  return res;
}

int get_vn(char *s) {
  int res;
  sscanf(s, "%*d%*c%*d%*c%d", &res);
  return res;
}

void indexVinit(indexV_t *v) {
  v->size = 4;
  v->n = 0;
  v->l = malloc(v->size * sizeof(vert_t));
}

void add_vert(indexV_t *v, vert_t val) {
  if (v->n == v->size) {
    v->size *= 2;
    v->l = realloc(v->l, v->size * sizeof(vert_t));
  }
  v->l[v->n++] = val;
}

void free_indexV(indexV_t *v) {
  free(v->l);
  v->l = nullptr;
  v->n = 0;
  v->size = 0;
}
