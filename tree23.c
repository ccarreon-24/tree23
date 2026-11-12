#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int keys[2];
    Node* child[3];
}Node;

Node* newNode(int key){
    Node* new = malloc(sizeof(*new));
    new->keys[0] = key;
    new->keys[1] = -1;
    new->child[0] = NULL;
    new->child[1] = NULL;
    new->child[2] = NULL;
    return new;
}

int search23(Node* root, int key){
    if(!root) return 0;
    Node* curr = root;
    while(curr){
        if(curr->keys[0] == key) return 1;

        if(curr->child[0] == NULL){
            if(curr->keys[1] == key) return 1;
            return 0;
        }

        if(curr->child[2] != NULL){
            if(curr->keys[1] == key) return 1;

            if(curr->keys[0] > key)
                curr = curr->child[0];
            else if(curr->keys[1] > key)
                curr = curr->child[1];
            else
                curr = curr->child[2];
            
        } else{
            if(curr->keys[0] > key)
                curr = curr->child[0];
            else
                curr = curr->child[1];
        }
    }
    return 0;
}

int search(Node* root, int key){
    Node* curr = root;
    
    while(curr){
        if(curr->keys[0] == key) return 1;

        if(curr->size == 2){
            if(curr->keys[1] == key) return 1;

            if(key < curr->keys[0])
                curr = curr->child[0];
            else if(key < curr->keys[1])
                curr = curr->child[1];
            else
                curr = curr->child[2];
        }
        else{
            if(key < curr->keys[0])
                curr = curr->child[0];
            else
                curr = curr->child[1];
        }
        
    }
    return 0;
}

void sortInsert(Node* root, int key){
    if(root->keys[0] < key){
        root->keys[1] = key;
    } else{
        int tmp = root->keys[0];
        root->keys[0] = key;
        root->keys[1] = tmp;
    }

}

Node* destino(Node* root, int key){
    Node* curr = root;

    while(curr && curr->child[0] != NULL){
        if(key < curr->keys[0]) curr = curr->child[0];
        else if(curr->child[2]){
            if(curr->keys[1] > key) 
                curr = curr->child[1];
            else
                curr = curr->child[2];
        }
        else{
            curr = curr->child[1];
        }
    }
    return curr;
}

int splitNode(Node* cur, int p, Node* p_child,int idx, int* promoted, Node** newChild){
    int k0 = cur->keys[0];
    int k1 = cur->keys[1];
    Node* c0 = cur->child[0], *c1 = cur->child[1], *c2 = cur->child[2];

    int menor, mediana, mayor;
    Node* n0, *n1, *n2, *n3;

    if(idx == 0){
        menor = p, mediana = k0, mayor = k1;
        n0 = c0, n1 = p_child, n2 = c1, n3 = c2;
    }else if(idx == 1){
        menor = k0, mediana = p, mayor = k1;
        n0 = c0, n1 = c1, n2 = p_child, n3 = c2;
    }else{
        menor = k0, mediana = k1, mayor = p;
        n0 = c0, n1 = c1, n2 = c2, n3 = p_child;
    }
    
    cur->keys[0] = menor;
    cur->keys[1] = -1;
    cur->child[0] = n0;
    cur->child[1] = n1;
    cur->child[2] = NULL;

    Node* rigth = newNode(mayor);
    rigth->child[0] = n2;
    rigth->child[1] = n3;
    rigth->child[2] = NULL;

    *promoted = mediana;
    *newChild = rigth;
    return 1;
}


int insertHelper(Node* cur, int key, int* promoted, Node** newChild){
    if(cur->child[0] == NULL){
        //Convenio si una casilla esta vacia sera -1

        if(cur->keys[1] == -1){
            sortInsert(cur, key);
            return 0;
        }
        int idx = 0;
        if(key > cur->keys[0]){
            idx = (key > cur->keys[1]) ? 2 : 1;
        }
        return splitNode(cur, key, NULL, idx, promoted, newChild);
    }




    int idx = 0;
    if(key > cur->keys[0]){
        if(cur->child[2] != NULL && key > cur->keys[1])
            idx = 2;
        else
            idx = 1;
    }

    int p;
    Node* p_child = NULL;
    int split = insertHelper(cur->child[idx], key, &p, &p_child);

    if(split == 0) return 0;

    if(cur->keys[1] == -1){
        if(idx == 0){
            cur->keys[1] = cur->keys[0];
            cur->keys[0] = p;
            cur->child[2] = cur->child[1];
            cur->child[1] = p_child;
        }else{
            cur->keys[1] = p;
            cur->child[2] = p_child;
        }
        return 0;
    }

    return splitNode(cur, p, p_child, idx, promoted, newChild);
}

Node* insert(Node* root, int key){
    if(!root) return newNode(key);

    int p;
    Node* p_child;
    if(insertHelper(root, key, &p, &p_child) == 1){
        Node* new = newNode(p);
        new->child[0] = root;
        new->child[1] = p_child;
        return new;
    }
    return root;
}













