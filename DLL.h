#ifndef DLL_H
#define DLL_H

#include<iostream>
#include "RETROPLAYER.h"
using namespace std;

struct dnode
{
	RetroPlayer d;
	dnode* next, * prev;

	dnode(RetroPlayer n):d(n), next(NULL), prev(NULL) {}
};

class DLL
{
	dnode* head, * tail;
	dnode* current = head;

public:
	DLL():head(NULL),tail(NULL), current(NULL) {}
	bool isEmpty() { return head == NULL; }
	// current = head;
	void IAS(RetroPlayer d)
	{
		dnode* n = new dnode(d);
		if (isEmpty())
		{
			head = tail = n;
		}
		else
		{
			head->prev = n;
			n->next = head;
			head = n;
		}
	}
	void IAE(RetroPlayer d)

	{
		if (isEmpty())
		{
			IAS(d);
		}
		else
		{
			dnode* n = new dnode(d);
			tail->next = n;
			n->prev = tail;
			tail = n;
		}
	}
	int getLength()
	{
		dnode* temp = tail;
		int count = 0;
		while (temp != NULL)
		{
			count++;
			temp = temp->prev;
		}
		return count;
	}
	void IAAP(RetroPlayer d, int pos)
	{
		if (pos == 1)
		{
			IAS(d);
		}
		else if (pos > getLength())
		{
			if (pos == getLength() + 1)
				IAE(d);
			else
				return;
		}

		else
		{
			dnode* temp = head;
			int count = 1;
			while (count < pos - 1)
			{
				temp = temp->next;
				count++;
			}

			dnode* n = new dnode(d);
			n->next = temp->next;
			temp->next = n;
			n->prev = temp;
			n->next->prev = n;
		}
	}
	void DAE()
	{
		if (!isEmpty())
		{
			if (head == tail)
				DAS();
			else
			{
				dnode* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
		}
	}
	void DAS()
	{
		if (!isEmpty())
		{
			if (head == tail)
			{
				delete head;
				head = tail = NULL;
			}

			else

			{
				dnode* temp = head;
				head = head->next;
				delete temp;
				head->prev = NULL;
			}
		}
	}
    void DAAP(int pos)
	{
		if (pos == 1)
		{
			DAS();
		}
		else if (pos > getLength())
		{
			if (pos == getLength() + 1)
				DAE();
			else
				return;
		}
		else
		{
			dnode* temp = head;
			int count = 1;
			while (count < pos - 1)
			{
				temp = temp->next;
				count++;
			}
            dnode* n = temp->next;
            temp->next = temp->next->next;
            temp->prev = n->prev;
            delete n;
            n = NULL;
			cout << "Track deleted successfully! " << endl;
            return;
		}
	}

	int getPosition(int id){
		dnode* temp = head;
		int count = 1;
		while (count < getLength())
		{
			if(temp->d.getTrackID() == id){
				return count;
			}
			else {
				temp = temp->next;
				count++;
			}
		}
		return -1;
	}

	void displayRev()
	{
		dnode* temp = tail;

		while (temp != NULL)
		{
			cout << temp->d<<endl;
			cout << "------------------------" << endl;
			temp=temp->prev;
		}
        cout<< endl;
	}

    void displayFwd()
	{
		dnode* temp = head;

		while (temp != NULL)
		{
			cout << temp->d<< endl;
			cout << "-------------------------" << endl;
			temp=temp->next;
		}
        cout<< endl;
	}

	void display(string t){
		dnode* temp = head;

		while (temp != NULL)
		{ 
			if(temp->d.getTitle() == t){
				cout << temp->d<< endl;
				cout << "-------------------------" << endl;
				break;
			}
			else {
				temp=temp->next;
			}	
		}
        cout<< endl;
	}

    bool search(string data){
        bool found = false;
        dnode* n = head;
        while(n != NULL){
            if(n->d.getTitle() == data){
                found = true;
                return found;
            }
            n = n->next;
        }
        return found;
    }

	void displayCurrent() {
		if (current != NULL) {
			cout << "--- Currently Playing ---" << endl;
			cout << current->d;
		} 
		else if (head != NULL) {
			current = head;
			cout << "--- Currently Playing ---" << endl;
			cout << current->d ;
		} 
		else {
			cout << "No track currently selected." << endl;
		}
	}

	RetroPlayer getCurrent(){
		return current->d;
	}

	void MoveBackward()
	{
		if (current != NULL && current->prev != NULL) {
			current = current->prev;
			cout << "--- Moved to Previous Track ---" << endl;
			cout << current->d;
		} 
		else if (current != NULL && current->prev == NULL) {
			cout << "Already at the first track!" << endl;
			cout << current->d;
		} 
		else {
			cout << "No track selected or list is empty!" << endl;
		}
    	cout << endl;
	}

    void MoveForward()
	{
		if (current != NULL && current->next != NULL) {
			current = current->next;
			cout << "--- Moved to Next Track ---" << endl;
			cout << current->d;
		} 
		else if (current != NULL && current->next == NULL) {
			cout << "Already at the last track!" << endl;
			cout << current->d;
		} 
		else {
			cout << "No track selected or list is empty!" << endl;
		}
    	cout << endl;
	}

    DLL(const DLL& obj){
        head = tail = NULL;
        dnode* temp = obj.head;
        while(temp!=NULL){
            IAE(temp->d);
            temp = temp->next;
        }
    }

    ~DLL(){
        while(head!=NULL){
            DAE();
        }
    }

};
#endif