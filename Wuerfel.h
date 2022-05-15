class Wuerfel {

public:
    Wuerfel();
    void zeichneWuerfel(GLfloat fSeitenL);
    void Wuerfel1(GLfloat fSeitenL, GLfloat fSeitenLX, GLfloat fSeitenLY, GLfloat fSeitenLZ, GLfloat fTransLX, GLfloat fTransLY, GLfloat fTransLZ);
    void scaleCube(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
    void translateCube(GLfloat translateX, GLfloat translateY, GLfloat translateZ);
    void rotateCube(GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ);
};