//
// Created by DELL on 2020/3/6.
//

#ifndef HOMEWORK1_Q4_Q6_Q4_Q6_H
#define HOMEWORK1_Q4_Q6_Q4_Q6_H


template <typename T>
class LinkedNode {
private:
    T m_nodeValue;
    LinkedNode* m_prevNode;
    LinkedNode* m_nextNode;

public:
    LinkedNode(T value, LinkedNode* prev, LinkedNode* next);
    T getValue() const;
    LinkedNode* getPrev() const;
    LinkedNode* getNext() const;
    void setPreviousPointerToNull();
    void setNextPointerToNull();
    void setBeforeAndAfterPointers();
};

template <typename T> LinkedNode<T>::LinkedNode(T value, LinkedNode<T>* prev, LinkedNode<T>* next){
    m_nodeValue = value;
    m_prevNode = prev;
    m_nextNode = next;
}

template <typename T> T LinkedNode<T>::getValue() const{
    return m_nodeValue;
}

template <typename T> LinkedNode<T>* LinkedNode<T>::getPrev() const{
    return m_prevNode;
};

template <typename T> LinkedNode<T>* LinkedNode<T>::getNext() const{
    return m_nextNode;
};

template <typename T> void LinkedNode<T>::setPreviousPointerToNull(){
    m_prevNode = nullptr;
};
template <typename T> void LinkedNode<T>::setNextPointerToNull(){
    m_nextNode = nullptr;
};
template <typename T> void LinkedNode<T>::setBeforeAndAfterPointers(){
    if ( m_prevNode == nullptr){
        m_nextNode -> m_prevNode = this;
    } else if (m_nextNode == nullptr) {
        m_prevNode -> m_nextNode = this;
    } else{
        m_prevNode -> m_nextNode = this;
        m_nextNode -> m_prevNode = this;
    }

};





template <typename T> class SortedList{
private:
    LinkedNode<T>* m_head;
    LinkedNode<T>* m_tail;

public:
    SortedList(){
        m_head = nullptr;
        m_tail = nullptr;
    }
    SortedList(const SortedList& source);
    SortedList& operator=(const SortedList& rhs);
    int getNumElems() const;
    pair<bool, T> getElemAtIndex(int index) const;
    void insertValue(T value);
    pair<bool, T> removeFront();
    pair<bool, T> removeBack();
    void printForward() const;
    void printBackward() const;
    void clear();
    ~SortedList();
};

template <typename T> SortedList<T>::SortedList(const SortedList<T>& source){
    m_head = source.m_head;
    m_tail = source.m_tail;
}

template <typename T> SortedList<T>& SortedList<T>::operator=(const SortedList<T>& rhs){
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
}

template <typename T> int SortedList<T>::getNumElems() const{
    int num = 0;
    LinkedNode<T>* temp = m_head ;
    while (temp != nullptr){
        num++;
        temp = temp -> getNext();
    }
    return num;
}

template <typename T> pair<bool, T> SortedList<T>::getElemAtIndex(int index) const{
    if (index > getNumElems()){
        return make_pair(false, NAN);
    } else {
        LinkedNode<T>* temp = this -> m_head;
        for (int num = 0; num < index; num++){
            temp = temp -> getNext();
        }
        return make_pair(true, temp ->getValue());
    }
}

template <typename T> void SortedList<T>::insertValue(T value){
    if (getNumElems() == 0){
        m_head = new LinkedNode<T>(value, nullptr, nullptr);
    } else if (getNumElems() == 1){
        if (value < m_head->getValue()){
            m_tail = new LinkedNode<T>(m_head->getValue(), m_head, nullptr);
            m_head = new LinkedNode<T>(value, nullptr, m_tail);
            m_head->setBeforeAndAfterPointers();
        } else{
            m_tail = new LinkedNode<T>(value, m_head, nullptr);
            m_head = new LinkedNode<T>(m_head->getValue(), nullptr, m_tail);
            m_head->setBeforeAndAfterPointers();
        }
    }else{
        if (value < m_head->getValue()){
            LinkedNode<T>* temp = new LinkedNode<T>(value, nullptr, m_head);
            temp->setBeforeAndAfterPointers();
            m_head = temp;
        } else {
            LinkedNode<T>* temp = m_head;
            while (temp->getValue() <= value & temp->getNext() != nullptr){
                temp = temp->getNext();
            }
            if (temp->getValue() > value){
                LinkedNode<T>* result = new LinkedNode<T>(value, temp->getPrev(), temp);
                result ->setBeforeAndAfterPointers();
            }else if(temp->getValue() <= value & temp->getNext() == nullptr){
                LinkedNode<T>* result = new LinkedNode<T>(value, m_tail, nullptr);
                m_tail = new LinkedNode<T>(value, result->getPrev(), nullptr);
                m_tail ->setBeforeAndAfterPointers();
            }
        }

    }
}

template <typename T> pair<bool, T> SortedList<T>::removeFront() {
    if (getNumElems() == 0){
        return make_pair(false, NAN);
    } else {
        LinkedNode<T>* temp = this -> m_head;
        T removed = temp->getValue();
        temp = temp -> getNext();
        temp->setPreviousPointerToNull();
        m_head = temp;
        return make_pair(true, removed);
    }
}

template <typename T> pair<bool, T> SortedList<T>::removeBack() {
    if (getNumElems() == 0){
        return make_pair(false, NAN);
    } else {
        LinkedNode<T>* temp = this -> m_tail;
        T removed = temp->getValue();
        temp = temp -> getPrev();
        temp->setNextPointerToNull();
        m_tail = temp;
        return make_pair(true, removed);
    }
}

template <typename T> void SortedList<T>::printForward() const{
    if (getNumElems() == 0){
        cout << "The list is empty." << endl;
    } else {
        cout << "Forward List Contents Follow:" << endl;
        LinkedNode<T>* temp = this -> m_head;
        for (int i = 0; i < getNumElems(); ++i) {
            cout << temp->getValue() << endl;
            temp = temp -> getNext();
        }
        cout << "End Of List Contents" << endl;
    }
}

template <typename T> void SortedList<T>::printBackward() const{
    if (getNumElems() == 0){
        cout << "The list is empty." << endl;
    } else {
        cout << "Backward List Contents Follow:" << endl;
        LinkedNode<T>* temp = this -> m_tail;
        while (temp->getPrev() != nullptr){
            cout << temp->getValue() << endl;
            temp = temp->getPrev();
        }
        cout << temp->getValue() << endl;
        cout << "End Of List Contents" << endl;
    }
}

template <typename T> void SortedList<T>::clear(){
    LinkedNode<T>* temp = this -> m_head;
    LinkedNode<T>* tempA;
    while (temp->getNext() != nullptr){
        tempA = temp;
        temp = temp->getNext();
        delete(tempA);
    }
    delete(temp);
    m_head = nullptr;
    m_tail = nullptr;
};

template <typename T> SortedList<T>::~SortedList(){
    delete(m_head);
    delete(m_tail);
};

#endif //HOMEWORK1_Q4_Q6_Q4_Q6_H
