package com.estsoft.pangpang.drawing;

import java.util.Arrays;

/**제네릭 배열에서 막혀서 일단 String으로 구현한 것.
   * 추후에 노드로 수정?
   * 테이블 크기 resize */


public class BusinessTable<K, V> implements  KeyList<K, V> {
    private Business[] table;
    private static int INITIAL_TABLE = 1 << 11;

    public BusinessTable() {
        this.table = new Business[INITIAL_TABLE];
        for (Business b : table) {
            b = null;
        }
    }

    public void add(K businessName, V productName) {
        int hash = (businessName.hashCode() & 0x7fffffff) % 701;

        if (table[hash] == null) {
           newKey(businessName);
        }

        int index =  table[hash].getLastIndex();
        table[hash].setProduct(productName, index);
        table[hash].incLastIndex();
        table[hash].incNumofProducts();
    }

    public void put(K businessName, V productName, int index) {
        int hash = (businessName.hashCode() & 0x7fffffff) % 701;

        if (table[hash] == null) {
            newKey(businessName);
        }

        if (index > table[hash].getSizeofArray()) {
            table[hash].setSizeofArray(index);
        }

        table[hash].setProduct(productName, index);

        if (table[hash].getLastIndex()== index){
            table[hash].incLastIndex();
        }

        table[hash].incNumofProducts();

    }
    public V get(K businessName, int index) {
        int hash = (businessName.hashCode() & 0x7fffffff) % 701;

        if (table[hash] == null) {
            throw new BusinessNotExistException("Business Not Exist");
        }

        if (table[hash].getLastIndex() < index) {
            throw new ProductArraySizeOverException("Index Not Exist");
        }

        if (table[hash].getProduct(index) == null ) {
            throw new ProductNotExist("Product Not Exist");
        }

        return (V) table[hash].getProduct(index);
    }

    public String toString() {
        String listofBusinessNProducts = "";
        for (Business b : table) {
            if (b != null) {
                listofBusinessNProducts =  listofBusinessNProducts+b.toString()+"\n";
            }
        }
        return listofBusinessNProducts;
    }

    public void newKey(K businessName) {
        int hash = (businessName.hashCode() & 0x7fffffff) % 701;

        table[hash] = new Business();
        table[hash].setBusinessName(businessName);
        table[hash].setLastIndex(0);
    }
}
