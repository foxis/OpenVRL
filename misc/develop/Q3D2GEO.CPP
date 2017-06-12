struct HEADER {
       char signature[8];
     char version[2];
     long  numberMeshes;
     long  numberMaterials;
     long  numberTextures;
};

struct vertex
{
        float x, y, z;
};

struct face
{
        unsigned long a, b, c;
};

/*struct MESH {
long   numberVertices;
vertex vertices[numberVertices];
long   numberFaces;
short  faceShapes[numberFaces];
face   faces[numberFaces]
int    materialIndices[numberFaces];
long   numberNormals;
normal normals[numberNormals];
long   numberTextureCoordinates;
texUV  textureCoordinates[numberTextureCoordinates];
face   textureIndices[numberFaces];
vertex centerOfMass;
float  boundingBox[6];
};*/

/*struct MATERIAL {
string materialName;
color  ambientColor;
color  diffuseColor;
color  specularColor;
float  transparency;
};

struct TEXTURE {
string textureName;
int    textureWidth;
int    textureHeight;
pixel  texture[textureWidth * textureHeight]
};*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>

void main(int, char**str)
{

        FILE *in;
        in = fopen(str[1], "rb");
        HEADER h;
        long tmp,vb, i,j,e;
        char c;
        vertex *v;
        long f,lf;
        short *shapes;



        if ( in==0 ) return;
        fread(&h, sizeof(h),1, in);
        fread(&c, 1, 1, in);
        if ( c!='m' ) return;
        fread(&vb, sizeof(vb),1, in);
        v = new vertex[vb];
        fread(v, sizeof(vertex), vb, in);

        fread(&tmp, sizeof(tmp),1, in);
        shapes = new short[tmp];
        fread(shapes, sizeof(short), tmp, in);
        for ( i=0,j=0;i<tmp;i++ ) j+=shapes[i];

        printf("%lu ", vb);
        printf("%lu ", tmp);
        printf("%lu\n", j);
        for ( i=0;i<vb;i++ )
          printf("%.12f %.12f %.12f\n", v[i].x ,v[i].y, v[i].z);

        for ( i=0;i<tmp;i++ )
        {
                printf("%u", shapes[i]);
                for ( j=0;j<shapes[i];j++ )
                {
                        fread(&f, sizeof(f), 1, in);
                        printf(" %lu", f+1);
                }
                printf("\n");
        }

        delete[] v;
        delete[] shapes;
        fclose(in);

};