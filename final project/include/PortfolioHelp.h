//
// Created by DELL on 2020/3/6.
//

#ifndef HOMEWORK1_Q4_Q6_Q4_Q6_H
#define HOMEWORK1_Q4_Q6_Q4_Q6_H

#include <chrono>


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
    void insertValue(T value);
    void clear();
    ~SortedList();

    LinkedNode<T>* getStart(){
        return m_head;
    };
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


template <typename T> void SortedList<T>::insertValue(T value){
    if (getNumElems() == 0){
        m_head = new LinkedNode<T>(value, nullptr, nullptr);
    } else if (getNumElems() == 1){
        m_tail = new LinkedNode<T>(value, m_head, nullptr);
        m_head = new LinkedNode<T>(m_head->getValue(), nullptr, m_tail);
        m_head->setBeforeAndAfterPointers();
    }else{
        LinkedNode<T>* result = new LinkedNode<T>(value, m_tail, nullptr);
        m_tail = new LinkedNode<T>(value, result->getPrev(), nullptr);
        m_tail ->setBeforeAndAfterPointers();
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

vector<double> normalDist(double mean, double sd, int length){
    vector<double> normalVec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    normal_distribution<double> dis(mean,sd);
    for (int i=0; i<length; ++i){
        normalVec.push_back(dis(gen));
    }
    return normalVec;
}

double findSum(vector<double> inputVec){
    double sum = 0.0;
    for (int i = 0; i < inputVec.size(); i++) {
        sum += inputVec[i];
    }
    return sum;
}

double findMax(vector<double> input){
    double value = input[0];
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] > value) value = input[i];
    }
    return value;
}

double findMin(vector<double> input){
    double value = input[0];
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] < value) value = input[i];
    }
    return value;
}

vector<double> standardize(vector<double> input){
    double max = findMax(input);
    double min = findMin(input);
    double range = max-min;
    vector<double> out;
    for (int i = 0; i < input.size(); ++i)  {
        out.push_back((input[i]-min)/range);
    }
    return out;
}

double cov(vector<double> A1, vector<double> B1){
    vector<double> E1;
    for (int i = 0; i < A1.size(); ++i) {
        E1.push_back(A1[i]*B1[i]);
    }
    return findMean(E1)-findMean(A1)*findMean(B1);
}


double CorrelationCoefficient(vector<double> A2, vector<double> B2){
    return cov(A2,B2)/(sampleSd(A2)*sampleSd(B2));
}



#endif //HOMEWORK1_Q4_Q6_Q4_Q6_H
