
/*Cette fonction permet de retirer du nom du fichier le .obj qu'il contient
 * pour avoir uniquement le nom pour créer les fichier .h et .c
 */
char *slice_by_char(char *filename, char c);

typedef struct{
    long int n; //position du début de l'objet après sa déclaration dans le fichier source
    size_t v_count;
    size_t vn_count;
    size_t vt_count;

}obj_t;

typedef struct{
  float x;
  float y;
  float z;
} vert_t;

typedef struct{
  long int *l;
  size_t size;
  size_t n;
  }indexV_t;


void indexVinit(indexV_t *v);
void add_vert(indexV_t *v, long int val);
void free_indexV(indexV_t *v);
