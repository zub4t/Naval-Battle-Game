
 --------------------- Compilar -----------------

O makefile gera o ficheiro executavel chamado "game".

--------------------- Como colocar os barcos ----------------

O primeiro input que o programa pede é tamanho do tabuleiro, 
deve ser um inteiro entre 20 a 40;

Depois o programa pede se quer gerar os barcos de forma aleatoria 
nos tabuleiros (1) ou de forma manual (0);

Se optar pela opção manual, tem uma breve descrição do formato do barco, 
deve dizer quantos barcos é que quer daquelo tipo, e deve intruduzir as 
coordenadas em que pretende colocar o barco, por ultimo deve dizer a 
rotação que pretende que o barco tenha (0,90,180,270);

------------------- como jogar o jogo --------------------

Devera seguir as indicações para mudar de jogador entre rondas;
Quando for a sua de jogar, tera uma primeira matriz com a disposição dos
seus barcos e uma segunda matriz com os seus disparos;

Para disparar deve introduzir as coordenadas que pretende atingir e
no topo das matrizes vai aparecer um aviso que o avisa se atingiu
um barco, afundou um navio, se ganhou o jogo ou se falhou, também
pode confirmar visualmente o resultado se olhar para a célula que 
disparou;

---------------- Legenda da matriz ----------------------------

Simbolo                   descrição                     cor   
           
 '~'              nenhum barco / por decobrir           azul
 '#'                 célula de um barco                branco
 'X'     célula de um barco atingida por um tiro      vermelho
 'O'       tiro que não acertou em nenhum barco        amarelo  
  

