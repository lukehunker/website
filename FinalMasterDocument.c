//STUFF//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct node node;
typedef struct tree tree;
typedef int Key;
typedef struct listNode listNode;
typedef struct StkNode StkNode;
typedef struct item item;
typedef struct Node Node;



//------LINKED LISTS------//
struct listNode {
    int value;
    listNode *next;
};

listNode *head = NULL;
listNode *current = NULL;

void insertFirst(int data) {
    listNode *link = (listNode*)malloc(sizeof(listNode));
    link->value = data;
    link->next = head;
    head = link;
}

listNode *createListNode(int data) {
    listNode *link = (listNode*)malloc(sizeof(listNode));
    link->value = data;
    link->next = NULL;
}

listNode *insertEnd(listNode* head, int newData) {
    if(!head) {
        head = createListNode(newData);
        return head; 
    }
    listNode *cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }
    listNode *newnode = createListNode(newData);
    cur->next = newnode;
    return head;
}

void printList() {
    listNode *ptr = head;
    printf("\n[");
    while(ptr != NULL) {
        printf("%d", ptr->value);
        ptr = ptr->next;
    }
    printf("]");
}

void extract(int aValue) {
    listNode *curr = head;
    listNode *prev = NULL;

    while(curr != NULL && curr->value != aValue) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL)
        printf("no item is found\n");
    if(curr == head)
        head = curr->next;
    else
        prev->next = curr->next;
}

listNode *copylist(listNode * head) {
    listNode *current = head;
    listNode *newList = NULL;
    listNode *tail = NULL;

    while(current != NULL) {
        if(newList == NULL) {
            newList = (listNode*)malloc(sizeof(listNode));
            newList->value = current->value;
            newList->next = NULL;
            tail = newList;
        }
        else {
            tail->next = (listNode*)malloc(sizeof(listNode));
            tail = tail->next;
            tail->value = current->value;
            tail->next = NULL;
        }
        current = current->next;
    }
    return newList;
}

// ----------Stacks---------//

//LINKED LIST IMPLEMENTATION//
struct StkNode {
    StkNode *next;
    int nodval;
};

StkNode *head1 = NULL;

void push(StkNode *stkhead, int n) {
    StkNode *p = malloc(sizeof(StkNode));
    p->nodval = n;
    p->next = stkhead;
    stkhead = p;
}

int pop(StkNode *stkhead) {
    StkNode *p = stkhead;
    int rslt = p->nodval;
    stkhead = p->next;
    return rslt;
}

int *tos(StkNode *stkhead) {
    return &(stkhead->nodval);
}

//ARRAY IMPLEMENTATION//
int top1 = -1;
char stack[100];

char push (char c)
{
	if (top1 == 100-1)  return 0;
	stack[++top1] = c;
	return  1;
}

int  pop (char *character)
{
	if (top1 == -1)  return 0;
	*character = stack[top1--];
	return  1;
}

char tos (int **ptop)
{
	if (top1 == -1) return 0;
	*ptop = &stack[top1];
	return  1;
}

//------QUEUES------//

struct item {
    item *next;
    int value;
};
item *front, *end;
int count = 0;

bool isEmpty() {
    if(front == -1) return true;
    return false;
}

//LINKED LIST IMPLEMENTATION//
void enqueue(int n) {
    item *pnew = malloc(sizeof(item));
    pnew->value = n;
    pnew->next = NULL;

    if(end != NULL)
        end->next = pnew;
    end = pnew;

    if(front == NULL)
        front = pnew;
    count++;
}

bool dequeue(int *n) {
    item *temp = front;
    if(count == 0) return false;
    *n = front->value;
    front = front->next;
    free(temp);
    count--;
    return true;
}

//ARRAY IMPLEMENTATION//

int q[100];
int count1 = 0, front1 = -1, end1 = -1;


bool enqueue(int n) {
    if(count == 100) return false;

    end1 = (end1+1) % 100;
    q[end1] = n;
    return true;
}

bool dequeue(int *n) {
    if(count == 0) return false;

    *n = q[front1];
    front1 = (front1 +1) % 100;
    count--;

    if(count == 100) front = end = -1;
    return true;
}

//------RECURSION------//

int factorial (int n) {
    int temp;

    if(n==0) 
        temp = 1; 
    else
        temp = n*factorial(n-1);
    return temp;
}

int fibonacci(int n) {
    int temp;
    if(n == 0) return 0;
    if(n == 1) return 1;
    temp = fibonacci(n-1) + fibonacci(n-2);
    return temp;
}
//------TREES------//
struct node {
    Key key;
    struct node* left;
    struct node* right;
    int height;
    void* value;
};

struct tree {
    node* root;
};

node* newNode(Key k) {

    node* n = (node*)malloc(sizeof(node));

    if(n != NULL) {
        n->key = k;
        n->left = NULL;
        n->right = NULL;
        n->height = 0;
    }
    return n;
}

node* insert(node *root, Key k) {

    //if tree is empty and root == NULL
    //create new node and set it to root
    if(root == NULL) {
        root = newNode(k);
        return root;
    }
    //if the key you are inserting is the value of the current root
    // return the root and don't insert to avoid duplicates
    if(root->key == k) return root;

    //if the key is greater than the root key
    //recursively call insert for right sub tree
    if(k > root->key) {
        //if there exists a right subtree, recursively call insert
        if(root->right != NULL) {
            root = insert(root->right, k);
        }else {
        // if right subtree doesn't exist, make a new right node
            node *n = newNode(k);
            root->right = n;
            return n;
        }
    // If the key is less than the root key 
    } else if (k < root->key) {
        //if there exists a left subtree, recursively call insert
        if(root->left != NULL) {
            root = insert(root->left, k);
        }else {
        //if left subtree doesn't exist, make a new left node
            node *n= newNode(k);
            root->left = n;
            return n;
        }
    }
    //return root when insert is successful
    return root;
}

int intmax(int a, int b) {(a>=b) ? a:b; }

int height(node *root) {

    int nodeheight = -1;
    //if the root and tree exists
    if(root != NULL) {
        //compare the two heights of left and right subtree to find largest one
        //set nodehight to max height plus 1
        nodeheight = 1 + intmax(height(root->left), height(root->right));
    }
    return nodeheight;
}

void printPreOrder(node* root) {
    if(root == NULL) return;

    print("%d", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(node *root) {
    if(root == NULL) return;

    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d", root->key);
}

void printInOrder(node *root) {
    if(root==NULL) return;

    printInOrder(root->left);
    printf("%d", root->key);
    printInOrder(root->right);
}

node* find(node *root, Key k) {

    if(root == NULL) return NULL;

    //is the item you want to find is greater than root
    //recursively call find in right subtree
    if(k > root->key)
        find(root->right, k);
    //else do the same with left subtree
    else if(k < root->key)
        find(root->left, k);
    //Element found!
    else
        return root;
}

node* FindMin(node* node) {
    //There is no element in the tree
    if(node == NULL) return NULL;
    //go to left subtree and find the min element
    else if(node->left != NULL) return FindMin(node->left);
    //when element is found (no more left nodes) return node
    else return node;
}

node* FindMax(node *node) {
    //There is no element in the tree
    if(node == NULL) return NULL;
    //go to right subtree and find the min element
    else if(node->right != NULL) return FindMax(node->right);
    //when element is found (no more right nodes) return node
    else return node;
}

node* temp;

node *delete (node* node, Key k) {

    //if the tree is empty of the node doesn't exist
    if(node == NULL)
        return NULL;
    //if key we are looking to delete is less than node, call delete in left subtree
    else if(k < node->key)
        node->left = delete(node->left, k);
    //if key we are looking to delete is greater than node, call delete in right subtree
    else if(k > node->key)
        node->right = delete(node->right, k);
    //base case actual delete function
    else {
        // is there exists two children
        if(node->right && node->left) {
            temp = FindMin(node->right);
            node->key = temp->key;
            node->right = delete(node->right, temp->key);
        // only right child exists
        } else if(node->left == NULL) {
            node = node->right;
        //only left child exists
        }else if(node->right== NULL) {
            node = node->left;
        }
        free(temp);
    }
    return node;
}

//------AVL TREES------//

int getBalanceFactor(node* root)
// Get balance factor - difference between left height and right height
{
	int	hr = -1, hl = -1;	

    if(root == NULL) return 0;
    else {
        hl = height(root->left);
        hr = height(root->right);
    }
	return hl - hr;
}

node* rotateLeft(node* root)
// Rotate to left.  Returns new root pointer.
{
	printf("Rotate Left\n");
	
	node* RChild = root->right;
	node* RChildLChild = RChild->left;

	RChild->left = root;
	root->right = RChildLChild;

	root->height = height(root);
	RChild->height = height(RChild);

	root = RChild;

    return root;
}//rotateLeft()

node* rotateRight(node* root)
// Rotate to right.  Returns new root pointer.
{
    printf("Rotate Right\n");

    node* LChild = root->left;
    node* LChildRChild = LChild->right;

    LChild->right = root;
    root->left = LChildRChild;

    root->height = height(root);
    LChild->height = height(LChild);

    root = LChild;
	
	return root;
}//rotateRight()

node* rebalance(node* root)
// Check balance factor to see if balancing required (bf > 1 or bf < -1).
// If balancing required, perform necessary rotations.
{
	int bf = getBalanceFactor(root);

    if (bf > 1)
    {
        // case 1, RR rotation
        if (getBalanceFactor(root->left) > 0)
            root = rotateRight(root);
        // case 2 LR rotation
        else if (getBalanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    }
    else if (bf < -1)
    {
        // case 3 LL rotation
        if (getBalanceFactor(root->right) > 0)
            root = rotateLeft(root);
        // case 4 RL rotation
        else if (getBalanceFactor(root->right) < 0)
        {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;
}//rebalance()


//------HEAPS AND PRIORITY QUEUES------//

/*
Notes:

Node = arr[i]
Left Child = arr[2*i+1];
Right Child = arr[2*i+2];
Parent = arr[(i-1)/2];

Insert in max-heap:
 - Attach item as farthest left leaf
 - Compare with parent, if item is greater, perform swap

Deletion from heap:
 - Can only delete form the root of the heap
 - swap root with last element
 - filter the (new) root down into its correct position


*/
//min heap
void pushHeap(int arr[], int last, int item) {
    int currPos, parentPos;

    currPos = last;
    parentPos = (currPos-1)/2;

    //traverse path of parents up to the root
    while(currPos != 0) {
        // if the item you want to insert is less than the parent
        if(item < arr[parentPos]) {
            //move data from parent position to current position
            arr[currPos] = arr[parentPos];
            //update current position to parent position
            currPos = parentPos;
            //compute next parent
            parentPos = (currPos-1)/2;

        }else {
            break;
        }
    }
    //correct location discovered, assign target
    arr[currPos] = item;
}

void adjustHeap(int arr[], int first, int last) {
    int currentPos, childPos;
    int target;

    //start at first and filter target down the heap
    currentPos = first;
    target = arr[first];

    //compute the left child index and scan down path of children
    childPos = 2 * currentPos +1;

    while(childPos < last) {
        //index of right child is childPos+1, compare two children
        if((childPos+1 < last) && arr[childPos+1] > arr[childPos])
            //change childPos if arr[childPos+1] > arr[childPos]
            childPos = childPos + 1;
        //compare selected child to target
        if(arr[childPos] > target) {
            //move selected child to the parent
            arr[currentPos] = arr[childPos];
            //update indices to continue the scan
            currentPos = childPos;
            childPos = 2 * currentPos + 1;
        } else {
            break;
        }
    }
    arr[currentPos] = target;
}

int popHeap(int arr[], int last) {
    
    //swaps arr[0] and arr[last-1]
    int temp = arr[0];
    arr[0] = arr[last-1];
    arr[last-1] = temp;

    //filter down the root over the range [0, last-1)
    adjustHeap(arr, 0, last-1);
    //returns the top value at arr[0]
    return temp;
}

void makeHeap(int arr[], int size) {
    int heapPos, lastPos;

    lastPos = size;
    heapPos = (lastPos-2)/2;

    while(heapPos >= 0) {
        adjustHeap(arr, heapPos, lastPos);
        heapPos--;
    }
}

//------SORTING------//

void selectionSort(int arr[]) {

    //index of minimum value in sublist
    int smallIndex;
    int pass, j, n = sizeof(arr)/sizeof(arr[0]);
    int temp;

    //pass has the range 0 to n-2
    //counts the literations of selection sort process
    for(pass = 0; pass < n-1; pass++) {

        //scan the sublist starting at index pass
        //assume the minimum value is initially arr[pass]
        smallIndex = pass;

        //j traverses the sublist arr[pass+1] to arr[n-1]
        //iterates through the array until next smallest value is found
        for(j = pass+1; j<n; j++) 
        //if smaller element found, assign smallIndex to that index
            if(arr[j]< arr[smallIndex])
                smallIndex = j; 
        //assigns the smallestIndex the index of the smallest value in the unsorted portion of the array
        //swaps the d=smaller element with the first unsorted element in the array @arr[pass]
        swap(arr[pass], arr[smallIndex]);

        
    }
}

void bubbleSort(int arr[]) {
    int i,j, n = sizeof(arr)/sizeof(arr[0]);

    //starts at the last element and iterates down to the first.
    //keeps track of the number of times the bubblesort has passed through
    //removes the last element from the unsorted array
    for(i = n-1; i > 0; i--)
    //j starts from the front and moves through the array swapping if current element is larger than next element
        for(j = 0; j < i; j++)
            if(arr[j]>arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void heapSort(int arr[]) {

    int n = sizeof(arr)/sizeof(arr[0]);

    makeHeap(arr, n);

    for(int i = n; i > 1; i--) {
        popHeap(arr, i);
    }
}

void insertionSort(int arr[]) {
    int i, j, n = sizeof(arr)/sizeof(arr[0]);
    int target;

    for(i = 1; i<n; ++i) {
        //index j scans down list from index i looking for correct position to locate target
        //assigns it to arr at index j
        j = i;
        target = arr[i];

        //locate insertion point by scanning downward as long as target < arr[j]
        while(j >0 && target < arr[j-1]) {
            //shift elements up list to make room for insertion
            //keeps shifting until there is a plce for the target at index j
            arr[j] = arr[j-1];
            j--;
        }
        //the location is found; insert target
        arr[j] = target;
    }
}

void swap(int *b, int *y) {
    int temp = *b;
    *b = *y;
    *y = temp;

}


void binarySort(int arr[]) {
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 1; i<n; i++) {
        int tmp = arr[i];
        int left = 0;
        int right = i;
        while( left < right) {
            int mid = (left+right)/2;
            if(tmp >= arr[mid])
                left = mid+1;
            else
                right = mid;
        }
        for(int j = i; j > left; --j)
            swap(&arr[j-1], &arr[j]);
    }
}

void shellSort(int arr[], int n) {
    //rearrange elements at each n/2. n/4, n/8, ... intervals
    for(int interval = n/2; interval > 0; interval /= 2) {
        for(int i = interval; i<n; i+=1) {
            int temp = arr[i];
            int j;
            for(j = i; j>= interval && arr[j-interval] > temp; j-=interval) {
                arr[j] = arr[j-interval];
            }
            arr[j] = temp;
        }
    }
}

void quickSort(int arr[], int first, int last) {
    int i, j, pivot, temp;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while(i<j) {
            while(arr[i]<=arr[pivot] && i <last)
            i++;
            while(arr[j]> arr[pivot])
            j--;
            if(i<j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quickSort(arr, first, j-1);
        quickSort(arr, j+1, last);
    }
}

//MERGE SORT//
void sort(int arr[]) {
    int size = sizeof(arr)/sizeof(arr[0]);
    int *tempArr = (int*)malloc(size * sizeof(arr[0]));

    for(int i = 0; i <size; i++)
        tempArr[i] = arr[i];

    msort(arr,tempArr,0,size);
}

void msort(int arr[], int tempArr[], int first, int last) {

    if(first+1 < last) {
        int midpt = (last+first)/2;
        //sort from first element f=to midpoint
        msort(arr,tempArr,first,midpt);
        //sort the values from midpoint to last element
        msort(arr,tempArr, midpt, last);
        if(arr[midpt-1] <= arr[midpt])
            return;
        merge(arr, tempArr, first, midpt, last);
    }
}

void merge (int arr[], int tempArr[], int first, int midpt, int last) {
    int indexA, indexB, indexC;
    indexA = first;
    indexB = midpt;
    indexC = last;
    //starts at first index and loops until midpt
    //starts at midpt and loops until last element.
    while(indexA < midpt && indexB < last) {
        //compare element in the first half with of list with those in the left
        //if one value is smaller than the other, assign that small value to the next index in the temporary array
        if(arr[indexA] < arr[indexB]) {
            tempArr[indexC] = arr[indexA];
            //once value is coped to temparr, indexA increases
            indexA++;
        }
        else {
            tempArr[indexC] = arr[indexB];
            indexB++;
        }
        //either way the index in temparr increases b/c it is guarunteed to acquire a value from
        //arr[indexA] or arr[indexB] depending on which is smaller
        indexC++;
    }
    //if there are remaining elements in first half of arr, copy them to tempArr
    //this occurs when one half is larger than the other so some elements are left out of while loop
    while(indexA < midpt) {
        tempArr[indexC] = arr[indexA];
        indexA++;
        indexC++;
    }
    //same thing here except is there are remaining value in second half
    while(indexB < last) {
        tempArr[indexC] = arr[indexB];
        indexB++;
        indexC++;
    }

    //copies elements from temparr to original arr after merging
    for(int i = first; i <last; i++) {
        arr[i] = tempArr[i];
    }
}


//BUCKET SORT//
struct Node {
    int data;
    Node * next;
};
int NBUCKETS = 10;
int NARRAY = 100;

int getBucketIndex(int value) {
    return value/ INTERVAL;
}

void BucketSort(int arr[]) {
    int i,j;
    Node **buckets;
    //creates buckets and allocates memory size
    buckets = (Node**)malloc(sizeof(Node*)* NBUCKETS);
    //initialize empty buckets
    for(i = 0; i < NARRAY; ++i) {
        buckets[i] = NULL;
    }
    //fill buckets with respective elements
    for(i= 0; i<NARRAY; ++i) {
        Node* current;
        int pos = getBucketIndex(arr[i]);
        current = (Node*)malloc(sizeof(Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }
    //sort the elements of each bucket using insertionsort
    for(i = 0; i <NBUCKETS; ++i) {
        buckets[i] = insertionSort(buckets[i]);
    }
    //put sorted elelments on arr
    for(j = 0, i = 0; i < NBUCKETS; ++i) {
        Node* node;
        node = buckets[i];
        while(node) {
            arr[j++] = node->data;
            node = node->next;
        }
    }
    return;
}


//RADIX SORT//
//First sorts the values based off ones place by putting them in different bins from 0-9
//Next sorts the items based off 10's place using same bins 0-9
//finally sorts based off 100s place again using bins 0-9
void countingSort(int arr[], int size, int place) {
    int output[size + 1];
    int max = (arr[0] / place) % 10;
    for (int i = 1; i < size; i++) {
        if (((arr[i] / place) % 10) > max)
            max = arr[i]; 
    }
    int count[max + 1];
    for (int i = 0; i < max; ++i)
        count[i] = 0;
    // Calculate count of elements
    for (int i = 0; i < size; i++)
        count[(arr[i] / place) % 10]++;
    // Calculate cumulative count
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--; 
    }
    //copy elements form output to original array
    for (int i = 0; i < size; i++)
    arr[i] = output[i];
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++) 
        if(arr[i]> max)
            max = arr[i];
    return max;
}
void radixsort(int arr[], int size) {
    //get maximum element
    int max = getMax(arr, size);
    //apply counting sort to sort elements based on place value
    for(int place = 1; max/place > 0; place *=10)
        countingSort(arr,size, place);
}

//-----GRAPHS-----//

#define MAX 100
#define initial 1
#define waiting 2
#define visited 3

int n;
int adj[MAX][MAX];
int state[MAX];
int queue[MAX], front = -1, rear = -1;

void create_graph() {
    int count, max_edge, origin, destin;
    printf("Enter number of vertices");
    scanf("%d", &n);
    max_edge = n*(n-1);

    for(count =1; count <= max_edge; count++) {
        printf("Enter edge %d(-1 -1 to quit): ", count);
        scanf("%d %d", &origin, &destin);

        if((origin == -1) && (destin ==-1)) break;

        if(origin >= n || destin >= n || origin < 0|| destin <0) {
            printf("invalid edge");
            count--;
        }else {
            adj[origin][destin] = 1;
        }
    }
}

void BF_Traversal() {
    int v;
    
    for(v = 0; v <n; v++)
        state[v] = initial;

    printf("Enter Start vertex for BFS:");
    scanf("%d", &v);
    BFS(v);
}

void BFS(int v) {
    enqueue(v);
    state[v] = waiting;
    while(!isEmpty()) {
        v = dequeue();
        printf("%d", v);
        state[v] = visited;
        for(int i = 0; i < n; i++) {
            if(adj[v][i] == 1 && state[i] == initial) {
                enqueue(i);
                state[i] = waiting;
            }
        }
    }
    printf("\n");
}

int G[10][10], visitd[10], n;

void DFS(int i) {
    int j;
    printf("\n%d", i);
    visitd[i] = 1;

    for(j=0; j<n; j++) 
        if(!visitd[j] && G[i][j] == 1)
            DFS(j);

}

#define INFINITY 99999 

void Djikstra(int Graph[MAX][MAX], int n, int start) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visit[MAX], count, mindistance, nextnode, i, j;

    for(i=0; i < n; i++)
        for(j=0; j<n; j++) 
        if(Graph[i][j]== 0)
            cost[i][j] = INFINITY;
        else
            cost[i][j] = Graph[i][j];
    for(i = 0; i < n; i++) {
        distance[i] = cost[start][i];
        pred[i] = start;
        visit[i] = 0;
    }
    distance[start] = 0;
    visit[start] = 0;
    count = 1;

    while(count < n-1) {
        mindistance = INIFINITY;
        for(i = 0; i < n; i++) 
            if(distance[i] < mindistance && !visit[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        visit[nextnode] = 1;
        for(i = 0; i < n; i++)
            if(!visit[i])
                if(mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
}

//???
int V = 10;
# define INT_MAX 40
//????

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool mstSet[V];

    for(int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    
    key[0] = 0;
    parent[0] = -1;
    for(int count = 0; count < V-1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for(int v=0; v < V; v++)
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;

    for(int v = 0; v < V; v++)
        if(mstSet[v]==false && key[v] < min)
            min = key[v], min_index = v;
    
    return min_index;
}

//-----Hash Tables-----//

//SEPERATE CHAINING//
// typedef struct Hashnode  {
//     int key;
//     int data;
//     struct Hashnode *next;
// }Hashnode;

// typedef struct hash {
//     Hashnode *head;
//     int count;
// }hash;

// int M = 21;
// hash hashTable[21];

// Hashnode *createNode(int key, int data) {
//     Hashnode *newnode;
//     newnode = (Hashnode*)malloc(sizeof(Hashnode));

//     newnode->key = key;
//     newnode->data = data;
//     newnode->next = NULL;

//     return newnode;
// }


// void insertionToHash(int key, int data) {
//     int hashIndex = key % M;
//     Hashnode *newnode = createNode(key, data);

//     //head of list for the bucket with index "hashIndex"
//     if(!hashTable[hashIndex].head) {
//         hashTable[hashIndex].head = newnode;
//         hashTable[hashIndex].count = 1;
//         return;
//     }

//     //adding new node to the list
//     newnode->next = (hashTable[hashIndex].head);

//     //updaye the head of the list and no of nodes int the current bucket
//     hashTable[hashIndex].head = newnode;
//     hashTable[hashIndex].count++;

// } 

