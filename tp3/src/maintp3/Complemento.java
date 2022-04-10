
package maintp3;

/**
 * Classe que gerará o complemento do conjunto em questão
 * O complemento nesse caso retorna verdadeiro sempre que é procurado um número que não é parte do conjunto
 */

public class Complemento<T> extends Conjunto<T> {
   
   private final Conjunto<T> conjunto; 
    
   public Complemento(Conjunto<T> conjunto){
       
       this.conjunto = conjunto;
   }
   
   @Override
   public Boolean contemElemento(T elemento){
   
       return !(conjunto.contemElemento(elemento));   
   }
}
