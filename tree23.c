

typedef struct Node{
    int keys[2];
    Node* child[3];
}Node;

int search23(Node* root, int key){
    if(!root) return 0;
    Node* curr = root;
    while(curr){
        if(curr->keys[0] == key) return 1;

        if(curr->childs[0] == NULL){
            if(curr->keys[1] == key) return 1;
            return false;
        }

        if(curr->childs[2] != NULL){
            if(curr->keys[1] == key) return 1;

            if(curr->keys[0] > key)
                curr = curr->childs[0];
            else if(curr->keys[1] > key)
                curr = curr->childs[1];
            else
                curr = curr->childs[2];
            }
        } else{
            if(curr->keys[0] > key)
                curr = curr->childs[0];
            else
                curr = curr->childs[1];
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
                curr = curr->childs[0];
            else if(key < curr->keys[1])
                curr = curr->childs[1];
            else
                curr = curr->childs[2];
        }
        else{
            if(key < curr->keys[0])
                curr = curr->childs[0];
            else
                curr = curr->childs[1];
        }
        
    }
    return 0;
}

void sortInsert(Node* root, int key){
    if(root->keys[0] < key){
        root->keys[1] = key;
        return 1;
    } else{
        int tmp = root->keys[0];
        root->keys[0] = key;
        root->keys[1] = tmp;
        return 0;
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

int insertHelper(Node* cur, int key, int* promoted, Node** newChild){
    if(cur->child[0] == NULL){
        //Convenio si una casilla esta vacia sera -1

        if(cur->keys[1] == -1){
            sortInsert(cur, key);
            return 0;
        }else {
            int mediana, mayor;
            if(key < cur->keys[0]){
                mediana = cur->keys[0];
                mayor = cur->keys[1];
                cur->keys[0] = key;
            }else if(key < cur->keys[1]){
                mediana = key;
                mayor = cur->keys[1];
            }else{
                mediana = cur->keys[1];
                mayor = key;
            }


            Node* new_ = newNode(mayor);
            *promoted = mediana;
            *newChild = new_;
            return 1;
        }
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

    if(split == 1){
        if(cur->keys[1] == -1){
            if(idx == 0){
                cur->keys[1] = cur->keys[0];
                cur->keys[0] = p;
                cur->childs[2] = cur->childs[1];
                cur->childs[1] = p_child;
            }
            else{
                curr->keys[1] = p;
                curr->childs[2] = p_child;
            }
            return 0;
        }
        else{
            return 1;
        }

    }

}














