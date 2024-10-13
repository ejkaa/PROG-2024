#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct branch{
    int num;
    struct branch* left;
    struct branch* right;
};


struct branch *make_branch(int num);
bool add_branch(struct branch **root, int num);
//void print_tree(struct branch *root, int level);
//void printtabs(int numtabs);
bool are_similar( struct branch *tree1, struct branch *tree2);
//bool is_in_array(int tree, int list[], int size);


int main(){

    int n, k;
    scanf("%d %d", &n, &k);
//    printf("%d %d\n", n, k);
//
    struct branch *list[n];
//
    int arr[n*k];
//

    for (int i = 0, t = n*k; i < t; ++i) {
        scanf("%d", &arr[i]);
    }

//    for (int i = 0, t = n*k; i < t; ++i) {
//        printf("%d ", arr[i]);
//    }

//    for (int i = 0; i < n; ++i) {
//        list[i] = make_branch(scanf("%d"));
//        for (int j = 0; j < k-1; ++j) {
//            add_branch(&list[i], scanf("%d"));
//        }
//    }
    int index = 0;
    for (int i = 0; i < n; ++i) {
        list[i] = make_branch(arr[index]);
        index++;

        for (int j = 0; j < k-1; j++) {
            add_branch(&list[i], arr[index]);
            index++;
        }
    }


//    for (int i = 0; i < n; ++i) {
//        print_tree(list[i], 0);
//    }



    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if(are_similar(list[i], list[j])){
                list[j] = NULL;
            }
        }
    }

    int types = 0;
    for (int i = 0; i < n; ++i){
        if (list[i] != NULL){
            types++;
        }
    }

    printf("%d\n", types);
    return 0;
}

struct branch *make_branch(int num){
    struct branch *result = calloc(1, sizeof(struct branch));

    result->left = NULL;
    result->right = NULL;
    result->num = num;

    return result;
}

bool add_branch(struct branch **rootpoint, int num){
    struct branch *root = *rootpoint;

    if(root == NULL){
        *rootpoint = make_branch(num);
        return true;
    }

    if(num < root->num){
        add_branch(&(root->left), num);
    }

    else if (num > root->num){
        add_branch(&(root->right), num);
    }

    else{
        return false;
    }

    return false;
}

//void print_tree(struct branch *root, int level){
//  if(root == NULL){
//        printtabs(level);
//      printf("--<empty>--\n");
//      return;
//  }
//    printtabs(level);
//    printf("num = %d\n", root->num);
//
//    printtabs(level);
//  printf("left\n");
//  print_tree(root->left, level+1);
//
//    printtabs(level);
//  printf("right\n");
//  print_tree(root->right, level+1);
//
//    printtabs(level);
//  printf("done\n");
//}

//void printtabs(int numtabs){
//    for (int i = 0; i < numtabs; ++i) {
//        printf("\t");
//    }
//}

bool are_similar( struct branch *tree1, struct branch *tree2){
    if(tree1 == NULL && tree2 == NULL){
        return true;
    }

    if(tree1 != NULL && tree2 != NULL){
        return (are_similar(tree1->left, tree2->left) && are_similar(tree1->right, tree2->right));
    }

    //    if( (tree1 == NULL && tree2 == NULL) || (tree1 != NULL && tree2 != NULL) ){
//        return true;
//    }
//
//    if( (tree1 == NULL && tree2 != NULL) || (tree1 != NULL && tree2 == NULL) ){
//        return false;
//    }
//
//    printf("left\n");
//    if(!are_similar(tree1->left, tree2->left)){
//        return false;
//    }
//
//    printf("right\n");
//    if(!are_similar(tree1->right, tree2->right)){
//        return false;
//    }
//
    return false;
}

//bool is_in_array(struct branch tree, struct branch list[], int size){
//    for (int i = 0; i < size; ++i){
//        if(tree == list[i])
//            return true;
//    }
//    return false;
//}
