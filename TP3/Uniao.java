
package maintp3;

/**
 * Classe que gerará a união dos conjuntos em questão
 * O objeto é um "conjunto" que armazena dois conjuntos
 */
public class Uniao<T> extends Conjunto<T>{
   
   private final Conjunto<T> conjunto;
   private final Conjunto<T> conjunto2;
    
   public Uniao (Conjunto <T> conjunto, Conjunto<T> conjunto2){
       this.conjunto = conjunto;
       this.conjunto2 = conjunto2;
   }
   
   @Override
   public Boolean contemElemento(T elemento){
       return conjunto.contemElemento(elemento) || conjunto2.contemElemento(elemento);
   }           
}
