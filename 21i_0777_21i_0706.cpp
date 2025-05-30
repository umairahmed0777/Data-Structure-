
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class RtNode;
class RTable;
class machineNode;
class machines_list;


int totalMachines = 0;
int highest_id = 0;
int lowest_id = 0;
int hashFunction(long int val, int sId)
{
	return val % sId;

}

long int keyGetter(int choice, int idPool)
{
    long int id = 0;

    if (choice == 1)
    {
        id = hashFunction(rand(), idPool);
        cout << id << endl;
    }
    else if (choice == 2)
    {
        cout << "Enter the ID of Machine : ";
        cin >> id;
        id = hashFunction(id, idPool);
    }
    else
    {
        cout << "\nInput Not Valid ! Enter The Valid Input." << endl;
        return -1;
    }

    return id;
}


int idMenu()
{
	cout << "\nPress 1 for the Random Insertion of the Id of Machine." << endl;
	cout << "Press 2 for the Manual Insertion of the Id of Machine." << endl;
	int choice;
	cout << "What's Your choice : ";
	cin >> choice;

	while (choice != 1 and choice != 2)
	{
		cout << "Choice Not Valid.\nPlease Enter your choice again : ";
		cin >> choice;
	}
	return choice;
}

class RtNode
{
public:
	int id;
	machineNode* ref;
	RtNode* next;
	RtNode* prev;

	RtNode(int i, machineNode* machine)
	{
		id = i;
		ref = machine;
		next = NULL;
		prev = NULL;
	}
};

class RTable
{
public:
    RtNode* head;
    RtNode* tail;

    RTable()
    {
        head = nullptr;
        tail = nullptr;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void insert(int id, machineNode* machine)
    {
        RtNode* newNode = new RtNode(id, machine);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    bool idFound(int ID) const
    {
        RtNode* currNode = head;
        while (currNode != nullptr)
        {
            if (currNode->id == ID)
                return true;
            currNode = currNode->next;
        }
        return false;
    }

    void remove(int ID)
    {
        if (isEmpty())
        {
            cout << "Empty List. :(" << endl;
            return;
        }

        RtNode* currNode = head;
        while (currNode != nullptr)
        {
            if (currNode->id == ID)
            {
                if (currNode == head)
                {
                    head = currNode->next;
                    if (head != nullptr)
                        head->prev = nullptr;
                }
                else if (currNode == tail)
                {
                    tail = currNode->prev;
                    if (tail != nullptr)
                        tail->next = nullptr;
                }
                else
                {
                    currNode->prev->next = currNode->next;
                    currNode->next->prev = currNode->prev;
                }

                delete currNode;
                cout << "ID " << ID << " removed successfully." << endl;
                return;
            }
            currNode = currNode->next;
        }

        cout << "Sorry! ID not Found :(" << endl;
    }

    void display();
};


class BTNode
{
	int t;
	int* id;
	string* data;

	BTNode** c;
	int n;
	bool childNode;

public:
		
	BTNode* search(int k);
	
BTNode(int t1, bool childNode1)
{
	t=t1;
	childNode=childNode1;
	id = new int[2 * t - 1];
	data = new string[2 * t - 1];
	c = new BTNode * [2 * t];
	n = 0;
}

void addInNode(int id, const string& data)
{
    int i = n - 1;

    // Handle the case for childNode nodes
    if (childNode == true)
    {
        while (i >= 0 && this->id[i] > id)
        {
            this->id[i + 1] = this->id[i];
            this->data[i + 1] = this->data[i];
            i--;
        }

        this->id[i + 1] = id;
        this->data[i + 1] = data;
        n = n + 1;
    }
    else // Handle the case for non-childNode nodes
    {
        while (i >= 0 && this->id[i] > id)
            i--;

        if (c[i + 1]->n == 2 * t - 1)
        {
            splitchild(i + 1, c[i + 1]);
            if (this->id[i + 1] < id)
                i++;
        }

        // Recursive call to the child node
        c[i + 1]->addInNode(id, data);
    }
}



void findNext()
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (childNode == false)
			c[i]->findNext();
		cout << " " << id[i] << ":" << data[i];
	}
	if (childNode == false)
		c[i]->findNext();
}


void splitchild(int i, BTNode* y)
{
    BTNode* z = new BTNode(y->t, y->childNode);
    z->n = t - 1;

    // Copy keys and data from y to z
    for (int j = 0; j < t - 1; j++)
    {
        z->id[j] = y->id[j + t];
        z->data[j] = y->data[j + t];
    }

    // If y is not a leaf, copy child nodes from y to z
    if (!y->childNode)
    {
        for (int j = 0; j < t; j++)
            z->c[j] = y->c[j + t];
    }

    // Shift elements in c to make space for z
    for (int j = n - 1; j >= i; j--)
        c[j + 1] = c[j];

    // Update c[i + 1] with z
    c[i + 1] = z;

    // Shift elements in id and data to make space for the new key and data
    for (int j = n - 1; j >= i; j--)
    {
        id[j + 1] = id[j];
        data[j + 1] = data[j];
    }

    // Copy the middle key and data from y to the current node
    id[i] = y->id[t - 1];
    data[i] = y->data[t - 1];

    n = n + 1;
}



int findkey(int k)

{

	int targetId = 0;

	while (targetId < n && id[targetId] < k)

		++targetId;

	return targetId;

}


void remove(int k)
{
    int targetId = findkey(k);

    // Check if the key exists in the current node
    if (targetId < n && id[targetId] == k)
    {
        // If the current node is a child node, delete the key directly
        if (childNode)
            deletefromchildNode(targetId);
        else
            deletefromnonchildNode(targetId);
    }
    else
    {
        // If the current node is a child node and the key is not found, print a message and return
        if (childNode)
        {
            cout << "Key " << k << " not Found :(" << endl;
            return;
        }

        bool flag;
        if (targetId == n)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }

        // If the child node has less than t keys, fill it
        if (c[targetId]->n < t)
            fill(targetId);

        // Recursively remove the key from the appropriate child node
        if (flag && targetId > n)
            c[targetId - 1]->remove(k);
        else
            c[targetId]->remove(k);
    }
}



void deletefromnonchildNode(int targetId)
{
    int k = id[targetId];

    // If the child node c[targetId] has at least t keys, replace k with its predecessor and remove it from c[targetId]
    if (c[targetId]->n >= t)
    {
        int pred = getpred(targetId);
        id[targetId] = pred;
        c[targetId]->deletefromchildNode(pred);
    }
    // If the child node c[targetId+1] has at least t keys, replace k with its successor and remove it from c[targetId+1]
    else if (c[targetId + 1]->n >= t)
    {
        int succ = getsucc(targetId);
        id[targetId] = succ;
        c[targetId + 1]->deletefromchildNode(succ);
    }
    // If both child nodes have t-1 keys, merge them into one
    else
    {
        merge(targetId);
        c[targetId]->deletefromchildNode(k);
    }
}



void deletefromchildNode(int targetId)
{
    // Check if targetId is a valid index within the node
    if (targetId >= 0 && targetId < n)
    {
        // Shift the keys to the left, effectively removing the key at targetId
        for (int j = targetId; j < n - 1; ++j)
        {
            id[j] = id[j + 1];
            data[j] = data[j + 1];
        }

        // Decrement the count of keys (n) to reflect the removal
        n--;
    }
}



void fill(int targetId)
{
    // Check if there is a previous child node with enough keys to borrow from
    if (targetId != 0 && c[targetId - 1]->n >= t)
    {
        borrowfromprev(targetId);
    }
    // Check if there is a next child node with enough keys to borrow from
    else if (targetId != n && c[targetId + 1]->n >= t)
    {
        borrowfromnext(targetId);
    }
    // If neither previous nor next child node has enough keys to borrow from, merge them
    else
    {
        merge(targetId);
    }
}



void merge(int targetId)
{
    BTNode* child = c[targetId];
    BTNode* sibling = c[targetId + 1];

    // Move the key from the current node to the child node
    child->id[t - 1] = id[targetId];

    // Copy keys from the sibling node to the child node
    for (int j = 0; j < sibling->n; ++j)
    {
        child->id[j + t] = sibling->id[j];
        child->data[j + t] = sibling->data[j]; // Assuming data needs to be copied as well
    }

    // If the nodes are not child nodes, copy child pointers as well
    if (!child->childNode)
    {
        for (int j = 0; j <= sibling->n; ++j)
        {
            child->c[j + t] = sibling->c[j];
        }
    }

    // Shift keys in the current node to remove the merged key
    for (int i = targetId + 1; i < n; ++i)
    {
        id[i - 1] = id[i];
        data[i - 1] = data[i]; // Assuming data needs to be shifted as well
    }

    // Shift child pointers to remove the merged sibling node
    for (int j = targetId + 2; j <= n; ++j)
    {
        c[j - 1] = c[j];
    }

    // Update the child node's count of keys
    child->n += sibling->n + 1;

    // Update the current node's count of keys
    n--;

    // Delete the merged sibling node
    delete sibling;
}



int getsucc(int targetId)
{
    BTNode* cur = c[targetId + 1];

    // Traverse to the leftmost leaf node in the subtree
    while (cur && !cur->childNode)
    {
        cur = cur->c[0];
    }

    // If a leaf node was found, return its leftmost key
    if (cur)
    {
        return cur->id[0];
    }

    // Return an appropriate value when no successor is found
    return -1; // You can choose an appropriate value to represent "no successor"
}



int getpred(int targetId)
{
    BTNode* cur = c[targetId];

    // Traverse to the rightmost leaf node in the subtree
    while (cur && !cur->childNode)
    {
        cur = cur->c[cur->n];
    }

    // If a leaf node was found, return its rightmost key
    if (cur)
    {
        return cur->id[cur->n - 1];
    }

    // Return an appropriate value when no predecessor is found
    return -1; // You can choose an appropriate value to represent "no predecessor"
}




void borrowfromnext(int targetId)
{
    BTNode* child = c[targetId];
    BTNode* sibling = c[targetId + 1];

    // Borrow the key from the sibling node
    child->id[child->n] = id[targetId];
    child->n++;

    // If the nodes are not child nodes, copy the child pointer as well
    if (!child->childNode)
    {
        child->c[child->n] = sibling->c[0];
    }

    // Update the current node's key with the first key from the sibling
    id[targetId] = sibling->id[0];

    // Shift the keys in the sibling node to the left
    for (int j = 1; j < sibling->n; ++j)
    {
        sibling->id[j - 1] = sibling->id[j];
    }

    // If the nodes are not child nodes, shift the child pointers as well
    if (!sibling->childNode)
    {
        for (int j = 1; j <= sibling->n; ++j)
        {
            sibling->c[j - 1] = sibling->c[j];
        }
    }

    // Update the sibling node's key count
    sibling->n--;
}



void borrowfromprev(int targetId)
{
    BTNode* child = c[targetId];
    BTNode* sibling = c[targetId - 1];

    // Shift the keys in the child node to make room for the borrowed key
    for (int i = child->n - 1; i >= 0; --i)
    {
        child->id[i + 1] = child->id[i];
    }

    // If the nodes are not child nodes, shift the child pointers as well
    if (!child->childNode)
    {
        for (int i = child->n; i >= 0; --i)
        {
            child->c[i + 1] = child->c[i];
        }
    }

    // Copy the key from the sibling node to the child node
    child->id[0] = id[targetId - 1];

    // If the nodes are not child nodes, copy the child pointer as well
    if (!child->childNode)
    {
        child->c[0] = sibling->c[sibling->n];
    }

    // Update the current node's key with the last key from the sibling
    id[targetId - 1] = sibling->id[sibling->n - 1];

    // Adjust the key counts in both the child and sibling nodes
    child->n += 1;
    sibling->n -= 1;
}


	friend class BTree;
};

class BTree
{
	BTNode* root;
	int t;

public:
	BTree() {
		t = 4;

	}
	BTree(int _t)
	{
		root = NULL;
		t = _t;
	}

	void findNext()
	{
		if (root != NULL)
			root->findNext();
	}

	void insert(int id, const string& data)
{
    if (root == NULL)
    {
        root = new BTNode(t, true);
        root->id[0] = id;
        root->data[0] = data;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            // Create a new root node if the current root is full
            BTNode* s = new BTNode(t, false);
            s->c[0] = root;
            s->splitchild(0, root);
            int i = 0;
            // Find the appropriate child to insert into
            while (i < s->n && s->id[i] < id)
            {
                i++;
            }
            // Insert the key and data into the appropriate child
            s->c[i]->addInNode(id, data);
            root = s; // Update the root node
        }
        else
        {
            // If the current root is not full, insert into it
            root->addInNode(id, data);
        }
    }
}



	BTNode* search(int k)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        // Call the search method of the root node
        return root->search(k);
    }
}


	void remove(int k)
{
    if (!root)
    {
        cout << "Empty Tree :( Insert the Data First! \n";
        return;
    }

    root->remove(k);

    // Check if the root node is empty after removal
    if (root->n == 0)
    {
        BTNode* tmp = root;
        
        // Update the root based on whether it's a leaf or not
        if (root->childNode)
        {
            root = NULL;
        }
        else
        {
            root = root->c[0];
        }
        
        delete tmp;
    }
}


};




class machineNode
{
public:
	int id;
	machineNode* next;
	RTable table;  
	BTree b_tree;

	machineNode()
	{
		id = 0;
		next = nullptr;
	}

	void displayRTable()
	{
		table.display();
	}
};


void RTable::display()
{
	RtNode* currNode = RTable::head;
	int i = 1;
	if (head == NULL)
		cout << "RTable is empty." << endl;
	else
	{
		cout << "No.\tID" << endl;
		while (currNode != NULL)
		{
			cout << i << "\t" << currNode->ref->id << endl;
			currNode = currNode->next;
			i++;
		}
	}
}

class allMachines
{
public:
	machineNode* head;
	machineNode* tail;
	unsigned long long int idPool;
	int bits;

	allMachines()
	{
		head = NULL;
		tail = NULL;

		cout << "Enter the No. of Bits for the identifier space : ";
		cin >> bits;

		idPool = 2;
		for (int i = 1; i < bits; i++)
		{
			idPool *= 2;
		}
	}

	void insert()
{
    machineNode* new_machine = new machineNode;
    totalMachines++;
    int choice = idMenu();
    new_machine->id = keyGetter(choice, idPool);

    if (highest_id < new_machine->id)
        highest_id = new_machine->id;

    if (new_machine->id < lowest_id)
        lowest_id = new_machine->id;

    new_machine->id = hashFunction(new_machine->id, idPool);

    machineNode* currentMachine = head;

    if (currentMachine == NULL)
    {
        head = new_machine;
        tail = new_machine;
        new_machine->next = new_machine; // Point to itself since it's the only element
    }
    else if (currentMachine->id > new_machine->id)
    {
        // Insert at the beginning
        new_machine->next = head;
        head = new_machine;
        tail->next = head; // Update the tail's next pointer
    }
    else
    {
        // Insert in the middle or at the end
        while (currentMachine->next != head && currentMachine->next->id < new_machine->id)
        {
            currentMachine = currentMachine->next;
        }

        new_machine->next = currentMachine->next;
        currentMachine->next = new_machine;

        if (currentMachine == tail)
        {
            tail = new_machine; // Update the tail if inserting at the end
        }
    }
}



	


	void deleteMachine(int machine_id)
{
    if (head == NULL)
    {
        cout << "List is empty :(" << endl;
        return;
    }

    machineNode* currentMachine = head;
    machineNode* previousMachine = NULL;

    while (currentMachine->id != machine_id && currentMachine->next != head)
    {
        previousMachine = currentMachine;
        currentMachine = currentMachine->next;
    }

    if (currentMachine->id == machine_id)
    {
        if (head == tail)
        {
            head = tail = NULL;
        }
        else if (currentMachine == head)
        {
            head = head->next;
            tail->next = head;
        }
        else if (currentMachine == tail)
        {
            previousMachine->next = head;
            tail = previousMachine;
        }
        else
        {
            previousMachine->next = currentMachine->next;
        }

        cout << "Machine with ID " << machine_id << " deleted Successfully :)\n";
        delete currentMachine;
    }
    else
    {
        cout << "Machine with ID " << machine_id << " not Found :( \n";
    }
}




	void addData(int id, string data, machineNode* currentMachine)
	{

		currentMachine->b_tree.insert(id, data);
		cout << "Data inserted on machine " << id <<" Successfully :) \n";
	}

	void deleteData(int id, string data, machineNode* currentMachine)
{
    // Assuming `currentMachine->b_tree.remove(id)` correctly removes the data.
    currentMachine->b_tree.remove(id);

    // Print a message indicating successful deletion.
    cout << "Data with ID " << id << " deleted Successfully :)" << endl;
}

	machineNode* findMachines(int findId)
{
    machineNode* currentMachine = head;

    do
    {
        if (currentMachine->id == findId)
        {
            return currentMachine;
        }
        currentMachine = currentMachine->next;

    } while (currentMachine != head);

    return NULL; // Return NULL if the machine with the specified ID is not found.
}

	void displayBTree(int i)
{
    // Find the machine with the specified ID
    machineNode* currentMachine = findMachines(i);

    if (currentMachine == NULL)
    {
        cout << "Machine with ID " << i << " not found :(\n";
    }
    else
    {
        cout << "Machine " << currentMachine->id << " data:\n";

        // Assuming `currentMachine->b_tree.findNext()` correctly displays B-tree data
        currentMachine->b_tree.findNext();

        cout << endl;
    }
}


	void displayMachines()
{
    cout << "Machines Left:\n\n" << endl;
    machineNode* curr = head;
    
    if (curr == NULL)
    {
        cout << "No machines found in the list.\n";
        return;
    }

    do
    {
        cout << "Machine ID: " << curr->id << " ";
        curr = curr->next;
    } while (curr != head);

    cout << endl;
}

	void displayRTable(int id)
{
    // Find the machine with the specified ID
    machineNode* currentMachine = findMachines(id);

    if (currentMachine != NULL)
    {
        cout << "Routing Table for Machine " << currentMachine->id << ":\n";
        currentMachine->table.display();
    }
    else
    {
        cout << "Machine with ID " << id << " not found :(\n";
    }
}


};



machineNode* succ(int e, allMachines machines)
{
    machineNode* currentMachine = machines.head;

    while (currentMachine != NULL && currentMachine->id < e)
    {
        currentMachine = currentMachine->next;
    }

    // Check if the current machine's ID is greater than or equal to e
    if (currentMachine != NULL && currentMachine->id >= e)
    {
        return currentMachine;
    }
    else
    {
        // No machine with ID greater than or equal to e was found
        return NULL;
    }
}


allMachines fingerTable(allMachines machines)
{
    machineNode* currentMachine = machines.head;
    machineNode* r_machine = NULL;

    do
    {
        for (int i = 1; i <= machines.bits; i++)
        {
            int e = (currentMachine->id + pow(2, i - 1));
            e = hashFunction(e, machines.idPool);

            if (e > highest_id || e <= machines.head->id)
                r_machine = machines.head;
            else
                r_machine = succ(e, machines);

            // Insert the entry (i, r_machine) into the routing table of the current machine
            currentMachine->table.insert(i, r_machine);
        }
        currentMachine = currentMachine->next;
    } while (currentMachine != machines.head);

    return machines;
}


machineNode* getSuitableMachine(int id, machineNode* currentMachine, RtNode* currentNode)
{

	if (id == currentMachine->id)
	{
		return currentMachine;
	}
	else if (id <= currentNode->ref->id)
	{
		return currentNode->ref;
	}
	else if (id > currentNode->ref->id and id <= currentNode->next->ref->id)
	{
		currentMachine = getSuitableMachine(id, currentNode->ref, currentNode->next);
	}
}


void mainMenu()
{
	cout << "Press 1 for Data Insertion.\n";
	cout << "Press 2 for B tree Display.\n";
	cout << "Press 3 for routing table of a Machine.\n";
	cout << "Press 4 for Machines Display.\n";
	cout << "Press 5 for Data deletion from any Machine.\n";
	cout << "Press 6 for Deletion of any Machine.\n";
	cout << "Press 0 for exit." << endl;
}

int main()
{
	int machineNmbr, choice, id2 = 0;
	allMachines machines;
	machineNode* currentMachine = machines.head;
	string data;
	int id = 0;
	int tempId = 0;
	int idrem = 0;
	int rem_machine_id = 0;
	srand(time(NULL));

	cout << "Enter No. of machines : ";
	cin >> machineNmbr;

	while (machineNmbr > machines.idPool)
	{
		cout << "No. of Machines is Greater than identifier Space :( \nPLease Enter it again : ";
		cin >> machineNmbr;
	}
	for (int i = 0; i < machineNmbr; i++)
	{
		machines.insert();
	}

	machines = fingerTable(machines);
	cout << endl;
	cout << endl;

	mainMenu();
	cout << "What's Your choice? Enter it : ";
	cin >> choice;

	while (choice != 0)
	{

		switch (choice)
		{
		case 0:
			return 0;
			break;
		case 1:

			cout << "Enter the ID of the Machine to Insert Data : ";
			cin >> id;

			if (machines.findMachines(id) == nullptr) {
				cout << "Machine Can not be found:(\n";
			}
			else {

				cin.ignore(); 
				cout << "Enter the Data to insert : ";
				getline(cin, data);

				cout << "Enter the Key of Data : ";
				cin >> tempId;


				id = hashFunction(id, machines.idPool);
				currentMachine = machines.head;
				currentMachine = getSuitableMachine(id, currentMachine, currentMachine->table.head);
				machines.addData(tempId, data, currentMachine);
				machines.displayBTree(currentMachine->id);
			}

			break;
		case 2:
			cout << "\nEnter the ID to Print B tree  : ";
			cin >> id;
			machines.displayBTree(id);
			break;
		case 3:
			cout << "\nEnter the MAchine ID to Print Routing Table  : ";
			cin >> id;

			id = hashFunction(id, machines.idPool);
			machines.displayRTable(id);
			break;
		case 4:
			machines.displayMachines();
			break;
		case 5:


			cout << "Enter the MAchine ID to Delete Data on: ";
			cin >> id;

			if (machines.findMachines(id) == nullptr) {
				cout << "Machine can not be found :(";
			}
			else {
				cout << "Available Data of MAchine : " << endl;

				machines.displayBTree(currentMachine->id);

				cin.ignore();
				cout << "Enter The Data ID : ";
				cin >> idrem;

				id = hashFunction(id, machines.idPool);
				currentMachine = machines.head;
				currentMachine = getSuitableMachine(id, currentMachine, currentMachine->table.head);

				cout << "\nData Stored on Machine : " << currentMachine->id << endl;
				machines.deleteData(idrem, data, currentMachine);
				cout << endl;
				cout << "TREE AFTER REMOVAL IS :  \n";
				machines.displayBTree(currentMachine->id);

			}
			break;
		case 6:

			cout << "Enter the ID of the Machine To delete :  " << endl;
			cin >> rem_machine_id;
			machines.deleteMachine(rem_machine_id);
			cout << "Remaining MAchines are : " << endl;
			machines.displayMachines();
			break;

		default:
			cout << "\n\nInput Not Valid :(" << endl;
		}

		mainMenu();
		cout << "\nEnter your choice :  ";
		cin >> choice;
	}


}