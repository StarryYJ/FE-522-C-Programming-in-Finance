//
// Created by DELL on 2020/3/6.
//

#ifndef HOMEWORK1_Q4_Q6_Q4_Q6_H
#define HOMEWORK1_Q4_Q6_Q4_Q6_H

class LinkedNode {
private:
    int m_nodeValue;
    LinkedNode* m_prevNode;
    LinkedNode* m_nextNode;

public:
    LinkedNode(int value, LinkedNode* prev, LinkedNode* next);
    int getValue() const;
    LinkedNode* getPrev() const;
    LinkedNode* getNext() const;
    void setPreviousPointerToNull();
    void setNextPointerToNull();
    void setBeforeAndAfterPointers();
};

LinkedNode::LinkedNode(int value, LinkedNode* prev, LinkedNode* next){
    m_nodeValue = value;
    m_prevNode = prev;
    m_nextNode = next;
}


int LinkedNode::getValue() const{
    return m_nodeValue;
}

LinkedNode* LinkedNode::getPrev() const{
    return m_prevNode;
};

LinkedNode* LinkedNode::getNext() const{
    return m_nextNode;
};

void LinkedNode::setPreviousPointerToNull(){
    m_prevNode = nullptr;
};
void LinkedNode::setNextPointerToNull(){
    m_nextNode = nullptr;
};
void LinkedNode::setBeforeAndAfterPointers(){
    if ( m_prevNode == nullptr){
        //cout << "insert at beginning   ";
        m_nextNode -> m_prevNode = this;
    } else if (m_nextNode == nullptr) {
        //cout << "push   ";
        m_prevNode -> m_nextNode = this;
    } else{
        //cout << "middle   ";
        m_prevNode -> m_nextNode = this;
        m_nextNode -> m_prevNode = this;
    }

};


class SortedList{
private:
    LinkedNode* m_head;
    LinkedNode* m_tail;

public:
    SortedList(){
        m_head = nullptr;
        m_tail = nullptr;
    }
    SortedList(const SortedList& source);
    SortedList& operator=(const SortedList& rhs);
    int getNumElems() const;
    pair<bool, int> getElemAtIndex(int index) const;
    void insertValue(int value);
    pair<bool, int> removeFront();
    pair<bool, int> removeBack();
    void printForward() const;
    void printBackward() const;
    void clear();
    ~SortedList();
};

SortedList::SortedList(const SortedList& source){
    m_head = source.m_head;
    m_tail = source.m_tail;
}

SortedList& SortedList::operator=(const SortedList& rhs){
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
}

int SortedList::getNumElems() const{
    int num = 0;
    LinkedNode* temp = m_head ;
    while (temp != nullptr){
        num++;
        temp = temp -> getNext();
    }
    return num;
}

pair<bool, int> SortedList::getElemAtIndex(int index) const{
    if (index > getNumElems()){
        return make_pair(false, NAN);
    } else {
        LinkedNode* temp = this -> m_head;
        for (int num = 0; num < index; num++){
            temp = temp -> getNext();
        }
        return make_pair(true, temp ->getValue());
    }
}

void SortedList::insertValue(int value){
    if (getNumElems() == 0){
        m_head = new LinkedNode(value, nullptr, nullptr);
    } else if (getNumElems() == 1){
        if (value < m_head->getValue()){
            m_tail = new LinkedNode(m_head->getValue(), m_head, nullptr);
            m_head = new LinkedNode(value, nullptr, m_tail);
            m_head->setBeforeAndAfterPointers();
        } else{
            m_tail = new LinkedNode(value, m_head, nullptr);
            m_head = new LinkedNode(m_head->getValue(), nullptr, m_tail);
            m_head->setBeforeAndAfterPointers();
        }
    }else{
        if (value < m_head->getValue()){
            LinkedNode* temp = new LinkedNode(value, nullptr, m_head);
            temp->setBeforeAndAfterPointers();
            m_head = temp;
        } else {
            LinkedNode* temp = m_head;
            while (temp->getValue() <= value & temp->getNext() != nullptr){
                temp = temp->getNext();

            }
            if (temp->getValue() > value){
                LinkedNode* result = new LinkedNode(value, temp->getPrev(), temp);
                result ->setBeforeAndAfterPointers();
            }else if(temp->getValue() <= value & temp->getNext() == nullptr){
                LinkedNode* result = new LinkedNode(value, m_tail, nullptr);
                m_tail = new LinkedNode(value, result->getPrev(), nullptr);
                m_tail ->setBeforeAndAfterPointers();
            }
        }
    }
}

pair<bool, int> SortedList::removeFront() {
    if (getNumElems() == 0){
        return make_pair(false, NAN);
    } else {
        LinkedNode* temp = this -> m_head;
        int removed = temp->getValue();
        temp = temp -> getNext();
        temp->setPreviousPointerToNull();
        m_head = temp;
        return make_pair(true, removed);
    }
}

pair<bool, int> SortedList::removeBack() {
    if (getNumElems() == 0){
        return make_pair(false, NAN);
    } else {
        LinkedNode* temp = this -> m_tail;
        int removed = temp->getValue();
        temp = temp -> getPrev();
        temp->setNextPointerToNull();
        m_tail = temp;
        return make_pair(true, removed);
    }
}

void SortedList::printForward() const{
    if (getNumElems() == 0){
        cout << "The list is empty." << endl;
    } else {
        cout << "Forward List Contents Follow:" << endl;
        LinkedNode* temp = this -> m_head;
        for (int i = 0; i < getNumElems(); ++i) {
            cout << temp->getValue() << endl;
            temp = temp -> getNext();
        }
        cout << "End Of List Contents" << endl;
    }
}

void SortedList::printBackward() const{
    if (getNumElems() == 0){
        cout << "The list is empty." << endl;
    } else {
        cout << "Backward List Contents Follow:" << endl;
        LinkedNode* temp = this -> m_tail;
        while (temp->getPrev() != nullptr){
            cout << temp->getValue() << endl;
            temp = temp->getPrev();
        }
        cout << temp->getValue() << endl;
        cout << "End Of List Contents" << endl;
    }
}

void SortedList::clear(){
    LinkedNode* temp = this -> m_head;
    LinkedNode* tempA;
    while (temp->getNext() != nullptr){
        tempA = temp;
        temp = temp->getNext();
        delete(tempA);
    }
    delete(temp);
    m_head = nullptr;
    m_tail = nullptr;
};

SortedList::~SortedList(){
    delete(m_head);
    delete(m_tail);
};

#endif //HOMEWORK1_Q4_Q6_Q4_Q6_H
