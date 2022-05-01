
package maintp3;

/**
 * Classe que existe como o conjunto vazio, no qual serão adicionados valores e depois fetias outras operações
 * O objeto criado só existe como um "receptaculo"
 * @author danie
 */
public class ConjuntoVazio<T> extends Conjunto<T> {
    
    @Override
    public Boolean contemElemento(T elemento){
        return false;
    }
    
}
