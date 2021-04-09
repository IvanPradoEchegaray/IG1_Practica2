#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }
    if (vTexCoords.size() > 0) { // transfer texture  data
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=4), type of each component, stride, pointer
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES; 
  //_LOOP = every vertex connected, _STRIP = every vertex connected except last with first, _FAN = first vertex with every other vertex

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);
  //Vertices Inicio y fin de la linea
  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  //Colores de los vertices, NOTA: Si los vertices tienen distintos colores hace un degradado
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}

Mesh* Mesh::createTriangleRGB(GLdouble rd) //Creacion de una malla que se llamara en su entidad correspondiente
{
    /*Triangulo RGB comentado porque tiene muchas notas utiles
    //Crea una nueva malla vacia
    Mesh* mesh = new Mesh();
    //Le dice a la malla que se rellene siguiendo el GL asignado, Point, Lines, Polygon...
    //NOTA: DEPENDE DE LA MALLA PRIMITIVA se crearan v/n mallas, sienddo v la cantidad de vertices asignados y n la cantidad minima de vertices necesarios para crear la malla,
    //ignorando el resto de la division
    mesh->mPrimitive = GL_TRIANGLES;
    //Vertices de la malla
    mesh->mNumVertices = 3; //En este caso se crearan -> mNumVertices/3 vertices necesarios para malla triangulo = 1
    //Se reserva en el vector vertices un n de espacios igual al de vertices, todo vertice con indice mayor a mNumVerices, no se mostrara
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vVertices.emplace_back(0.0, 50.0, 0.0);
    mesh->vVertices.emplace_back(-50.0, -25.0, 0.0);
    mesh->vVertices.emplace_back(50.0, -25.0, 0.0);
    mesh->vVertices.emplace_back(0.0, 50.0, 20.0);  //Ignorado
    //Se reserva la cantidad de colores igual al numero de vertices, todo vertice con indice mayor a mNumVerices, no se coloreara (con emplaceback())
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 0.0, 1.0); //Ignorado

    return mesh;*/

    //TrianguloRGB ejercicio
    Mesh* mesh = generaPoligono(3, rd);
    mesh->mPrimitive = GL_TRIANGLES;
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return mesh;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd)
{
    //Malla vacia
    Mesh* mesh = new Mesh;
    mesh->mPrimitive = GL_LINE_LOOP;
    //Vertices de malla
    mesh->mNumVertices = numL;
    
    //Posicion
    mesh->vVertices.reserve(mesh->mNumVertices);
    GLdouble ang = 90;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        double x = 0 + rd*cos(radians(ang));
        double y = 0 + rd*sin(radians(ang));
        mesh->vVertices.emplace_back(x, y, 0.0);
        ang += 360.0 / numL;
    }

    return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP)
{
    Mesh* triangulo = generaPoligono(3, rd);
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_POINTS;
    //VerTices de la malla
    mesh->mNumVertices = numP;
    //Posicion y creacion de de la malla
    mesh->vVertices.reserve(mesh->mNumVertices);
    //Crear los 3 vertices iniciales del triangulo
    mesh->vVertices.emplace_back(triangulo->vVertices[0]);
    mesh->vVertices.emplace_back(triangulo->vVertices[1]);
    mesh->vVertices.emplace_back(triangulo->vVertices[2]);
    dvec3 lastVert;
    for (int i = 0; i < numP-3; i++) {
        //Eleccion aleatoria de un vertice inicial
        dvec3 randVertice = triangulo->vVertices[rand() % 3];

        if (i > 0) {
            dvec3 puntoMedio = (lastVert + randVertice) / 2.0;
            lastVert = puntoMedio;
        }
        else
            lastVert = randVertice;

        mesh->vVertices.emplace_back(lastVert);
    }
    delete triangulo; triangulo = nullptr;
    return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0, h, 0.0); //v0
    mesh->vVertices.emplace_back(0, 0, 0.0); //v1
    mesh->vVertices.emplace_back(w, h, 0.0); //v2
    mesh->vVertices.emplace_back(w , 0, 0.0); //v3

    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(-w / 2.0, -h / 2.0, 0.0); //v0
    mesh->vVertices.emplace_back(w / 2.0, -h / 2.0, 0.0); //v1
    mesh->vVertices.emplace_back(-w / 2.0, h / 2.0, 0.0); //v2
    mesh->vVertices.emplace_back(w / 2.0, h / 2.0, 0.0); //v3
    //Color
    mesh->vColors.reserve(mesh->mNumVertices);
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); //v0
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); //v1
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); //v2
    mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); //v3
    return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    //Vertices
    mesh->mNumVertices = 2 * np + 2;
    //angulo inicial
    GLdouble ang = 90;
    
    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);
    //Primer Vertice
    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
    //El resto
    for (int i = 0; i < mesh->mNumVertices - 1; i++) {
        GLdouble radio;
        //cambiar radio entre vertices impares y pares
        if (i % 2 == 0)
            radio = re;
        else
            radio = re / 2;

        GLdouble x = 0 + radio * cos(radians(ang));
        GLdouble y = 0 + radio * sin(radians(ang));
        ang += 360.0 / (2.0 * np);

        mesh->vVertices.emplace_back(x, y, h);

        mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
    }
    return mesh;
}

Mesh* Mesh::generaContCubo(GLdouble ld)
{
    Mesh* mesh = new Mesh();
    //primitiva
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    //vertices
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //10 vertices del cubo
    mesh->vVertices.emplace_back(0, ld , ld); //v0
    mesh->vVertices.emplace_back(0, 0, ld); //v1

    mesh->vVertices.emplace_back(ld, ld, ld); //v2
    mesh->vVertices.emplace_back(ld, 0, ld); //v3

    mesh->vVertices.emplace_back(ld, ld, 0); //v4
    mesh->vVertices.emplace_back(ld , 0, 0); //v5

    mesh->vVertices.emplace_back(0, ld , 0); //v6
    mesh->vVertices.emplace_back(0, 0, 0); //v7

    mesh->vVertices.emplace_back(mesh->vVertices[0]); //v8
    mesh->vVertices.emplace_back(mesh->vVertices[1]); //v9


    return mesh;
}
Mesh* Mesh::generaContCuboSuelo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();
    //primitiva
    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    //vertices
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //10 vertices del cubo
    mesh->vVertices.emplace_back(0, h, w); //v0
    mesh->vVertices.emplace_back(0, 0, w); //v1

    mesh->vVertices.emplace_back(w, h, w); //v2
    mesh->vVertices.emplace_back(w, 0, w); //v3

    mesh->vVertices.emplace_back(w, h, 0); //v4
    mesh->vVertices.emplace_back(w, 0, 0); //v5

    mesh->vVertices.emplace_back(0, h, 0); //v6
    mesh->vVertices.emplace_back(0, 0, 0); //v7

    mesh->vVertices.emplace_back(mesh->vVertices[0]); //v8
    mesh->vVertices.emplace_back(mesh->vVertices[1]); //v9


    return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
    Mesh* mesh = generaRectangulo(w, h);
    //Coordenadas de texturas
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0, 1.0 *rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(1.0*rw, 1.0*rh);
    mesh->vTexCoords.emplace_back(1.0*rw, 0);

    return mesh;
}

Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
    Mesh* mesh = generaEstrella3D(re, np, h);

    mesh->vTexCoords.reserve(mesh->mNumVertices);

    float ang = 90;

    mesh->vTexCoords.emplace_back(0, 0);    //Origen de la estrella

    for (int i = 0; i < mesh->mNumVertices - 1; i++) { //-1 pq el vertice inicial se declara antes
        
        float x = cos(radians(ang))*0.5f;
        float y = sin(radians(ang))*0.5f;
        mesh->vTexCoords.emplace_back(x, y);
        ang = ang + 360.0 / (2.0 * np);
    }

    return mesh;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble nl)
{
    Mesh* mesh = generaContCubo(nl);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    //10 vertices de la textura
    mesh->vTexCoords.emplace_back(0, 1.0f);
    mesh->vTexCoords.emplace_back(0, 0);
    //1a cara
    mesh->vTexCoords.emplace_back(1.0f, 1.0f);
    mesh->vTexCoords.emplace_back(1.0f, 0); 
    //2a cara
    mesh->vTexCoords.emplace_back(0, 1.0f);
    mesh->vTexCoords.emplace_back(0, 0);
    //3a cara
    mesh->vTexCoords.emplace_back(1.0f, 1.0f);
    mesh->vTexCoords.emplace_back(1.0f, 0);
    //4a cara
    mesh->vTexCoords.emplace_back(0, 1.0f);
    mesh->vTexCoords.emplace_back(0, 0);

    return mesh;
}

Mesh* Mesh::generaContCuboSueloTexCor(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaContCuboSuelo(w,h);
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    //10 vertices de la textura
    mesh->vTexCoords.emplace_back(0, 1.0f);
    mesh->vTexCoords.emplace_back(0, 0);
    //1a cara
    mesh->vTexCoords.emplace_back(1.0f, 1.0f);
    mesh->vTexCoords.emplace_back(1.0f, 0);
    //2a cara
    mesh->vTexCoords.emplace_back(0, 1.0f);
    mesh->vTexCoords.emplace_back(0, 0);
    //3a cara
    mesh->vTexCoords.emplace_back(1.0f, 1.0f);
    mesh->vTexCoords.emplace_back(1.0f, 0);
    //4a cara
    mesh->vTexCoords.emplace_back(mesh->vTexCoords[0]);
    mesh->vTexCoords.emplace_back(mesh->vTexCoords[1]);

    return mesh;
}


