
package maintp3;

/**
 * Classe que funciona como adicionadora de elementos no conjunto
 * 
 */

public class ConjuntoElemento<T> extends Conjunto<T>{
    private final T valor;
    private final Conjunto<T> conjunto;
    
    
    public ConjuntoElemento(T valor, Conjunto<T> conjunto){
        this.valor = valor;
        this.conjunto = conjunto;
    }
    
    @Override
    public Boolean contemElemento(T elemento){
        return elemento == valor || conjunto.contemElemento(elemento);
    }

}
