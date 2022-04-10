
package maintp3;

/**
 * @file TP3.java
 * @author Daniel de Miranda Almeida
 * @brief Trabalho para a disciplina de AEDS do terceiro módulo
 * @date 16/01/2022
 */

public class TP3 {
    
    public static void main(String[] args) {
       
       // c1 = {1, 2, 3, 4, 5}
       Conjunto<Integer> c1 = new ConjuntoVazio<>();
       c1 = c1.adicionarElemento(1);
       c1 = c1.adicionarElemento(2);
       c1 = c1.adicionarElemento(3);
       c1 = c1.adicionarElemento(4);
       c1 = c1.adicionarElemento(5);

       // c2 = {1, 3, 5, 7, 9}
       Conjunto<Integer> c2 = new ConjuntoVazio<>();
       c2 = c2.adicionarElemento(1);
       c2 = c2.adicionarElemento(3);
       c2 = c2.adicionarElemento(5);
       c2 = c2.adicionarElemento(7);
       c2 = c2.adicionarElemento(9);

       System.out.println(c1.contemElemento(2)? "2 ∈ c1" :"2 ∉ c1");
       System.out.println(c1.contemElemento(7)? "7 ∈ c1" :"7 ∉ c1");

       System.out.println(c2.contemElemento(7)? "7 ∈ c2" :"7 ∉ c2");
       System.out.println(c2.contemElemento(8)? "8 ∈ c2" :"8 ∉ c2");

       // c3 = c1 U c2 = {1, 2, 3, 4, 5, 7, 9}
       Conjunto<Integer> c3 = c1.uniao(c2);

       System.out.println(c3.contemElemento(5)? "5 ∈ c3" :"5 ∉ c3");
       System.out.println(c3.contemElemento(6)? "6 ∈ c3" :"6 ∉ c3");

       // c4 = c1 ∩ c2 = {1, 3, 5}
       Conjunto<Integer> c4 = c1.intersecao(c2);

       System.out.println(c4.contemElemento(3)? "3 ∈ c4" :"3 ∉ c4");
       System.out.println(c4.contemElemento(4)? "4 ∈ c4" :"4 ∉ c4");

       // c5 = c1 - c2 = {2, 4}
       Conjunto<Integer> c5 = c1.diferenca(c2);

       System.out.println(c5.contemElemento(3)? "3 ∈ c5" :"3 ∉ c5");
       System.out.println(c5.contemElemento(4)? "4 ∈ c5" :"4 ∉ c5");

       // c6 = complemento(c1)
       Conjunto<Integer> c6 = c1.complemento();

       System.out.println(c6.contemElemento(2)? "2 ∈ c6" :"2 ∉ c6");
       System.out.println(c6.contemElemento(7)? "7 ∈ c6" :"7 ∉ c6");
   }    
}
