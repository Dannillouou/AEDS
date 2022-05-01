void setup()
{
  size(600, 600);
  background(0);
  thread("main");
}

void main()
{
  int aux;
 
  criaMapa(matrizG, DIMENSAO_MATRIZ);
  aux = waveFront(matrizG);
  caminho(matrizG, aux);
  simulacao(matrizG);  
}
