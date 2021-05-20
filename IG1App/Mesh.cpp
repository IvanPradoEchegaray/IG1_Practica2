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

    if (vNormals.size() > 0) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_DOUBLE, 0, vNormals.data());
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
    glDisableClientState(GL_NORMAL_ARRAY);
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

Mesh* Mesh::generaPolygon3D(GLdouble re, GLuint np)
{
    Mesh* mesh = new Mesh();
    mesh->mPrimitive = GL_TRIANGLE_FAN;
    //Vertices
    mesh->mNumVertices = np + 2;
    //angulo inicial
    GLdouble ang = 0;

    mesh->vVertices.reserve(mesh->mNumVertices);
    mesh->vColors.reserve(mesh->mNumVertices);
    //Primer Vertice
    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
    //El resto
    for (int i = 0; i < mesh->mNumVertices - 1; i++) {
        GLdouble x = 0 + re * cos(radians(ang));
        GLdouble y = 0 + re * sin(radians(ang));
        ang -= 360.0 / np;

        mesh->vVertices.emplace_back(x, y, 0.0);

        mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
    }
    return mesh;
}

Mesh* Mesh::generaPolygonTexCor(GLdouble re, GLuint np)
{
    Mesh* mesh = generaPolygon3D(re, np);

    mesh->vTexCoords.reserve(mesh->mNumVertices);

    float ang = 0;

    mesh->vTexCoords.emplace_back(0.5, 0.5);    //Origen de poligono

    for (int i = 0; i < mesh->mNumVertices - 1; i++) { //-1 pq el vertice inicial se declara antes

        float x = cos(radians(ang))*0.5+0.5;
        float y = sin(radians(ang))*0.5+0.5;
        ang -= 360.0 / np;

        mesh->vTexCoords.emplace_back(x, y);
    }

    return mesh;
}
Mesh* Mesh::generaGrassTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    mesh->vVertices.emplace_back(0, h, 0.0); //v0
    mesh->vVertices.emplace_back(0, 0, 0.0); //v1
    mesh->vVertices.emplace_back(w, h, 0.0); //v2
    mesh->vVertices.emplace_back(w, 0, 0.0); //v3

    //Coordenadas de texturas
    mesh->vTexCoords.reserve(mesh->mNumVertices);
    mesh->vTexCoords.emplace_back(0, 1.0 * rh);
    mesh->vTexCoords.emplace_back(0, 0);
    mesh->vTexCoords.emplace_back(1.0 * rw, 1.0 * rh);
    mesh->vTexCoords.emplace_back(1.0 * rw, 0);

    return mesh;
}

Mesh* Mesh::generaContCristal(GLdouble ld)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    mesh->mNumVertices = 10;
    mesh->vVertices.reserve(mesh->mNumVertices);

    //V0
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, ld / 2.0));

    //V1
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, ld / 2.0));
    //V2
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 6.0, ld / 2.0));
    //V3
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 6.0, ld / 2.0));
    //V4
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, ld / 6.0, -ld / 2.0));
    //V5
    mesh->vVertices.emplace_back(dvec3(ld / 2.0, -ld / 6.0, -ld / 2.0));
    //V6
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, -ld / 2.0));
    //V7
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, -ld / 2.0));

    //2 para cerrar
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, ld / 6.0, ld / 2.0));
    mesh->vVertices.emplace_back(dvec3(-ld / 2.0, -ld / 6.0, ld / 2.0));


    mesh->vTexCoords.reserve(mesh->mNumVertices);

    //V0
    mesh->vTexCoords.emplace_back(0, 1);

    //V1
    mesh->vTexCoords.emplace_back(0, 0);
    //V2
    mesh->vTexCoords.emplace_back(1, 1);
    //V3
    mesh->vTexCoords.emplace_back(1, 0);
    //V4
    mesh->vTexCoords.emplace_back(2, 1);
    //V5
    mesh->vTexCoords.emplace_back(2, 0);
    //V6
    mesh->vTexCoords.emplace_back(3, 1);
    //V7
    mesh->vTexCoords.emplace_back(3, 0);
    //V8
    mesh->vTexCoords.emplace_back(4, 1);
    mesh->vTexCoords.emplace_back(4, 0);

    //2 mas para cerrar
    mesh->vTexCoords.emplace_back(0, 1);
    mesh->vTexCoords.emplace_back(0, 0);

    return mesh;
}
//---Mesh Index--
void IndexMesh::render() const
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
        if (vIndices != nullptr) {
            glEnableClientState(GL_INDEX_ARRAY);
            glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
        }
        if (vNormals.size() > 0) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_DOUBLE, 0, vNormals.data());
        }
        draw();

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_INDEX_ARRAY);
    }
}


void IndexMesh::buildNormalVectors()
{
    vNormals.reserve(mNumVertices);
    for (int i = 0; i < mNumVertices; i++)
        vNormals.push_back(glm::dvec3(0,0,0));

   for (int i = 0; i < mNumIndices; i += 3)
    {
        GLuint aux0, aux1, aux2;

        aux0 = vIndices[i];
        aux1 = vIndices[i + 1];
        aux2 = vIndices[i + 2];

        dvec3 n = cross((vVertices[aux2] - vVertices[aux1]), (vVertices[aux0] - vVertices[aux1]));

        vNormals[aux0] += n;
        vNormals[aux1] += n;
        vNormals[aux2] += n;
    }
   for (int i = 0; i < mNumVertices; i++)
       vNormals[i] = normalize(vNormals[i]);
}
void IndexMesh::draw() const
{
    glDrawElements(mPrimitive, mNumIndices, GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generaAnilloCuadradoIndexado()
{
    IndexMesh* m = new IndexMesh();

    m->mPrimitive = GL_TRIANGLE_STRIP;

    m->mNumVertices = 8;

    m->vVertices.reserve(m->mNumVertices);

    m->vColors.reserve(m->mNumVertices);

    //Colores                                //V駻tices                                
    m->vColors.emplace_back(0.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(30.0, 30.0, 0.0);
    m->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(10.0, 10.0, 0.0);
    m->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); m->vVertices.emplace_back(70.0, 30.0, 0.0);
    m->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); m->vVertices.emplace_back(90.0, 10.0, 0.0);
    m->vColors.emplace_back(1.0, 1.0, 0.0, 1.0); m->vVertices.emplace_back(70.0, 70.0, 0.0);
    m->vColors.emplace_back(1.0, 0.0, 1.0, 1.0); m->vVertices.emplace_back(90.0, 90.0, 0.0);
    m->vColors.emplace_back(0.0, 1.0, 1.0, 1.0); m->vVertices.emplace_back(30.0, 70.0, 0.0);
    m->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(10.0, 90.0, 0.0);

    //Indices
    m->mNumIndices = 10;

    m->vIndices = new GLuint[m->mNumIndices];

    for (int i = 0; i < m->mNumIndices; i++) {
        m->vIndices[i] = i % 8;
    }

    //Normales

    m->vNormals.reserve(m->mNumVertices);

    for (int i = 0; i < m->mNumVertices; i++) {
        m->vNormals.push_back(glm::dvec3(0, 0, 0));
    }

    //Los tres v駻tices del tri疣gulo y n la normal
    glm::dvec3 a, b, c, n;

    a = m->vVertices[m->vIndices[0]];
    b = m->vVertices[m->vIndices[1]];
    c = m->vVertices[m->vIndices[2]];

    //Producto vectorial para sacar la perpendicular
    n = glm::cross((b - a), (c - a));

    //Porque todos los tri疣gulos tienen la misma normal
    for (int i = 0; i < m->mNumVertices; i++) {
        m->vNormals[i] = glm::normalize(n);
    }

    return m;
}

IndexMesh* IndexMesh::generaCuboConTapasIndexado(GLdouble l)
{
    IndexMesh* m = new IndexMesh();

    m->mPrimitive = GL_TRIANGLES;

    m->mNumVertices = 8;

    m->vVertices.reserve(m->mNumVertices);

    m->vColors.reserve(m->mNumVertices);

    //Vertices
    m->vVertices.emplace_back(-l / 2, l / 2, l / 2);
    m->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
    m->vVertices.emplace_back(l / 2, l / 2, l / 2);
    m->vVertices.emplace_back(l / 2, -l / 2, l / 2);
    m->vVertices.emplace_back(l / 2, l / 2, -l / 2);
    m->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
    m->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
    m->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

    //Indices
    m->mNumIndices = 36;

    m->vIndices = new GLuint[m->mNumIndices]
    { 0, 1, 3,  //Cara delantera
     3, 2, 0,
     2, 3, 4,   //Cara derecha
     4, 3, 5,
     4, 5, 6,   //Cara trasera
     6, 5, 7,
     6, 7, 1,   //Cara izqda
     6, 1, 0,
     6, 0, 4,   //Cara superior
     4, 0, 2,
     1, 7, 5,   //Cara inferior
     5, 3, 1 };

    m->vNormals.reserve(m->mNumVertices);
    //Inicializa
    for (int i = 0; i < m->mNumVertices; i++) {
        m->vNormals.push_back(glm::dvec3(0, 0, 0));
    }

    //SEGUNDO:
    /*m->vNormals[0] = glm::normalize(glm::dvec3(-1, 1, 1));
    m->vNormals[1] = glm::normalize(glm::dvec3(-1, -1, 1));
    m->vNormals[2] = glm::normalize(glm::dvec3(1, 1, 1));
    m->vNormals[3] = glm::normalize(glm::dvec3(1, -1, 1));
    m->vNormals[4] = glm::normalize(glm::dvec3(1, 1, -1));
    m->vNormals[5] = glm::normalize(glm::dvec3(1, -1, -1));
    m->vNormals[6] = glm::normalize(glm::dvec3(-1, 1, -1));
    m->vNormals[7] = glm::normalize(glm::dvec3(-1, -1, -1));*/

    //Metodo eficiente
    m->buildNormalVectors();

    return m;
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint nDiv)
{
    IndexMesh* m = new IndexMesh();

    m->mPrimitive = GL_TRIANGLES;

    GLdouble incrXZ = lado / nDiv; //Longitud de la division
    GLdouble numFC = nDiv+1; //Longitud de la division

    //Generacion de vertices
    m->mNumVertices = numFC * numFC;
    m->vVertices.resize(m->mNumVertices);

    //Vertices
    for (int i = 0; i < numFC; i++) {
        for (int j = 0; j < numFC; j++)
        {
            GLdouble x = - lado / 2;
            GLdouble z = - lado / 2;
            m->vVertices[i * numFC + j] = glm::dvec3(x + j * incrXZ, 0, z + i * incrXZ);
        }
    }
    //Indices
    m->mNumIndices = nDiv * nDiv * 6;
    m->vIndices = new GLuint[m->mNumIndices];
    //generacion de indices
    int i = 0;
    for (int h = 0; h < nDiv; h++)
    {
        for (int k = 0; k < nDiv; k++)
        {
            GLuint iv = h * numFC + k;
            m->vIndices[i++] = iv;
            m->vIndices[i++] = iv + numFC; 
            m->vIndices[i++] = iv + 1;
            m->vIndices[i++] = iv + 1;
            m->vIndices[i++] = iv + numFC;
            m->vIndices[i++] = iv + numFC + 1;

        }
    }

    m->vNormals.reserve(m->mNumVertices);
    //Inicializa
    for (int i = 0; i < m->mNumVertices; i++) {
        m->vNormals.push_back(glm::dvec3(0, 0, 0));
    }
    //Metodo eficiente
    m->buildNormalVectors();
    return m;
}

IndexMesh* IndexMesh::generateGridTex(GLdouble lado, GLuint nDiv)
{
    IndexMesh* m = generateGrid(lado, nDiv);
    GLdouble numFC = nDiv + 1;

    //Generacion coordenadas
    m->vTexCoords.resize(m->mNumVertices);

    int s = 0, t = 1;
    for (int i = 0; i < numFC; i++)
    {
        for (int j = 0; j < numFC; j++)
        {
            m->vTexCoords[i * numFC + j] = dvec2(s + (1 / numFC * j), t - (1 / numFC * i));
        }
    }

    return m;
}


MbR::MbR(int m, int n, dvec3* perfil) : m_(m), n_(n), perfil_(perfil) {};

MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, dvec3* perfil)
{
    MbR* mesh = new MbR(mm, nn, perfil);
    // Definir la primitiva como GL_TRIANGLES
    mesh->mPrimitive = GL_TRIANGLES;
    // Definir el n伹ero de v駻tices como nn*mm
    mesh->mNumVertices = nn * mm;
    // Usar un vector auxiliar de v駻tices
    dvec3* verticesAux = new dvec3[mesh->mNumVertices];
    for (int i = 0; i < nn; i++) {
        // Generar la muestra i-駸ima de v駻tices
        GLdouble theta = i * 360 / nn;
        GLdouble c = cos(radians(theta));
        GLdouble s = sin(radians(theta));
        // R_y(theta) es la matriz de rotaci alrededor del eje Y
        for (int j = 0; j < mm; j++) {
            int indice = i * mm + j;
            GLdouble x = c * perfil[j].x + s * perfil[j].z;
            GLdouble z = -s * perfil[j].x + c * perfil[j].z;
            verticesAux[indice] = dvec3(x, perfil[j].y, z);
        }
    }

    //Volcar el array auxiliar vertices que acabamos de usar, en vVertices
    for (int i = 0; i < mesh->mNumVertices; i++)
        mesh->vVertices.push_back(verticesAux[i]);

    // Es 6mn - 6n
    //  Al ser 6 vertices por cara, y dar mn vueltas, esas son las caras que se construyen.
    // Como arriba y abajo no son 6 sino 3, pues hay que restarle esos vertices al total. 
    // Como se realiza n vueltas, y arriba y abajo son 6 en total, es -6*n
    mesh->mNumIndices = 6 * nn * (mm - 1);
    mesh->vIndices = new GLuint[mesh->mNumIndices];
    int indiceMayor = 0;
    //El contador i recorre las muestras alrededor del eje Y
    for (int i = 0; i < nn; i++) {
        // El contador j recorre los v�rtices del perfil, 
        // de abajo arriba. Las caras cuadrangulares resultan
        // al unir la muestra i-�sima con la (i+1)%nn-�sima
        for (int j = 0; j < mm - 1; j++) {
            // El contador indice sirve para llevar cuenta 
            // de los �ndices generados hasta ahora. Se recorre
            // la cara desde la esquina inferior izquierda 
            int indice = i * mm + j;
            //Primer triangulo de la cara
            mesh->vIndices[indiceMayor++] = indice;
            mesh->vIndices[indiceMayor++] = (indice + mm) % (nn * mm);
            mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
            //Segundo subnormal triangulo de la cara
            mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
            mesh->vIndices[indiceMayor++] = (indice + 1);
            mesh->vIndices[indiceMayor++] = indice;
        }
    }

    mesh->buildNormalVectors();
    return mesh;
}