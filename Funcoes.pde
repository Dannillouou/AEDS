void criaMapa(int [][] matriz, int n)
{
  int linha, coluna;
  boolean denovo = true;
  
  //Preenchendo com espaçoes vazios
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
      matriz[i][j] = ESPACO_VAZIO;
    }
  }

  //Obstáculos
  for(int i = 0; i < NUMERO_OBSTACULOS; i++)
  {
    denovo = true;
    delay(100);
    while(denovo)
    {
      linha = (int)random(n);
      coluna = (int)random(n);
      
      if(matriz[linha][coluna] == ESPACO_VAZIO) 
      {
        matriz[linha][coluna] = OBSTACULO;
        denovo = false;
      }
    }
  }

  denovo = true;
  delay(500);

  //Robo
  while(denovo)
  {
    linha = (int)random(n);
    coluna = (int)random(n);
    if(matriz[linha][coluna] == ESPACO_VAZIO)
    {
      denovo = false;
      matriz[linha][coluna] = ROBO;
    }
  }

  denovo = true;

  delay(500);
  
  //Destino
  while(denovo)
  {
    linha = (int)random(n);
    coluna = (int)random(n);
    if(matriz[linha][coluna] == ESPACO_VAZIO)
    {
      denovo = false;
      matriz[linha][coluna] = DESTINO_ROBO;
    }
  }
  delay(250);
}

int waveFront (int[][] matriz)
{
  int procurando = DESTINO_ROBO, passo = 1;
  boolean achoRobo = false;
  
  while(!achoRobo)
  {
    for(int i = 0; i < DIMENSAO_MATRIZ; i++)
    {
      for(int j = 0; j < DIMENSAO_MATRIZ; j++)
      {
        if(matriz[i][j] == procurando)
        {
          if(i < DIMENSAO_MATRIZ - 1)
          {
            if(matriz[i + 1][j] == ROBO) achoRobo = true;
            else if(matriz[i + 1][j] == ESPACO_VAZIO) matriz[i + 1][j] = passo;
          }
          if(i != 0)
          {
            if(matriz[i - 1][j] == ROBO) achoRobo = true;
            else if(matriz[i - 1][j] == ESPACO_VAZIO) matriz[i - 1][j] = passo;
          }
          if(j < DIMENSAO_MATRIZ - 1)
          {
            if(matriz[i][j + 1] == ROBO) achoRobo = true;
            else if(matriz[i][j + 1] == ESPACO_VAZIO) matriz[i][j + 1] = passo;
          }
          if(j != 0)
          {
            if(matriz[i][j - 1] == ROBO) achoRobo = true;
            else if(matriz[i][j - 1] == ESPACO_VAZIO) matriz[i][j - 1] = passo;
          }
        }
      }
    }
    delay(150);
    procurando = passo;
    passo++;
  }
  
  return passo - 2;
}

void caminho (int[][] matriz, int passos)
{
  int[][] coordenadas = new int[passos][2];
  int aux = 0, passosOriginal = passos, ultimoi = 0, ultimoj = 0;
  boolean chegouDestino = false;
  
  while(!chegouDestino)
  {
    for(int i = 0; i < DIMENSAO_MATRIZ; i++)
    {
      for(int j = 0; j < DIMENSAO_MATRIZ; j++)
      {
        if(matriz[i][j] == passos) 
        {
          if(i < DIMENSAO_MATRIZ - 1)
          {
            if(((i + 1 == ultimoi) && (j == ultimoj)) || (matriz[i + 1][j] == ROBO))
            {
              coordenadas[aux][0] = i;
              coordenadas[aux][1] = j;
              ultimoi = i;
              ultimoj = j;
            }
            if(matriz[i + 1][j] == DESTINO_ROBO) chegouDestino = true;
          }
          if(i != 0)
          {
            if(((i - 1 == ultimoi) && (j == ultimoj)) || (matriz[i - 1][j] == ROBO))
            {
              coordenadas[aux][0] = i;
              coordenadas[aux][1] = j;
              ultimoi = i;
              ultimoj = j;
            }
            if(matriz[i - 1][j] == DESTINO_ROBO) chegouDestino = true;
          }
          if(j < DIMENSAO_MATRIZ - 1)
          {
            if(((i == ultimoi) && (j + 1 == ultimoj)) || (matriz[i][j + 1] == ROBO))
            {
              coordenadas[aux][0] = i;
              coordenadas[aux][1] = j;
              ultimoi = i;
              ultimoj = j;
            }
            if(matriz[i][j + 1] == DESTINO_ROBO) chegouDestino = true;
          }
          if(j != 0)
          {
            if(((i == ultimoi) && (j - 1 == ultimoj)) || (matriz[i][j - 1] == ROBO))
            {
              coordenadas[aux][0] = i;
              coordenadas[aux][1] = j;
              ultimoi = i;
              ultimoj = j;
            }
            if(matriz[i][j - 1] == DESTINO_ROBO) chegouDestino = true;
          }
        }
      }
    }
    passos--;
    aux++;
  }
  
  for(int i = 0; i < passosOriginal; i++)
  {
    delay(100);
    matriz[coordenadas[i][0]][coordenadas[i][1]] = CAMINHO;
  }
}

void simulacao(int[][] matriz)
{
  boolean chegouDestino = false;
  
  delay(50);
  for(int i = 0; i < DIMENSAO_MATRIZ; i++)
  {
    delay(1);
    for(int j = 0; j < DIMENSAO_MATRIZ; j++)
    {
      delay(1);
      if(matriz[i][j] > 0) matriz[i][j] = ESPACO_VAZIO;
    }
  }
  
  while(!chegouDestino)
  {
    for(int i = 0; i < DIMENSAO_MATRIZ; i++)
    {
      for(int j = 0; j < DIMENSAO_MATRIZ; j++)
      {
        if(matriz[i][j] == ROBO) 
        {
          if(i < DIMENSAO_MATRIZ - 1)
          {
            if(matriz[i + 1][j] == CAMINHO) 
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              matriz[i + 1][j] = ROBO;
            }
            else if(matriz[i + 1][j] == DESTINO_ROBO)
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              chegouDestino = true;
              matriz[i + 1][j] = ROBO;
            }
          }
          if(i != 0)
          {
            if(matriz[i - 1][j] == CAMINHO) 
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              matriz[i - 1][j] = ROBO;
            }
            else if(matriz[i - 1][j] == DESTINO_ROBO)
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              chegouDestino = true;
              matriz[i - 1][j] = ROBO;
            }
          }
          if(j < DIMENSAO_MATRIZ - 1)
          {
            if(matriz[i][j + 1] == CAMINHO) 
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              matriz[i][j + 1] = ROBO;
            }
            else if(matriz[i][j + 1] == DESTINO_ROBO)
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              chegouDestino = true;
              matriz[i][j + 1] = ROBO;
            }
          }
          if(j != 0)
          {
            if(matriz[i][j - 1] == CAMINHO) 
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              matriz[i][j - 1] = ROBO;
            }
            else if(matriz[i][j - 1] == DESTINO_ROBO)
            {
              delay(250);
              matriz[i][j] = ESPACO_VAZIO;
              chegouDestino = true;
              matriz[i][j - 1] = ROBO;
            }
          }
        }
      }
    }
  }
}


//============================================================================================================================================================================================

void draw()
{
  background(255);
  
  float largura = width / DIMENSAO_MATRIZ;
  float altura = height / DIMENSAO_MATRIZ;
  
  for(int i = 0; i < DIMENSAO_MATRIZ; i++)
  {
    for(int j = 0; j < DIMENSAO_MATRIZ; j++)
    {
      float y = i * largura;
      float x = j * altura;
      
      if(matrizG[i][j] == ROBO)fill(0, 255, 0);
      else if(matrizG[i][j] == DESTINO_ROBO)fill(#7fffd4);
      else if(matrizG[i][j] == OBSTACULO) fill(#993399);
      else if(matrizG[i][j] == ESPACO_VAZIO)  fill(255);
      else if(matrizG[i][j] == CAMINHO)  fill(0, 0, 255);
      else fill(250 - matrizG[i][j] * 8);
      
      rect(x, y, largura, altura);
      
      fill(0);
      textAlign(CENTER, CENTER);
      text(matrizG[i][j], x + largura / 2, y + altura / 2); 
    }
  }
}
