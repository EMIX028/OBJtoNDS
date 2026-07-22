/*permet de couper la chaine de caractère contenant les données d'une face en
 * plusieurs morceaux pour chaque vertices de cette face
 *
 */
void strFacesCut(char *buffer, char *out, size_t index);

/*
 * récupère la position du vertices de la face dans le fichier source
 */
int get_v(char *s);
int get_vn(char *s);

/*renvoie le nombre de vertices que contient une face
 */
unsigned int strnombre_vert(char *s, size_t n);

typedef struct{
  float x;
  float y;
  float z;
} vert_t;

typedef struct {
  vert_t *l; //liste d'emplacement de chaque vertices dans le fichier source
  size_t size; //taille de la liste (malloc)
  size_t n; //longueur de la liste
} indexV_t;

void indexVinit(indexV_t *v); //initialise la structure
void add_vert(indexV_t *v, vert_t val); // ajoute une vertices à la liste
void free_indexV(indexV_t *v); //libère la mémoire de la variable v
