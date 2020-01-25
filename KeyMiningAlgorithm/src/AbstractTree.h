//
// Created by 佘崧林 on 2020/1/22.
//

#ifndef KEYMININGALGORITHM_ABSTRACTTREE_H
#define KEYMININGALGORITHM_ABSTRACTTREE_H

#include <list>
#include <ostream>

template <typename DataType>
class AbstractTree {
protected:
    DataType nodeData;
    AbstractTree *parentTree = nullptr;
    AbstractTree *leftChild = nullptr;
    AbstractTree *rightChild = nullptr;

public:
    ~AbstractTree();
    AbstractTree(const AbstractTree &copy);
    explicit AbstractTree(const DataType &data): nodeData(data) {}
    AbstractTree(const DataType &data, AbstractTree *lt, AbstractTree *rt);

    const DataType &getNodeData() const { return this->nodeData; }
    AbstractTree *getParent() const { return this->parentTree; }
    AbstractTree *getLeftChild() const { return this->leftChild; }
    AbstractTree *getRightChild() const { return this->rightChild; }

    void setNodeData(const DataType &data) { this->nodeData = data; }
    void setParent(AbstractTree *data) { this->parentTree = data; }
    void preOrderForEach(const std::function<void(AbstractTree<mpz_class> *)> &exec);
    std::list<DataType> preOrderGetLeafList();
};

#include "AbstractTree.tpp"

#endif //KEYMININGALGORITHM_ABSTRACTTREE_H
