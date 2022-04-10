
package maintp3;

/**
 * Classe que, ao usar a funcao de contemElemento, retorna a diferenca entre dois conjuntos
 *
 */
public class Diferenca<T> extends Conjunto<T> {
  
    private final Conjunto<T> conjunto;
    private final Conjunto<T> conjunto2;
    
    public Diferenca(Conjunto<T> conjunto, Conjunto<T> conjunto2){
        this.conjunto = conjunto;
        this.conjunto2 = conjunto2;
    }
    
    @Override
    public Boolean contemElemento(T elemento){
        return conjunto.contemElemento(elemento) && !(conjunto2.contemElemento(elemento));
    }
    
}
