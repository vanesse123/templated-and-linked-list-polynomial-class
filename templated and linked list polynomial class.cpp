#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#define Node dummy_head_circular_Node  //singly_Node,double_Node,circular_Node,dummy_head_circular_Node

struct singly_Node {
	int coef;
	int pow;
	struct singly_Node* next;
};

struct double_Node {
	int coef;
	int pow;
	struct double_Node* next;
	struct double_Node* prev;
};

class circular_Node{
public:
	int coef;
	int pow;
	circular_Node* next;
};

class dummy_head_circular_Node{
	public:
		int coef;
		int pow;
		dummy_head_circular_Node* next;
		
};

//將重複項刪除 
template<class T>
void removeDuplicates(T* start)
{
    T *ptr1, *ptr2, *dup;
    ptr1 = start;
    while (ptr1 != NULL && ptr1->next != NULL &&ptr1->next != start) {
        ptr2 = ptr1;
        while (ptr2->next != NULL && ptr2->next != ptr1) {
            if (ptr1->pow == ptr2->next->pow) {
                ptr1->coef = ptr1->coef + ptr2->next->coef;
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}
//singly_Node增加節點 
singly_Node* addnode(singly_Node* start, int coeff, int power)
{
    singly_Node* newnode = new singly_Node;
    newnode->coef = coeff;
    newnode->pow = power;
    newnode->next = NULL;
    if (start == NULL)
        return newnode;
    singly_Node* ptr = start;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = newnode;
 
    return start;
}
//double_Node增加節點 
double_Node* addnode(double_Node* start,int coeff,int pow){
	double_Node* newnode = new double_Node;
	newnode->coef = coeff;
	newnode->pow = pow;
	newnode->next = NULL;
	newnode->prev = NULL;
	if(start == NULL)
		return newnode;
	else{
	double_Node* ptr = start;
	while(ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = newnode;
	ptr->prev = ptr;
	}
	return start;
} 
//circular_Node增加節點
circular_Node* addnode(circular_Node* start,int coeff,int power){
	circular_Node* newnode = new circular_Node;
	newnode->coef = coeff;
	newnode->pow = power;
	newnode->next = start;
	if(start == NULL){
		return newnode;
	}
	else{
		circular_Node* ptr = start;
		while(ptr->next != start)
			ptr = ptr->next;
		ptr->next = newnode;
	}
	return start;
}
//dummy_head_circular_Node增加節點
dummy_head_circular_Node* addnode(dummy_head_circular_Node* start,int coeff,int power){
	dummy_head_circular_Node* head = new dummy_head_circular_Node;
	head->coef = coeff;
	head->pow = power;
	head->next = start;
	if(start == NULL){
		head->next = head;
		return head;
	}
	else{
		dummy_head_circular_Node* ptr = start;
		while(ptr->next != start)
			ptr = ptr->next;
		ptr->next = head;
	}
	return start;
}

template<class T>
class Polynomial {
public:
	Polynomial(){};
	~Polynomial(){};
	static T* polyadd(T* poly1,T* poly2,T* poly); //多項式加法 
	static T* polyreduce(T* poly1,T* poly2,T* poly); //多項式減法 
	static T* polymult(T* poly1,T* poly2,T* poly); //多項式乘法 
	static void printList(T* poly); //顯示多項式 
};

//多項式加法 
template<class T>
T* Polynomial<T>::polyadd(T* poly1,T* poly2,T* poly) {
	T *ptr1,*ptr2;
	ptr1 = poly1;
	ptr2 = poly2;
	int coeff,power;
	while (ptr1 !=NULL && ptr2 !=NULL) {
		if (ptr1->pow == ptr2->pow) {
			coeff = ptr1->coef + ptr2->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;			
		}
		else if (ptr1->pow < ptr2->pow) {
			coeff = ptr2->coef;
			power = ptr2->pow;
			poly = addnode(poly,coeff,power);
			ptr2 = ptr2->next;
		}
		else {
			coeff = ptr1->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
		}
		if(ptr1 == poly1 || ptr2 == poly2)
			break;
	}
	while (ptr1 != NULL || ptr2 != NULL) {
		if (ptr1!=NULL && ptr1!=poly1) {
			coeff = ptr1->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
		}
		if (ptr2!=NULL && ptr2!=poly2) {
			coeff = ptr2->coef;
			power = ptr2->pow;
			poly = addnode(poly,coeff,power);
			ptr2 = ptr2->next;
		}
		if(ptr1 == poly1 && ptr2 == poly2)
			break;
	}
	return poly;
}

//多項式減法 
template<class T>
T* Polynomial<T>::polyreduce(T* poly1,T* poly2,T* poly) {
	T *ptr1,*ptr2;
	ptr1 = poly1;
	ptr2 = poly2;
	int coeff,power;
	while (ptr1 !=NULL && ptr2 !=NULL) {
		if (ptr1->pow == ptr2->pow) {
			coeff = ptr1->coef - ptr2->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		else if (ptr1->pow < ptr2->pow) {
			coeff = -ptr2->coef;
			power = ptr2->pow;
			poly = addnode(poly,coeff,power);
			ptr2 = ptr2->next;
		}
		else {
			coeff = ptr1->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
		}
		if(ptr1 == poly1 || ptr2 == poly2)
			break;
	}
	while (ptr1 != NULL || ptr2 != NULL) {
		if (ptr1!=NULL && ptr1!=poly1) {
			coeff = ptr1->coef;
			power = ptr1->pow;
			poly = addnode(poly,coeff,power);
			ptr1 = ptr1->next;
		}
		if (ptr2!=NULL && ptr2!=poly2) {
			coeff = -ptr2->coef;
			power = ptr2->pow;
			poly = addnode(poly,coeff,power);
			ptr2 = ptr2->next;
		}
		if(ptr1 == poly1 && ptr2 == poly2)
			break;
	}
	return poly;
}

//多項式乘法 
template<class T>
T* Polynomial<T>::polymult(T* poly1, T* poly2,T* poly3)
{
    T *ptr1, *ptr2;
    ptr1 = poly1;
    ptr2 = poly2;
    while (ptr1 != NULL) {
        while (ptr2 != NULL) {
            int coeff, power;
            coeff = ptr1->coef * ptr2->coef;
            power = ptr1->pow + ptr2->pow;
            poly3 = addnode(poly3, coeff, power);
            ptr2 = ptr2->next;
            if(ptr2 == poly2)
            	break;
        }
        ptr2 = poly2;
        ptr1 = ptr1->next;
        if(ptr1 == poly1)
        	break;
    }
    removeDuplicates(poly3);
    return poly3;
}

//印出多項式 
template<class T>
void Polynomial<T>::printList(T* poly)
{
    T *ptr = poly;
    T *temp = poly;
	while (ptr->next != NULL) {
    	if(ptr->coef!=0){
        	cout << ptr->coef << "x^" << ptr->pow ;
    		if( ptr->next!=NULL && ptr->next->coef >=0)
        		cout << "+";
 		}
        ptr = ptr->next;
        if(ptr->next == poly)
        	break;
    }
    cout << ptr->coef << "\n";
}

int main(void) {
	Node *poly1 = NULL, *poly2 = NULL, *poly = NULL;
	poly1 = addnode(poly1, 0, 5);
	poly1 = addnode(poly1, 4, 3);
	poly1 = addnode(poly1, 4, 0);
	cout << "first polynomial:"; 
	Polynomial<Node>::printList(poly1);
	poly2 = addnode(poly2, 6, 5);
	poly2 = addnode(poly2, 3, 0);
	cout << "second polynomial:";
	Polynomial<Node>::printList(poly2);
	poly = Polynomial<Node>::polyadd(poly1,poly2,poly);
	cout << "相加得到:";
	Polynomial<Node>::printList(poly);
	poly = NULL;
	poly = Polynomial<Node>::polyreduce(poly1,poly2,poly);
	cout << "相減得到:";
	Polynomial<Node>::printList(poly);
	poly = NULL;
	poly = Polynomial<Node>::polymult(poly1,poly2,poly);
	cout << "相乘得到:";
	Polynomial<Node>::printList(poly);
	poly = NULL;
	return 0;
}


