
package maintp3;

public abstract class Conjunto<T> {
    public abstract Boolean contemElemento(T elemento);
    
    Conjunto<T> adicionarElemento(T elemento){
        return new ConjuntoElemento<>(elemento, this);
    }
    
    Conjunto<T> uniao(Conjunto<T> conjunto){
        return new Uniao<>(this, conjunto);
    }
    
    Conjunto<T> intersecao(Conjunto<T> conjunto){
        return new Intersecao<>(this, conjunto);
    }
    
    Conjunto<T> diferenca(Conjunto<T> conjunto){
        return new Diferenca<>(this, conjunto);
    }
    
    Conjunto<T> complemento(){
        return new Complemento<>(this);
    }
    
}
